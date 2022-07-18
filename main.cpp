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
                interpreter.evaluateQueries();

                cout << "Success!" << endl;
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
        myFile.open("./example.txt");
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
                interpreter.evaluateQueries();

                cout << "Success!" << endl;
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
    // try
    // {
    //     Tuple t1;
    //     t1.push_back("A");
    //     t1.push_back("B");
    //     t1.push_back("C");

    //     Tuple t2;
    //     t2.push_back("1");
    //     t2.push_back("2");
    //     t2.push_back("1");

    //     Header h1;
    //     h1.push_back("col0");
    //     h1.push_back("col1");
    //     h1.push_back("col2");

    //     vector<unsigned int> colsToKeep;
    //     colsToKeep.push_back(2);
    //     colsToKeep.push_back(0);

    //     Relation r1;
    //     r1.setName("first");
    //     r1.setHeader(h1);
    //     r1.addTuple(t1);
    //     r1.addTuple(t2);

    //     cout << r1.project(colsToKeep)->toString() << endl;

    //     return 0;
    // }
    // catch (const char *errorMsg)
    // {
    //     cout << errorMsg;
    // }
}