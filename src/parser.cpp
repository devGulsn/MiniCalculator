#include "parser.h"
#include <cctype>
#include <cmath>pwd
#include <stdexcept>
#include <string>

using namespace std;

Parser::Parser(const string& expr) : expr(expr), pos(0) {}

double Parser::parseExpression() {
    double result = parseTerm();
    while (true) {
        skipWhitespace();
        if (peek() == '+') {
            get();
            result += parseTerm();
        } else if (peek() == '-') {
            get();
            result -= parseTerm();
        } else {
            break;
        }
    }
    return result;
}

double Parser::parseTerm() {
    double result = parseFactor();
    while (true) {
        skipWhitespace();
        if (peek() == '*') {
            get();
            result *= parseFactor();
        } else if (peek() == '/') {
            get();
            double divisor = parseFactor();
            if (divisor == 0) throw runtime_error("Division by zero");
            result /= divisor;
        } else if (peek() == '%') {
            get();
            int left = static_cast<int>(result);
            int right = static_cast<int>(parseFactor());
            if (right == 0) throw runtime_error("Modulo by zero");
            result = left % right;
        } else {
            break;
        }
    }
    return result;
}

double Parser::parseFactor() {
    double base = parsePrimary();
    skipWhitespace();
    if (peek() == '^') {
        get();
        double exponent = parseFactor();
        return pow(base, exponent);
    }
    return base;
}

double Parser::parsePrimary() {
    skipWhitespace();
    if (peek() == '(') {
        get(); // consume '('
        double value = parseExpression();
        if (get() != ')') throw runtime_error("Missing closing parenthesis");
        return value;
    }

    size_t start = pos;
    if (peek() == '-' || peek() == '+') get(); // unary sign
    while (isdigit(peek()) || peek() == '.') get();

    string numberStr = expr.substr(start, pos - start);
    try {
        return stod(numberStr);
    } catch (...) {
        throw runtime_error("Invalid number: " + numberStr);
    }
}

void Parser::skipWhitespace() {
    while (isspace(peek())) get();
}

char Parser::peek() const {
    return pos < expr.length() ? expr[pos] : '\0';
}

char Parser::get() {
    return pos < expr.length() ? expr[pos++] : '\0';
}
