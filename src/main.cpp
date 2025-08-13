#include "../mechanics/main.hpp"



int main() {

    /*Initialization
    *******************/
    constexpr int screen_width = 1000;
    constexpr int screen_height = 862;
    constexpr int scene_height = 700;
    InitWindow(screen_width, screen_height, "The Transient - A Point & Click Investigation");


    // Frame rate cap
    SetTargetFPS(60);


    // Player Creation
    const auto new_player = std::make_shared<Player>();
    new_player->initialize();
    float frame_time = 0.3f;
    new_player->update(frame_time);


    // Scene Creation
    printf("-scene engine creation: ");
    SceneEngine scene_engine;
    scene_engine.player = new_player;
    scene_engine.init(screen_width, scene_height);
    scene_engine.current_scene->entering();
    printf("-scene engine creation: complete\n");


    // Audio init
    InitAudioDevice();
    Music music = LoadMusicStream("../assets/sounds/we-have-time.mp3");
    PlayMusicStream(music);


    /* GAME LOOP
    ***************/
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        const float dt = GetFrameTime();


        // Handle input
        scene_engine.handle_mouse();
        scene_engine.update(dt);

        /* DRAWING
        *************/
        BeginDrawing();
        ClearBackground(BLACK);



        // DRAW scene
        scene_engine.render();

        // DRAW interaction state
        if (scene_engine.current_scene->dialogue != " ") {
            DrawTextEx(scene_engine.in_game_font, scene_engine.current_scene->dialogue.c_str(),
                (Vector2){50, 782}, 12, 1.0f, BLACK);
        } else {
            DrawTextEx(scene_engine.in_game_font, scene_engine.player->dialogue.c_str(),
                (Vector2){50, 782}, 15, 1.0f, BLACK);
        }

        for (int i = 0; i < (scene_engine.current_scene->walk_zone.size() - 1); i++) {
            Vector2 beginning_pt = scene_engine.current_scene->walk_zone.at(i);
            Vector2 ending_pt = scene_engine.current_scene->walk_zone.at(i+1);
            DrawLineEx(beginning_pt, ending_pt, 5.0f, GREEN);
        }

        if (scene_engine.current_scene->exit_scene.count("right")) {
            DrawRectangleRec(scene_engine.current_scene->exit_scene["right"], WHITE);
        }
        if (scene_engine.current_scene->exit_scene.count("left")) {
            DrawRectangleRec(scene_engine.current_scene->exit_scene["left"], WHITE);
        }

        EndDrawing();
    }

    // UNLOAD textures
    UnloadMusicStream(music);
    scene_engine.current_scene->exiting();
    scene_engine.player->unload();

    // CLOSE window
    CloseWindow();

    return 0;
}
