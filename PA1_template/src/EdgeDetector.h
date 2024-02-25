    #ifndef EDGE_DETECTOR_H
    #define EDGE_DETECTOR_H

    #include "ImageMatrix.h"
    #include "Convolution.h"
    #include <vector>

    class EdgeDetector {
        public:
            EdgeDetector(); 
            ~EdgeDetector(); 
            
            std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

        private:
            int gradient_height;
            int gradient_width;
            int gradient_stride;
            bool gradient_padding;
            double** gradient_x;
            double** gradient_y;
    };

    #endif // EDGE_DETECTOR_H


