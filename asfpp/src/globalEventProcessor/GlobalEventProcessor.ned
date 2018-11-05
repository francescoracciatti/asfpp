package globalEventProcessor;

//
// The node GlobalEventProcessor is responsible to perform
// attack-related events.
//
simple GlobalEventProcessor {

    parameters:
        bool    collectTraceInfo        = default (false);
        bool    evaluateAttacks         = default (false);
        string  applicationName         = default("");
        string  routingProtocolName     = default("BypassRouting");
        string  macProtocolName         = default("BypassMac");
    
    gates:
        output  toWirelessChannel;
        output  toNode[];
        output  toLogger;

        input   fromWirelessChannel;
        input   fromNode[];

}
 
