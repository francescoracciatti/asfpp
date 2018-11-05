package logger;

//
// The node Logger provides logging services.
//
simple Logger {

    parameters:
        bool collectTraceInfo = default (false);

        // List of available logs (set to true to activate)
        bool logPacketDrop = default (false);
        bool logCompromisedPacket = default (false);

    gates:
        input fromNode[];
        input fromGlobalEventProcessor;

}
