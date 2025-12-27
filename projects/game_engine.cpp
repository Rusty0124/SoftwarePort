#include "game_engine.h"
#include <iostream>

// Example usage of the game engine
int main() {
    using namespace GameEngine;

    // Create engine instance
    GameEngine engine;
    engine.Initialize();

    // Create a scene
    Scene* scene = engine.GetScene();

    // Create entities
    Entity* player = scene->CreateEntity("player");
    Entity* enemy = scene->CreateEntity("enemy");

    // Add transform components
    player->AddComponent<TransformComponent>(
        std::make_unique<TransformComponent>(0.0f, 0.0f, 0.0f)
    );
    enemy->AddComponent<TransformComponent>(
        std::make_unique<TransformComponent>(10.0f, 0.0f, 5.0f)
    );

    // Add render components
    player->AddComponent<RenderComponent>(
        std::make_unique<RenderComponent>("models/player.obj")
    );
    enemy->AddComponent<RenderComponent>(
        std::make_unique<RenderComponent>("models/enemy.obj")
    );

    // Game loop simulation
    std::cout << "Game Engine Demo\n";
    std::cout << "================\n\n";

    for (int frame = 0; frame < 5; ++frame) {
        engine.Update();

        // Get and update player position
        if (auto* transform = player->GetComponent<TransformComponent>()) {
            transform->Translate(1.0f, 0.0f, 0.0f);
            std::cout << "Frame " << frame << ": Player position ("
                      << transform->GetX() << ", "
                      << transform->GetY() << ", "
                      << transform->GetZ() << ")\n";
        }

        if (auto* render = player->GetComponent<RenderComponent>()) {
            std::cout << "Player mesh: " << render->GetMeshPath() << "\n";
            std::cout << "Visible: " << (render->IsVisible() ? "Yes" : "No") << "\n";
        }

        std::cout << "Entities in scene: " << scene->GetEntityCount() << "\n\n";
    }

    engine.Shutdown();
    std::cout << "Engine shutdown complete.\n";

    return 0;
}

