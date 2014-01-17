/*
    TonePlayer.h - Library for some basic function with a led array.
    Created by Jérôme Grossé, January 2014.
*/

#ifndef TonePlayer_h
#define TonePlayer_h


#include "Arduino.h"
#include <avr/pgmspace.h>


class TonePlayer
{
    public:
        TonePlayer(int pin, prog_uint16_t* notes, prog_uint16_t* durations, int duration, int timer, bool timestamp);
        bool        finished();
        void        playNote();
        void        resetPointer();
        int         getPointer();
        int         getNote();
        int         getDuration();
        int         correctTempo(float correction);
        void        nextNote();
        int         getFrequency();
    private:
        int         _pin;
        prog_uint16_t*        _notes;
        prog_uint16_t*        _durations;
        int         _frequency;
        int         _duration;
        int         _pointer;
        float       _tempoCorrector;
        int         _time_left_to_play;
        int         _timestamp;
        int         _timer;
        int         _start_timestamp;
        int         _timestamp_duration;
        void        _playNoteTimer1();
        void        _playNoteTimer2();
};


#endif