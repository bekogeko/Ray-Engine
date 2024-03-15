#include "raylib.h"
#include "Player.h"

#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    Player player = Player({0, 0});


    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.position.x + 12, player.position.y + 12 };
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;



    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if(IsKeyDown(KEY_D)){
            player.velocity.x = 2;
        }
        if(IsKeyDown(KEY_A)){
            player.velocity.x = -2;
        }
        if(IsKeyDown(KEY_SPACE)){
            player.velocity.x = 0;
        }



        // Physics
        //----------------------------------------------------------------------------------
        // Update player acceleration
        // Update player velocity
        // Update player position
        // Update player collider
        player.Update();


        // Camera target follows player
        //        camera.target = (Vector2){ player.position.x + 12, player.position.y + 12 };

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        // Draw player
        player.Draw();


        EndMode2D();
        DrawText(TextFormat("Player's Speed: %f",player.velocity.x) , 10, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Player's Position: %f",player.position.x) , 10, 60, 20, LIGHTGRAY);



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}