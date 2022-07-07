
#ifndef LAB1_TOKEN_H
#define LAB1_TOKEN_H
#include <string>
#include <sstream>
using namespace std;

enum TokenType
{
    COMMA,
    COLON,
    COLON_DASH,
    ID,
    UNDEFINED,
    EOFF,
    COMMENT,
    STRING,
    QUERIES,
    RULES,
    FACTS,
    SCHEMES,
    ADD,
    MULTIPLY,
    RIGHT_PAREN,
    LEFT_PAREN,
    Q_MARK,
    PERIOD
};
class Token
{
public:
    Token(TokenType type, const string &contents, unsigned int line);
    string toString() const
    {
        stringstream out;
        if (contents.at(0) != EOF)
        {
            out << "(" << typeName(type) << ","
                << "\"" << contents << "\""
                << "," << line << ")";
        }
        else
        {
            out << "(" << typeName(type) << ","
                << "\""
                << ""
                << "\""
                << "," << line << ")";
        }
        return out.str();
    }
    string getContents()
    {
        return contents;
    }
    string typeName(TokenType temp) const
    {
        switch (temp)
        {
        case COMMA:
            return "COMMA";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case ID:
            return "ID";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case EOFF:
            return "EOF";
        case UNDEFINED:
            return "UNDEFINED";
        default:
            return 0;
        }
    }
    TokenType getType() const
    {
        return type;
    }

private:
    TokenType type;
    string contents;
    unsigned int line;
};

Token::Token(TokenType type, const string &contents, unsigned int line) : type(type), contents(contents), line(line) {}

#endif // LAB1_TOKEN_H
