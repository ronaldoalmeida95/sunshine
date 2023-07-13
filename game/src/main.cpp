#include "rlImGui.h"
#include "raymath.h"
#include <raylib.h>
#include "raymath.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
float dt = 1.0f / 240.0f;


class Agent
{
public:
    Vector2 position;
    Vector2 toTarget;
    Vector2 desiredVel;
    Vector2 deltaVel;
    Vector2 deltaVelnorm;
    float currentSpeed;
    Vector2 maxSpeed;
    Vector2 acceleration;
    Vector2 maxAccel;
    Vector2 velocity;

    Agent()
    {
        position = { (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) };
        toTarget = { 0,0 };
        desiredVel = { 0,0 };
        deltaVel = { 0,0 };
        deltaVelnorm = { 0,0 };
        currentSpeed = 0.0f;
        maxSpeed = { 300, 300};
        acceleration = { 0,0 };
        maxAccel = { 500, 500 };
        velocity = { 0,0 };
    }

    void UpdatePhysicsSeek(Vector2 mouse, float dt)
    {
        toTarget = Vector2Normalize(Vector2Subtract(mouse, position));
        desiredVel = Vector2Multiply(toTarget, maxSpeed);
        deltaVel = Vector2Subtract(desiredVel, velocity);
        deltaVelnorm = Vector2Normalize(deltaVel);
        acceleration = Vector2Multiply(deltaVelnorm, maxAccel);
        position.x += velocity.x * dt + (acceleration.x * dt * dt * 0.5);
        position.y += velocity.y * dt + (acceleration.y * dt * dt * 0.5);
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;
        currentSpeed = Vector2Length(velocity);
        if (currentSpeed > maxSpeed.x)
        {
            velocity.x = velocity.x * (maxSpeed.x / currentSpeed);
        }
        if (currentSpeed > maxSpeed.y)
        {
            velocity.y = velocity.y * (maxSpeed.y / currentSpeed);
        }
    }
    void UpdatePhysicsFlee(Vector2 mouse, float dt)
    {
        toTarget = Vector2Normalize(Vector2Subtract(mouse, position));
        desiredVel = Vector2Multiply(toTarget, maxSpeed);
        desiredVel = { (-1) * (desiredVel.x), (-1) * (desiredVel.y) };
        deltaVel = Vector2Subtract(desiredVel, velocity);
        deltaVelnorm = Vector2Normalize(deltaVel);
        acceleration = Vector2Multiply(deltaVelnorm, maxAccel);
        position.x += velocity.x * dt + (acceleration.x * dt * dt * 0.5);
        position.y += velocity.y * dt + (acceleration.y * dt * dt * 0.5);
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;
        currentSpeed = Vector2Length(velocity);
        if (currentSpeed > maxSpeed.x)
        {
            velocity.x = velocity.x * (maxSpeed.x / currentSpeed);
        }
        if (currentSpeed > maxSpeed.y)
        {
            velocity.y = velocity.y * (maxSpeed.y / currentSpeed);
        }
    }
    

};

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
    SetTargetFPS(60);

    Agent BlueCircle;
    Agent YellowCircle;
    Vector2 mouse;
   
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}