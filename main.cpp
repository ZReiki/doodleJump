/*#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Point {
    int x;
    int y;
};

class LineShape {
public:
    LineShape(int count, float circleRadius, float alpha, int x0, int y0, Color color) : count(count), color(color) {   // конструктор
        points = new Point[count];

        // Cube lines
        points[0] = {x0, y0};
        points[1] = {(int)(x0 + 2 * circleRadius * cos(alpha + 3 * M_PI / 2)),
                     (int)(y0 + 2 * circleRadius * sin(alpha + 3 * M_PI / 2))};
        points[2] = {(int)(points[1].x + circleRadius / 2 * cos(alpha + 5 * M_PI / 4)),
                     (int)(points[1].y + circleRadius / 2 * sin(alpha + 5 * M_PI / 4))};
        points[3] = {(int)(points[2].x + circleRadius / 2 * cos(alpha + 7 * M_PI / 4)),
                     (int)(points[2].y + circleRadius / 2 * sin(alpha + 7 * M_PI / 4))};
        points[4] = {(int)(points[3].x + circleRadius / 2 * cos(alpha + M_PI / 4)),
                     (int)(points[3].y + circleRadius / 2 * sin(alpha + M_PI / 4))};
        points[5] = {points[1].x, points[1].y};

        // Triangle lines
        points[6] = {x0, y0};
        points[7] = {(int)(points[6].x + (2 * circleRadius + 20) * cos(alpha + 7 * M_PI / 4)),
                     (int)(points[6].y + (2 * circleRadius + 20) * sin(alpha + 7 * M_PI / 4))};
        points[8] = {(int)(points[7].x + circleRadius * cos(alpha + 3 * M_PI / 2)),
                     (int)(points[7].y + circleRadius * sin(alpha + 3 * M_PI / 2))};
        points[9] = {(int)(points[8].x + sqrt(2 * pow(circleRadius, 2)) * cos(alpha + M_PI / 4)),
                     (int)(points[8].y + sqrt(2 * pow(circleRadius, 2)) * sin(alpha + M_PI / 4))};
        points[10] = {points[7].x, points[7].y};
    }

    ~LineShape() {                                                                                                      // деструктор
        delete[] points;
    }

    [[nodiscard]] VertexArray toVertexArray() const {                                                                   //
        VertexArray curve(LinesStrip, 0);
        for (int i = 0; i < count; i++) {
            curve.append(Vertex(Vector2f((float)points[i].x, (float)points[i].y), color));
        }
        return curve;
    }

private:
    Point* points;
    int count;
    Color color;

};

class StarShape {
public:
    StarShape(float circleRadius, float alpha, int x0, int y0) {
        curve.setPrimitiveType(LinesStrip);

        int count = 100;
        float t;

        const float angle = M_PI / 4;
        const float cosAngle = cos(angle);
        const float sinAngle = sin(angle);

        for (int i = 0; i <= count; ++i) {
            t = i * 2 * M_PI / count;
            float x = pow(cos(t + M_PI / 4), 3) * 2 * circleRadius;
            float y = pow(sin(t + M_PI / 4), 3) * 2 * circleRadius;

            float rotatedX = x * cosAngle - y * sinAngle;
            float rotatedY = x * sinAngle + y * cosAngle;

            curve.append(Vertex(Vector2f(float(x0) + rotatedX, float(y0) - rotatedY)));
        }
    }

    [[nodiscard]] VertexArray getCurve() const {
        return curve;
    }

private:
    VertexArray curve;
};

class ShapeFactory {
public:
    static CircleShape createCircle(float circleRadius, int width, int height) {
        CircleShape circle(circleRadius);
        circle.setPosition((float)width / 2 - circleRadius, (float)height / 2 - circleRadius);
        circle.setFillColor(Color::Transparent);
        circle.setOutlineColor(Color::White);
        circle.setOutlineThickness(1);
        return circle;
    }

    static CircleShape createDiamond(float circleRadius, int width, int height) {
        CircleShape diamond(circleRadius, 4);
        diamond.setPosition((float)width / 2 - circleRadius, (float)height / 2 - circleRadius);
        diamond.setFillColor(Color::Transparent);
        diamond.setOutlineColor(Color::White);
        diamond.setOutlineThickness(1);
        return diamond;
    }
};

class Figure {
public:
    Figure(VertexArray line1, VertexArray line2, VertexArray line3, VertexArray line4) {
        figure.push_back(line1);
        figure.push_back(line2);
        figure.push_back(line3);
        figure.push_back(line4);
        return figure;
    }
private:
    vector<auto> figure{};
};

int main() {
    const int width = 800, height = 800;
    constexpr float circleRadius = 125.f;
    constexpr int x0 = width / 2, y0 = height / 2;
    constexpr int count = 11;

    Color color = Color::White;

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(width, height), "SFML_Lab1", Style::Default, settings);

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);

        LineShape line1(count, circleRadius, 0, x0, y0, color);
        window.draw(line1.toVertexArray());

        LineShape line2(count, circleRadius, M_PI / 2, x0, y0, color);
        window.draw(line2.toVertexArray());

        LineShape line3(count, circleRadius, M_PI, x0, y0, color);
        window.draw(line3.toVertexArray());

        LineShape line4(count, circleRadius, 3 * M_PI / 2, x0, y0, color);
        window.draw(line4.toVertexArray());

        // auto figure = Figure(line1.toVertexArray(), line2.toVertexArray(), line3.toVertexArray(), line4.toVertexArray());
        // window.draw(figure);

        StarShape curve(circleRadius + 10, M_PI, x0, y0);
        window.draw(curve.getCurve());

        window.draw(ShapeFactory::createCircle(circleRadius, width, height));
        window.draw(ShapeFactory::createDiamond(circleRadius * 2, width, height));

        window.display();
    }
}
*/