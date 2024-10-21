#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    Vector2 position;
    Vector2 destination;
    Texture2D sprite;
    float speed;
};

typedef struct Player Player;

#endif //PLAYER_H
