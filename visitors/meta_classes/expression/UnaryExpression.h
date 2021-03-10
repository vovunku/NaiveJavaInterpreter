#ifndef COMPILERS_UNARYEXPRESSION_H
#define COMPILERS_UNARYEXPRESSION_H

#include "Expression.h"

// for those who require one expressions ro evaluate
class UnaryExpression : public Expression {
public:
    explicit UnaryExpression(Expression *expr) : expr_(expr) {}

private:
    Expression *expr_;
};

#endif //COMPILERS_UNARYEXPRESSION_H
