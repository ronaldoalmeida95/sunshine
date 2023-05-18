#include "rlImGui.h"
#include "raylib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);       //this function sets the fps (very useful because we don't have to count tiks as in SDL)

    Texture2D shrek = LoadTexture("../game/assets/textures/shrek.png");  // This function loads textures and we can later draw the textures
    Sound roar = LoadSound("../game/assets/textures/roar.mp3");
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE); //clean background to draw

        Rectangle grass = { 0, (SCREEN_HEIGHT / 2), SCREEN_WIDTH, (SCREEN_HEIGHT / 2) };
        Rectangle sky = { 0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT / 2) };
        DrawRectangleRec(grass, DARKGREEN); //Draw grass
        DrawRectangleRec(sky, SKYBLUE);  //Draw sky
        DrawCircle(50.0f, 50.0f, 45.0, YELLOW); // Draw Sun
        DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 50.0, BLACK); // Draw head
        DrawLineEx({ SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 - 100 }, { SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 + 150 }, 25, BLACK); // draw body
        DrawLineEx({ SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 + 150 }, { SCREEN_WIDTH / 2 + 50,  SCREEN_HEIGHT / 2 + 250 }, 25, BLACK); // draw right leg
        DrawLineEx({ SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 + 150 }, { SCREEN_WIDTH / 2 - 50,  SCREEN_HEIGHT / 2 + 250 }, 25, BLACK); // draw left leg
        DrawLineEx({ SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 - 50 }, { SCREEN_WIDTH / 2 + 50,  SCREEN_HEIGHT / 2 + 100 }, 20, BLACK); // draw right arm
        DrawLineEx({ SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 - 50 }, { SCREEN_WIDTH / 2 - 50,  SCREEN_HEIGHT / 2 + 100 }, 20, BLACK); // draw left arm

        int mouseX = GetMouseX(); //Get mouse X position
        int mouseY = GetMouseY(); //Get mouse Y position

        DrawCircle(mouseX, mouseY, 15, RED); // draw red circle in mouse position

        Vector2 mouseCenter = { mouseX, mouseY };
        Vector2 headCenter = { (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 100) };

        bool collision = CheckCollisionCircles(mouseCenter, 15.0f, headCenter, 50.0f); //check collision between head and mouse


        if (collision)
        {
            PlaySound(roar);
            DrawText("RAAAAW!!!!", 0, 20, 55, RED);
            DrawTexture(shrek, 0, 100, RAYWHITE);
            DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 50.0, RED); //draw a red circle over head
        }
        EndDrawing();
    }
    UnloadTexture(shrek);
    CloseWindow();
    return 0;
}