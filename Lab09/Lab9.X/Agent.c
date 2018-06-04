#include "Agent.h"
#include "Protocol.h"

NegotiationData nData;
GuessData gData;

ProtocolParserStatus myStatus;
int agentEvent = AGENT_EVENT_NONE;



//Im doing Agent Run and AgentGetEnemyStatus

int AgentRun(char in, char *outBuffer)
{
    myStatus = ProtocolDecode(in, &nData, &gData);
    //check what ProtocolDecode returns
    //then enter proper case and begin task
    
    switch (myStatus)
    {
    case AGENT_EVENT_NONE:
        
        break;
    case AGENT_EVENT_MESSAGE_PARSING_FAILED:
        
        break;
    case AGENT_EVENT_RECEIVED_COO_MESSAGE:
        
        break;
    case AGENT_EVENT_RECEIVED_CHA_MESSAGE:
        
        break;
    case AGENT_EVENT_RECEIVED_HIT_MESSAGE:
        
        break;
    case AGENT_EVENT_RECEIVED_DET_MESSAGE:
        
        break;
    }     
}