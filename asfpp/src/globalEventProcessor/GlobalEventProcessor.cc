#include "GlobalEventProcessor.h"

#include "Parser.h"
#include "UnconditionalAttack.h"
#include "PhysicalAttack.h"

Define_Module(GlobalEventProcessor);

void GlobalEventProcessor::scheduleUnconditionalAttacksOnInitialize()
{	
	// Retrieves the name of the attack configuration file (xml)
	std::string attackConfigurationFileName = (getParentModule()->par("configurationFile")).stringValue();
    if ( attackConfigurationFileName == "none" )
    {
		return;
    }

    cModule* callerNode = getParentModule();

    // instantiate the parser
	Parser parser(callerNode, attackConfigurationFileName, applicationName, routingProtocolName, macProtocolName);
	// parse the attack configuration file (looking for unconditional attacks)
	parser.parse("Unconditional", unconditionalEntries);
    
    for (int i = 0; i < unconditionalEntries.size(); i++) {
        ScheduleUnconditionalAttackMessage* scheduleUnconditionalAttackMessage
                    = new ScheduleUnconditionalAttackMessage("Fire Unconditional Attack", UNCONDITIONAL_ATTACK);
        SimTime occurrenceTime = unconditionalEntries[i]->getTime();
        scheduleUnconditionalAttackMessage->setUnconditionalAttackIdentifier(i);
        scheduleAt(occurrenceTime, scheduleUnconditionalAttackMessage);
    }
}


void GlobalEventProcessor::handleScheduleUnconditionalAttackMessage(ScheduleUnconditionalAttackMessage* scheduleUnconditionalAttackMessage)
{
    // retrieve the unconditional attack
    int entryIndex = scheduleUnconditionalAttackMessage->getUnconditionalAttackIdentifier();
    UnconditionalAttack* attack = (UnconditionalAttack*)(unconditionalEntries[entryIndex]->getAttack());
    
    // execute the unconditional attack
    vector<cMessage*> generatedMessages;
    attack->execute(generatedMessages);
    
    // deliver PutMsg that have been created
    for (size_t i = 0; i < generatedMessages.size(); i++) {
        handlePutMessage((PutMessage*) generatedMessages[i]);
    }
    
    // retrieve the frequency of the unconditional attack just performed
    double frequency = attack->getFrequency();
    if (frequency == 0.0) {
        return;
    }
    else {
        // re-schedule the unconditional attack
        double nextOccurrenceTime = simTime().dbl() + frequency;
        ScheduleUnconditionalAttackMessage* nextScheduleUnconditionalAttackMessage = new ScheduleUnconditionalAttackMessage("Fire Unconditional Attack", UNCONDITIONAL_ATTACK);
        nextScheduleUnconditionalAttackMessage->setUnconditionalAttackIdentifier(entryIndex);
        scheduleAt(nextOccurrenceTime, nextScheduleUnconditionalAttackMessage);
    }
}


void GlobalEventProcessor::handleDestroyRequest(DestroyRequest* destroyRequest)
{
    // retrieve the entry
    Entry* entry = (destroyRequest->getEntryWrapper()).getEntry();
    
    // retrieve the physical attack (made by a single destory action) and its occurrence time
    PhysicalAttack* physicalAttack = (PhysicalAttack*) (entry->getAttack());
    double occurrenceTime = (entry->getTime()).dbl();
    
    // build the wrapper for the physical attack
    PhysicalAttackWrapper physicalAttackWrapper = PhysicalAttackWrapper(physicalAttack);
    
    // schedule the DestroyFireMessage
    DestroyFireMessage* destroyFireMessage = new DestroyFireMessage("Fire Destroy Action");
    destroyFireMessage->setPhysicalAttackWrapper(physicalAttackWrapper);
    scheduleAt(occurrenceTime, destroyFireMessage);
    
    // now entry is useless
    delete entry;
}


void GlobalEventProcessor::handleDestroyFireMessage(DestroyFireMessage* destroyFireMessage)
{
    // retrieve and execute the physical attack (made by a single destroy action)
    PhysicalAttack* physicalAttack = (destroyFireMessage->getPhysicalAttackWrapper()).getPhysicalAttack();
    physicalAttack->execute();
      
    // now physicalAttack is useless
    delete physicalAttack;
}


void GlobalEventProcessor::handlePutMessage(PutMessage* putMessage)
{
    // get the message encapsulated in putMessage
	cMessage* encapsulatedPacket = putMessage->getPacket();
    // retrieve the recipient nodes
    vector<int> nodes = putMessage->getNodeVector();
	// retrieve parameters
	string direction = putMessage->getDirection();
	bool stats = putMessage->getStats();
	double delay = putMessage->getDelay();
		
    // for each recipient node create a PutRequest and send it to him
	for (size_t i = 0; i < nodes.size(); i++) {
        PutRequest* putRequest = new PutRequest(encapsulatedPacket, direction, stats);
        sendDelayed(putRequest, delay, "toNode", nodes[i]);
	}
}


void GlobalEventProcessor::initialize()
{
    applicationName = (par("applicationName")).stringValue();
    routingProtocolName = (par("routingProtocolName")).stringValue();
    macProtocolName = (par("macProtocolName")).stringValue();

    scheduleUnconditionalAttacksOnInitialize();
}


void GlobalEventProcessor::handleMessage(cMessage* msg)
{
    std::string msgClassName = msg->getClassName();

    if ( msg->isSelfMessage() )
    {
        if ( msgClassName == "ScheduleUnconditionalAttackMessage" )
        {
            handleScheduleUnconditionalAttackMessage((ScheduleUnconditionalAttackMessage*) msg);
        }

        if ( msgClassName == "DestroyFireMessage" )
        {
            handleDestroyFireMessage((DestroyFireMessage*) msg);
        }

        cancelAndDelete(msg);
    }
    else
    {
        if ( msgClassName == "PutMessage" )
        {
            handlePutMessage((PutMessage*) msg);
        }

        if ( msgClassName == "DestroyRequest" )
        {
            handleDestroyRequest((DestroyRequest*) msg);
        }

        delete msg;
    }
}


GlobalEventProcessor::GlobalEventProcessor()
        : unconditionalEntries(), applicationName(), routingProtocolName(), macProtocolName()
{
}


GlobalEventProcessor::~GlobalEventProcessor()
{
    // FIXME memory leak, use smart pointers instead

    // remove objects that are still helded by the global filter 
	/*
    for (size_t i = 0; i < unconditionalEntries.size(); i++) {
        // retrieve and delete the attack
        delete unconditionalEntries[i]->getAttack();
        // retrieve and delete the related entry
        delete unconditionalEntries[i];
    }
    */
}
