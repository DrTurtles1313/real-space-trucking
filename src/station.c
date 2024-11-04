#include "station.h"
#include <stdio.h>
#include <stdlib.h>

Station* NewStation(StationType type) {
    Station *station = malloc(sizeof(Station));

    station->stationType = type;
    station->stationState = INIT;

    return station;
}

void FreeStation(Station *station) {
    free(station->inputTypes);
    free(station->inputAmounts);
    free(station->inputPrices);
    free(station->inputsPerCycle);
    free(station->desiredInputAmounts);
    free(station);
}

void UpdateStations(StationList* stations) {
    for (int i = 0; i <= stations->top; i++) {
        UpdateStation(stations->stations[i]);
    }
}

//Update station based on state
static void UpdateStation(Station *station) {
    switch (station->stationState) {
    case IDLE:
        station->ticksSinceLastCycle += 1;
        CheckStationCycle(station);
    case HALTED:
        break;
    case ACTIVE:
        stationProductionCycle(station);
        break;
    case INIT:
        InitStation(station);
    }
}

static void InitStation(Station *station) {
    Resource* inputResources = NULL;
    int* inputsPerCycle = NULL;
    int* inputAmounts = NULL;
    int* desiredInputAmounts = NULL;
    int* inputPrices = NULL;

    //Set default station values
    switch (station->stationType) {
        case SUPPLIES_FACTORY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = ORE;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 200;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;

            station->ticksPerCycle = 10;
            station->maxTicksSinceLastCycle = 20;
            station->desiredOutputAmount = 300;
            station->outputPrice = 10;
            station->outputPerCycle = 10;
            station->outputType = SUPPLIES;
            break;
        case PARTS_FACTORY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = ORE;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 200;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;

            station->ticksPerCycle = 10;
            station->maxTicksSinceLastCycle = 20;
            station->desiredOutputAmount = 300;
            station->outputPrice = 10;
            station->outputPerCycle = 10;
            station->outputType = PARTS;
            break;
        case SHIPYARD:
            station->numOfInputs = 2;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = PARTS;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 0;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;
            inputResources[1] = TECH;
            inputsPerCycle[1] = 50;
            inputAmounts[1] = 0;
            desiredInputAmounts[1] = 400;
            inputPrices[1] = 30;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 2;
            station->outputPerCycle = 5;
            station->outputType = SHIP_PARTS;
            break;
        case POP_COLONY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = SUPPLIES;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 0;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 2;
            station->outputPerCycle = 5;
            station->outputType = POP;
            break;
        case TECH_COLONY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = SUPPLIES;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 0;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 2;
            station->outputPerCycle = 5;
            station->outputType = TECH;
            break;
        case ORE_MINE:
            station->numOfInputs = 0;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 2;
            station->outputPerCycle = 5;
            station->outputType = ORE;
            break;
        case GAS_MINE:
            station->numOfInputs = 0;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 1;
            station->outputPerCycle = 5;
            station->outputType = GAS;
            break;
        case REFINERY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = GAS;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 200;
            desiredInputAmounts[0] = 400;
            inputPrices[0] = 30;

            station->ticksPerCycle = 10;
            station->maxTicksSinceLastCycle = 20;
            station->desiredOutputAmount = 300;
            station->outputPrice = 10;
            station->outputPerCycle = 10;
            station->outputType = FUEL;
            break;
    }

    station->stationState = IDLE;
    station->outputAmount = 0;
    station->cycleTickCount = 0;
    station -> ticksSinceLastCycle = 0;

    station->inputTypes = inputResources;
    station->inputAmounts = inputAmounts;
    station->inputPrices = inputPrices;
    station->desiredInputAmounts = desiredInputAmounts;
    station->inputsPerCycle = inputsPerCycle;

    printf("Station Initialized!\n");
}

//Check if station has enough resources to begin production
//If not, evaluate time spent idle to raise prices
static void CheckStationCycle(Station *station) {
    //Stations with no input requirements should be active
    //TODO: Check if output storage is full before setting to active
    if (station->numOfInputs == 0) {
        station->stationState = ACTIVE;
        station->ticksSinceLastCycle = 0;
        station->cycleTickCount = 0;
    } else {
        //Check how many inputs meet their requirements for 1 cycle
        int metInputs = 0;

        for (int i = 0; i < station->numOfInputs; i++) {
            if (station->inputAmounts[i] >= station->inputsPerCycle[i]) {
                metInputs++;
            }
        }

        //Set the station to active, and consume inputs.
        if (metInputs == station->numOfInputs) {
            station->stationState = ACTIVE;
            station->ticksSinceLastCycle = 0;
            station->cycleTickCount = 0;

            for (int i = 0; i < station->numOfInputs; i++) {
                station->inputAmounts[i] -= station->inputsPerCycle[i];
            }
        } else {
            //Increase prices if we have been idle for a multiple of idle time multiplier
            if (station->ticksSinceLastCycle % station->maxTicksSinceLastCycle == 0) {
                for (int i = 0; i < station->numOfInputs; i++) {
                    if (station->inputAmounts[i] < station->inputsPerCycle[i]) {
                        station->inputPrices[i] += 2;
                    }
                }
            }
        }
    }
}

//Run station production cycle
static void stationProductionCycle(Station *station) {
    if (station->cycleTickCount == station->ticksPerCycle) {
        station->stationState = IDLE;
        station->outputAmount += station->outputPerCycle;
    }
    else {
        station->cycleTickCount += 1;
    }
}

Station* PopStation(StationList* stationList) {
    if (IsStationListEmpty(stationList)) {
        printf("Stack Underflow");
        return NULL;
    }

    Station* popped = stationList->stations[stationList->top];
    stationList->top--;

    return popped;
}

void PushStation(StationList* stationList, Station* station) {
    if (IsStationListFull(stationList)) {
        printf("Stack Overflow");
    }

    stationList->top++;
    station->id = stationList->top;
    stationList->stations[stationList->top] = station;
}

Station* PeekStation(StationList* stationList) {
    if (IsStationListEmpty(stationList)) {
        printf("Stack is empty");
        return NULL;
    }

    Station* peeked = stationList->stations[stationList->top];
    return peeked;
}

bool IsStationListEmpty(StationList* stationList) {
    return stationList->top == -1;
}

bool IsStationListFull(StationList* stationList) {
    return stationList->top == MAX_STATIONS - 1;
}

void InitStationList(StationList* stationList) {
    stationList->top = -1;
}

void FreeStationList(StationList* stationList) {
    for (int i = 0; i < MAX_STATIONS; i++) {
        if (stationList->stations[i] != NULL) {
            FreeStation(stationList->stations[i]);
        }
    }

    free(stationList->stations);
}

char* ResourceToString(Resource resource) {
    switch (resource) {
        case ORE:
            return "ORE";
        case PARTS:
            return "PARTS";
        case TECH:
            return "TECH";
        case FUEL:
            return "FUEL";
        case GAS:
            return "GAS";
        case POP:
            return "POP";
        case WEALTH:
            return "WEALTH";
        case SHIP_PARTS:
            return "SHIP_PARTS";
        case SUPPLIES:
            return "SUPPLIES";
    }

    return "0";
}

char* StationTypeToString(StationType station) {
    switch (station) {
        case PARTS_FACTORY:
            return "PARTS_FACTORY";
        case SUPPLIES_FACTORY:
            return "SUPPLIES_FACTORY";
        case SHIPYARD:
            return "SHIPYARD";
        case TECH_COLONY:
            return "TECH_COLONY";
        case POP_COLONY:
            return "POP_COLONY";
        case ORE_MINE:
            return "ORE_MINE";
        case GAS_MINE:
            return "GAS_MINE";
        case REFINERY:
            return "REFINERY";
    }
    return "0";
}

char* StationStateToString(StationState state) {
    switch (state) {
        case IDLE:
            return "IDLE";
        case HALTED:
            return "HALTED";
        case ACTIVE:
            return "ACTIVE";
        case INIT:
            return "INIT";
    }

    return "0";
}