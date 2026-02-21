#include "Functions.h"


bool isDigits(string str1) {
    return (str1.find_first_not_of("1234567890") == string::npos);
}
 
void readMediaList(istream& inFile, ostream& outFile, vector<Media*>& mediaLib) {
    string line;

    while (getline(inFile, line)) {
        if (line == "Q") {
            break;
        }
    
        stringstream ss(line);
        string token;
        vector<string> fields;
    
        // Extract fields from the line
        while (getline(ss, token, ',')) {
            fields.push_back(token);
        }

        char type = fields[0][0];
        string title = fields[1];
        string name = fields[2];
        string ratingStr = fields[3];
        string genre = fields[4];
        string lengthStr = fields[5];
        string yearStr = fields[6];

        int rating, length, year;

        // first check: invalid type
        if (type != 'M' && type != 'B' && type != 'S') {
            outFile << "ERROR: " << line << "\n";
            outFile << "Invalid value entered for type.\n\n";
            continue;
        }

        // second check: invalid rating
        try {
            rating = stoi(ratingStr);
        } catch (...) {
            outFile << "ERROR: " << line << "\n";
            outFile << "Previous record has an invalid stoi argument error\n\n";
            continue;
        }
        if (rating < 1 || rating > 10) {
            outFile << "ERROR: " << line << "\n";
            outFile << "There was an invalid value entered for rating.\n\n";
            continue;
        }

        // third check: invalid length
        try {
            length = stoi(lengthStr);
            if (length <= 0)
                throw invalid_argument("Invalid length");
        } catch (...) {
            outFile << "ERROR: " << line << "\n";
            outFile << "There was an invalid value entered for length.\n\n";
            continue;
        }

        // fourth check: invalid year
        try {
            year = stoi(yearStr);
            if (year < 1920 || year > 2024)
                throw invalid_argument("Invalid year");
        } catch (...) {
            outFile << "ERROR: " << line << "\n";
            outFile << "There was an invalid value entered for year.\n\n";
            continue;
        }

        // Type specific logic (new commands for Part 2)
        if (type == 'M') {
            vector<string> stars;
            for (size_t i = 7; i < fields.size(); ++i) {
                stars.push_back(fields[i]);
            }
            mediaLib.push_back(new Movie(type, title, name, rating, genre, length, year, stars));
        }

        else if (type == 'B') {
            try {
                int weeks = stoi(fields[7]);
                mediaLib.push_back(new Book(type, title, name, rating, genre, length, year, weeks));
            } catch (...) {
                outFile << "ERROR: " << line << "\n";
                outFile << "Previous record has an invalid stoi argument error\n\n";
                continue;
            }
        }

        else if (type == 'S') {
            try {
                if (fields[7] != "0" && fields[7] != "1") throw invalid_argument("Not boolean");
                bool top40 = (fields[7] == "1");
                mediaLib.push_back(new Song(type, title, name, rating, genre, length, year, top40));
            } catch (...) {
                outFile << "ERROR: " << line << "\n";
                outFile << "Previous record has an error in boolean value\n\n";
                continue;
            }
        }
    }
}


void handleCommand(const string& commandRecord, ostream& out, ostream& err, vector<Media*>& mediaLib) {
    if (commandRecord.empty()) return;

    stringstream ss(commandRecord);
    string token;
    vector<string> tokens;

    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    char command = tokens[0][0];

    // Part 5: additional commands for part 2
    // Command: L - List stars of a movie
    if (command == 'L' && tokens.size() == 2) {
        string movieTitle = tokens[1];
        bool found = false;
    
        for (Media* m : mediaLib) {
            if (m->getType() == 'M' && m->getTitle() == movieTitle) {
                // given to us by the instructor
                // converts Media pointer to a Movie pointer
                Movie* movie = static_cast<Movie*>(m);
                out << string(64, '+') << "\n";
                out << "THE STARS OF THE MOVIE " << movieTitle << " ARE: \n";
                for (const string& star : movie->getStars()) {
                    out << star << "\n";
                }
                out << "\n\n";
                found = true;
                break;
            }
        }
    
        if (!found) {
            err << "Unable to process command. The movie: '" << movieTitle << "' is not found in your list\n\n";
        }
        return;
    }
    

    // Command: F - List movies an actor appears in
    if (command == 'F' && tokens.size() == 2) {
        string actor = tokens[1];
        bool found = false;
    
        for (Media* m : mediaLib) {
            if (m->getType() == 'M') {
                Movie* movie = static_cast<Movie*>(m);
                for (const string& star : movie->getStars()) {
                    if (star == actor) {
                        if (!found) {
                            out << string(64, '+') << "\n";
                            out << actor << " appears in the following movie(s):\n";
                            found = true;
                        }
                        out << m->getTitle() << "\n";
                        break;
                    }
                }
            }
        }
    
        if (!found) {
            err << "Unable to process command. The star: " << actor << " is not found in any movies in your list\n\n";
        }
        else {
            out << "\n\n";
        }
    
        return;
    }
    

    // Command: K - List media by keyName
    if (command == 'K' && tokens.size() == 2) {
        string name = tokens[1];
        bool found = false;
    
        for (size_t i = 0; i < mediaLib.size(); ++i) {
            if (mediaLib[i]->getName() == name) {
                if (!found) {
                    out << string(64, '+') << "\n";
                    out << "\t\t\tYOUR LIST CONTAINING " << name << "\n\n";
                    out << left << setw(4) << "#" 
                        << setw(42) << "TITLE"
                        << setw(10)  << "YEAR"
                        << setw(12)  << "RATING"
                        << setw(28) << "GENRE"
                        << "OTHER FIELDS\n";
                    found = true;
                }
                out << left << setw(2) << i + 1 << "  ";
                mediaLib[i]->print(out, mediaLib);
            }
        }
    
        if (!found) {
            err << "Unable to process command. The name: " << name << " was not found in your list\n\n";
        }
        else {
            out << "\n\n";
        }
    
        return;
    }

    // PART 1: basic comands
    if (tokens.size() == 1) {
        switch (command) {
            case 'M': printByType('M', out, mediaLib); break;
            case 'B': printByType('B', out, mediaLib); break;
            case 'S': printByType('S', out, mediaLib); break;
            case 'A': printAll(out, mediaLib); break;
            case 'T': printTotals(out, mediaLib); break;
            case 'Q': break;
            default: err << "Invalid command: " << commandRecord << endl; break;
        }
    }
    // PART 2: rating-based filtering
    else if (tokens.size() == 2 && isdigit(tokens[1][0])) {
        try {
            int rating = stoi(tokens[1]);
            if (rating < 1 || rating > 10)
                throw invalid_argument("Out of range");

            printByRating(command, rating, out, mediaLib);
        } 
        catch (...) {
            err << "The rating provided: " << tokens[1] << " is invalid\n\n";
        }
    }
    // PART 3: genre-based filtering
    else if (tokens.size() == 2) {
        string genre = tokens[1];

        for (const auto& media : mediaLib){
            if (media->getGenre() == genre) {
                printByGenre(command, genre, out, mediaLib);
                return;
            }
        }
        err << "Unable to process command. The genre: " << genre << " is not found in your list\n\n";
    }
    // PART 4: adding media
    else if (command == 'N' && tokens.size() >= 8) {
        addMedia(tokens, out, err, mediaLib);
    }
    else {
        err << "Unknown command format: " << commandRecord << endl;
    }
}



void addMedia(const vector<string>& tokens, ostream& out, ostream& err, vector<Media*>& mediaLib) {

    char type = tokens[1][0];
    string title = tokens[2];
    string name = tokens[3];
    string ratingStr = tokens[4];
    string genre = tokens[5];
    string lengthStr = tokens[6];
    string yearStr = tokens[7];

    int rating, length, year;

    // Check for "ERROR" in any field
    for (const string& field : tokens) {
        if (field == "ERROR") {
            err << "Unable to process command. There was an ERROR located in the command for: " << title << "\n\n";
            return;
        }
    }

    // Same error checking as readMediaList
    try {
        rating = stoi(ratingStr);
        if (rating < 1 || rating > 10)
            throw invalid_argument("Invalid rating");
    } catch (...) {
        err << "Unable to process command. There was an invalid value entered for item: " << title << "\n\n";
        return;
    }

    try {
        length = stoi(lengthStr);
        if (length <= 0)
            throw invalid_argument("Invalid length");
    } catch (...) {
        err << "Unable to process command. There was an invalid value entered for length: " << title << "\n\n";
        return;
    }

    try {
        year = stoi(yearStr);
        if (year < 1920 || year > 2024)
            throw invalid_argument("Invalid year");
    } catch (...) {
        err << "Unable to process command. There was an invalid value entered for year: " << title << "\n\n";
        return;
    }

    // Create object based on type this time
    // Movie, Book, or Song
    if (type == 'M') {
        vector<string> stars;
        for (size_t i = 8; i < tokens.size(); ++i) {
            stars.push_back(tokens[i]);
        }
        mediaLib.push_back(new Movie(type, title, name, rating, genre, length, year, stars));
    }

    else if (type == 'B') {
        int weeks = stoi(tokens[8]);
        mediaLib.push_back(new Book(type, title, name, rating, genre, length, year, weeks));
    }

    else if (type == 'S') {
        string topStr = tokens[8];
        bool top40 = (topStr == "1");
        mediaLib.push_back(new Song(type, title, name, rating, genre, length, year, top40));
    }

    else {
        err << "Unable to process command. Unknown type: " << type << "\n\n";
        return;
    }

    out << endl;
    out << title << " was added to your list\n\n";
    out << endl;
}


void printByType(char type, ostream& out, const vector<Media*>& mediaLib) {
    // Determine the header based on the type
    string header;
    switch (type) {
        case 'M': header = "YOUR MOVIE LIST"; break;
        case 'B': header = "YOUR BOOK LIST"; break;
        case 'S': header = "YOUR SONG LIST"; break;
        default: return;
    }

    // Header and formatting
    out << string(64, '+') << "\n";
    out << "\t\t\t" << header << "\n\n";

    out << left << setw(4) << "#" 
        << setw(42) << "TITLE"
        << setw(10)  << "YEAR"
        << setw(12)  << "RATING"
        << setw(28) << "GENRE"
        << "OTHER FIELDS\n";

    // Print media of the specified type
    for (size_t i = 0; i < mediaLib.size(); ++i) {
        if (mediaLib[i]->getType() == type) {
            out << left << setw(2) << i + 1 << "  ";
            mediaLib[i]->print(out, mediaLib);
        }
    }

    out << "\n\n";
}



void printByRating(char type, int minRating, ostream& out, const vector<Media*>& mediaLib) {
    // Determine the header based on the type
    string header;
    switch (type) {
        case 'M': header = "YOUR MOVIE LIST"; break;
        case 'B': header = "YOUR BOOK LIST"; break;
        case 'S': header = "YOUR SONG LIST"; break;
        case 'A': header = "YOUR MEDIA LIST"; break;
        default: return;
    }

    // Header and formatting
    out << string(64, '+') << "\n";
    out << "\t\t\t" << header << " FOR RATINGS >= " << minRating << "\n\n";

    out << left << setw(4) << "#" 
        << setw(42) << "TITLE"
        << setw(10)  << "YEAR"
        << setw(12)  << "RATING"
        << setw(28) << "GENRE"
        << "OTHER FIELDS\n";

    // Print media of the specified type with rating >= minRating
    for (size_t i = 0; i < mediaLib.size(); ++i) {
        if ((type == 'A' || mediaLib[i]->getType() == type) && mediaLib[i]->getRating() >= minRating) {
            out << left << setw(2) << i + 1 << "  ";
            mediaLib[i]->print(out, mediaLib);
        }
    }

    out << "\n\n";
}



void printByGenre(char type, const string& genre, ostream& out, const vector<Media*>& mediaLib) {
    // Determine the header based on the type
    string header;
    switch (type) {
        case 'M': header = "YOUR MOVIE LIST"; break;
        case 'B': header = "YOUR BOOK LIST"; break;
        case 'S': header = "YOUR SONG LIST"; break;
        case 'A': header = "YOUR MEDIA LIST"; break;
        default: return;
    }

    // Header and formatting
    out << string(64, '+') << "\n";
    out << "\t\t\t" << header << " FOR GENRE " << genre << "\n\n";

    out << left << setw(4) << "#" 
        << setw(42) << "TITLE"
        << setw(10)  << "YEAR"
        << setw(12)  << "RATING"
        << setw(28) << "GENRE"
        << "OTHER FIELDS\n";

    // Print media of the specified type and genre
    for (size_t i = 0; i < mediaLib.size(); ++i) {
        if ((type == 'A' || mediaLib[i]->getType() == type) && mediaLib[i]->getGenre() == genre) {
            out << left << setw(2) << i + 1 << "  ";
            mediaLib[i]->print(out, mediaLib);
        }
    }

    out << "\n\n";
}


void printAll(ostream& out, const vector<Media*>& mediaLib) {
    // Header and formatting
    out << string(64, '+') << "\n";
    out << "\t\t\tYOUR MEDIA LIST\n\n";

    out << left << setw(4) << "#" 
        << setw(42) << "TITLE"
        << setw(10)  << "YEAR"
        << setw(12)  << "RATING"
        << setw(28) << "GENRE"
        << "OTHER FIELDS\n";

    // Print all media
    for (size_t i = 0; i < mediaLib.size(); ++i) {
        out << left << setw(2) << i + 1 << "  ";
        mediaLib[i]->print(out, mediaLib);
    }

    out << "\n\n";
}



void printTotals(ostream& out, const vector<Media*>& mediaLib) {
    int movies = 0, books = 0, songs = 0;

    for (const auto& media : mediaLib) {
        switch (media->getType()) {
            case 'M': movies++; break;
            case 'B': books++; break;
            case 'S': songs++; break;
        }
    }

    int total = movies + books + songs;

    out << string(64, '+') << "\n";
    out << "YOUR MEDIA LIBRARY\n";
    out << "#   TYPE\n";
    out << left << setw(2) << movies << "  Movies\n";
    out << left << setw(2) << books  << "  Books\n";
    out << left << setw(2) << songs  << "  Songs\n";
    out << left << setw(2) << total  << "  Items\n";
    out << "\n\n";
}








