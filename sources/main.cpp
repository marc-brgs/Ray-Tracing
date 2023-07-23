#include <iostream>
#include <vector>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "point.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include "entity.hpp"

#include "camera.hpp"
#include "light.hpp"

#include "plan.hpp"
#include "square.hpp"
#include "sphere.hpp"
#include "cube.hpp"

#include "color.hpp"
#include "material.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "cylinder.hpp"

using namespace std;

Color getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene);

int main() {
    int cols = 700;
    int rows = 700;
    string image_name = "result";
    string shadowInput = "n";

    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    int randomValue = timestamp;

    // std::cout << "Enter cols : ";
    // std::cin >> cols;
    // std::cout << "Enter rows : ";
    // std::cin >> rows;
    // std::cout << "Enter image name : ";
    // std::cin >> image_name;
    // std::cout << "Enable shadow? (y/n) ";
    // std::cin >> shadowInput;

    bool enabledShadow = shadowInput == "y" ? true : false;
    cv::Mat img(rows, cols, CV_8UC3, cv::Scalar(0, 0, 255));

    Scene scene(Color(0.05f, 0.05f, 0.05f), Color(0.1f, 0.1f, 0.1f));

    // Création d'une instance de Light
    Color diffuse(0.8f, 0.8f, 1.0f);
    Color specular(0.8f, 0.8f, 1.0f);
    Light light(diffuse, specular);
    light.translate(5, -5, 5);

    // Ajout de la lumière à la scène
    scene.addLight(&light);

    // vue d'en face
    Camera camera(7);
    camera.translate(0, 0, 30);
    //camera.rotateY(90);

    Plan plan;
    Sphere sphere;
    Sphere sphere2;
    Sphere sphere3;
    Square square;
    Cube cube;
    Cylinder cylinder;

    square.rotateX(30);
    square.rotateZ(35);
    square.scale(.8);
    square.translate(3, -2, -6);
    square.loadTexture("textures/lava.png");

    sphere.rotateX(90);
    sphere.rotateY(90);
    sphere.translate(2, 1, 0);
    sphere.loadTexture("textures/glow_rock.png");
    sphere.shininess = 1.0f;

    sphere2.rotateX(90);
    sphere2.scale(.8f);
    sphere2.translate(-2, 0, -2);
    sphere2.loadTexture("textures/puzzle.png");

    sphere3.rotateX(90);
    sphere3.scale(.5f);
    sphere3.translate(-2, 2.7, 6);
    sphere3.loadTexture("textures/maze.jpg");

    cube.scale(.5f);
    cube.translate(-2, 0, -2);
    cube.rotateX(45);
    cube.rotateY(45);
    cube.rotateZ(45);
    cube.translate(0, -1, 0);
    cube.loadTexture("textures/dirt.png");

    cylinder.rotateX(45);
    cylinder.rotateZ(45);
    cylinder.scale(.4);
    cylinder.translate(0, 0, -18);

    plan.rotateX(90);
    plan.translate(0, 3, 0);
    plan.loadTexture("textures/grid.png");


    scene.addObject(&sphere);
    scene.addObject(&sphere2);
    scene.addObject(&sphere3);
    scene.addObject(&cube);
    scene.addObject(&plan);
    scene.addObject(&cylinder);
    scene.addObject(&square);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            // Convertir les coordonnées de l'écran en coordonnées normalisées
            // allant de -1 à 1 dans les deux dimensions
            float screenX = static_cast<float>(x) / cols * 2 - 1;
            float screenY = static_cast<float>(y) / rows * 2 - 1;

            // Générer un rayon correspondant au pixel de l'écran
            Ray ray = camera.getRay(screenX, screenY);

            Point impact;
            Object* intersectedObject = scene.closer_intersected(ray, impact);

            // Définir la couleur du pixel en fonction de l'intersection
            cv::Vec3b color;
            if (intersectedObject != nullptr) {
                // Ombre
                bool isShadowed = false;
                Object* shadowedObject;
                Point shadowImpact;
                shadowedObject = scene.closer_intersected(light.getRayToLight(impact), shadowImpact);
                if (shadowedObject != nullptr && shadowedObject != intersectedObject) {
                    isShadowed = true;
                }

                if (isShadowed && enabledShadow) {
                    color = Color(0, 0, 0).toVec3b();
                }
                else {
                    // Pas d'ombre
                    Material material = intersectedObject->getMaterial(impact);

                    Color impactColor = getImpactColor(ray, *intersectedObject, impact, scene);

                    color = impactColor.toVec3b();
                }
            }
            else {
                    color = scene.getBackground().toVec3b();
            }

            // Définir la couleur du pixel dans l'image
            img.at<cv::Vec3b>(y, x) = color;
        }
    }

    string title = "Render result";
    cv::namedWindow(title, CV_WINDOW_AUTOSIZE); // fit to the screen if too big
    cv::imshow(title, img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    cv::imwrite("results/" + image_name + std::to_string(randomValue) + ".jpg", img);

    return 0;
}

// Phong
Color getImpactColor(const Ray& ray, const Object& obj, const Point& impact, const Scene& scene) {
    Material m = obj.getMaterial(impact);
    Ray normal = obj.getNormal(impact, ray.origin);
    Color c = m.ka.mul(scene.getAmbient());
    for (int l = 0; l < scene.nbLights(); l++) {
        const Light* light = scene.getLight(l);
        Vector lv = light->getVectorToLight(impact);
        float alpha = lv.dot(normal.vector);
        if (alpha > 0)
            c += (light->id) * m.kd * alpha;

        Vector rm = (normal.vector * (2 * normal.vector.dot(lv))) - lv;

        float beta = -rm.dot(ray.vector);
        if (beta > 0)
            c += (light->is) * m.ks * pow(beta, m.shininess);
    }

    c.clamp();
    return c;
}

