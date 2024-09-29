#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Returns amount of lines in user's console
int getConsoleHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

// Validates that value provided by user is compatible with value provided by format specifier
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

// Asks user for variant and validates if it is correct ( 1 || 2 && !char[] && !string)
unsigned int defineVariant() {
    unsigned int variant = 0;
    unsigned int valid = 0;
    while (!valid) {
        printf("\nSelect variant 1 || 2: ");
        if (validateInput("%u", &variant) && (variant == 1 || variant == 2)) {
            valid = 1;
        }
    }
    printf("\nYou selected %u variant.", variant);
    return variant;
}

// Asks for x1 with validation
double defineStartValue() {
    double x1;
    printf("\nType in start value: ");
    validateInput("%lf", &x1);

    return x1;
}

// Asks for x2 with validation
double defineEndValue() {
    double x2;
    printf("\nType in end value: ");
    validateInput("%lf", &x2);
    return x2;
}

// Checks variant -> asks for delta or steps -> calculates another variable based on provided
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

// Prints header of table (3 lines)
void printHeader() {
    printf("\n******************************************************");
    printf("\n|%5s|%20s|%25s|", "N", "X", "F(X)");
    printf("\n******************************************************");
    printf("\n+-----+--------------------+-------------------------+");
}

// Main logic
void functionOutput(double x1, double delta, int numberOfSteps) {
    int pausesCounter = 0;
    int printedLinesCounter = 0;
    int currentStep = 1;
    double currentX = x1;

    printHeader();
    printedLinesCounter = 6; // header takes 3 lines. = 6 to show 3 top lines

    while (currentStep <= numberOfSteps) {
        //pause logic
        if (printedLinesCounter % getConsoleHeight() == 0 && printedLinesCounter != 0 ) { // 24 is avg console size || (pausesCounter == 0) && printedLinesCounter > 24
            if (pausesCounter == 0) {
                printf("\nPress Enter to continue...");
                getchar();
                printf("\033[A\r"); //cursor 1 line up then to the beginning of line
            } else {
                getchar();
                printf("\r");
            }
            pausesCounter++;
        } else {
            printf("\n");
        }

        double fX = pow(currentX, 4) - 5 * pow(currentX, 3) - 0.25 * pow(currentX, 2) + 2;
        printf("|%5d|%20.3lf|%25.3lf|", currentStep, currentX, fX);
        printf("\n+-----+--------------------+-------------------------+");
        //counters
        printedLinesCounter += 2;
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
    system("clear");
    printf("You entered:\nVariant:%u\nNumber of steps:%d\nDelta:%lf\nX1:%lf\nX2:%lf",
        variant, numberOfSteps, delta, x1, x2);
    printf("\nPress Enter to continue.");
    getchar();
    functionOutput(x1, delta, numberOfSteps);
    printf("\nPress Enter to finish the program.");
    getchar();
    return 0;
}
