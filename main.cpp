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
    //à compléter
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
