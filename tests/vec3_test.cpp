#include <cassert>
#include "math_stuff/vec3.h"

//I am just including a couple of tests for a couple of classes

//Test cases
void testAdd() {
    Math::Vec3 test1(1, 3, 5);
    Math::Vec3 test2(3, 2, -4);

    Math::Vec3 result = test1 + test2;

    assert(result.x() == 4);
    assert(result.y() == 5);
    assert(result.z() == 1);
}

void testScalarMultiplication() {
    Math::Vec3 test1(1, 2, 3);
    float scalar = 4;
    Math::Vec3 result = test1 * scalar;
    
    assert(result.x() == 4);
    assert(result.y() == 8);
    assert(result.z() == 12);
}

void testCrossProduct() {
    Math::Vec3 test1(3, 1, -5);
    Math::Vec3 test2(9, -1, 4);
    Math::Vec3 result = test1.cross(test2);

    assert(result.x() == -1);
    assert(result.y() == -57);
    assert(result.z() == -12);
}

int main() {
    printf("Testing Addition\n");

    testAdd();

    printf("Addition Passed\n\n");

    printf("Testing Scalar Multiplication\n");

    testScalarMultiplication();

    printf("Scalar Multiplication Passed\n\n");

    printf("Testing Cross Product\n");

    testCrossProduct();

    printf("Cross Product Passed\n\n");

    printf("All tests passed!\n");
}

//This will literally break everything if i don't include it
//i know im bad at this coding stuff ill FIX it eventually
void gameLoop() { };