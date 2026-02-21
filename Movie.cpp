#include "Movie.h"

void Movie::print(ostream& out, const vector<Media*>&) {
    out << left  << setw(42) << title
        << setw(10)  << yearReleased
        << setw(12)  << rating
        << setw(28) << genre
        << "Stars: ";
    for (const string& s : stars) {
        out << s << " ";
    }
    out << "\n";
}



