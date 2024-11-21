#include "agent.h"

#include <stdio.h>

int nextAgentID = 0;

Agent* NewAgent(AgentType type) {
    Agent* agent = malloc(sizeof(Agent));
    agent->id = nextAgentId++;
    agent->wealth = 0;
    agent->type = type;
    agent->state = AGENT_IDLE;
    return agent;
}

void FreeAgent(Agent* agent) {
    free(agent);
}

void InitAgentList(AgentList* list) {
    list->top = -1;
}

void PushAgent(AgentList* list, Agent* agent) {
    if (!IsAgentListFull(list)) {
        list->top++;
        list->agents[list->top];
    }
    else {
        printf("Agent list is full\n");
    }
}

Agent* PeekAgent(AgentList* list) {
    if (!IsAgentListEmpty(list)) {
        return list->agents[list->top];
    }
    return NULL;
}

Agent* PopAgent(AgentList* list) {
    if (!IsAgentListEmpty(list)) {
        Agent* agent = list->agents[list->top];
        list->top--;
        return agent;
    }
    return NULL;
}

bool IsAgentListEmpty(AgentList* list) {
    if (list->top == -1) {
        return true;
    }
    return false;
}

bool IsAgentListFull(AgentList* list) {
    if (list->top == MAX_AGENTS) {
        return true;
    }
    return false;
}

Agent* GetAgent(AgentList* list, int id) {
    return NULL;
}