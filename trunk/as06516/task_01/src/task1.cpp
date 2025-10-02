#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Simulate linear model
std::vector<double> simulateLinear(double a, double b,
                                   const std::vector<double>& u,
                                   double y0)
{
    std::vector<double> y(u.size() + 1, 0.0);
    y[0] = y0;

    for (size_t t = 0; t < u.size(); ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

// Simulate nonlinear model
std::vector<double> simulateNonlinear(double a, double b, double c, double d,
                                      const std::vector<double>& u,
                                      double y0, double yPrev)
{
    std::vector<double> y(u.size() + 1, 0.0);
    y[0] = y0;

    double y_minus1 = yPrev;

    for (size_t t = 0; t < u.size(); ++t) {
        double u_prev = (t == 0 ? 0.0 : u[t - 1]);

        y[t + 1] = a * y[t] - b * y_minus1 * y_minus1
                   + c * u[t] + d * std::sin(u_prev);

        // Update previous y
        y_minus1 = y[t];
    }

    return y;
}

int main() {
    // Constants
    double a = 0.8;
    double b = 0.1;
    double c = 0.05;
    double d = 0.02;

    int steps = 20;          // number of time steps
    double y0 = 20.0;        // initial temperature
    double yPrev = 19.5;     // previous temperature for nonlinear model

    // Control input (constant heating = 5.0)
    std::vector<double> u(steps, 5.0);

    // Run simulations
    auto yLinear = simulateLinear(a, b, u, y0);
    auto yNonlinear = simulateNonlinear(a, b, c, d, u, y0, yPrev);

    // Print results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step\tLinear\tNonlinear\n";
    for (int t = 0; t <= steps; ++t) {
        std::cout << t << "\t" << yLinear[t] << "\t" << yNonlinear[t] << "\n";
    }

    return 0;
}
