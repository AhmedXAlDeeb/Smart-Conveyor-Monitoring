/**
 * Keypad.c
 */
#include "Keypad.h"
#include "Gpio.h"
#include "Std_Types.h"
#include "GPIO_Private.h"



#define KEYPAD_SIZE (ROW_COUNT * COL_COUNT)

const uint8 keypad_chars[KEYPAD_SIZE]  = {

    //1    2    3
    '1' , '2', '3', //A
    '4' , '5', '6', //B
    '7' , '8', '9', //C
    '*' , '0', '#'  //D

};

char selected_key = '\0';
char stored_key = '\0';

static KeypadConfig keypadConfig = {
    .rowPins = {
        {GPIOA, 9},
        {GPIOB, 6},
        {GPIOB, 0},
        {GPIOC, 7}
    },
    .colPins = {
        {GPIOA, 0},
        {GPIOA, 10},
        {GPIOB, 9}
    },
    .keymap = keypad_chars
};




void KEYPAD_INIT(void) {
    for (int i = 0; i < ROW_COUNT; i++) {
        GPIO_INIT(keypadConfig.rowPins[i].PortName, keypadConfig.rowPins[i].PinNum, OUTPUT_MODE, PUSH_PULL);
        GPIO_WritePin(keypadConfig.rowPins[i].PortName, keypadConfig.rowPins[i].PinNum, HIGH);
    }

    for (int j = 0; j < COL_COUNT; j++) {
        GPIO_INIT(keypadConfig.colPins[j].PortName, keypadConfig.colPins[j].PinNum, INPUT_MODE, PULL_UP);
    }
}

// void KEYPAD_INIT(void)
// {
//     uint8 idx = 0;
//     // Configure rows as output with push-pull
//     for(idx = ROW_START_INDEX; idx <= ROW_END_INDEX; idx++) {
//         GPIO_INIT(ROW_PORT, idx, OUTPUT_MODE, PUSH_PULL);
//         GPIO_WritePin(ROW_PORT, idx, HIGH); // Idle state (not driving low) active low buttons
//     }
//
//
//     // Configure columns as input with pull-up
//     for(idx= COL_START_INDEX; idx <= COL_END_INDEX; idx++) {
//         GPIO_INIT(COL_PORT, idx, INPUT_MODE, PULL_UP);
//     }
// }


void KeypadCallout_KeyPressNotification(void);

//Function shall not take any arguments.
void KEYPAD_MANAGE(void){

    uint8 row, col;
    uint8 detected_key = 0;
    uint8 key_was_pressed = 0;



    //(loop over rows and columns/ stop on the first press detected)
    for(row = 0; row < ROW_COUNT; row++) {
        //idle input
        // for(uint8 r = ROW_START_INDEX; r <= ROW_END_INDEX; r++) {
        //     GPIO_WritePin(ROW_PORT, r, HIGH);
        // }


        for (int r = 0; r < ROW_COUNT; r++) {
            GPIO_WritePin(keypadConfig.rowPins[r].PortName, keypadConfig.rowPins[r].PinNum, HIGH);
        }

        // Activate row
        // GPIO_WritePin(ROW_PORT, row, LOW);
        GPIO_WritePin(keypadConfig.rowPins[row].PortName, keypadConfig.rowPins[row].PinNum, LOW);



        //read from all columns

        //if(GPIO_ReadPin(COL_PORT, col) == LOW)
        //     {
        //         // Calculate the index into the keypad array
        //         int row_index = row - ROW_START_INDEX;
        //         int col_index = col - COL_START_INDEX;
        //         int index = row_index * (COL_END_INDEX - COL_START_INDEX + 1) + col_index;
        //
        //         //Once a valid key press is detected, function shall:
        //         selected_key = keypad_chars[index]; //holds the key value until it’s cleared



        for (col = 0; col < COL_COUNT; col++) {
            if (GPIO_ReadPin(keypadConfig.colPins[col].PortName, keypadConfig.colPins[col].PinNum) == LOW) {
                int index = row * COL_COUNT + col;
                selected_key = keypadConfig.keymap[index];
                detected_key = 1;
                break;
            }
        }

            if (detected_key) break; // Don't need to continu scanning
        }

        //Once a valid key press is detected, function shall:
            //Store the pressed key value

            //Call KeypadCallout_KeyPressNotification()
        if (detected_key) //valid press
        {
            // If no other key is hold or pressed and the last key was read
            if (!key_was_pressed && stored_key == '\0') {
                stored_key = selected_key; //store new value
                KeypadCallout_KeyPressNotification(); // call the callout fucntion
            }
            key_was_pressed = 1; //set the state to that there is a key pressed now so no other reading happen

        } else {
                key_was_pressed = 0; //release the key
            }
    }
    // if button pressed with our prefined conditions



char KEYPAD_GETKEY(void)
{
    char key = stored_key;
    stored_key = '\0'; // clear after reading
    return key;
}


