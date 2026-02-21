#include "Song.h"

void Song::print(ostream& out, const vector<Media*>&) {
    out << left  << setw(42) << title
        << setw(10)  << yearReleased
        << setw(12)  << rating
        << setw(28) << genre
        << (top40 ? "Top 40 Hit" : "---") << "\n";
}



