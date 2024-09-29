#include <math.h>
#include <stdio.h>

unsigned int validateInput(const char* formatSpecifier, void* value) { // pointers to pass by reference not by value
    char input[100]; // Buffer to hold user input

    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, formatSpecifier, value) == 1) {
            return 1; // Successfuly convertes to provided format
        } else {
            printf("\nInvalid input, try again.\n");
        }
    }
}
unsigned int defineVariant() {
    unsigned int variant;
    unsigned int valid;
    while (!valid) {
        printf("\nSelect variant 1 || 2: ");
        if (validateInput("%u", &variant) && (variant == 1 || variant == 2)) {
            valid = 1;
        }
    }
    printf("\nYou selected %u variant.", variant);
    return variant;
}
double defineStartValue() {
    double x1;
    printf("\nType in start value: ");
    validateInput("%lf", &x1);

    return x1;
}
double defineEndValue() {
    double x2;
    printf("\nType in end value: ");
    validateInput("%lf", &x2);
    return x2;
}
void getDeltaOrSteps(unsigned int variant, double* delta, int* numberOfSteps, double x1, double x2) {
    if (variant == 1) {
        printf("\nEnter number of steps:");
        validateInput("%d", numberOfSteps);
        *delta = (x2 - x1) / *numberOfSteps;
    } else if (variant == 2) {
        printf("\nEnter delta:");
        validateInput("%lf", delta);
        *numberOfSteps = (int)((x2 - x1) / *delta);
    } else {
        printf("\nInvalid variant input");
    }
}
void functionOutput(double x1, double delta, int numberOfSteps) {
    unsigned int currentStep = 1;
    double currentX = x1;
    double fX;
    printf("\n******************************************************");
    printf("\n*%5c*%20c*%25s*", 'N', 'X', "F(X)");
    printf("\n******************************************************");
    printf("\n+-----+--------------------+-------------------------+");
    while (currentStep <= numberOfSteps) {
        if (currentStep % 10 == 0) {
            if (currentStep == 10) {
                printf("\nPress Enter to continue...");
            }
            getchar();
        }
        fX = pow(currentX, 5) - 5 * pow(currentX, 3) - 0.25 * pow(currentX, 2) + 2;
        printf("\n|%5u|%20.3lf|%25.3lf|", currentStep, currentX, fX);
        printf("\n+-----+--------------------+-------------------------+");
        currentX += delta;
        currentStep++;
    }

}

int main(void) {
    // f(x) = x^4 - 5x^3 - 0.25x^2 + 2 -- 1 variant
    unsigned int variant = defineVariant();
    int numberOfSteps = 0;
    double x1 = defineStartValue();
    double x2 = defineEndValue();
    double delta = 0.0;
    getDeltaOrSteps(variant, &delta, &numberOfSteps, x1, x2);
    printf("Variant: %u, Number of steps: %d, x1: %lf, x2: %lf, delta: %lf", variant, numberOfSteps, x1, x2, delta);
    functionOutput(x1, delta, numberOfSteps);
    printf("\nPress Enter to finish the program.");
    getchar();
    return 0;
}
