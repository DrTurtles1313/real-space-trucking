#ifndef OBJECTSTACK_H
#define OBJECTSTACK_H

#include <stdbool.h>
#define STACK_SIZE 500

struct ObjStack {
    void *objects[STACK_SIZE];
    int top;
    bool sorted;
};
typedef struct ObjStack ObjStack;

void* PopObject(ObjStack* objStack);
void PushObject(ObjStack* objStack, void *object);
void* PeekObject(ObjStack* objStack);
bool IsObjectStackFull(ObjStack* objStack);
bool IsObjectStackEmpty(ObjStack* objStack);
void InitObjectStack(ObjStack* objStack);

#endif //OBJECTSTACK_H
