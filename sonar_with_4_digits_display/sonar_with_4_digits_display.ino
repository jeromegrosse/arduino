#include <NewPing.h>

//Pin Mapping
int pin_1  = 8;
int pin_2  = 9;
int pin_3  = 10;
int pin_4  = 11;
int pin_5  = 12;
int pin_6  = 13;
int pin_7  = 7;
int pin_8  = 6;
int pin_9  = 5;
int pin_10 = 4;
int pin_11 = 3;
int pin_12 = 2;

int pin_trigger = A4;
int pin_echo    = A5;

//Model related mapping
int d1      = pin_12;
int d2      = pin_9;
int d3      = pin_8;
int d4      = pin_6;
int pin_a   = pin_11;
int pin_b   = pin_7;
int pin_c   = pin_4;
int pin_d   = pin_2;
int pin_e   = pin_1;
int pin_f   = pin_10;
int pin_g   = pin_5;
int pin_dot = pin_3;

NewPing sonar(pin_trigger, pin_echo, 3000);

void setup() {
    pinMode(pin_echo,    INPUT);

    pinMode(pin_trigger, OUTPUT);
    pinMode(pin_1,       OUTPUT);
    pinMode(pin_2,       OUTPUT);
    pinMode(pin_3,       OUTPUT);
    pinMode(pin_4,       OUTPUT);
    pinMode(pin_5,       OUTPUT);
    pinMode(pin_6,       OUTPUT);
    pinMode(pin_7,       OUTPUT);
    pinMode(pin_8,       OUTPUT);
    pinMode(pin_9,       OUTPUT);
    pinMode(pin_10,      OUTPUT);
    pinMode(pin_11,      OUTPUT);
    pinMode(pin_12,      OUTPUT);

    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
}

void loop() {
    unsigned int uS = sonar.ping_median(3);
    float distance = (uS * 1.03) / US_ROUNDTRIP_CM;

    unsigned int timestamp = millis();
    while( millis() - timestamp < 1000)
    print_int(distance);

    pick_digit(0);
}

void print_int(int number){
    pick_digit(4);
    print_digit(number%10);
    pick_digit(3);
    print_digit((number/10) % 10);
    pick_digit(2);
    print_digit((number/100) % 10);
    pick_digit(1);
    print_digit((number/1000) % 10);
}

void pick_digit(int digit_number){
    clear_digit();

    if(digit_number != 1) digitalWrite(d1, HIGH); else digitalWrite(d1, LOW);
    if(digit_number != 2) digitalWrite(d2, HIGH); else digitalWrite(d2, LOW);
    if(digit_number != 3) digitalWrite(d3, HIGH); else digitalWrite(d3, LOW);
    if(digit_number != 4) digitalWrite(d4, HIGH); else digitalWrite(d4, LOW);
}


void clear_digit(){
    digitalWrite(pin_a,   LOW);
    digitalWrite(pin_b,   LOW);
    digitalWrite(pin_c,   LOW);
    digitalWrite(pin_d,   LOW);
    digitalWrite(pin_e,   LOW);
    digitalWrite(pin_f,   LOW);
    digitalWrite(pin_g,   LOW);
    digitalWrite(pin_dot, LOW);
}


void print_digit(int digit){
    switch(digit % 11){
        case 0:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_d, HIGH)
            digitalWrite(pin_e, HIGH);
            digitalWrite(pin_f, HIGH);
        break;
        case 1:
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
        break;
        case 2:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_g, HIGH);
            digitalWrite(pin_e, HIGH);
            digitalWrite(pin_d, HIGH);
        break;
        case 3:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_d, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 4:
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_f, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 5:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_d, HIGH);
            digitalWrite(pin_f, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 6:
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_d, HIGH);
            digitalWrite(pin_e, HIGH);
            digitalWrite(pin_f, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 7:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
        break;
        case 8:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_d, HIGH);
            digitalWrite(pin_e, HIGH);
            digitalWrite(pin_f, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 9:
            digitalWrite(pin_a, HIGH);
            digitalWrite(pin_b, HIGH);
            digitalWrite(pin_c, HIGH);
            digitalWrite(pin_f, HIGH);
            digitalWrite(pin_g, HIGH);
        break;
        case 10:
            digitalWrite(pin_e,   HIGH);
            digitalWrite(pin_f,   HIGH);
        break;
        default:
            digitalWrite(pin_g, HIGH);
    }
}
