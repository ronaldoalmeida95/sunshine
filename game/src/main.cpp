#include "rlImGui.h"
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
    SetTargetFPS(240);
    rlImGuiSetup(true);

    Agent BlueCircle;
    Agent YellowCircle;
    Vector2 mouse;
   
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        rlImGuiBegin();

        ImGui::DragFloat2("Position", &BlueCircle.position.x, 1, 0, SCREEN_WIDTH);
        ImGui::DragFloat2("Velocity", &BlueCircle.velocity.x, 1, -BlueCircle.maxSpeed.x, BlueCircle.maxSpeed.x);
        ImGui::DragFloat2("Acceleration", &BlueCircle.acceleration.x, 1, -BlueCircle.maxAccel.x, BlueCircle.maxAccel.x);
        ImGui::DragFloat("MaxAcceleration", &BlueCircle.maxAccel.x, 1, -BlueCircle.maxAccel.x, BlueCircle.maxAccel.x);

        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
        BlueCircle.UpdatePhysicsSeek(mouse, dt);
        YellowCircle.UpdatePhysicsFlee(mouse, dt);
        YellowCircle.position = WrapAroundScreen(YellowCircle.position);
        bool collision = false;

        DrawCircle(BlueCircle.position.x, BlueCircle.position.y, 30, BLUE);
        DrawCircle(YellowCircle.position.x, YellowCircle.position.y, 30, YELLOW);

        collision = CheckCollisionCircles(BlueCircle.position, 30, mouse, 30);
        if (collision)
        {
            BlueCircle.acceleration = { 0,0 };
            BlueCircle.velocity = { 0,0 };
        }
        collision = CheckCollisionCircles(YellowCircle.position, 30, mouse, 30);
        if (collision)
        {
            YellowCircle.acceleration = { 0,0 };
            YellowCircle.velocity = { 0,0 };
        }
        DrawCircle(mouse.x, mouse.y, 30, PINK);
        DrawLine(BlueCircle.position.x, BlueCircle.position.y, (BlueCircle.position.x + BlueCircle.velocity.x * 1), (BlueCircle.position.y + BlueCircle.velocity.y * 1), RED);
        DrawLine(BlueCircle.position.x, BlueCircle.position.y, (BlueCircle.position.x + BlueCircle.acceleration.x), (BlueCircle.position.y + BlueCircle.acceleration.y * 1), GREEN);
        DrawLine(BlueCircle.position.x, BlueCircle.position.y, ((BlueCircle.position.x + BlueCircle.desiredVel.x)), ((BlueCircle.position.y + BlueCircle.desiredVel.y)), BLACK);
        
        DrawLine(YellowCircle.position.x, YellowCircle.position.y, (YellowCircle.position.x + YellowCircle.velocity.x * 1), (YellowCircle.position.y + YellowCircle.velocity.y * 1), RED);
        DrawLine(YellowCircle.position.x, YellowCircle.position.y, (YellowCircle.position.x + YellowCircle.acceleration.x), (YellowCircle.position.y + YellowCircle.acceleration.y * 1), GREEN);
        DrawLine(YellowCircle.position.x, YellowCircle.position.y, ((YellowCircle.position.x + YellowCircle.desiredVel.x)), ((YellowCircle.position.y + YellowCircle.desiredVel.y)), BLACK);


        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}