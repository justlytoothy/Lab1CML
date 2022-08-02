#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Relation.h"
#include "Database.h"
#include <fstream>
#include "Interpreter.h"
using namespace std;
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
                DatalogProgram program;

                Database database;
                Parser parser(tokens);
                program = parser.run();
                Interpreter interpreter(program);
                interpreter.evaluateRules();
                interpreter.evaluateQueries();

                cout << interpreter.toString();
                return 0;
            }
            catch (Token errorToken)
            {
                cout << "Failure!" << endl
                     << "  " << errorToken.toString() << endl;
            }
            catch (const char *errorMsg)
            {
                cout << errorMsg;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        myFile.open("./Lab4PassOffCases/4-100/input1.txt");
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
                DatalogProgram program;

                Database database;
                Parser parser(tokens);
                program = parser.run();
                Interpreter interpreter(program);
                interpreter.evaluateRules();
                interpreter.evaluateQueries();

                cout << interpreter.toString();
                return 0;
            }
            catch (Token errorToken)
            {
                cout << "Failure!" << endl
                     << "  " << errorToken.toString() << endl;
            }
            catch (const char *errorMsg)
            {
                cout << errorMsg;
            }
        }
        else
        {
            return 1;
        }
    }
}