#ifndef AGENT_H
#define AGENT_H
#include <stdbool.h>
#define MAX_AGENTS 50
#include <stdlib.h>
#include "objectStack.h"

int nextAgentId;

enum AgentType {
    FREELANCER,
    EMPIRE,
    INDUSTRIALIST,
    PLAYER,
};

enum AgentState {
    AGENT_IDLE,
};

typedef enum AgentType AgentType;
typedef enum AgentState AgentState;

struct Agent {
    int id;
    int wealth;
    AgentType type;
    AgentState state;

};
typedef struct Agent Agent;

Agent* NewAgent(AgentType type);
void FreeAgent(Agent* agent);

Agent* GetAgent(ObjStack* list, int id);
void RemoveAgent(ObjStack* list, int id);
void SortAgentList(ObjStack* list);
void FreeagentList(ObjStack* list);

#endif //AGENT_H
