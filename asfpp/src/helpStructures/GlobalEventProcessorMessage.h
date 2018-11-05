#ifndef _GLOBAL_EVENT_PROCESSOR_MESSAGE_H_
#define _GLOBAL_EVENT_PROCESSOR_MESSAGE_H_

#include <cmessage.h>
#include <string>

using namespace std;

class GlobalEventProcessorMessage {

private:
    string arrivalGateName;

    string senderGateName;

public:
    GlobalEventProcessorMessage(const string& inGate, const string& outGate);

    GlobalEventProcessorMessage(const GlobalEventProcessorMessage& message);

    GlobalEventProcessorMessage& operator=(const GlobalEventProcessorMessage& message);

    virtual ~GlobalEventProcessorMessage();

    string getArrivalGateName() const;

    string getSenderGateName() const;

};

#endif
