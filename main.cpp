#include "Lexer.h"
#include "Token.h"
#include <fstream>
int main(int argc, char *argv[])
{
    ifstream myFile;
    if (argc > 1)
    {
        // for (int i = 1; i < argc; ++i) {
        //     cout << argv[i] << endl;
        // }

        myFile.open(argv[1]);
        Lexer lexer;
        string fullFile = "";
        if (myFile.is_open())
        {
            while (myFile.peek() != EOF)
            {
                fullFile += myFile.get();
            }
            cout << fullFile << endl;
            vector<Token> tokens = lexer.run(fullFile);
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
    else
    {
        myFile.open("project1-exampleIO/in10.txt");
        if (myFile.is_open())
        {
            Lexer lexer;
            string fullFile = "";
            while (myFile.peek() != EOF)
            {
                fullFile += myFile.get();
            }
            fullFile += EOF;
            vector<Token> tokens = lexer.run(fullFile);
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