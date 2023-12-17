#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

void generate_trajectory() {
    // Define parameters for the S-shaped path
    double amplitude = 20;      // Amplitude of the S-shape
    double frequency = 0.1;     // Frequency of the S-shape
    double time_interval = 10;  // Total time interval for the path
    double dt = 0.01;           // Time step

    // Generate the S-shaped path
    int num_steps = static_cast<int>(time_interval / dt) + 1;
    VectorXd t = VectorXd::LinSpaced(num_steps, 0, time_interval);
    
    VectorXd x = amplitude * (2 * M_PI * frequency * t).array().sin();
    VectorXd y = amplitude * (4 * M_PI * frequency * t).array().sin();
    VectorXd psi = (y.array() / x.array()).atan();

    // Calculate velocities
    VectorXd x_dot = (x.tail(num_steps - 1) - x.head(num_steps - 1)) / dt;
    VectorXd y_dot = (y.tail(num_steps - 1) - y.head(num_steps - 1)) / dt;
    VectorXd psi_dot = (psi.tail(num_steps - 1) - psi.head(num_steps - 1)) / dt;

    // Save the path, velocities, and heading to a file
    MatrixXd pos(3, num_steps);
    pos << x, y, psi;
    MatrixXd vel(3, num_steps - 1);
    vel << x_dot, y_dot, psi_dot;

    pos.transposeInPlace();
    vel.transposeInPlace();

    // Save to file (you can use Eigen's IO functions or other libraries)
    pos.transpose().array().colwise() -= pos.rowwise().mean().array();
    vel.transpose().array().colwise() -= vel.rowwise().mean().array();

    // Save to a file or use other visualization tools
    // ...

    std::cout << "Trajectory data saved to file." << std::endl;
}

int main() {
    generate_trajectory();
    return 0;
}
