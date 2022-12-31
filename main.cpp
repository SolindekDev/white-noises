#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#define  STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define  STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int random_number(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max); // distribution in range [1, 6]
    return dist6(rng);
}

void putpixel(unsigned char* data, int x, int y, int r, int g, int b, int width) {
    data[((x + y * width) * 3 + 0)] = r;
    data[((x + y * width) * 3 + 1)] = g;
    data[((x + y * width) * 3 + 2)] = b;
}

void generate_white_noises(unsigned char* data, int width, int height) {
    int rand, r, g, b;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            rand = random_number(0, 255);
            r = rand;
            g = rand;
            b = rand;

            putpixel(data, x, y, r, g, b, width);
        }
    }
}

void create_image(char* image_path, int width, int height) {
    unsigned char* image_data = (unsigned char*)malloc(width * height * 3); 
    
    generate_white_noises(image_data, width, height);
    stbi_write_png(image_path, width, height, 3, image_data, width * 3);
    free(image_data);
}

int main(int argc, char** argv) {
    (void)*argv++;

    if (argc < 2) {
        std::cout << "Example use of this program: white_noises [output.png] " << std::endl;
        return 1;
    }

    // TODO: implement argument that will specifie the png size so it's not hardcoded
    char* output_image_path = *argv++;
    create_image(output_image_path, 128, 128);

    return 0;
}