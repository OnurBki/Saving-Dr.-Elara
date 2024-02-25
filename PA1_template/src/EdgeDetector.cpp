// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    gradient_height = 3;
    gradient_width = 3;
    gradient_stride = 1;
    gradient_padding = true;

    // Allocate memory for the gradient_x
    gradient_x = new double*[gradient_height];
    for (int i = 0; i < gradient_height; ++i) {
        gradient_x[i] = new double[gradient_width];
    }

    double* gradient_x_data[3] = {
            new double[3]{-1.0, 0.0, 1.0},
            new double[3]{-2.0, 0.0, 2.0},
            new double[3]{-1.0, 0.0, 1.0}
    };

    // Copy data from customKernel to gradient_x
    for (int i = 0; i < gradient_height; ++i) {
        for (int j = 0; j < gradient_width; j++) {
            gradient_x[i][j] = gradient_x_data[i][j];
        }
    }

    // Allocate memory for the gradient_y
    gradient_y = new double*[gradient_height];
    for (int i = 0; i < gradient_height; ++i) {
        gradient_y[i] = new double[gradient_width];
    }

    double* gradient_y_data[3] = {
            new double[3]{-1.0, -2.0, -1.0},
            new double[3]{0.0, 0.0, 0.0},
            new double[3]{1.0, 2.0, 1.0}
    };

    // Copy data from customKernel to gradient_y
    for (int i = 0; i < gradient_height; ++i) {
        for (int j = 0; j < gradient_width; j++) {
            gradient_y[i][j] = gradient_y_data[i][j];
        }
    }
}

// Destructor
EdgeDetector::~EdgeDetector() {
    if (gradient_x != nullptr) {
        for (int i = 0; i < gradient_height; ++i) {
            delete[] gradient_x[i]; // Release memory for each row of a gradient_x
        }

        delete[] gradient_x; // Release memory for the array of row pointers of a gradient_x
    }

    if (gradient_y != nullptr) {
        for (int i = 0; i < gradient_height; ++i) {
            delete[] gradient_y[i]; // Release memory for each row of a gradient_y
        }

        delete[] gradient_y; // Release memory for the array of row pointers of a gradient_y
    }
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    Convolution x_kernel(gradient_x, gradient_height,
                             gradient_width, gradient_stride, gradient_padding);
    Convolution y_kernel(gradient_y, gradient_height,
                         gradient_width, gradient_stride, gradient_padding);

    ImageMatrix x_convolved(x_kernel.convolve(input_image));
    ImageMatrix y_convolved(y_kernel.convolve(input_image));

    ImageMatrix gradient_magnitude(x_convolved.get_height(), x_convolved.get_width());

    double sum = 0;
    for (int i = 0; i < gradient_magnitude.get_height(); ++i) {
        for (int j = 0; j < gradient_magnitude.get_width(); ++j) {
            double result = sqrt(pow(x_convolved.get_data(i, j), 2) + pow(y_convolved.get_data(i, j), 2));
            gradient_magnitude.set_data(i, j, result);

            sum += gradient_magnitude.get_data(i, j);
        }
    }

    double threshold = sum / (gradient_magnitude.get_height() * gradient_magnitude.get_width());
    std::vector<std::pair<int, int>> edge_indices;
    for (int i = 0; i < gradient_magnitude.get_height(); ++i) {
        for (int j = 0; j < gradient_magnitude.get_width(); ++j) {
            if (gradient_magnitude.get_data(i, j) > threshold) {
                edge_indices.push_back(std::make_pair(i, j));
            }
        }
    }

    return edge_indices;
}

