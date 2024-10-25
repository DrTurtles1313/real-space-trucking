#ifndef STATION_H
#define STATION_H

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
    FACTORY,
    SHIPYARD,
    COLONY,
    MINE
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
};

typedef struct Station Station;

Station* NewStation(StationType type);
void FreeStation(Station *station);
void InitStation(Station *station);
void UpdateStation(Station *station);
void CheckStationCycle(Station *station);
void stationProductionCycle(Station *station);
#endif //STATION_H
