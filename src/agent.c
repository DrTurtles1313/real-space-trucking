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

Agent* GetAgent(ObjStack* list, int id) {
    if (!list->sorted) {
        SortAgentList(list);
    }

    int low = 0;
    int high = list->top;
    Agent* current;

    // Repeat until the pointers low and high meet each other
    while (low <= high) {
        int mid = low + (high - low) / 2;
        current = (Agent*)list->objects[mid];

        if (id == current->id)
            return list->objects[mid];

        if (id > current->id)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return NULL;
}

void SortAgentList(ObjStack* list) {
    if (list->sorted) return;
    int n = list->top;
    Agent* current;
    Agent* min;

    for (int i = 0; i < n; i++) {
        int min_idx = i;

        for (int j = i + 1; j < n + 1; j++) {
            current = (Agent*)list->objects[j];
            min = (Agent*)list->objects[min_idx];

            if (current->id < min->id) {

                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }

        if (min_idx != i) {
            Agent* temp = list->objects[i];
            list->objects[i] = list->objects[min_idx];
            list->objects[min_idx] = temp;
        }
    }

    list->sorted = true;
}