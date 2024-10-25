#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include "player.h"
#include "station.h"

#define TILE_WIDTH 128
#define TILE_HEIGHT 64
#define TILE_WIDTH_HALF 64
#define TILE_HEIGHT_HALF 32
#define MAP_HEIGHT 25
#define MAP_WIDTH 25

struct World {
    int map[MAP_HEIGHT][MAP_WIDTH];
    Texture2D tileset;
    Camera2D camera;
    Player player;
    Vector2 mouseWorldPosition;
    Station* testStation;
};
typedef struct World World;

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset);
Vector2 WorldToScreen(Vector2 pos);
Vector2 ScreenToWorld(Vector2 pos);
Vector2 ScreenToWorldGrid(Vector2 pos);
void HandleInput(World* world);
void Render(World* world);
void MovePlayer(Player* player);

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Real Space Truckin");

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

    world.testStation = NewStation(FACTORY);

    while (!WindowShouldClose()) {
        world.mouseWorldPosition = ScreenToWorldGrid(GetScreenToWorld2D(GetMousePosition(), world.camera));

        HandleInput(&world);
        MovePlayer(&world.player);
        world.camera.target = Vector2Add(WorldToScreen(world.player.position), (Vector2){64,32});

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode2D(world.camera);


        Render(&world);

        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(world.tileset);
    CloseWindow();

    return 0;
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        world->player.destination = world->mouseWorldPosition;
    }
    if (IsKeyPressed(KEY_A)) {
        UpdateStation(world->testStation);
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