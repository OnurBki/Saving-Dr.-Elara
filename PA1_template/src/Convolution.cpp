#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
    height = 0;
    width = 0;
    stride = 1;
    padding = false;
    kernel = nullptr;
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad) : height(kh),
width(kw), stride(stride_val), padding(pad) {
    // Allocate memory for the kernel
    kernel = new double*[height];
    for (int i = 0; i < height; ++i) {
        kernel[i] = new double[width];
    }

    // Copy data from customKernel to kernel
    for (int i = 0; i < kh; ++i) {
        for (int j = 0; j < kw; j++) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] kernel[i]; // Release memory for each row of a kernel
        }

        delete[] kernel; // Release memory for the array of row pointers of a kernel
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    height = other.height;
    width = other.width;
    stride = other.stride;
    padding = other.padding;

    // Allocate memory for the kernel
    kernel = new double*[height];
    for (int i = 0; i < height; ++i) {
        kernel[i] = new double[width];
    }

    // Copy data from other kernel to kernel
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; // Avoid self-assignment
    }

    // Release the current data
    if (kernel != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] kernel[i]; // Release memory for each row of a kernel
        }

        delete[] kernel; // Release memory for the array of row pointers of a kernel
    }

    // Copy data from 'other' to 'this'
    height = other.height;
    width = other.width;
    stride = other.stride;
    padding = other.padding;
    kernel = new double*[height];
    for (int i = 0; i < height; i++) {
        kernel[i] = new double [width];
        for (int j = 0; j < width; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int image_height = (input_image.get_height() + (padding ? 2 : 0));
    int image_width = (input_image.get_width() + (padding ? 2 : 0));

    // Calculate the dimensions of the result matrix
    int result_height = (image_height - height) / stride + 1;
    int result_width = (image_width - width) / stride + 1;

    ImageMatrix copy_input_image(image_height, image_width);

    if (padding) {
        ImageMatrix::padding(input_image, copy_input_image); // Padded image
    } else {
        copy_input_image = input_image;
    }

    ImageMatrix result_matrix(result_height, result_width);

    for (int i = 0; i < result_matrix.get_height(); ++i) {
        for (int j = 0; j < result_matrix.get_width(); ++j) {
            double sum = 0;

            for (int k = 0; k < height; ++k) {
                for (int l = 0; l < width; ++l) {
                    int imgI = i*stride + k;
                    int imgJ = j*stride + l;

                    sum += static_cast<double > (kernel[k][l] * copy_input_image.get_data(imgI, imgJ));
                }
            }

            result_matrix.set_data(i, j, sum);
        }
    }

    return result_matrix;
}
