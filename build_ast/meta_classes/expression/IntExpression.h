#ifndef COMPILERS_INTEXPRESSION_H
#define COMPILERS_INTEXPRESSION_H

#include "Expression.h"

class IntExpression : public Expression {
public:
    explicit IntExpression(int integer) : integer_(integer) {}

private:
    int integer_;
};

#endif //COMPILERS_INTEXPRESSION_H
