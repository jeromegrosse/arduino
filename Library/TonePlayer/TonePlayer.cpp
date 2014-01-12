#include "TonePlayer.h"

/*
 * Constructor of the class.
 *
 * int pin       : Pin of the output
 * int* notes    : Array of note.
 * int* durations: Array of duration related to the notes defined above.
 * int duration  : Duration of the whole track (i.e. The length of the notes/durations array).
 */
TonePlayer::TonePlayer(int pin, int notes[], int durations[], int duration){
    _pin       = pin;
    _notes      = notes;
    _durations = durations;
    _duration  = duration;

    _pointer        = 0;
    _tempoCorrector = 1;

    pinMode(pin, OUTPUT);
}


/*
 * Returns a boolean telling whether the track is finished
 */
bool TonePlayer::finished(){
    return _pointer == _duration;
}


/*
 * Plays the next note
 */
void TonePlayer::playNote(){
    if(_pointer == _duration) return;
    int noteDuration = _durations[_pointer] * _tempoCorrector;
    tone(_pin, _notes[_pointer], noteDuration);

    delay(noteDuration * 1.30);
    noTone(_pin);

    _pointer++;
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
    return _notes[_pointer];
}


/*
 * Returns the duration of the current note.
 */
int TonePlayer::getDuration(){
    return _durations[_pointer];
}


/*
 * Correct the tempo (i.e. the durations of given in the constructor) by a ratio.
 */
int TonePlayer::correctTempo(float correction){
    if(correction > 0){
        _tempoCorrector = correction;
    }
}