#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

namespace GameEngine {

    // Component base class for Entity-Component-System architecture
    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
    };

    // Entity class - container for components
    class Entity {
    private:
        std::unordered_map<std::string, std::unique_ptr<Component>> components_;
        std::string id_;

    public:
        Entity(const std::string& id) : id_(id) {}

        template<typename T>
        void AddComponent(std::unique_ptr<T> component) {
            components_[typeid(T).name()] = std::move(component);
        }

        template<typename T>
        T* GetComponent() {
            auto it = components_.find(typeid(T).name());
            return it != components_.end() ? static_cast<T*>(it->second.get()) : nullptr;
        }

        const std::string& GetId() const { return id_; }
    };

    // Transform component for position, rotation, scale
    class TransformComponent : public Component {
    private:
        float x_, y_, z_;
        float rotationX_, rotationY_, rotationZ_;
        float scaleX_, scaleY_, scaleZ_;

    public:
        TransformComponent(float x = 0, float y = 0, float z = 0)
            : x_(x), y_(y), z_(z), rotationX_(0), rotationY_(0), rotationZ_(0),
              scaleX_(1), scaleY_(1), scaleZ_(1) {}

        void Update(float deltaTime) override {}

        void SetPosition(float x, float y, float z) {
            x_ = x; y_ = y; z_ = z;
        }

        void Translate(float dx, float dy, float dz) {
            x_ += dx; y_ += dy; z_ += dz;
        }

        float GetX() const { return x_; }
        float GetY() const { return y_; }
        float GetZ() const { return z_; }
    };

    // Render component for rendering entities
    class RenderComponent : public Component {
    private:
        std::string meshPath_;
        bool visible_;

    public:
        RenderComponent(const std::string& meshPath)
            : meshPath_(meshPath), visible_(true) {}

        void Update(float deltaTime) override {}

        void SetVisible(bool visible) { visible_ = visible; }
        bool IsVisible() const { return visible_; }
        const std::string& GetMeshPath() const { return meshPath_; }
    };

    // Scene manager for managing entities
    class Scene {
    private:
        std::vector<std::unique_ptr<Entity>> entities_;

    public:
        Entity* CreateEntity(const std::string& id) {
            entities_.push_back(std::make_unique<Entity>(id));
            return entities_.back().get();
        }

        void Update(float deltaTime) {
            for (auto& entity : entities_) {
                // Update all components of each entity
                // In a real implementation, this would iterate through components
            }
        }

        size_t GetEntityCount() const { return entities_.size(); }
    };

    // Main game engine class
    class GameEngine {
    private:
        std::unique_ptr<Scene> scene_;
        bool isRunning_;
        float lastFrameTime_;

    public:
        GameEngine() : isRunning_(false), lastFrameTime_(0.0f) {
            scene_ = std::make_unique<Scene>();
        }

        void Initialize() {
            isRunning_ = true;
            lastFrameTime_ = GetCurrentTime();
        }

        void Update() {
            if (!isRunning_) return;

            float currentTime = GetCurrentTime();
            float deltaTime = currentTime - lastFrameTime_;
            lastFrameTime_ = currentTime;

            scene_->Update(deltaTime);
        }

        Scene* GetScene() { return scene_.get(); }

        void Shutdown() {
            isRunning_ = false;
        }

        bool IsRunning() const { return isRunning_; }

    private:
        float GetCurrentTime() {
            // In real implementation, this would use platform-specific timing
            static float time = 0.0f;
            time += 0.016f; // Simulate 60 FPS
            return time;
        }
    };

} // namespace GameEngine

#endif // GAME_ENGINE_H

