#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define TILE_WIDTH 128
#define TILE_HEIGHT 64
#define TILE_WIDTH_HALF 64
#define TILE_HEIGHT_HALF 32

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset);
Vector2 WorldToScreen(Vector2 pos);
Vector2 ScreenToWorld(Vector2 pos);
Vector2 ScreenToWorldGrid(Vector2 pos);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Vector2 mousePosWorldPos;
    Vector2 mousePos;

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Real Space Truckin");

    Texture2D texture = LoadTexture("assets/TestingTileset.png");

    while (!WindowShouldClose()) {
        mousePos = GetMousePosition();
        mousePosWorldPos = ScreenToWorldGrid(mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("%f\n", mousePos.x);
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawTile((Vector2){0, 0}, 0, texture);
        DrawTile((Vector2){1, 0}, 0, texture);
        DrawTile((Vector2){1, 1}, 1, texture);

        DrawTile(mousePosWorldPos, 3, texture);

        EndDrawing();

    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset) {
    Vector2 screenPos = WorldToScreen(worldPos);

    Rectangle source = {tile * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT};
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
    return (Vector2){
        floorf(pos.x / TILE_WIDTH + pos.y / TILE_HEIGHT),
        floorf(pos.y / TILE_HEIGHT - pos.x / TILE_WIDTH)
    };
}