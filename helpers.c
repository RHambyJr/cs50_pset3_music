// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "helpers.h"
#include <stdio.h>

int getOctave(string note);
int getStep(string note);
int getFrequency(int octave, int step);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    const int NUM = atoi(&fraction[0]); // Holds converted to int numerator
    const int DENOM = atoi(&fraction[2]); // Holds converted to int demoninator
    const int MULTI = 8 / DENOM; // What numerator is multiplied by to get an 8th numerator

    return NUM * MULTI;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char temp[3]; //Holds music note

    // Checks if note is an accidental
    if (note[1] == '#' || note[1] == 'b')
    {
        temp[0] = note[0];
        temp[1] = note[1];
        temp[2] = '\0';
    }
    else
    {
        temp[0] = note[0];
        temp[1] = '\0';
    }

    string musicNote = temp;
    int octave = getOctave(note); //Get octave
    int step = getStep(musicNote); //Get step
    int frequency = getFrequency(octave, step); //Get frequency

    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //Checks if string is empty
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Gets the octave the note will be played in
int getOctave(string note)
{
    int octave;

    //Checks if note is accidental
    if (note[1] == '#' || note[1] == 'b')
    {
        octave = atoi(&note[2]);
    }
    else
    {
        octave = atoi(&note[1]);
    }

    return octave;
}

//Gets the semitone differental between A4 and note
int getStep(string note)
{
    int defA = 9; // Holds default position for A note
    int apart; // Will hold the difference in semitones for notes
    string noteUpdate;

    //Holds each note in order
    string notes[] =
    {
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B"
    };

    //Checks if the note is a flat, if it is, changes it to it's sharp equivalent.
    //This is really bad and I know it's poor practice but I can not, for the life of me,
    //figure out how to incorporate flats into the array and check distance more elegantly
    //than this garbage. Please forgive me.
    if (strcmp(note, "Db") == 0)
    {
        noteUpdate = "C#";
    }
    else if (strcmp(note, "Eb") == 0)
    {
        noteUpdate = "D#";
    }
    else if (strcmp(note, "Gb") == 0)
    {
        noteUpdate = "F#";
    }
    else if (strcmp(note, "Ab") == 0)
    {
        noteUpdate = "G#";
    }
    else if (strcmp(note, "Bb") == 0)
    {
        noteUpdate = "A#";
    }
    else
    {
        noteUpdate = note;
    }

    for (int i = 0; i < (int)sizeof(notes) / sizeof(notes[0]); i++)
    {
        if (strcmp(notes[i], noteUpdate) == 0)
        {
            apart = i - defA;
        }
    }

    return apart;
}

//Calculates the frequency of the current note
int getFrequency(int octave, int step)
{
    const int DEF_FREQ = 440;
    int octDif = octave - 4;
    float freq;

    //Calculate A4 in another octave
    if (octDif > 0)
    {
        freq = DEF_FREQ * pow(2., (octDif * 12.) / 12.);
    }
    else
    {
        freq = DEF_FREQ / pow(2., (abs(octDif) * 12.) / 12.);
    }

    //Calcultes semitones from A
    if (step > 0)
    {
        freq = freq * pow(2., step / 12.);
    }
    else
    {
        freq = freq / pow(2., abs(step) / 12.);
    }

    return (int)round(freq);
}