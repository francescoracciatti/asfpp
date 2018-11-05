#ifndef GLOBAL_EVENT_PROCESSOR_H
#define GLOBAL_EVENT_PROCESSOR_H


#include "CastaliaModule.h"

#include <vector>
#include <string>



#include "ScheduleUnconditionalAttackMessage_m.h"
#include "DestroyRequest_m.h"
#include "DestroyFireMessage_m.h"
#include "PutMessages.h"
#include "Entry.h"


enum attackTimer {
  UNCONDITIONAL_ATTACK = 12
};


//
// The GlobalEventProcessor performs unconditional attacks and destroys network's nodes.
//
class GlobalEventProcessor : public CastaliaModule {
public:
    GlobalEventProcessor();

    virtual ~GlobalEventProcessor();

protected:
    virtual void initialize() override;

    virtual void handleMessage(cMessage* msg) override;

private:
    //
    // Schedules the first occurrence of each unconditional attack on initialize.
    //
    void scheduleUnconditionalAttacksOnInitialize();
    
    /**
     * @brief Handles UnconditionalFireMessage(s) (self-messages), i.e. execute the relative 'unconditional' attack.
     * @param scheduleUnconditionalAttackMessage Is the UnconditionalFireMessage to handle.
     */
    void handleScheduleUnconditionalAttackMessage(ScheduleUnconditionalAttackMessage* scheduleUnconditionalAttackMessage);

    /**
     * @brief Handles DestroyRequest(s) received by the local-filter(s) and schedule the relative 'destroy' action.
     * @param destroyRequest Is the DestroyRequest to handle.
     */
    void handleDestroyRequest(DestroyRequest* destroyRequest);

    /**
     * @brief Handles DestroyFireMessage(s) (self-message), i.e. executes the relative 'destroy' action.
     * @param destroyFireMessage Is the DestroyFireMessage (self-message) to handle.
     */
    void handleDestroyFireMessage(DestroyFireMessage* destroyFireMessage);

    /**
     * @brief Handles put messages received by the local-filter(s) or creted by the global-filter.
     * @param putMsg Is the put message to handle.
     */
    void handlePutMessage(PutMessage* putMessage);

private:
    // list of entries wrapping the unconditional attacks handled by the global filter
    std::vector<Entry*> unconditionalEntries;

    std::string applicationName;

    std::string routingProtocolName;

    std::string macProtocolName;

};

#endif
