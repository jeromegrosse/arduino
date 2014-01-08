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
byte ascii_data_C[] = {
    0x0E,
    0x11,
    0x10,
    0x10,
    0x10,
    0x11,
    0x0E,
    0x00
};

byte ascii_data_o[] = {
    0x00,
    0x00,
    0x0E,
    0x11,
    0x11,
    0x11,
    0x0E,
    0x00
};

byte ascii_data_u[] = {
    0x00,
    0x00,
    0x12,
    0x12,
    0x12,
    0x12,
    0x0D,
    0x00
};

byte ascii_data_c[] = {
    0x00,
    0x00,
    0x0E,
    0x11,
    0x10,
    0x11,
    0x0E,
    0x00
};

byte ascii_data_m[] = {
    0x00,
    0x00,
    0x1A,
    0x15,
    0x15,
    0x15,
    0x15,
    0x00
};

byte ascii_data_a[] = {
    0x00,
    0x00,
    0x0E,
    0x01,
    0x0F,
    0x11,
    0x0F,
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

byte* ascii_data[] = {ascii_data_C, ascii_data_o, ascii_data_u, ascii_data_c, ascii_data_o, ascii_data_u, ascii_data_m, ascii_data_a, ascii_data_m, ascii_data_i, ascii_data_e};


//Timing variable
unsigned int timestamp_1 = millis();
unsigned int timestamp_2;



void setup(){
  ledArray.clear_display();
}

void loop(){

    timestamp_2 = millis();
    //ledArray.display_screen(ledArray.reverse_byte(ascii_data[ (timestamp_2 - timestamp_1)/1000 % 11 ]));
    ledArray.default_display();
}
