#include "ray_tracing_engine.h"
#include <iostream>
#include <iomanip>

using namespace RayTracing;

int main() {
    std::cout << "Ray Tracing Engine Demo\n";
    std::cout << "=======================\n\n";

    // Create materials
    Material redMaterial(Vector3(0.8f, 0.2f, 0.2f), 0.3f, 0.0f);
    Material blueMaterial(Vector3(0.2f, 0.2f, 0.8f), 0.5f, 0.2f);
    Material greenMaterial(Vector3(0.2f, 0.8f, 0.2f), 0.7f, 0.0f);
    Material goldMaterial(Vector3(0.8f, 0.7f, 0.2f), 0.1f, 0.9f);

    // Create scene
    Scene scene(Vector3(0.1f, 0.1f, 0.15f));

    // Add spheres to scene
    scene.addShape(std::make_unique<Sphere>(
        Vector3(-2.0f, 0.0f, -5.0f), 1.0f, redMaterial
    ));
    scene.addShape(std::make_unique<Sphere>(
        Vector3(0.0f, 0.0f, -5.0f), 1.0f, blueMaterial
    ));
    scene.addShape(std::make_unique<Sphere>(
        Vector3(2.0f, 0.0f, -5.0f), 1.0f, greenMaterial
    ));
    scene.addShape(std::make_unique<Sphere>(
        Vector3(0.0f, -2.0f, -3.0f), 0.8f, goldMaterial
    ));

    std::cout << "Scene created with " << scene.getShapeCount() << " objects\n";

    // Create camera
    Camera camera(
        Vector3(0.0f, 0.0f, 0.0f),  // Position
        Vector3(0.0f, 0.0f, -1.0f), // Target
        Vector3(0.0f, 1.0f, 0.0f),  // Up
        60.0f,                        // FOV
        800,                          // Width
        600                           // Height
    );

    std::cout << "Camera initialized: " << camera.getWidth() 
              << "x" << camera.getHeight() << "\n\n";

    // Create engine
    RayTracingEngine engine(scene, camera);

    // Render a sample pixel
    std::cout << "Rendering sample pixels...\n";
    Vector3 centerColor = engine.renderPixel(400, 300);
    Vector3 leftColor = engine.renderPixel(200, 300);
    Vector3 rightColor = engine.renderPixel(600, 300);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Center pixel color: (" 
              << centerColor.x << ", " << centerColor.y << ", " << centerColor.z << ")\n";
    std::cout << "Left pixel color: (" 
              << leftColor.x << ", " << leftColor.y << ", " << leftColor.z << ")\n";
    std::cout << "Right pixel color: (" 
              << rightColor.x << ", " << rightColor.y << ", " << rightColor.z << ")\n\n";

    std::cout << "Ray tracing engine ready for full scene rendering!\n";
    std::cout << "Features:\n";
    std::cout << "  - Physically-based ray tracing\n";
    std::cout << "  - Multiple material support\n";
    std::cout << "  - Sphere intersection algorithms\n";
    std::cout << "  - Normal-based lighting\n";
    std::cout << "  - Configurable camera system\n";

    return 0;
}

