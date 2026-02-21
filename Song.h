#pragma once
#include <iomanip>
#include "Media.h"

class Song : public Media {
private:
    bool top40;

public:
    Song() : Media(), top40(false) {}

    Song(char c, string t, string n, int r, string g, int l, int yr, bool top)
        : Media(c, t, n, r, g, l, yr), top40(top) {}

    // getter and setter
    bool getTop40() { return top40; }
    void setTop40(bool top) { top40 = top; }

    // override print
    void print(ostream& out, const vector<Media*>& mediaLib) override;
};