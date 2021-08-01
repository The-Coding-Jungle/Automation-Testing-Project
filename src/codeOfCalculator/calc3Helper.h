#include <math.h>

float absoluteDifference(float a, float b) {
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int aPowerB(float a, float b) {
    int a1 = (int)a, b1 = (int)b;
    if (b1 == 1) {
        return a1;
    } else if (b1 == 0) {
        return 1;
    } else if (b1 % 2 == 1) {
        return aPowerB(a1, b1/2) * aPowerB(a1, b1/2) * a1;
    } else {
        return aPowerB(a1, b1/2) * aPowerB(a1, b1/2);
    }
}

float squareRoot(float a) {
    // We assume that a is positive.
    return sqrt(a);
}
