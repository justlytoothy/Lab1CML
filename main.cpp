#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Rule.h"
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
                DatalogProgram program;
                Parser parser(tokens);
                program = parser.run();
                cout << "Success!";
                cout << endl
                     << program.toString();
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
                Parser parser(tokens);
                program = parser.run();
                cout << "Success!";
                cout << endl
                     << program.toString();
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
    //     DatalogProgram program;

    //     Predicate snapScheme;
    //     snapScheme.setName("snap");
    //     snapScheme.addParameter("S");
    //     snapScheme.addParameter("N");
    //     snapScheme.addParameter("A");
    //     snapScheme.addParameter("P");

    //     program.addScheme(snapScheme);
    //     Predicate addressScheme;
    //     addressScheme.setName("HasSameAddress");
    //     addressScheme.addParameter("X");
    //     addressScheme.addParameter("Y");

    //     program.addScheme(addressScheme);
    //     Predicate snapFact;
    //     snapFact.setName("snap");
    //     snapFact.addParameter("'12345'");
    //     snapFact.addParameter("'C. Brown'");
    //     snapFact.addParameter("'12 Apple'");
    //     snapFact.addParameter("'555-1234'");

    //     program.addFact(snapFact);
    //     Rule rule;
    //     rule.setHead(addressScheme);
    //     rule.addBody(snapScheme);
    //     rule.addBody(snapScheme);

    //     program.addRule(rule);
    //     Predicate addressQuery;
    //     addressQuery.setName("HasSameAddress");
    //     addressQuery.addParameter("'Snoopy'");
    //     addressQuery.addParameter("Who");

    //     program.addQuery(addressQuery);

    //     string domain = "'12 Apple'";
    //     program.addDomain(domain);

    //     cout << program.toString();
    //     return 0;
    // }
    // catch (Token errorToken)
    // {
    //     cout << errorToken.toString() << endl;
    // }
    // catch (const char *errorMsg)
    // {
    //     cout << errorMsg;
    // }
}