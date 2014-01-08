/*
    LedArray.h - Library for some basic function with a led array.
    Created by Jérôme Grossé, January 2014.
*/

#ifndef LedArray_h
#define LedArray_h


#include "Arduino.h"

class LedArray
{
    public:
        LedArray(int row[], int col[], int width, int height);
        void clear_display();
        void default_display();
        void display_screen(byte* data, bool reverse);
        void display_screen(byte* data);
        byte reverse_byte(byte x);
        void print_letter(char c);
        void print_string(char c[], int amount, int time);
        void print_string_width_shift(char c[], int amount, int time, int shift);
        void set_shift(int shift);
        void slide_string(char c[], int amount, int speed);
    private:
        int*         _row;
        int*         _col;
        int          _width;
        int          _height;
        byte**       _charset;
        int         _shift;

        void display_line(byte data, int row_number);
};


#endif