#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const double PI = 3.141592653589793;
// Base class Triangle
class Triangle {
protected:
    double a, b, c; // sides of the triangle

public:
    // Constructor
    Triangle(double sideA, double sideB, double sideC) {
        a = sideA;
        b = sideB;
        c = sideC;
    }

    // Methods to set sides
    void setSides(double sideA, double sideB, double sideC) {
        a = sideA;
        b = sideB;
        c = sideC;
    }

    // Method to calculate perimeter
    double getPerimeter() const {
        return a + b + c;
    }

    // Method to calculate angles using the cosine rule
    void getAngles(double& A, double& B, double& C) const {
        A = acos((b * b + c * c - a * a) / (2 * b * c)) * 180.0 / PI;
        B = acos((a * a + c * c - b * b) / (2 * a * c)) * 180.0 / PI;
        C = 180.0 - A - B;
    }
};

// Derived class RightAngled
class RightAngled : public Triangle {
private:
    double area;

public:
    // Constructor
    RightAngled(double sideA, double sideB, double sideC)
        : Triangle(sideA, sideB, sideC) {
        if (!isRightAngled()) {
            cout << "Warning: The triangle is not right-angled!" << endl;
        }
    }

    // Check for right-angled triangle
    bool isRightAngled() const {
        double sides[3] = { a, b, c };
        sort(sides, sides + 3);
        return fabs(sides[2] * sides[2] - (sides[0] * sides[0] + sides[1] * sides[1])) < 1e-6;
    }

    // Calculate area
    double getArea() {
        double sides[3] = { a, b, c };
        sort(sides, sides + 3); // sides[2] is hypotenuse
        area = 0.5 * sides[0] * sides[1];
        return area;
    }
};

// Main function
int main() {
    // Create a general triangle
    Triangle t(3, 4, 5);
    double angleA, angleB, angleC;
    t.getAngles(angleA, angleB, angleC);

    cout << "Triangle sides: 3, 4, 5" << endl;
    cout << "Perimeter: " << t.getPerimeter() << endl;
    cout << "Angles (in degrees): A = " << angleA
        << ", B = " << angleB
        << ", C = " << angleC << endl;

    // Create a right-angled triangle
    RightAngled rt(3, 4, 5);
    cout << "\nRight-angled triangle check: "
        << (rt.isRightAngled() ? "Yes" : "No") << endl;
    cout << "Area: " << rt.getArea() << endl;

    return 0;
}