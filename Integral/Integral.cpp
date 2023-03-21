#include <clocale>
#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return ((9 + (x * x)) / ((x * x * x) +6.8272 * x * x + 5.3272));
}

int Integration(double a, double b, int n, string wayToCalculate, double* address) {
    *address = 0.0;

    double h = (b - a) / (double)n;

    int i;
    double x;

    if (wayToCalculate == "LeftRectangle") {
        for (i = 0, x = a; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    }
    else if (wayToCalculate == "MiddleRectangle") {
        for (i = 0, x = a + h / 2.0; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    }
    else if (wayToCalculate == "RightRectangle") {
        for (i = 0, x = b; i <= n - 1; i++, x -= h) {
            *address += f(x);
        }
        *address *= h;
    }
    else if (wayToCalculate == "Trapezoid") {
        *address += (f(a) + f(b)) / 2.0;
        for (i = 1, x = a + h; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    }
    else if (wayToCalculate == "Parabola") {
        *address = f(a) + f(b);
        for (i = 1, x = a + h; i <= n - 1; i++, x += h) {
            if (i % 2 == 0) *address += 2.0 * f(x);
            if (i % 2 == 1) *address += 4.0 * f(x);
        }
        *address *= h / 3.0;
    }
    else {
        return -1;
    }

    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a = 0;
    double b = 2.5;

    int n = 5;

    int errorCode;
    double result;

    errorCode = Integration(a, b, n, "LeftRectangle", &result);
    if (errorCode == 0) printf("LeftRectangle:   %.4f\n", result);

    errorCode = Integration(a, b, n, "MiddleRectangle", &result);
    if (errorCode == 0) printf("MiddleRectangle: %.4f\n", result);

    errorCode = Integration(a, b, n, "RightRectangle", &result);
    if (errorCode == 0) printf("RightRectangle:  %.4f\n", result);

    errorCode = Integration(a, b, n, "Trapezoid", &result);
    if (errorCode == 0) printf("Trapezoid:               %.4f\n", result);

    errorCode = Integration(a, b, 2 * n, "Parabola", &result);
    if (errorCode == 0) printf("Parabola:               %.4f\n", result);

    double test = 3.0 / 1000.0;
    printf("test = %f\n", test);

    return 0;
}