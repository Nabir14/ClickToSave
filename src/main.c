#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <stdbool.h>

#define GRAVITY -3.0f
#define MAX_HEIGHT  -72.0f
#define MIN_HEIGHT 350.0f
#define FONT_SIZE 32

typedef struct {
    Vector2 position;
    Vector2 scale;
    float rotation;
    Texture texture;
} Sprite;

void apply_gravity(Sprite* sprite) {
    sprite->position.y -= GRAVITY;
}

void DrawSprite(Sprite* sprite) {
    Rectangle sourceRect = {0.0f, 0.0f, (float)sprite->texture.width, (float)sprite->texture.height};
    Rectangle destRect = {sprite->position.x, sprite->position.y, (float)sprite->texture.width * sprite->scale.x, (float)sprite->texture.height * sprite->scale.y};
    DrawTexturePro(sprite->texture, sourceRect, destRect, (Vector2){0.0f, 0.0f}, sprite->rotation, WHITE);
}

int main()
{
    InitWindow(640, 480, "ClickToSave");
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
        .texture = LoadTexture("../resources/bg.png")
    };
    
    Sprite player = {
        .position = (Vector2){240.0f, 0.0f},
        .scale = (Vector2){ 0.25f, 0.25f },
        .rotation = 0.0f,
        .texture = LoadTexture("../resources/face.png")
    };
    
    Sprite monster = {
        .position = (Vector2){0.0f, 0.0f},
        .scale = (Vector2){ 1.3f, 1.0f},
        .rotation = 0.0f,
        .texture = LoadTexture("../resources/monster.png")
    };
    
    // Game
    memset(&text_buffer, 0, sizeof(text_buffer));
    
    while (!WindowShouldClose())
    {        
        if (!game_over) {
            player.rotation += 1.0f;
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                player.position.y -= 50.0f;
                score++;
                sprintf(text_buffer, "Score: %d", score);
            }
        
            if (player.position.y < MAX_HEIGHT) {
                game_over = true;
            } else if (player.position.y > MIN_HEIGHT) {
                game_over = true;
            }
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            DrawSprite(&bg);
            
            if (!game_over) {
                DrawSprite(&player);
            }
            
            DrawSprite(&monster);
            
            if (!game_over && score) {
                DrawText((const char*)text_buffer, 0, 0, FONT_SIZE, BLACK);
            } else if (game_over) {
                DrawText("Game Over!", 0, 0, FONT_SIZE, BLACK);
            } else {    
                DrawText("Score: 0", 0, 0, FONT_SIZE, BLACK);
            }
            
            apply_gravity(&player);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}