#include <iostream>
#include <vector>

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

    // std::cout << "Enter cols : ";
    // std::cin >> cols;
    // std::cout << "Enter rows : ";
    // std::cin >> rows;
    // std::cout << "Enter image name : ";
    // std::cin >> image_name;

    cv::Mat img(rows, cols, CV_8UC3, cv::Scalar(0, 0, 255));

    Scene scene(Color(1.0f, 1.0f, 1.0f), Color(0.2f, 0.2f, 0.2f));

    // Création d'une instance de Light
    Color diffuse(1.0f, 1.0f, 1.0f);
    Color specular(0.0f, 0.0f, 1.0f);
    Light light(diffuse, specular);
    light.translate(5, 5, -5);

    // Ajout de la lumière à la scène
    scene.addLight(&light);

    // vue d'en face
    Camera camera(30);
    camera.translate(0, 0, 100);
    //camera.rotateX(0);

    // Vue arrière
    //camera.translate(1, 1, -100);
    //camera.rotateY(180);

    // vue du haut
    //camera.translate(0, -100, 0); // monte la cam
    //camera.rotateX(-90); // tourne vers le bas

    Plan plan;
    Sphere sphere;
    Sphere sphere2;
    Square square;
    Cube cube;
    Cylinder cylinder;

    square.rotateZ(45);
    sphere.translate(2, 0, 0);
    sphere2.scale(.8f);
    sphere2.translate(-2, 0, -1);

    cube.scale(.5f);
    cube.translate(-2, 0, -2);
    cube.rotateX(45);
    cube.rotateY(45);
    cube.rotateZ(45);
    cube.translate(0, -1, 0);

    cylinder.rotateX(45);
    cylinder.rotateZ(45);

    plan.rotateX(90);
    plan.translate(0, 3, 0);


    scene.addObject(&sphere);
    scene.addObject(&sphere2);
    scene.addObject(&cube);
    //scene.addObject(&plan);
    scene.addObject(&cylinder);

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

                if (isShadowed) {
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

    cv::imwrite(image_name + ".jpg", img);

    return 0;
}

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

    return c;
}

