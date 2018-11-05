#include "GlobalEventProcessorMessage.h"

GlobalEventProcessorMessage::GlobalEventProcessorMessage(const string& inGate, const string& outGate)
{

    arrivalGateName = inGate;
    senderGateName = outGate;

}

GlobalEventProcessorMessage::GlobalEventProcessorMessage(const GlobalEventProcessorMessage& message)
{

    arrivalGateName = message.getArrivalGateName();
    senderGateName = message.getSenderGateName();

}

GlobalEventProcessorMessage& GlobalEventProcessorMessage::operator=(const GlobalEventProcessorMessage& message)
{

    arrivalGateName.clear();
    senderGateName.clear();
    arrivalGateName = message.getArrivalGateName();
    senderGateName = message.getSenderGateName();

}

GlobalEventProcessorMessage::~GlobalEventProcessorMessage()
{

    arrivalGateName.clear();
    senderGateName.clear();

}

string GlobalEventProcessorMessage::getArrivalGateName() const
{
    return arrivalGateName;
}

string GlobalEventProcessorMessage::getSenderGateName() const
{
    return senderGateName;
}