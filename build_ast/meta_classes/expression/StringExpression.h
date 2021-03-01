#ifndef COMPILERS_STRINGEXPRESSION_H
#define COMPILERS_STRINGEXPRESSION_H

#include "Expression.h"

class StringExpression : public Expression {
public:
    explicit StringExpression(const std::string &string) : string_(string) {}

private:
    std::string string_;
};

#endif //COMPILERS_STRINGEXPRESSION_H
