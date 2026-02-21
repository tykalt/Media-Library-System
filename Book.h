#pragma once
#include <iomanip>
#include "Media.h"

class Book : public Media {
private:
    int weeksNYT;

public:
    Book() : Media(), weeksNYT(0) {}

    Book(char c, string t, string n, int r, string g, int l, int yr, int w)
        : Media(c, t, n, r, g, l, yr), weeksNYT(w) {}

    // getter and setter
    int getWeeks() { return weeksNYT; }
    void setWeeks(int w) { weeksNYT = w; }

    // override print
    void print(ostream& out, const vector<Media*>& mediaLib) override;
};
