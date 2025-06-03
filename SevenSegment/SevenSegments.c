#include "Gpio.h"
#include "Std_Types.h"
#include "SevenSegments.h"
#include "Keypad.h"


/* Internal configuration - defined here instead of passed as parameters */
const SegmentPin segmentPins[SEGMENT_COUNT] = {
    {GPIOB, 0},  // Segment A
    {GPIOB, 1},  // Segment B
    {GPIOB, 2},  // Segment C
    {GPIOB, 3},  // Segment D
    {GPIOB, 4},  // Segment E
    {GPIOB, 5},  // Segment F
    {GPIOB, 6}   // Segment G
};


void delay(int ms) {

    for (int i = 0; i < ms*10000; i++) {}
}

#define DIGIT_COUNT 4

const SegmentPin digitSelectors[DIGIT_COUNT] = {
    {GPIOB, 7},   // Digit 1 (rightmost)
    {GPIOB, 8},   // Digit 2
    {GPIOB, 9},   // Digit 3
    {GPIOB, 10}   // Digit 4 (leftmost)
};

// Segment patterns for digits 0-9 (common cathode)
// Format: {a, b, c, d, e, f, g} segments
const uint8 digitSegments[10][SEGMENT_COUNT] = {
     // a  b  c  d  e  f  g
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

void SevenSegment_Init() {
    // Segment pins
    for (uint8 i = 0; i < SEGMENT_COUNT; i++) {
        GPIO_INIT(segmentPins[i].PortName, segmentPins[i].PinNum, OUTPUT_MODE, PUSH_PULL);
    }

    // Digit selector pins
    for (uint8 i = 0; i < DIGIT_COUNT; i++) {
        GPIO_INIT(digitSelectors[i].PortName, digitSelectors[i].PinNum, OUTPUT_MODE, PUSH_PULL);
    }
}
void SevenSegment_DisplayDigit(uint8 digit) {
    if (digit > 9) return;

    for (uint8 i = 0; i < SEGMENT_COUNT; i++) {
        GPIO_WritePin(segmentPins[i].PortName, segmentPins[i].PinNum, digitSegments[digit][i]);
    }
}


void SevenSegment_Display(uint16 number) {
    uint8 digits[4] = {
        (number / 1000) % 10,
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };

    for (int i = 0; i < 4; ++i) {
        // Enable only the current digit selector
        GPIO_WritePin(digitSelectors[i].PortName, digitSelectors[i].PinNum, HIGH);

        // Display digit on shared segment pins
        SevenSegment_DisplayDigit(digits[i]);
        delay(5); // Short delay for persistence of vision

        SevenSegment_Clear();
    }
}

void SevenSegment_Clear() {
    // Turn off all segment LEDs
    for (uint8 i = 0; i < SEGMENT_COUNT; i++) {
        GPIO_WritePin(segmentPins[i].PortName, segmentPins[i].PinNum, LOW);
    }

    // Disable all digit selectors
    for (uint8 i = 0; i < DIGIT_COUNT; i++) {
        GPIO_WritePin(digitSelectors[i].PortName, digitSelectors[i].PinNum, LOW);
    }
}

