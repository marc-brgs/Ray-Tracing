#include <iostream>

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

using namespace std;

int main() {
    int cols = 300;
    int rows = 300;
    string image_name = "test";

    // std::cout << "Enter cols : ";
    // std::cin >> cols;
    // std::cout << "Enter rows : ";
    // std::cin >> rows;
    // std::cout << "Enter image name : ";
    // std::cin >> image_name;

    cv::Mat img(cols, rows, CV_8UC3, cv::Scalar(0, 0, 255));

    std::cout << "Hello, World!" << std::endl;

    string title = "test";
    cv::namedWindow(title, CV_WINDOW_AUTOSIZE); // fit to the screen if too big
    cv::imshow(title, img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    Point origin(1, 2, 3);
    Vector direction(0, 1, 0);

    Ray ray(origin, direction);

    cv::imwrite(image_name + ".jpg", img);

    return 0;
}
