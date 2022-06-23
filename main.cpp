#include "Lexer.h"
#include <fstream>
int main(int argc, char *argv[]) {
    if (argc > 1) {
        // for (int i = 1; i < argc; ++i) {
        //     cout << argv[i] << endl;
        // }
        ifstream myFile;
        myFile.open(argv[1]);
        if (myFile.is_open()) {
            Lexer lexer;
            string line = "";
            unsigned int lineNum = 0;
            while (getline(myFile, line)) {
                lexer.run(line, lineNum);
                lineNum++;
            }

            return 0;
        } else {
            return 1;
        }

    }
    else {
        ifstream myFile;
        myFile.open("example.txt");
        if (myFile.is_open()) {
            Lexer lexer;
            string line = "";
            unsigned int lineNum = 0;
            while (getline(myFile, line)) {
                lexer.run(line, lineNum);
                lineNum++;
            }
            return 0;
        } else {
            return 1;
        }
    }
}