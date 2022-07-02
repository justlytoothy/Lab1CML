#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
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
            try
            {
                Parser parser(tokens);
                parser.run();
                cout << "Success!";
                return 0;
            }
            catch (Token errorToken)
            {
                cout << "Failure!" << endl
                     << "  " << errorToken.toString() << endl;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        myFile.open("./Project2aPassOffCases/2-80/input1.txt");
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
            try
            {
                Parser parser(tokens);
                parser.run();
                cout << "Success!";
                return 0;
            }
            catch (Token errorToken)
            {
                cout << "Failure!" << endl
                     << "  " << errorToken.toString() << endl;
            }
        }
        else
        {
            return 1;
        }
    }
}