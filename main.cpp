#include "Lexer.h"
#include <fstream>
int main(int argc, char *argv[]) {
    if (argc > 0) {
        cout << "You have entered " << argc << " arguments:" << endl;
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }
    else {
        ifstream myFile;
        myFile.open("../in10.txt");
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