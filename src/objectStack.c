#include "objectStack.h"

#include <stdio.h>

void* PopObject(ObjStack* objStack) {
    if (IsObjectStackEmpty(objStack)) {
        printf("Stack Underflow");
        return NULL;
    }

    void* popped = objStack->objects[objStack->top];
    objStack->top--;

    return popped;
}

void PushObject(ObjStack* objStack, void* station) {
    if (IsObjectStackFull(objStack)) {
        printf("Stack Overflow");
    }

    objStack->top++;
    objStack->objects[objStack->top] = station;
}

void* PeekObject(ObjStack* objStack) {
    if (IsObjectStackEmpty(objStack)) {
        printf("Stack is empty");
        return NULL;
    }

    void* peeked = objStack->objects[objStack->top];
    return peeked;
}

bool IsObjectStackEmpty(ObjStack* objStack) {
    return objStack->top == -1;
}

bool IsObjectStackFull(ObjStack* objStack) {
    return objStack->top == STACK_SIZE - 1;
}

void InitObjectStack(ObjStack* objStack) {
    objStack->top = -1;
    objStack->sorted = false;
}