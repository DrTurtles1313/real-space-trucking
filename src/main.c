#define RAYGUI_IMPLEMENTATION

#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include <raygui.h>
#include "player.h"
#include "station.h"
#include "world.h"

void DebugGui(World *world, char *message);

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Real Space Truckin");
    GuiLoadStyle("assets/style_dark.rgs");

    World world;
    world.tileset = LoadTexture("assets/TestingTileset.png");
    for (int x = 0; x < MAP_HEIGHT; x++) {
        for (int y = 0; y < MAP_WIDTH; y++) {
            world.map[x][y] = 0;
        }
    }
    world.map[0][0] = 1;
    world.map[1][0] = 2;
    world.map[2][0] = 1;

    world.camera.target = (Vector2){0, 0};
    world.camera.offset = (Vector2){(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    world.camera.rotation = 0.0f;
    world.camera.zoom = 1.0f;

    world.player.position = (Vector2){0, 0};
    world.player.destination = (Vector2){0, 0};
    world.player.speed = 5.0f;

    world.debug = false;
    world.debugStation = 0;
    world.runTicks = false;
    world.timeSinceTick = 0.0f;

    InitStationList(&world.stations);
    LoadStations(&world.stations);

    char messageBox[2048];
    UpdateStations(&world.stations);

    while (!WindowShouldClose()) {
        UpdateWorld(&world);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(world.camera);
        Render(&world);
        EndMode2D();

        if (world.debug) {
            DebugGui(&world, messageBox);
        }

        EndDrawing();
    }

    SaveStations(&world.stations);

    UnloadTexture(world.tileset);
    CloseWindow();

    return 0;
}

//Debug GUI Stuff
Vector2 viewScroll = {0,0};
Rectangle view = {0};
const char DEBUG_STRING[] = "ID: %d\nState: %s\nType: %s\nProd Cycle Length: %d\nProd Cycle Progress: %d\nIdle Time Mult: %d\nTicks Idle: %d";
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))

void DebugGui(World *world, char *message) {

    if (!IsStationListEmpty(&world->stations)) {
        Station *station = world->stations.stations[world->debugStation];
        int inputs = station->numOfInputs;

        GuiScrollPanel((Rectangle){0,0,280,400}, NULL, (Rectangle){0,0,250,2000}, &viewScroll, &view);
        BeginScissorMode(view.x, view.y, view.width, view.height);

        snprintf(message, 2048, DEBUG_STRING, station->id,
            StationStateToString(station->stationState), StationTypeToString(station->stationType), station->ticksPerCycle, station->cycleTickCount,
            station->maxTicksSinceLastCycle, station->ticksSinceLastCycle);

        GuiTextBox((Rectangle){0 + viewScroll.x, 0 + viewScroll.y,180,180}, message, 26, false);
        //GuiGrid((Rectangle){200 + viewScroll.x, viewScroll.y, 100, 1000}, NULL, 16, 3, NULL);

        snprintf(message, 2048, "Output Type: %s\nAmount: %d\nTarget Amount: %d\n\\Cycle: %d\nPrice: %d", ResourceToString(station->outputType),
                station->outputAmount, station->desiredOutputAmount, station->outputPerCycle, station->outputPrice);
        GuiTextBox((Rectangle){0 + viewScroll.x,180 + viewScroll.y,180,130}, message, 26, false);

        for (int i = 0; i < inputs; i++) {
            snprintf(message, 2048, "Input Type: %s\nAmount: %d\nTarget Amount: %d\n\\Cycle: %d\nPrice: %d", ResourceToString(station->inputTypes[i]),
                station->inputAmounts[i], station->desiredInputAmounts[i], station->inputsPerCycle[i], station->inputPrices[i]);
            GuiTextBox((Rectangle){0 + viewScroll.x,180 + 130 + 130 * i + viewScroll.y,180,130}, message, 26, false);
        }

        if (GuiButton((Rectangle){180 + viewScroll.x, viewScroll.y, 35,25}, "Next")) {
            world->debugStation = new_min(world->stations.top, world->debugStation + 1);
        }
        if (GuiButton((Rectangle){180 + viewScroll.x, 25 + viewScroll.y, 35,25}, "Prev")) {
            world->debugStation = new_max(0, world->debugStation - 1);
        }
        if (GuiButton((Rectangle){180 + viewScroll.x, 50 + viewScroll.y, 35,25}, "Tick")) {
            UpdateStations(&world->stations);
        }
        GuiCheckBox((Rectangle){180 + viewScroll.x, 75 + viewScroll.y, 35,25}, "Run", &world->runTicks);
        snprintf(message, 2048, "FT: %.2f", 1 / GetFrameTime());
        GuiLabel((Rectangle){180 + viewScroll.x, 100 + viewScroll.y, 80,25}, message);

        EndScissorMode();
    }
}