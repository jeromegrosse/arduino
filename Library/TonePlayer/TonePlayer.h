/*
    TonePlayer.h - Library for some basic function with a led array.
    Created by Jérôme Grossé, January 2014.
*/

#ifndef TonePlayer_h
#define TonePlayer_h


#include "Arduino.h"

class TonePlayer
{
    public:
        TonePlayer(int pin, int notes[], int durations[], int duration);
        bool finished();
        void playNote();
        void resetPointer();
        int  getPointer();
        int  getNote();
        int  getDuration();
        int  correctTempo(float correction);
    private:
        int         _pin;
        int*        _notes;
        int*        _durations;
        int         _duration;
        int         _pointer;
        float       _tempoCorrector;
};


#endif