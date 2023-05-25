#include "rlImGui.h"
#include <raylib.h>
#include "raymath.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
float dt = 1.0f / 240.0f;

Vector2 WrapAroundScreen(Vector2 position)
{
    Vector2 outPosition = 
    {
    fmodf(position.x + SCREEN_WIDTH, SCREEN_WIDTH),
    fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(240);
    rlImGuiSetup(true);

    Vector2 vel = { 100, 100};
    Vector2 pos = { 0, (SCREEN_HEIGHT / 2) };
    Vector2 maxSpeed = { 1000, 1000 };
    Vector2 acceleration = { 50, 50};
    float maxAccel = 500;
   
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        rlImGuiBegin();
        ImGui::DragFloat2("Position", &pos.x, 1, 0, SCREEN_WIDTH);
        ImGui::DragFloat2("Velocity", &vel.x, 1, -maxSpeed.x, maxSpeed.x);
        ImGui::DragFloat2("Acceleration", &acceleration.x, 1, -maxAccel, maxAccel);
        pos.x += vel.x * dt + (acceleration.x * dt * dt * 0.5);
        pos.y += vel.y * dt + (acceleration.y * dt * dt * 0.5);
        pos = WrapAroundScreen(pos);
        vel.x += acceleration.x * dt;
        vel.y += acceleration.y * dt;
        if (vel.x >= maxSpeed.x)
        {
            vel.x = maxSpeed.x;
        }
        if (vel.x <= -maxSpeed.x)
        {
            vel.x = -maxSpeed.x;
        }
        if (vel.y >= maxSpeed.y)
        {
            vel.y = maxSpeed.y;
        }
        if (vel.y <= -maxSpeed.y)
        {
            vel.y = -maxSpeed.y;
        }
        rlImGuiEnd();
        DrawCircle(pos.x, pos.y, 30, BLUE);
        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}