#ifndef AGENT_H
#define AGENT_H
#include <stdbool.h>
#define MAX_AGENTS 50
#include <stdlib.h>

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

struct AgentList {
    Agent* agents[MAX_AGENTS];
    int top;
};
typedef struct AgentList AgentList;

Agent* NewAgent(AgentType type);
void FreeAgent(Agent* agent);

void InitAgentList(AgentList* list);
void PushAgent(AgentList* list, Agent* agent);
Agent* PeekAgent(AgentList* list);
Agent* PopAgent(AgentList* list);
bool IsAgentListEmpty(AgentList* list);
bool IsAgentListFull(AgentList* list);
Agent* GetAgent(AgentList* list, int id);
void RemoveAgent(AgentList* list, int id);

#endif //AGENT_H
