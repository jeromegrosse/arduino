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

//Ascii char to be displayed
byte ascii_data_H[] = {
    0x11,
    0x11,
    0x11,
    0x1F,
    0x11,
    0x11,
    0x11,
    0x00
};

byte ascii_data_i[] = {
    0x04,
    0x00,
    0x0C,
    0x04,
    0x04,
    0x04,
    0x0E,
    0x00
};

byte ascii_data_t[] = {
    0x08,
    0x08,
    0x1C,
    0x08,
    0x08,
    0x09,
    0x06,
    0x00
};

byte ascii_data_h[] = {
    0x10,
    0x10,
    0x16,
    0x19,
    0x11,
    0x11,
    0x11,
    0x00
};

byte ascii_data_e[] = {
    0x00,
    0x00,
    0x0E,
    0x11,
    0x1F,
    0x10,
    0x0E,
    0x00
};

byte ascii_data_r[] = {
    0x00,
    0x00,
    0x16,
    0x19,
    0x10,
    0x10,
    0x10,
    0x00
};

byte* ascii_data[] = {ascii_data_H, ascii_data_i, ascii_data_t, ascii_data_h, ascii_data_e, ascii_data_r, ascii_data_e};


//Timing variable
unsigned int timestamp_1 = millis();
unsigned int timestamp_2;



void setup(){
  ledArray.clear_display();
}

void loop(){

    timestamp_2 = millis();
    //ledArray.display_screen(ascii_data[ (timestamp_2 - timestamp_1)/1000 % 6 ], true);
    ledArray.default_display();
}
