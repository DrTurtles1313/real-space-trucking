#ifndef STATION_H
#define STATION_H

#include <stdbool.h>
#define MAX_STATIONS 500

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
};

typedef struct Station Station;

struct StationList {
    Station *stations[MAX_STATIONS];
    int top;
};
typedef struct StationList StationList;

Station* PopStation(StationList* stationList);
void PushStation(StationList* stationList, Station *station);
Station* PeakStationList(StationList* stationList);
bool IsStationListFull(StationList* stationList);
bool IsStationListEmpty(StationList* stationList);
void InitStationList(StationList* stationList);
void UpdateStations(StationList* stations);

Station* NewStation(StationType type);
void FreeStation(Station *station);
void InitStation(Station *station);
void UpdateStation(Station *station);
void CheckStationCycle(Station *station);
void stationProductionCycle(Station *station);
#endif //STATION_H
