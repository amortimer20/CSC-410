#include <stdio.h>

#define N 2140000000 // intervals

double f(double x) {
    return 4.0 / (1.0 + x * x); // Function to integrate
}

double trapezoidalRule() 
{
    double a = 0;
    double b = 1;
    double h = (b - a) / N;
    double sum = f(a) + f(b);

    for (int i = 1; i < N; i++)
    {
        sum += 2 * f(a + i * h);
    }
    
    return sum * h / 2;
}

int main() {
    double pi = trapezoidalRule();
    printf("Estimated value of π: %f\n", pi);
    return 0;
}
