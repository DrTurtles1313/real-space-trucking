#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <raymath.h>

#define TILE_WIDTH 128
#define TILE_HEIGHT 64
#define TILE_WIDTH_HALF 64
#define TILE_HEIGHT_HALF 32

struct World
{
    int map[10][10];
    Texture2D tileset;
};

void DrawTile(Vector2 worldPos, int tile, Texture2D tileset);
Vector2 WorldToScreen(Vector2 pos);
Vector2 ScreenToWorld(Vector2 pos);
Vector2 ScreenToWorldGrid(Vector2 pos);
void HandleInput(struct World *world);
void Render(struct World *world);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Vector2 mousePosWorldPos;
    Vector2 mousePos;

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Real Space Truckin");

    struct World world;
    world.tileset = LoadTexture("assets/TestingTileset.png");
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            world.map[x][y] = 1;
        }
    }
    world.map[0][0] = 1;
    world.map[1][0] = 2;
    world.map[2][0] = 1;

    Camera2D camera = {0};
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    while (!WindowShouldClose()) {

        mousePosWorldPos = ScreenToWorldGrid(GetScreenToWorld2D(GetMousePosition(), camera));

        // Translate based on mouse right click
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode2D(camera);
        Render(&world);
        DrawTile(mousePosWorldPos, 3, world.tileset);
        EndMode2D();

        EndDrawing();

    }

    UnloadTexture(world.tileset);
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

void HandleInput(struct World *world)
{

}

void Render(struct World *world)
{
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            DrawTile((Vector2){x,y}, world->map[x][y], world->tileset);
        }
    }
}