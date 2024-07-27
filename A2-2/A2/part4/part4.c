#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

int first_set_bit(int i) {
    if (i == 0) {
        return -1;
    }

    for (int bitIndex = 0; bitIndex < 32; ++bitIndex) {
        if (i & (1 << bitIndex)) {
            return bitIndex;
        }
    }
	
    return -1;
}

int main(int argc, char** argv) {
	if (argc != 2) { 
		fprintf(stderr, "Usage: ./firstsetbit INTEGER");
		return 1;
	}
	printf("%d\n", first_set_bit(atoi(argv[1])));
}
