#ifndef RAY_TRACING_ENGINE_H
#define RAY_TRACING_ENGINE_H

#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>

namespace RayTracing {

    // Vector3 class for 3D mathematics
    class Vector3 {
    public:
        float x, y, z;

        Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& v) const {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3 operator-(const Vector3& v) const {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3 operator*(float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        float dot(const Vector3& v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        Vector3 cross(const Vector3& v) const {
            return Vector3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }

        float length() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3 normalize() const {
            float len = length();
            if (len > 0.0001f) {
                return Vector3(x / len, y / len, z / len);
            }
            return Vector3(0, 0, 0);
        }
    };

    // Ray structure
    struct Ray {
        Vector3 origin;
        Vector3 direction;

        Ray(const Vector3& o, const Vector3& d) 
            : origin(o), direction(d.normalize()) {}
    };

    // Material properties
    struct Material {
        Vector3 albedo;      // Surface color
        float roughness;     // Surface roughness (0-1)
        float metallic;      // Metallic factor (0-1)
        float emission;      // Light emission strength

        Material(const Vector3& alb = Vector3(0.8f, 0.8f, 0.8f), 
                 float rough = 0.5f, float met = 0.0f, float em = 0.0f)
            : albedo(alb), roughness(rough), metallic(met), emission(em) {}
    };

    // Hit information
    struct HitInfo {
        float t;                    // Distance along ray
        Vector3 point;              // Hit point
        Vector3 normal;             // Surface normal
        Material material;          // Material at hit point
        bool hit;                   // Whether ray hit something

        HitInfo() : t(0), hit(false) {}
    };

    // Base shape class
    class Shape {
    public:
        Material material;

        Shape(const Material& mat) : material(mat) {}
        virtual ~Shape() = default;

        virtual bool intersect(const Ray& ray, HitInfo& hitInfo) const = 0;
        virtual Vector3 getNormal(const Vector3& point) const = 0;
    };

    // Sphere shape
    class Sphere : public Shape {
    private:
        Vector3 center;
        float radius;

    public:
        Sphere(const Vector3& c, float r, const Material& mat)
            : Shape(mat), center(c), radius(r) {}

        bool intersect(const Ray& ray, HitInfo& hitInfo) const override {
            Vector3 oc = ray.origin - center;
            float a = ray.direction.dot(ray.direction);
            float b = 2.0f * oc.dot(ray.direction);
            float c = oc.dot(oc) - radius * radius;
            float discriminant = b * b - 4 * a * c;

            if (discriminant < 0) {
                return false;
            }

            float sqrtD = std::sqrt(discriminant);
            float t1 = (-b - sqrtD) / (2.0f * a);
            float t2 = (-b + sqrtD) / (2.0f * a);

            float t = (t1 > 0.001f) ? t1 : t2;
            if (t < 0.001f) {
                return false;
            }

            hitInfo.t = t;
            hitInfo.point = ray.origin + ray.direction * t;
            hitInfo.normal = getNormal(hitInfo.point);
            hitInfo.material = material;
            hitInfo.hit = true;
            return true;
        }

        Vector3 getNormal(const Vector3& point) const override {
            return (point - center).normalize();
        }
    };

    // Scene containing all objects
    class Scene {
    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        Vector3 backgroundColor;

    public:
        Scene(const Vector3& bgColor = Vector3(0.1f, 0.1f, 0.15f))
            : backgroundColor(bgColor) {}

        void addShape(std::unique_ptr<Shape> shape) {
            shapes.push_back(std::move(shape));
        }

        HitInfo traceRay(const Ray& ray) const {
            HitInfo closestHit;
            float closestT = std::numeric_limits<float>::max();

            for (const auto& shape : shapes) {
                HitInfo hitInfo;
                if (shape->intersect(ray, hitInfo) && hitInfo.t < closestT) {
                    closestT = hitInfo.t;
                    closestHit = hitInfo;
                }
            }

            return closestHit;
        }

        Vector3 getBackgroundColor() const {
            return backgroundColor;
        }

        size_t getShapeCount() const {
            return shapes.size();
        }
    };

    // Camera for rendering
    class Camera {
    private:
        Vector3 position;
        Vector3 target;
        Vector3 up;
        float fov;
        int width, height;

    public:
        Camera(const Vector3& pos, const Vector3& tgt, const Vector3& u,
               float fieldOfView, int w, int h)
            : position(pos), target(tgt), up(u), fov(fieldOfView), width(w), height(h) {}

        Ray generateRay(int x, int y) const {
            float aspect = (float)width / height;
            float scale = std::tan(fov * 0.5f * M_PI / 180.0f);
            
            Vector3 forward = (target - position).normalize();
            Vector3 right = forward.cross(up).normalize();
            Vector3 upVec = right.cross(forward).normalize();

            float px = (2.0f * (x + 0.5f) / width - 1.0f) * aspect * scale;
            float py = (1.0f - 2.0f * (y + 0.5f) / height) * scale;

            Vector3 direction = (forward + right * px + upVec * py).normalize();
            return Ray(position, direction);
        }

        int getWidth() const { return width; }
        int getHeight() const { return height; }
    };

    // Ray Tracing Engine
    class RayTracingEngine {
    private:
        Scene scene;
        Camera camera;

    public:
        RayTracingEngine(const Scene& s, const Camera& c)
            : scene(s), camera(c) {}

        Vector3 renderPixel(int x, int y) const {
            Ray ray = camera.generateRay(x, y);
            HitInfo hit = scene.traceRay(ray);

            if (hit.hit) {
                // Simple shading with normal-based lighting
                Vector3 lightDir = Vector3(1, 1, 1).normalize();
                float lightIntensity = std::max(0.0f, hit.normal.dot(lightDir));
                return hit.material.albedo * (0.3f + 0.7f * lightIntensity);
            }

            return scene.getBackgroundColor();
        }

        void render(int* pixels) const {
            for (int y = 0; y < camera.getHeight(); y++) {
                for (int x = 0; x < camera.getWidth(); x++) {
                    Vector3 color = renderPixel(x, y);
                    int index = (y * camera.getWidth() + x) * 3;
                    pixels[index] = (int)(std::min(1.0f, color.x) * 255);
                    pixels[index + 1] = (int)(std::min(1.0f, color.y) * 255);
                    pixels[index + 2] = (int)(std::min(1.0f, color.z) * 255);
                }
            }
        }
    };

} // namespace RayTracing

#endif // RAY_TRACING_ENGINE_H

