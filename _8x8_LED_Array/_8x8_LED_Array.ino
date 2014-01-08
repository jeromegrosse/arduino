#include <LedArray.h>

//Led settings
int col1 = 2;
int col2 = 11;
int col3 = 10;
int col4 = A2;
int col5 = 8;
int col6 = A1;
int col7 = 4;
int col8 = 5;
int row1 = A3;
int row2 = 3;
int row3 = 6;
int row4 = A0;
int row5 = 13;
int row6 = 7;
int row7 = 12;
int row8 = 9;
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
