#include "filetext.h"

#include <fstream>
#include <iostream>

using namespace std;

string File::Text::load(const string& fileName) {
    string contents;
    ifstream ifs(fileName, ios::in);
    if (ifs.is_open()) {
        string line;
        while (getline(ifs, line)) {
            contents += "\n" + line;
        }
        ifs.close();
    } else {
        cerr << "Cannot open file: " << fileName << endl;
        contents = "";
    }
    return contents;
}
