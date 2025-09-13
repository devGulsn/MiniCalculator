#include "calculator.h"
#include "parser.h"

double Calculator::evaluate(const std::string& expression) {
    Parser parser(expression);
    return parser.parseExpression();
}
