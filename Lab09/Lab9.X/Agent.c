#include "Agent.h"
#include "Protocol.h"
#include "Field.h"
#include "FieldOled.h"
#include "Oled.h"

NegotiationData nData;
GuessData gData;

ProtocolParserStatus myStatus;
int agentEvent = AGENT_EVENT_NONE; //flag for current AgentEvent
static AgentState checkState = AGENT_EVENT_NONE;



//Im doing Agent Run and AgentGetEnemyStatus

int AgentRun(char in, char *outBuffer)
{
    myStatus = ProtocolDecode(in, &nData, &gData);
    //check what ProtocolDecode returns and set a flag
    if (in != NULL) {
        if (checkState == PROTOCOL_PARSING_GOOD) {
            agentEvent = AGENT_EVENT_NONE;
        } else if (checkState == PROTOCOL_PARSED_CHA_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_CHA_MESSAGE;
        } else if (checkState == PROTOCOL_PARSED_COO_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_COO_MESSAGE;
        } else if (checkState == PROTOCOL_PARSED_DET_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_DET_MESSAGE;
        } else if (checkState == PROTOCOL_PARSED_HIT_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_HIT_MESSAGE;
        } else {
            //if tne input isn't valid, set an error flag
            agentEvent = AGENT_EVENT_MESSAGE_PARSING_FAILED;
        }
    }
    
    switch (checkState)
    {
    case AGENT_STATE_GENERATE_NEG_DATA:
        
        break;
        
    case AGENT_STATE_SEND_CHALLENGE_DATA:
        
        break;
        
    case AGENT_STATE_DETERMINE_TURN_ORDER:
        
        break;
        
    case AGENT_STATE_SEND_GUESS:
        
        break;
    case AGENT_STATE_WAIT_FOR_HIT:
        
        break;
    case AGENT_STATE_WAIT_FOR_GUESS:
        
        break;
    case AGENT_STATE_INVALID:
        
        break;
    case AGENT_STATE_LOST:
        
        break;
    case AGENT_STATE_WON:
        
        break;
        
    }
}
