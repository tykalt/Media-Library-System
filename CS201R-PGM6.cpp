// CS201R-PGM6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Name: Ty K

// Changed to .cpp for mac compatibility
#include "Functions.cpp"
#include "Media.cpp"
#include "Movie.cpp"
#include "Book.cpp"
#include "Song.cpp"

using namespace std;

int main() {
    ifstream inList, inCommands;
    ofstream outFile, outErr;

    inList.open("mediaList.txt");
    if (!inList.good()) {
        cerr << "Could not open mediaList.txt\n";
        return 1;
    }

    inCommands.open("mediaCommands.txt");
    if (!inCommands.good()) {
        cerr << "Could not open mediaCommands.txt\n";
        return 1;
    }

    outFile.open("mediaReport.txt");
    if (!outFile.good()) {
        cerr << "Could not open mediaReport.txt\n";
        return 1;
    }

    outErr.open("mediaError.txt");
    if (!outErr.good()) {
        cerr << "Could not open mediaError.txt\n";
        return 1;
    }

    vector<Media*> mediaLib;

    readMediaList(inList, outErr, mediaLib);
    inList.close();

    string commandRecord;
    while (getline(inCommands, commandRecord)) {
        if (!commandRecord.empty() && toupper(commandRecord[0]) == 'Q') {
            break;
        }
        handleCommand(commandRecord, outFile, outErr, mediaLib);
    }

    inCommands.close();
    outFile.close();
    outErr.close();

    for (Media* m : mediaLib) {
        delete m;
    }

    return 0;
}


