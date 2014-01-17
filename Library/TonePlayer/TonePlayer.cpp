#include "TonePlayer.h"

/*
 * Constructor of the class.
 *
 * int pin       : Pin of the output
 * int* notes    : Array of note.
 * int* durations: Array of duration related to the notes defined above.
 * int duration  : Duration of the whole track (i.e. The length of the notes/durations array).
 */
TonePlayer::TonePlayer(int pin, prog_uint16_t notes[], prog_uint16_t durations[], int duration, int timer, bool timestamp){
    _pin                = pin;
    _notes              = notes;
    _durations          = durations;
    _duration           = duration;
    _timer              = timer;
    _timestamp_duration = timestamp;
    _start_timestamp   = 0;

    _pointer           = 0;
    _tempoCorrector    = 1;
    _time_left_to_play = 0;

    pinMode(_pin, OUTPUT);

    if(_timer == 1){
        TCCR1A = _BV(COM1A0) | _BV(WGM13) | _BV(WGM10);
        OCR1B  = 100;
    } else if(_timer == 2){
        TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        OCR2B  = 100;
    }

}


/*
 * Returns a boolean telling whether the track is finished
 */
bool TonePlayer::finished(){
    int finished = _pointer >= _duration;

    if(finished){
        if(_timer == 1) OCR1A = 0;
        if(_timer == 2) OCR2A = 0;
    }
    return finished;
}


/*
 * Plays the next note
 */
void TonePlayer::playNote(){
    if(finished()) return;
    int timestamp = millis();

    if(_timestamp_duration){
        if(_start_timestamp == 0) _start_timestamp = timestamp;
        if(pgm_read_word_near(_durations + _pointer + 1) < timestamp - _start_timestamp){
            _pointer++;

            if(_timer == 1)      _playNoteTimer1();
            else if(_timer == 2) _playNoteTimer2();
        }

    }else {
        if(_timestamp +  pgm_read_word_near(_durations + _pointer) <= timestamp){
            _pointer++;
            _timestamp = timestamp;

            if(_timer == 1)      _playNoteTimer1();
            else if(_timer == 2) _playNoteTimer2();
        }
    }
}


void TonePlayer::_playNoteTimer1(){
    _frequency      = pgm_read_word_near(_notes + _pointer);
    uint32_t ocr            = F_CPU / _frequency / 2 / 1 - 1;
    byte prescalarbits = 0b001;

    if (ocr > 0xffff)
    {
        ocr = F_CPU / _frequency / 2 / 8 - 1;
        prescalarbits = 0b010;
    }

    if (ocr > 0xffff)
    {
        ocr = F_CPU / _frequency / 2 / 64 - 1;
        prescalarbits = 0b011;
    }

    if (ocr > 0xffff)
    {
        ocr = F_CPU / _frequency / 2 / 256 - 1;
        prescalarbits = 0b100;
    }

    if (ocr > 0xffff)
    {
        ocr = F_CPU / _frequency / 2 / 1024 - 1;
        prescalarbits = 0b101;
    }

    TCCR1B = _BV(WGM13) | prescalarbits;
    OCR1A  = ocr;
}

void TonePlayer::_playNoteTimer2(){
    _frequency      = pgm_read_word_near(_notes + _pointer);
    uint32_t ocr      = (F_CPU / _frequency / 2 / 1) - 1;
    byte prescalarbits = 0b001;

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 8) - 1;
        prescalarbits = 0b010;
    }

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 32) - 1;
        prescalarbits = 0b011;
    }

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 64) - 1;
        prescalarbits = 0b100;
    }

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 128) - 1;
        prescalarbits = 0b101;
    }

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 256) - 1;
        prescalarbits = 0b110;
    }

    if (ocr > 255)
    {
        ocr = (F_CPU / _frequency / 2 / 1024) - 1;
        prescalarbits = 0b111;
    }

    if (ocr > 255)
    {
        //The note can't be played
        ocr = 0;
        prescalarbits = 0b000;
    }

    TCCR2B = _BV(WGM22) | prescalarbits;
    OCR2A  = ocr;
}

/*
 * Resets the pointer to the beginning of the track.
 */
void TonePlayer::resetPointer(){
    _pointer = 0;
}


/*
 * Returns the position of the pointer.
 */
int TonePlayer::getPointer(){
    return _pointer;
}


/*
 * Returns the current note.
 */
int TonePlayer::getNote(){
    return _frequency;
}


/*
 * Returns the duration of the current note.
 */
int TonePlayer::getDuration(){
    return pgm_read_word_near(_durations + _pointer);
}


/*
 * Correct the tempo (i.e. the durations of given in the constructor) by a ratio.
 */
int TonePlayer::correctTempo(float correction){
    if(correction > 0){
        _tempoCorrector = correction;
    }
}

/*
 *
 */
void TonePlayer::nextNote(){
    if(finished()) return;
    _pointer++;
    if(_timer == 1)      _playNoteTimer1();
    else if(_timer == 2) _playNoteTimer2();
}

int TonePlayer::getFrequency(){
    return _frequency;
}