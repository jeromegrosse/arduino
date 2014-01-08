#include <LedArray.h>

//Arduino - Display pin mapping.
int pin_1  = 13;
int pin_2  = 12;
int pin_3  = 11;
int pin_4  = 10;
int pin_5  = 9;
int pin_6  = 8;
int pin_7  = 7;
int pin_8  = 6;
int pin_9  = A3;
int pin_10 = A2;
int pin_11 = A1;
int pin_12 = A0;
int pin_13 = 2;
int pin_14 = 3;
int pin_15 = 4;
int pin_16 = 5;

//Device-related configuration:
int col1 = pin_13;
int col2 = pin_3;
int col3 = pin_4;
int col4 = pin_10;
int col5 = pin_6;
int col6 = pin_11;
int col7 = pin_15;
int col8 = pin_16;
int row1 = pin_9;
int row2 = pin_14;
int row3 = pin_8;
int row4 = pin_12;
int row5 = pin_1;
int row6 = pin_7;
int row7 = pin_2;
int row8 = pin_5;


int row[] = {row1, row2, row3, row4, row5, row6, row7, row8};
int col[] = {col1, col2, col3, col4, col5, col6, col7, col8};

LedArray ledArray(row, col, 8, 8);

//Timing variable
unsigned int timestamp_1 = millis();
unsigned int timestamp_2;


void setup(){
  ledArray.clear_display();
}

void loop(){
    timestamp_2 = millis();
    ledArray.set_shift(1);
    ledArray.print_string("TestDisplay!", 12, 750);
}
