#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser {
public:
    explicit Parser(const std::string& expr);
    double parseExpression();

private:
    std::string expr;
    size_t pos;

    double parseTerm();
    double parseFactor();
    double parsePrimary();
    void skipWhitespace();
    char peek() const;
    char get();
};

#endif
