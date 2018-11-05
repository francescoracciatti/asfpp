package logger;

simple Logger {

 parameters:
    bool collectTraceInfo = default (false);	// M.T.

    // List of available logs (set to true to activate)
    bool logPacketDrop = default (false);
    bool logCompromisedPacket = default (false);

  gates:
    input fromNode[];
    input fromGlobalEventProcessor;

}
