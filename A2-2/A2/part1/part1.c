#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * C does include a pow function, but it returns
 * a float value. Unfortunately, converting from
 * a float too long/int can lead to precision
 * issues. For this reason, you'll be asked to 
 * implement a custom pow function. make sure to
 * handle 2^0 :-)
 *
 * example input:
 *  mathpow(3,2)
 *  return value:
 *  9
 *
 *  Use goto statements
 */
long mathpow(int base, int exp){
  long result = 1;
    if (exp == 0) return 1;

    calculate_power:
        result *= base;
        exp--;
        if (exp > 0) goto calculate_power;

    return result;
}
/**
 * Part one - Binary to Decimal conversion:
 * In this part of the assignment, you will
 * convert a binary string to it's signed
 * or unsigned decimal representation. assume twos
 * complement for this representation
 * 
 * example input:
 * ./part1 11111111 1
 * output:
 * -1
 *
 * YOU MAY NOT USE STRTOL FOR THIS!
 *
 * one more thing:
 *
 * YOU MUST USE GOTO statements, no loops, else if, else.
 */
int main(int argc, char** argv){
    if (argc != 3){
        printf("./binarytodec {binary string} {1 for signed, 0 for unsigned}\n");
        return 1;
    }

    char* binaryString = argv[1];
    int isSigned = atoi(argv[2]);
    int length = strlen(binaryString);
    long decimalValue = 0;
    int position = 0;

    validate_input:
        if (binaryString[position] < '0' || binaryString[position] > '1') {
            printf("invalid binary string\n");
            return 1;
        }
        position++;
        if (position < length) goto validate_input;

    position = 0;
    int isNegative = (isSigned && binaryString[0] == '1');

    convert_to_decimal:
        decimalValue += (binaryString[length - position - 1] - '0') * mathpow(2, position);
        position++;
        if (position < length) goto convert_to_decimal;

    if (isSigned && isNegative) {
        decimalValue -= mathpow(2, length);
    }

    printf("%ld\n", decimalValue);

    return 0;
}
