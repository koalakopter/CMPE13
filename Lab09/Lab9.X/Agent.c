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
        if (myStatus == PROTOCOL_PARSING_GOOD) {
            agentEvent = AGENT_EVENT_NONE;
        } else if (myStatus == PROTOCOL_PARSED_CHA_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_CHA_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_COO_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_COO_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_DET_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_DET_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_HIT_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_HIT_MESSAGE;
        } else {
            //if tne input isn't valid, set an error flag
            agentEvent = AGENT_EVENT_MESSAGE_PARSING_FAILED;
        }
    }
    
    switch (checkState)
    {
    case AGENT_STATE_GENERATE_NEG_DATA:
        //generate Negotiation data and put it into nData
        ProtocolGenerateNegotiationData(&nData);
        
        //encode some challenge data
        ProtocolEncodeChaMessage(outBuffer, &nData);
        checkState = AGENT_STATE_SEND_CHALLENGE_DATA;
        return strlen(outBuffer); //returns length of the outBuffer string
        break;
        
    case AGENT_STATE_SEND_CHALLENGE_DATA:
        
        //send determine data
        ProtocolEncodeDetMessage(outBuffer, &nData);
        checkState = AGENT_STATE_DETERMINE_TURN_ORDER;
        return strlen(outBuffer);
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
