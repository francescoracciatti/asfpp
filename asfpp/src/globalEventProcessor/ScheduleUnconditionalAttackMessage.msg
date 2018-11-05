//
// Upon the arrival of an ExecuteUnconditionalAttackMessage, the GlobalEventProcessor schedules the
// unconditional attack referred by the message itself.
//
message ScheduleUnconditionalAttackMessage {
	
    int unconditionalAttackIdentifier;

}
