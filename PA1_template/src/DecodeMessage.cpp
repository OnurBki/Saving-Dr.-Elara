// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binary_string = "";
    for (std::pair<int, int> pr : edgePixels) {
        int pixel_value = static_cast<int>(image.get_data(pr.first, pr.second));

        std::string binary_value = ((pixel_value & 1) == 0 ? "0" : "1");
        binary_string += binary_value;
    }

    // Ensure binary_string's length is a multiple of 7 by padding with zeros if necessary
    int padding = 7 - (binary_string.length() % 7);
    for (int i = 0; i < padding; i++) {
        binary_string = "0" + binary_string;
    }

    std::string decoded_message = "";
    int n = binary_string.length();
    for (size_t i = 0; i < n; i += 7) {
        std::string segment = binary_string.substr(i, 7);

        int decimalValue = 0;
        int base = 1; // Initialize base value to 1

        // Traverse the binary string from right to left
        for (int j = segment.size() - 1; j >= 0; j--) {
            if (segment[j] == '1') {
                decimalValue += base; // Add the current bit's contribution to the decimal value
            }
            base *= 2; // Move to the next bit position
        }

        if (decimalValue <= 32) {
            decimalValue += 33;
        } else if (decimalValue >= 127) {
            decimalValue = 126;
        }

        decoded_message += static_cast<char>(decimalValue);
    }

    return decoded_message;
}

