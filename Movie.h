#pragma once
#include <vector>
#include <iomanip>
#include "Media.h"

class Movie : public Media {
private:
    vector<string> stars;

public:
    Movie() : Media() {}

    Movie(char c, string t, string n, int r, string g, int l, int yr, vector<string> s)
        : Media(c, t, n, r, g, l, yr), stars(s) {}

    // getter and setter
    vector<string> getStars() { return stars; }
    void setStars(vector<string> s) { stars = s; }

    // override print
    void print(ostream& out, const vector<Media*>& mediaLib) override;
};
