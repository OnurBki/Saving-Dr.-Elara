#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageMatrix sharpened_image = (new ImageSharpening) -> sharpen(img, 2);
    std::string message = (new DecodeMessage) -> decodeFromImage(sharpened_image, (new EdgeDetector) -> detectEdges(sharpened_image));

    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {

}
