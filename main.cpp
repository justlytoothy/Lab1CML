#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include <fstream>
int main(int argc, char *argv[])
{
    // ifstream myFile;
    // if (argc > 1)
    // {

    //     myFile.open(argv[1]);
    //     if (myFile.is_open())
    //     {
    //         Lexer lexer;
    //         string fullFile = "";
    //         while (myFile.peek() != EOF)
    //         {
    //             fullFile += myFile.get();
    //         }
    //         fullFile += EOF;
    //         vector<Token> tokens = lexer.run(fullFile);
    //         for (unsigned int i = 0; i < tokens.size() - 1; i++)
    //         {
    //             cout << tokens.at(i).toString() << endl;
    //         }
    //         cout << "Total Tokens = " << tokens.size() - 1;
    //         return 0;
    //     }
    //     else
    //     {
    //         return 1;
    //     }
    // }
    // else
    // {
    //     myFile.open("example.txt");
    //     if (myFile.is_open())
    //     {
    //         Lexer lexer;
    //         string fullFile = "";
    //         while (myFile.peek() != EOF)
    //         {
    //             fullFile += myFile.get();
    //         }
    //         fullFile += EOF;
    //         vector<Token> tokens = lexer.run(fullFile);
    //         for (unsigned int i = 0; i < tokens.size() - 1; i++)
    //         {
    //             cout << tokens.at(i).toString() << endl;
    //         }
    //         return 0;
    //     }
    //     else
    //     {
    //         return 1;
    //     }
    // }
    vector<Token> tokens = {
        Token(COMMA, ",", 2),
        Token(RIGHT_PAREN, ")", 2),
        Token(COMMA, ",", 2),
        Token(ID, "Zed", 2),
        Token(RIGHT_PAREN, ")", 2),
    };

    try
    {
        Parser p = Parser(tokens);
        p.idList();
        cout << "Success!";
    }
    catch (Token errorToken)
    {
        cout << "Failure!" << endl
             << "  " << errorToken.toString();
    }
}