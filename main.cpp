#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

bool in_img(cv::Point2d const& pt, cv::Mat const& img) {
    return pt.x > 0 && pt.y > 0 && pt.x+1 < img.cols && pt.y + 1 < img.rows;
}

void plot_line(cv::Mat& img, cv::Point2d origin, cv::Point2d direction) {
    cv::Point2d pt2 = origin;
    for (int t = 0; in_img(origin + (t+1)*direction, img); ++t) {
        pt2 = origin + t*direction;
    }
    cv::line(img, origin, pt2, cv::Scalar(0,0,0), 1.0, cv::LINE_AA);
}

int main() {

    int const width = 1000;
    int const height = 1000;

    int const c_x = width/2;
    int const c_y = height/2;

    int px_step = 2;
    double max_angle_deg = 80;
    double k = 1;

    while (true) {
        cv::Mat_<cv::Vec3b> plot(height, width, cv::Vec3b(255,255,255));

        for (int origin = 0; origin < c_x; origin += px_step) {
            double const alpha_deg = -k*origin;
            if (std::abs(alpha_deg) > max_angle_deg) {
                break;
            }
            double const sin = std::sin(M_PI*alpha_deg/180.0);
            double const cos = std::cos(M_PI*alpha_deg/180.0);
            plot_line(plot, {c_x + origin, c_y}, {sin, -cos});
            plot_line(plot, {c_x - origin, c_y}, {-sin, -cos});
        }

        std::cout << "Max angle [°]: " << max_angle_deg << ", change with w/s" << std::endl
                  << "One ray every " << px_step << "px, change with e/d" << std::endl
                  << "Angle change per px: " << k << ", change with r/f" << std::endl << std::endl;



        cv::imshow("plot", plot);
        char const key = cv::waitKey(0);

        switch (key) {
        case 'q': return EXIT_SUCCESS;
        case 'w': max_angle_deg += 5; break;
        case 's': max_angle_deg -= 5; break;
        case 'e': px_step++; break;
        case 'd': px_step = std::max(2, px_step-1); break;
        case 'r': k *= 2; break;
        case 'f': k /= 2; break;
        }
    }


}
