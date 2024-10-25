#include "station.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>



Station* NewStation(StationType type) {
    Station *station = malloc(sizeof(Station));;

    switch (type) {
        case COLONY:
        case FACTORY:
            station->numOfInputs = 1;
            break;
        case SHIPYARD:
            station->numOfInputs = 2;
            break;
        case MINE:
            station->numOfInputs = 0;
            break;
    }

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

void UpdateStation(Station *station) {
    switch (station->stationState) {
    case IDLE:
        station->ticksSinceLastCycle += 1;
        printf("Ticks: %d\n", station->ticksSinceLastCycle);
    case HALTED:
        break;
    case ACTIVE:
        break;
    case INIT:
        InitStation(station);
        printf("Station Initialized!\n");
    }
}

void InitStation(Station *station) {
    Resource* inputResources;
    int* inputsPerCycle;
    int* inputAmounts;
    int* desiredInputAmounts;
    int* inputPrices;

    switch (station->stationType) {
        case FACTORY:
            station->numOfInputs = 1;

            inputResources = malloc(sizeof(Resource) * station->numOfInputs);
            inputsPerCycle = malloc(sizeof(int) * station->numOfInputs);
            inputAmounts = malloc(sizeof(int) * station->numOfInputs);
            desiredInputAmounts = malloc(sizeof(int) * station->numOfInputs);
            inputPrices = malloc(sizeof(int) * station->numOfInputs);
            inputResources[0] = ORE;
            inputsPerCycle[0] = 50;
            inputAmounts[0] = 0;
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
        case COLONY:
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
        case MINE:
            station->numOfInputs = 0;
            inputResources = NULL;;
            inputsPerCycle = NULL;
            inputAmounts = NULL;;
            desiredInputAmounts = NULL;
            inputPrices = NULL;

            station->ticksPerCycle = 5;
            station->maxTicksSinceLastCycle = 5;
            station->desiredOutputAmount = 700;
            station->outputPrice = 2;
            station->outputPerCycle = 5;
            station->outputType = ORE;
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
}