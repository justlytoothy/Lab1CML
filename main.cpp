#include "Lexer.h"
#include "Token.h"
#include <fstream>
int main(int argc, char *argv[])
{
    ifstream myFile;
    if (argc > 1)
    {

        myFile.open(argv[1]);
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
    // else
    // {
    // myFile.open("project1-exampleIO/in10.txt");
    // if (myFile.is_open())
    // {
    //     Lexer lexer;
    //     string fullFile = "";
    //     while (myFile.peek() != EOF)
    //     {
    //         fullFile += myFile.get();
    //     }
    //     fullFile += EOF;
    //     vector<Token> tokens = lexer.run(fullFile);
    //     for (unsigned int i = 0; i < tokens.size() - 1; i++)
    //     {
    //         cout << tokens.at(i).toString() << endl;
    //     }
    //     return 0;
    // }
    // else
    // {
    //     return 1;
    // }
    // }
}