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
    //         try
    //         {
    //             DatalogProgram program;

    //             Database database;
    //             Parser parser(tokens);
    //             program = parser.run();
    //             Interpreter interpreter(program);
    //             interpreter.evaluateQueries();

    //             cout << interpreter.toString();
    //             return 0;
    //         }
    //         catch (Token errorToken)
    //         {
    //             cout << "Failure!" << endl
    //                  << "  " << errorToken.toString() << endl;
    //         }
    //         catch (const char *errorMsg)
    //         {
    //             cout << errorMsg;
    //         }
    //     }
    //     else
    //     {
    //         return 1;
    //     }
    // }
    // else
    // {
    //     myFile.open("./Lab3PassOffCases/3-80/input1.txt");
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
    //         try
    //         {
    //             DatalogProgram program;

    //             Database database;
    //             Parser parser(tokens);
    //             program = parser.run();
    //             Interpreter interpreter(program);
    //             interpreter.evaluateQueries();

    //             cout << interpreter.toString();
    //             return 0;
    //         }
    //         catch (Token errorToken)
    //         {
    //             cout << "Failure!" << endl
    //                  << "  " << errorToken.toString() << endl;
    //         }
    //         catch (const char *errorMsg)
    //         {
    //             cout << errorMsg;
    //         }
    //     }
    //     else
    //     {
    //         return 1;
    //     }
    // }
    try
    {
        Tuple snap_t1;
        snap_t1.push_back("33333");
        snap_t1.push_back("Snoopy");
        snap_t1.push_back("12 Apple St.");
        snap_t1.push_back("555-1234");

        Tuple snap_t2;
        snap_t2.push_back("12345");
        snap_t2.push_back("C. Brown");
        snap_t2.push_back("12 Apple St.");
        snap_t2.push_back("555-1234");

        Tuple snap_t3;
        snap_t3.push_back("22222");
        snap_t3.push_back("P. Patty");
        snap_t3.push_back("56 Grape Blvd");
        snap_t3.push_back("555-9999");

        Tuple csg_t1;
        csg_t1.push_back("cs101");
        csg_t1.push_back("12345");
        csg_t1.push_back("A");

        Tuple csg_t2;
        csg_t2.push_back("cs101");
        csg_t2.push_back("22222");
        csg_t2.push_back("B");

        Tuple csg_t3;
        csg_t3.push_back("cs101");
        csg_t3.push_back("33333");
        csg_t3.push_back("C");

        Tuple csg_t4;
        csg_t4.push_back("EE200");
        csg_t4.push_back("12345");
        csg_t4.push_back("B+");

        Tuple csg_t5;
        csg_t5.push_back("EE200");
        csg_t5.push_back("22222");
        csg_t5.push_back("B");

        Header h1;
        h1.push_back("StudentID");
        h1.push_back("Name");
        h1.push_back("Address");
        h1.push_back("Phone");

        Header h2;
        h2.push_back("Course");
        h2.push_back("StudentID");
        h2.push_back("Grade");

        Relation r1;
        r1.setName("snap");
        r1.setHeader(h1);
        r1.addTuple(snap_t1);
        r1.addTuple(snap_t2);
        r1.addTuple(snap_t3);

        Relation r2;
        r2.setName("csg");
        r2.setHeader(h2);
        r2.addTuple(csg_t1);
        r2.addTuple(csg_t2);
        r2.addTuple(csg_t3);
        r2.addTuple(csg_t4);
        r2.addTuple(csg_t5);

        cout << r1.naturalJoin(&r2)->toString() << endl
             << endl;

        return 0;
    }
    catch (const char *errorMsg)
    {
        cout << errorMsg;
    }
}