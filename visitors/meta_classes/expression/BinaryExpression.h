#ifndef COMPILERS_BINARYEXPRESSION_H
#define COMPILERS_BINARYEXPRESSION_H

#include "Expression.h"

// for those who require two expressions ro evaluate
class BinaryExpression : public Expression {
public:
    BinaryExpression(Expression *left, Expression *right) : left_(left), right_(right) {}

private:
    Expression *left_;
    Expression *right_;
};

#endif //COMPILERS_BINARYEXPRESSION_H
