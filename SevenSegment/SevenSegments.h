#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "Gpio.h"
#include "Std_Types.h"

#define SEGMENT_COUNT 7  // Number of segments in display (excluding DP)

typedef struct {
    uint8 PortName;      // GPIO port (e.g., 'A', 'B')
    uint8 PinNum;        // GPIO pin number (0-15)
} SegmentPin;



void SevenSegment_Init();


void SevenSegment_Display(uint16 digit);

void SevenSegment_Clear();

#endif /* SEVEN_SEGMENT_H */