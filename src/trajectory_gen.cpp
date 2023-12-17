#include <iostream>
#include <cmath>
#include <fstream>
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
    MatrixXd pos(4, num_steps);
    pos.row(0) = t.transpose();
    pos.row(1) = x.transpose();
    pos.row(2) = y.transpose();
    pos.row(3) = psi.transpose();
    //remove 1st row
    pos.leftCols(pos.cols() - 1) = pos.rightCols(pos.cols() - 1);

    VectorXd time_vel = t.tail(t.size() - 1);
    MatrixXd vel(4, num_steps - 1);
    vel.row(0) = time_vel.transpose();
    vel.row(1) = x_dot.transpose();
    vel.row(2) = y_dot.transpose();
    vel.row(3) = psi_dot.transpose();
    //remove 1st row
     vel.leftCols(vel.cols() - 1) = vel.rightCols(vel.cols() - 1);



    std::cout << "the vector x_dot has dimension: " << vel.rows() << vel.cols() << std::endl;

    pos.transposeInPlace();
    vel.transposeInPlace();

    // Save to file (you can use Eigen's IO functions or other libraries)
 //   pos.transpose().array().colwise() -= pos.rowwise().mean().array();
//    vel.transpose().array().colwise() -= vel.rowwise().mean().array();


    // Save to a file or use other visualization tools
    // ...

    std::cout << "Trajectory data saved to file." << std::endl;

    // Open a file for writing
    std::ofstream PosFile("pos.txt");
    
    if (PosFile.is_open()) {
        // Write the matrix to the file
        PosFile << pos << std::endl;

        // Close the file
        PosFile.close();

        std::cout << "Matrix written to coordinates.txt" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }

    std::ofstream VelFile("vel.txt");
    if (VelFile.is_open()) {
        // Write the matrix to the file
        VelFile << vel << std::endl;

        // Close the file
        VelFile.close();

        std::cout << "Matrix written to coordinates.txt" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }

}


int main() {
    generate_trajectory();
    return 0;
}
