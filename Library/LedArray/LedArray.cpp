#include "Arduino.h"
#include "LedArray.h"

//Charset obtained on the website: http://www.piclist.com/techref/datafile/charset/8x8.htm
byte charset[96][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x00 },
    { 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00 },
    { 0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04, 0x00 },
    { 0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00 },
    { 0x0C, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0D, 0x00 },
    { 0x0C, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00 },
    { 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00 },
    { 0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00, 0x00 },
    { 0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x08, 0x00 },
    { 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00 },
    { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00 },
    { 0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E, 0x00 },
    { 0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 },
    { 0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F, 0x00 },
    { 0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E, 0x00 },
    { 0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02, 0x00 },
    { 0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E, 0x00 },
    { 0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E, 0x00 },
    { 0x1F, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04, 0x00 },
    { 0x1E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00 },
    { 0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C, 0x00 },
    { 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00 },
    { 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x04, 0x08, 0x00 },
    { 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00 },
    { 0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00 },
    { 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00 },
    { 0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04, 0x00 },
    { 0x0E, 0x11, 0x01, 0x0D, 0x15, 0x15, 0x0E, 0x00 },
    { 0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00 },
    { 0x1E, 0x09, 0x09, 0x0E, 0x09, 0x09, 0x1E, 0x00 },
    { 0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E, 0x00 },
    { 0x1E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x1E, 0x00 },
    { 0x1F, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x1F, 0x00 },
    { 0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x00 },
    { 0x0E, 0x11, 0x10, 0x13, 0x11, 0x11, 0x0F, 0x00 },
    { 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00 },
    { 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 },
    { 0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C, 0x00 },
    { 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00 },
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00 },
    { 0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00 },
    { 0x11, 0x19, 0x19, 0x15, 0x13, 0x13, 0x11, 0x00 },
    { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 },
    { 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x00 },
    { 0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x1D, 0x00 },
    { 0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x00 },
    { 0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E, 0x00 },
    { 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00 },
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 },
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00 },
    { 0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11, 0x00 },
    { 0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00 },
    { 0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x00 },
    { 0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F, 0x00 },
    { 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00 },
    { 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00 },
    { 0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x00 },
    { 0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00 },
    { 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0F, 0x00 },
    { 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1E, 0x00 },
    { 0x00, 0x00, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x00 },
    { 0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x0F, 0x00 },
    { 0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00 },
    { 0x02, 0x05, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x00 },
    { 0x00, 0x0D, 0x13, 0x13, 0x0D, 0x01, 0x0E, 0x00 },
    { 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00 },
    { 0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E, 0x00 },
    { 0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0C, 0x00 },
    { 0x08, 0x08, 0x09, 0x0A, 0x0C, 0x0A, 0x09, 0x00 },
    { 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 },
    { 0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15, 0x00 },
    { 0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00 },
    { 0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 },
    { 0x00, 0x16, 0x19, 0x19, 0x16, 0x10, 0x10, 0x00 },
    { 0x00, 0x0D, 0x13, 0x13, 0x0D, 0x01, 0x01, 0x00 },
    { 0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10, 0x00 },
    { 0x00, 0x00, 0x0F, 0x10, 0x1E, 0x01, 0x1F, 0x00 },
    { 0x08, 0x08, 0x1C, 0x08, 0x08, 0x09, 0x06, 0x00 },
    { 0x00, 0x00, 0x12, 0x12, 0x12, 0x12, 0x0D, 0x00 },
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00 },
    { 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00 },
    { 0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00 },
    { 0x00, 0x00, 0x11, 0x11, 0x13, 0x0D, 0x01, 0x0E },
    { 0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00 },
    { 0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02, 0x00 },
    { 0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04, 0x00 },
    { 0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08, 0x00 },
    { 0x08, 0x15, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

/*
 * Constructor of the class.
 *
 * int* row : The array of pin for the rows.    In position 0 has to be stored the pin for row number 0, etc.
 * int* col : The array of pin for the columns. In position 0 has to be stored the pin for column number 0, etc.
 * int width: Width of the display.
 * int height: Height of the display.
 */
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


/*
 * Turns the display blank (no led turned on).
 */
void LedArray::clear_display()
{
    for(int i = 0; i < _width; i++){
        digitalWrite(_col[i], HIGH);
    }

    for(int i = 0; i < _height; i++){
        digitalWrite(_row[i], LOW);
    }
}


/*
 * Display on the grid an animation.
 */
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
    display_screen(arr_screen[ (timestamp_2 - _timestamp)/1000  % (2*_height)], false);
}


/*
 * Display data on line row_number.
 * byte data     : Byte to be displayed on the line.
 * int row_number: Row where the data has to be displayed.
 */
void LedArray::display_line(byte data, int row_number){
    clear_display();
    digitalWrite(_row[row_number], HIGH);

    int temp = data;
    for(int i = 0; i < _width; i++){
        digitalWrite(_col[i], temp & 0x01 == 1 ? LOW : HIGH);
        temp = temp >> 1;
    }
}


/*
 * Display an array of byte on the screen. The size of the array has to fit the declared height and width.
 * byte* data  : Array of byte to be displayed.
 * bool reverse: Reverse the data horizontally if true.
 */
void LedArray::display_screen(byte* data, bool reverse){
    if(!reverse) return display_screen(data);
    for(int i = 0; i < _height; i++){
        display_line(reverse_byte(data[i]), i);
    }
}

/*
 * Display an array of byte on the screen. The size of the array has to fit the declared height and width.
 * byte* data: Array of byte to be displayed.
 */
void LedArray::display_screen(byte* data){
    for(int i = 0; i < _height; i++){
        display_line(data[i], i);
    }
}


/*
 * Reverse a byte. Useful here to reverse a letter.
 * byte x : Byte to reverse.
 *
 * Returns byte reversed.
 */
byte LedArray::reverse_byte(byte x){
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
    return x;
}

/*
 * Print a letter on the display.
 * char c : Letter to display.
 */
void LedArray::print_letter(char c){
    display_screen(charset[c - ' '], true);
}

/*
 * Print a string on the display.
 *
 * char c    : String to display
 * int amount: Amount of letters in c
 * int time  : Interval between each letters in millisecond.
 */
void LedArray::print_string(char c[], int amount, int time){
    unsigned int timestamp_2 = millis();
    print_letter(c[ ((timestamp_2 - _timestamp)/time) % amount]);
}