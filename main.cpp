#include "Lexer.h"
#include "Token.h"
#include <fstream>
#include <sstream>
int main(int argc, char *argv[])
{
    stringstream fullFile;
    ifstream myFile;
    if (argc > 1)
    {
        // for (int i = 1; i < argc; ++i) {
        //     cout << argv[i] << endl;
        // }

        myFile.open(argv[1]);
        if (myFile.is_open())
        {
            Lexer lexer;
            string line = "";
            while (getline(myFile, line))
            {
                fullFile << line << endl;
            }
            fullFile << "EOF" << endl;
            lexer.run(fullFile.str());
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        myFile.open("example.txt");
        if (myFile.is_open())
        {
            Lexer lexer;
            string line = "";
            while (getline(myFile, line))
            {
                fullFile << line << endl;
            }
            // cout << fullFile.str() << endl;
            vector<Token> tokens = lexer.run(fullFile.str());
            for (unsigned int i = 0; i < tokens.size() - 1; i++)
            {
                cout << tokens.at(i).toString() << endl;
            }
            return 0;
        }
        else
        {
            return 1;
        }
    }
}