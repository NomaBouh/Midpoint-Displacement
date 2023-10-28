#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Paramètres
const float ROUGHNESS = 0.5f;

// Structure pour définir un point
struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
};

// Fonction de déplacement du point médian
void midpointDisplacement(std::vector<Point>& points, int iterations) {
    if (iterations == 0) return;

    std::vector<Point> newPoints;

    for (size_t i = 0; i < points.size() - 1; i++) {
        Point start = points[i];
        Point end = points[i + 1];

        Point midpoint((start.x + end.x) / 2.0f, (start.y + end.y) / 2.0f);
        float displacement = (rand() % 2000 - 1000) / 1000.0f * ROUGHNESS / iterations;
        midpoint.y += displacement;

        newPoints.push_back(start);
        newPoints.push_back(midpoint);
    }
    newPoints.push_back(points.back());

    points = newPoints;
    midpointDisplacement(points, iterations - 1);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Midpoint Displacement", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    std::vector<Point> points = { Point(0, 0.5), Point(1, 0.5) };
    int iterations = 6;  // À ajuster selon le besoin
    srand(time(nullptr)); // Initialisation du générateur de nombres aléatoires
    midpointDisplacement(points, iterations);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINE_STRIP);
        for (const Point& p : points) {
            glVertex2f(p.x * 2 - 1, p.y * 2 - 1);  // Conversion pour ajuster les coordonnées à [-1, 1]
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
