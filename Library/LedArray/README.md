LedArray Library
================

Library tested on a 8x8 LED Array.

The constructor needs the following:
    - row:    An array of integer giving the pin number for each row number.
    - col:    An array of integer giving the pin number for each row number.
    - width:  The width of the array of LED.
    - height: The hight of the array of LED.

An exemple of this library in use can be found in the project: 8x8 LED Array.

This library allow basic operations on the display such as writing bytes line by line, writing a letter or writing a string on the display letter by letter and shifting.

TODO:
    - Give the possibility to have a scrolling text rather than one letter at a time.
