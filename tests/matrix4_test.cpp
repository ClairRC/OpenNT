#include <cassert>
#include <cmath>
#include "math_stuff/matrix4.h"

void testInverse() {
    float data[] = {
        1, 5, 3, 2,
        -1, 4, 6, -4,
        1, 6, 5, -3,
        6, 5, 4, 1
    };
    Math::Matrix4 test1(data);
    Math::Matrix4 test2(test1.inverse());

    float* test2Dat = test2.getDataPointer();
    float expected[] = {
        -0.166667, -0.06173, 0.03086, 0.17901,
        0.083333, -0.28395, 0.391975, -0.12654,
        0.083333, 0.419753, -0.45987, 0.132716,
        0.25, 0.111111, -0.305555, 0.027777
    };

    for (int i = 0; i < 15; ++i) {
        // Since its floating point, this checks if its within 0.1%
        assert(abs(test2Dat[i] - expected[i]) <= abs(expected[i]/1000));
    }
}

void testDeterminant() {
    float data[] = {
        1, 5, 3, 2,
        -1, 4, 6, -4,
        1, 6, 5, -3,
        6, 5, 4, 1
    };

    Math::Matrix4 test1(data);
    float determinant = test1.getDeterminant();

    assert(determinant == 324);
}

void testTranspose() {
    float data[] = {
        1, 5, 3, 2,
        -1, 4, 6, -4,
        1, 6, 5, -3,
        6, 5, 4, 1
    };

    Math::Matrix4 test1(data);
    Math::Matrix4 test2 = test1.transpose();

    float* test2Dat = test2.getDataPointer();
    float expected[] {
        1, -1, 1, 6, 
        5, 4, 6, 5,
        3, 6, 5, 4, 
        2, -4, -3, 1
    };

    for (int i = 0; i < 15; ++i) {
        assert(test2Dat[i] == expected[i]);
    }
}

int main() {
    printf("Testing Inverse\n");
    testInverse();
    printf("Inverse Passed!\n\n");

    printf("Testing Determinant\n");
    testDeterminant();
    printf("Determinant Passed!\n\n");

    printf("Testing Transpose\n");
    testTranspose();
    printf("Transpose Passed!\n\n");

    printf("All tests passed!\n");

    return 0;
}

//Again, this will give me lots of errors if I don't have this
//Its fiine I'll fix it though this is just for the prototype example anyway
void gameLoop() {}