#ifndef STATION_H
#define STATION_H

#include <stdbool.h>
#include "objectStack.h"

enum Resource {
    ORE,
    PARTS,
    TECH,
    FUEL,
    GAS,
    POP,
    WEALTH,
    SHIP_PARTS,
    SUPPLIES
};

enum StationType {
    PARTS_FACTORY,
    SUPPLIES_FACTORY,
    SHIPYARD,
    TECH_COLONY,
    POP_COLONY,
    ORE_MINE,
    GAS_MINE,
    REFINERY,
};

enum StationState {
    IDLE,
    HALTED,
    ACTIVE,
    INIT,
};

typedef enum Resource Resource;
typedef enum StationType StationType;
typedef enum StationState StationState;

struct Station {
    Resource outputType;
    Resource *inputTypes;
    int outputPerCycle;
    int outputAmount;
    int outputPrice;
    int desiredOutputAmount;
    int numOfInputs;
    int *inputsPerCycle;
    int *inputAmounts;
    int *inputPrices;
    int *desiredInputAmounts;
    StationType stationType;
    StationState stationState;
    int ticksPerCycle;
    int cycleTickCount;
    int maxTicksSinceLastCycle;
    int ticksSinceLastCycle;
    int id;
    int agentID;
};

typedef struct Station Station;



void FreeStationList(ObjStack* stationList);
void SortStationList(ObjStack* stationList);
void UpdateStations(ObjStack* stations);

Station* NewStation(StationType type, int agentID);
void FreeStation(Station *station);
static void InitStation(Station *station);
static void UpdateStation(Station *station);
static void CheckStationCycle(Station *station);
static void stationProductionCycle(Station *station);

char* ResourceToString(Resource resource);
char* StationTypeToString(StationType type);
char* StationStateToString(StationState state);

void SaveStations(ObjStack *stationList);
void LoadStations(ObjStack *stationList);

bool BuyStationOutput(int stationID, int entityID, int amt);
bool SellStationInput(int stationID, int entityID, int amt, Resource inputType);
#endif //STATION_H
