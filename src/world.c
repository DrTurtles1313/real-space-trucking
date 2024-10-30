#include "world.h"
#include <raylib.h>
#include "player.h"
#include <math.h>
#include <raymath.h>

#define TILE_WIDTH 128
#define TILE_HEIGHT 64
#define TILE_WIDTH_HALF 64
#define TILE_HEIGHT_HALF 32
#define TICK_LENGTH 1.0f

void UpdateWorld(World *world) {
    world->mouseWorldPosition = ScreenToWorldGrid(GetScreenToWorld2D(GetMousePosition(), world->camera));

    HandleInput(world);
    MovePlayer(&world->player);
    world->camera.target = Vector2Add(WorldToScreen(world->player.position), (Vector2){64,32});

    if (world->runTicks) {
        world->timeSinceTick += GetFrameTime();
        if (world->timeSinceTick > TICK_LENGTH) {
            world->timeSinceTick = 0.0f;
            UpdateStations(&world->stations);
        }
    }
}

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset) {
    Vector2 screenPos = WorldToScreen(worldPos);

    Rectangle source = {(float)tile * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT};
    DrawTextureRec(tileset, source, screenPos, RAYWHITE);
}

Vector2 WorldToScreen(Vector2 pos) {
    return (Vector2){(pos.x - pos.y) * TILE_WIDTH_HALF - TILE_WIDTH_HALF, (pos.x + pos.y) * TILE_HEIGHT_HALF};
}

Vector2 ScreenToWorld(Vector2 pos) {
    return (Vector2){
        (pos.x / TILE_WIDTH_HALF + pos.y / TILE_HEIGHT_HALF),
        (pos.y / TILE_HEIGHT_HALF - pos.x / TILE_WIDTH_HALF)
    };
}

Vector2 ScreenToWorldGrid(Vector2 pos) {
    float x = floorf(pos.x / TILE_WIDTH + pos.y / TILE_HEIGHT);
    float y = floorf(pos.y / TILE_HEIGHT - pos.x / TILE_WIDTH);
    x = fmaxf(0.0f, x);
    x = fminf(x, MAP_WIDTH - 1);
    y = fmaxf(0.0f, y);
    y = fminf(y, MAP_HEIGHT - 1);


    return (Vector2){
        x,y
    };
}

void HandleInput(World* world) {
    // Translate based on mouse right click
    /*if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / world->camera.zoom);
        world->camera.target = Vector2Add(world->camera.target, delta);
    }*/

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !world->debug) {
        world->player.destination = world->mouseWorldPosition;
    }
    if (IsKeyPressed(KEY_A)) {
        UpdateStations(&world->stations);
    }
    if (IsKeyPressed(KEY_D)) {
        world->debug = !world->debug;
    }
}

void Render(World* world) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            DrawTile((Vector2){(float)x, (float)y}, world->map[x][y], world->tileset);
        }
    }
    DrawTile(world->player.position, 2, world->tileset);
    DrawTile(world->mouseWorldPosition, 3, world->tileset);
}

void MovePlayer(Player* player) {
    if (player->position.x != player->destination.x || player->position.y != player->destination.y) {
        player->position = Vector2MoveTowards(player->position, player->destination, player->speed * GetFrameTime());
    }
}


