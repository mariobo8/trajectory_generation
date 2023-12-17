import os
import numpy as np
import matplotlib.pyplot as plt

def read_matrix_from_file(file_path):
    # Read the matrix from the text file
    matrix = np.loadtxt(file_path)
    return matrix

def plot_matrix(matrix, title):
    # Extract x, y, z values
    time = matrix[:, 0]
    x = matrix[:, 1]
    y = matrix[:, 2]
    psi = matrix[:, 3]

    # Plot the matrix of positions
    plt.figure(figsize=(10, 6))
    plt.plot(time, x, label='X')
    plt.plot(time, y, label='Y')
    plt.plot(time, psi, label='PSI')

    # Add labels and title
    plt.xlabel('Time')
    plt.ylabel('Value')
    plt.title('Plot of X, Y, and PSI over Time')

    plt.show()


if __name__ == "__main__":

    file_path1 = "/Users/mariobozza/Desktop/trajectory_generation/pos.txt"
    if os.path.exists(file_path1):
        print("File1 exists!")
    else:
        print("File1 not found.")

    file_path2 = "/Users/mariobozza/Desktop/trajectory_generation/vel.txt"
    if os.path.exists(file_path2):
        print("File2 exists!")
    else:
        print("File2 not found.")


    
    # Read matrices from files
    matrix1 = read_matrix_from_file(file_path1)
    matrix2 = read_matrix_from_file(file_path2)

    # Plot matrices
    plot_matrix(matrix1, 'pos')
    plot_matrix(matrix2, 'vel')
