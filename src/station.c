#include "station.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Station* NewStation(StationType type, Resource output, char name[], int numOfInputs, ...) {
    va_list args;
    va_start(args, numOfInputs);
    Station *station = malloc(sizeof(Station));;

    station->stationType = type;
    station->stationState = INIT;

    Resource inputTypes[numOfInputs];
    int inputsPerCycle[numOfInputs];
    int inputAmounts[numOfInputs];
    int desiredInputAmounts[numOfInputs];
    int inputPrices[numOfInputs];

    for (int i = 0; i < numOfInputs; i++) {
        inputTypes[i] = va_arg(args, Resource);
    }

    station->inputTypes = inputTypes;
    station->inputsPerCycle = inputsPerCycle;
    station->inputAmounts = inputAmounts;
    station->desiredInputAmounts = desiredInputAmounts;
    station->inputPrices = inputPrices;

    station->outputType = output;
    station->outputAmount = 512;

    return station;
}

void FreeStation(Station *station) {
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
    station->stationState = IDLE;
    station->outputPrice = 0;
    station->outputAmount = 0;
    station->outputPerCycle = 0;
    station->desiredOutputAmount = 0;
    station->ticksPerCycle = 5;
    station->cycleTickCount = 0;
    station->maxTicksSinceLastCycle = 10;
    station -> ticksSinceLastCycle = 0;

    for (int i = 0; i < station->numOfInputs; i++) {
        station->inputAmounts[i] = 0;
        station->inputPrices[i] = 0;
        station->desiredInputAmounts[i] = 0;
        station->inputsPerCycle[i] = 0;
    }
}