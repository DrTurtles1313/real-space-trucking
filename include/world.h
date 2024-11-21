#ifndef WORLD_H
#define WORLD_H
#include <agent.h>
#include <raylib.h>
#include "player.h"
#include "station.h"

#define MAP_HEIGHT 25
#define MAP_WIDTH 25

struct World {
    int map[MAP_HEIGHT][MAP_WIDTH];
    Texture2D tileset;
    Camera2D camera;
    Player player;
    Vector2 mouseWorldPosition;
    StationList stations;
    AgentList agents;
    bool debug;
    bool runTicks;
    float timeSinceTick;
    int debugStation;
};
typedef struct World World;

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset);
static Vector2 WorldToScreen(Vector2 pos);
static Vector2 ScreenToWorld(Vector2 pos);
static Vector2 ScreenToWorldGrid(Vector2 pos);
void HandleInput(World* world);
void Render(World* world);
void MovePlayer(Player* player);
void UpdateWorld(World* world);
#endif //WORLD_H
