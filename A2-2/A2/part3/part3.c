#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**
 * in this part of the assignment, you will be converting
 * a half-precision floating using an IEEE754 representation
 * to its decimal equivalent. You will have to account for
 * normalized, denormalized, and special cases.
 * +-+-----+----------+
 * |S|EEEEE|FFFFFFFFFF| <- representation of a half precision float 
 * +-+-----+----------+
 * 
 * example input:
 * ./floattoIEEE754 001110000000000000
 * output:
 * 0.50000000
 *
 * you'll only have to print out eight decimal places.
 * printf("%.xxLf", myLongdouble) will let you print myLongdouble to 
 * xx decimal places. 
 *
 * USE GOTO statements.
 *
 * I highly recommend splitting your code into different functions for
 * cleanliness, and to make troubleshooting easier. Don't use recursion.
 *
 * you may use strtol() ```man 3 strtol```
 *
 */



//Don't change these macros for this assignment.
//If you want to experiment with different EXP and
//FRAC for practice, you can, when compiling, use:
//-DEXP=XX, defines EXP as XX, and -DFRAC=XX, defining
//FRAC as XX
#ifndef EXP
    #define EXP 5
#endif

#ifndef FRAC
    #define FRAC 10
#endif

#define BIAS ((1 << (EXP - 1)) - 1)


int isValidBinary(const char *str) {
    int i = 0;
check_next:
    if (str[i] == '\0') return 1;
    if (str[i] != '0' && str[i] != '1') return -1;
    i++;
    goto check_next;
}

void toDecimal(const char *ieee754String) {
    unsigned long ieeeNumber = strtoul(ieee754String, NULL, 2);
    unsigned int sign = ieeeNumber >> (EXP + FRAC);
    unsigned int exponent = (ieeeNumber >> FRAC) & ((1 << EXP) - 1);
    unsigned long fraction = ieeeNumber & ((1 << FRAC) - 1);
    long double value;

    if (exponent == 0 && fraction == 0) {
        printf(sign ? "-0.00000000\n" : "0.00000000\n");
        return;
    }

    if (exponent == 0) {
        value = (long double)fraction / (1L << FRAC) * powl(2, 1 - BIAS);
        goto print_value;
    }

    if (exponent == (1 << EXP) - 1 && fraction == 0) {
        printf(sign ? "-infinity\n" : "+infinity\n");
        return;
    }

    if (exponent == (1 << EXP) - 1) {
        printf("NaN\n");
        return;
    }

    value = (1 + (long double)fraction / (1L << FRAC)) * powl(2, exponent - BIAS);

print_value:
    printf("%.8Lf\n", value * (sign ? -1.0 : 1.0));
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./program <IEEE754 string>\n");
        return 1;
    }

    if (isValidBinary(argv[1]) != 1) {
        printf("invalid binary format\n");
        return 1;
    }

    if (strlen(argv[1]) != 1 + EXP + FRAC) {
        printf("insert IEEE754 string with length >= 16\n");
        return 1;
    }

    toDecimal(argv[1]);
    return 0;
}