#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <stdbool.h>

#define GRAVITY -98.0f
#define MAX_HEIGHT  -72.0f
#define MIN_HEIGHT 350.0f
#define FONT_SIZE 32
#define PLAYER_JUMP_VELOCITY 64.0f
#define PLAYER_SPIN_SPEED 1.0f

typedef struct {
    Vector2 position;
    Vector2 scale;
    float rotation;
    Texture texture;
    Vector2 origin;
} Sprite;
 
typedef struct {
    Sprite sprite;
    Vector2 velocity;
} Player;

void ApplyGravity(Player* player, float delta) {
    player->velocity.y -= GRAVITY * delta;
}

void ApplyVelocity(Player* player, float delta) {
        player->sprite.position.x += player->velocity.x * delta;
        player->sprite.position.y += player->velocity.y * delta;
}

void DrawSprite(Sprite* sprite) {
    Rectangle sourceRect = {0.0f, 0.0f, (float)sprite->texture.width, (float)sprite->texture.height};
    Rectangle destRect = {sprite->position.x, sprite->position.y, (float)sprite->texture.width * sprite->scale.x, (float)sprite->texture.height * sprite->scale.y};
    DrawTexturePro(sprite->texture, sourceRect, destRect, sprite->origin, sprite->rotation, WHITE);
}

int main()
{
    InitWindow(640, 480, "ClickToSave");
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(60);
    HideCursor();

    // Game Attributes
    int score = 0;
    char text_buffer[8];
    bool game_over = false;
    
    // Object Data
    Sprite bg = {
        .position = (Vector2){0.0f, 0.0f},
        .scale = (Vector2){ 1.5f, 1.0f},
        .rotation = 0.0f,
        .texture = LoadTexture("../resources/bg.png"),
        .origin = (Vector2){0.0f, 0.0f}
    };
    
    Player player = {
        .sprite = { 
            .position = (Vector2){240.0f, 0.0f},
            .scale = (Vector2){ 0.25f, 0.25f },
            .rotation = 0.0f,
            .texture = LoadTexture("../resources/face.png"),
            .origin = (Vector2){0.0f, 0.0f}
        },
        .velocity = (Vector2){ 0.0f, 0.0f }
    };
    
    Sprite monster = {
        .position = (Vector2){0.0f, 0.0f},
        .scale = (Vector2){ 1.3f, 1.0f},
        .rotation = 0.0f,
        .texture = LoadTexture("../resources/monster.png"),
        .origin = (Vector2){0.0f, 0.0f}
    };
    
    // Game
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        
        if (!game_over) {
            player.sprite.rotation += PLAYER_SPIN_SPEED;
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                player.velocity.y -= PLAYER_JUMP_VELOCITY;
                score++;
                sprintf(text_buffer, "Score: %d", score);
            } else {
                ApplyGravity(&player, delta);
            }
        
            if (player.sprite.position.y < MAX_HEIGHT || player.sprite.position.y > MIN_HEIGHT) {
                game_over = true;
            }
            
            ApplyVelocity(&player, delta);
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            DrawSprite(&bg);
            
            if (!game_over) {
                DrawSprite(&player.sprite);
            }
            
            DrawSprite(&monster);
            
            if (!game_over && score) {
                DrawText((const char*)text_buffer, 0, 0, FONT_SIZE, BLACK);
            } else if (game_over) {
                DrawText("Game Over!", 0, 0, FONT_SIZE, BLACK);
                DrawText((const char*)text_buffer, 0, FONT_SIZE+1, FONT_SIZE, BLACK);
            } else {    
                DrawText("Score: 0", 0, 0, FONT_SIZE, BLACK);
            }
            
        EndDrawing();
    }
    
    UnloadTexture(bg.texture);
    UnloadTexture(player.sprite.texture);
    UnloadTexture(monster.texture);

    CloseWindow();
    return 0;
}