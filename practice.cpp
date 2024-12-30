#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Point {
    int x;
    int y;
};

class LinePoints {
public:
    LinePoints(const int x0, const int y0, const double rad, double alpha, const double rotate = 0) {
        point = new Point[point_count];
        const double angle = alpha + rotate;
        // Cube lines
        point[0] = {x0, y0};
        point[1] = calculatePoint(x0, y0, 2 * rad, angle + 3 * M_PI / 2);
        point[2] = calculatePoint(point[1].x, point[1].y, rad / 2, angle + 5 * M_PI / 4);
        point[3] = calculatePoint(point[2].x, point[2].y, rad / 2, angle + 7 * M_PI / 4);
        point[4] = calculatePoint(point[3].x, point[3].y, rad / 2, angle + M_PI / 4);
        point[5] = {point[1].x, point[1].y};

        // Triangle lines
        double t = rad / 6;
        point[6] = {x0, y0};
        point[7] = calculatePoint(point[6].x, point[6].y, 2 * rad + t, angle + 7 * M_PI / 4);
        point[8] = calculatePoint(point[7].x, point[7].y, rad, angle + 3 * M_PI / 2);
        point[9] = calculatePoint(point[8].x, point[8].y, sqrt(2 * pow(rad, 2)), angle + M_PI / 4);
        point[10] = {point[7].x, point[7].y};
    }

    VertexArray PartOfFigure() {
        VertexArray curve(LinesStrip, 0);
        for (int i = 0; i < 11; i++) {
            curve.append(Vector2f(point[i].x, point[i].y));
        }
        return curve;
    }

    ~LinePoints() {
        delete[] point;
    }

private:
    Point* point;
    const int point_count = 11;
    static Point calculatePoint(const int x, const int y, const double distance, const double angle) {
        return {(int)(double(x) + distance * cos(angle)), (int)(double(y) + distance * sin(angle))};
    }
};

class SolidFigures {
public:
    static CircleShape createCircle(const double rad, const int x0, const int y0) {
        CircleShape circle(rad);
        circle.setPosition((double)x0 - rad, (double)y0 - rad);
        circle.setFillColor(Color::Transparent);
        circle.setOutlineColor(Color::White);
        circle.setOutlineThickness(1);
        return circle;
    }

    static VertexArray createDiamond(const double rad, const int x0, const int y0, const double rotate = 0) {
        VertexArray diamond(LinesStrip, 0);
        diamond.append(Vector2f((double)x0 + rad * cos(rotate), (double)y0 + rad * sin(rotate)));
        diamond.append(Vector2f(x0 + rad * cos(rotate + M_PI / 2),
            y0 + rad * sin(rotate  + M_PI / 2)));
        diamond.append(Vector2f(x0 + rad * cos(rotate + M_PI),
            y0 + rad * sin(rotate  + M_PI)));
        diamond.append(Vector2f(x0 + rad * cos(rotate + 3 * M_PI / 2),
            y0 + rad * sin(rotate  + 3 * M_PI / 2)));
        diamond.append(Vector2f(x0 + rad * cos(rotate), y0 + rad * sin(rotate)));
        return diamond;
    }

    static VertexArray StarShape(const double rad, const int x0, const int y0, const double rotate) {
        VertexArray curve (LinesStrip, 0);

        constexpr int count = 100;
        double t;

        constexpr double angle = M_PI / 4;
        const double cosAngle = cos(angle - rotate);
        const double sinAngle = sin(angle - rotate);

        for (int i = 0; i <= count; ++i) {
            t = double(i * 2 * M_PI / count);
            double x = pow(cos(t + M_PI / 4), 3) * 2 * rad;
            double y = pow(sin(t + M_PI / 4), 3) * 2 * rad;

            double rotatedX = x * cosAngle - y * sinAngle;
            double rotatedY = x * sinAngle + y * cosAngle;

            curve.append(Vertex(Vector2f(double(x0) + rotatedX, double(y0) - rotatedY)));
        }
        return curve;
    }
};

class Drawing {
public:
    Drawing(RenderWindow& window, const int x0, const int y0, const double rad, const double rotate = 0){
        window.clear(Color::Black);
        for (int i = 0; i < 4; i++){
            auto lines = LinePoints(x0, y0, rad, double(i * M_PI / 2), rotate);
            window.draw(lines.PartOfFigure());
        }
        window.draw(SolidFigures::createCircle(rad, x0, y0));
        window.draw(SolidFigures::createDiamond(rad * 2, x0, y0, rotate));
        window.draw(SolidFigures::StarShape(rad, x0, y0, rotate));
    }
};

class Controller {
public:
    static void WinShow(RenderWindow& window, int x0, int y0, double rad, double alpha) {
        while (window.isOpen()) {
            Controller controller;
            Event event{};
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
            }

            window.clear(Color::Black);

            controller.Movement(x0, y0, rad, alpha);

            Drawing(window, x0, y0, rad, alpha);
            window.display();
        }
    }

    void Movement(int& x, int& y, double& rad, double& rotate) const {
        if(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) y -= step;
        if(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) y += step;
        if(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) x -= step;
        if(Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) x += step;

        if (Keyboard::isKeyPressed(Keyboard::E)) rotate += rotation_angle;
        if (Keyboard::isKeyPressed(Keyboard::Q)) rotate -= rotation_angle;

        if (Keyboard::isKeyPressed(Keyboard::J)) rad += radius_step;
        if (Keyboard::isKeyPressed(Keyboard::K)) rad -= radius_step;

        if (Keyboard::isKeyPressed(Keyboard::R)) {
            rad = base_radius;
            x = base_x;
            y = base_y;
            rotate = base_angle;
        }
    }

private:
    int step = 3;
    double rotation_angle = M_PI / 180;
    double radius_step = 1;
    int base_x = 800, base_y = 450;
    double base_angle = 0;
    double base_radius = 100.f;
};

int main() {
    constexpr int width  = 1600, height = 900;
    double rad = 100.f;
    int x0 = width / 2, y0 = height / 2;
    double alpha = 0;

    ContextSettings settings;
    settings.antialiasingLevel = 16;

    RenderWindow window(VideoMode(width, height), "SFML_Lab1", Style::Default, settings);

    Controller::WinShow(window, x0, y0, rad, alpha);
}