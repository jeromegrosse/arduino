#include "Arduino.h"
#include "LedArray.h"

LedArray::LedArray(int row[], int col[], int width, int height){
    _timestamp = millis();
    _row    = row;
    _col    = col;
    _width  = width;
    _height = height;

    for(int i = 0; i < _width; i++){
        pinMode(_col[i], OUTPUT);
    }

    for(int i = 0; i < _height; i++){
        pinMode(_row[i], OUTPUT);
    }
}


//Returns a blank display (no led turned on)
void LedArray::clear_display()
{
    for(int i = 0; i < _width; i++){
        digitalWrite(_col[i], HIGH);
    }

    for(int i = 0; i < _height; i++){
        digitalWrite(_row[i], LOW);
    }
}


//Default view to check if things are working
void LedArray::default_display(){
    byte arr_screen[16][8] = {
        {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    unsigned int timestamp_2 = millis();
    display_screen(arr_screen[ (timestamp_2 - _timestamp)/1000  % (2*_height)]);
}


//Given a byte and a row number, show print the line on the display
void LedArray::display_line(byte data, int row_number){
    clear_display();
    digitalWrite(_row[row_number], HIGH);

    int temp = data;
    for(int i = 0; i < _width; i++){
        digitalWrite(_col[i], temp & 0x01 == 1 ? LOW : HIGH);
        temp = temp >> 1;
    }
}


//Given an array of byte, display them on the display
void LedArray::display_screen(byte* data, bool reverse){
    if(!reverse) return display_screen(data);
    for(int i = 0; i < _height; i++){
        display_line(reverse_byte(data[i]), i);
    }
}

void LedArray::display_screen(byte* data){
    for(int i = 0; i < _height; i++){
        display_line(data[i], i);
    }
}

//I came up with the need to reverse some byte on some char set found on the internet
byte LedArray::reverse_byte(byte x){
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
    return x;
}