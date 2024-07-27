#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/**
 * PART ZWEI
 * In this part, you'll check if an IEEE 754 string
 * is normalized, denormalized, or is a special case. check
 * the writeup and autograder for expected values. 
 */
int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: ./part2 <IEEE754 string>\n");
        return EXIT_FAILURE;
    }

    char* binaryString = argv[1];
    int length = strlen(binaryString);

    for (int i = 0; i < length; ++i) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            printf("invalid format\n");
            return EXIT_FAILURE;
        }
    }

    if (length != 16) {
        printf("must be 16 bits\n");
        return EXIT_FAILURE;
    }

    unsigned long ieeeNumber = strtoul(binaryString, NULL, 2);
    unsigned int exponent = (ieeeNumber >> 10) & 0x1F;
    unsigned int fraction = ieeeNumber & 0x3FF;

    if (exponent == 0x1F) {
        printf("This value is a special case\n");
        return EXIT_SUCCESS;
    }

    if (exponent == 0) {
        printf("This value is denormalized\n");
        return EXIT_SUCCESS;
    }

    printf("This value is normalized\n");

    return EXIT_SUCCESS;
}
