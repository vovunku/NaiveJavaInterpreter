#ifndef COMPILERS_IDENTIFIEREXPRESSION_H
#define COMPILERS_IDENTIFIEREXPRESSION_H

#include "Expression.h"

class IdentifierExpression : public Expression {
public:
    explicit IdentifierExpression(const std::string& ident) : identifier_(ident) {}

private:
    std::string identifier_;
};

#endif //COMPILERS_IDENTIFIEREXPRESSION_H
