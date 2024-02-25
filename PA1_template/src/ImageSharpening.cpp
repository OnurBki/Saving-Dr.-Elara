#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    kernel_height = 3;
    kernel_width = 3;
    kernel_stride = 1;
    kernel_padding = true;

    // Allocate memory for the kernel
    blurring_kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        blurring_kernel[i] = new double[kernel_width];
    }

    // Copy data from customKernel to kernel
    for (int i = 0; i < kernel_height; ++i) {
        for (int j = 0; j < kernel_width; j++) {
            blurring_kernel[i][j] = 1.0 / 9.0;
        }
    }
}

ImageSharpening::~ImageSharpening(){
    if (blurring_kernel != nullptr) {
        for (int i = 0; i < kernel_height; ++i) {
            delete[] blurring_kernel[i]; // Release memory for each row of a kernel
        }

        delete[] blurring_kernel; // Release memory for the array of row pointers of a kernel
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    Convolution noisy_kernel(blurring_kernel, kernel_height,
                            kernel_width, kernel_stride, kernel_padding);

    ImageMatrix noisy_image(noisy_kernel.convolve(input_image));
    ImageMatrix sharpened_image(input_image + ((input_image - noisy_image) * k));

    for (int i = 0; i < sharpened_image.get_height(); ++i) {
        for (int j = 0; j < sharpened_image.get_width(); ++j) {
            if (sharpened_image.get_data(i, j) < 0.0) {
                sharpened_image.set_data(i, j, 0.0);
            } else if (sharpened_image.get_data(i, j) > 255.0) {
                sharpened_image.set_data(i, j, 255.0);
            }
        }
    }

    return sharpened_image;
}
