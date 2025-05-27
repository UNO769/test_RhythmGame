#ifndef NOTE_H
#define NOTE_H

struct Note {
    int x;
    int y;
    int speed;
    int key;

    Note() : x(0), y(0), speed(0), key(0) {}
    Note(int px, int py, int pspeed, int pkey) : x(px), y(py), speed(pspeed), key(pkey) {}
};

#endif // NOTE_H