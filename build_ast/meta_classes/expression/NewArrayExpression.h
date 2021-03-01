#ifndef COMPILERS_NEWARRAYEXPRESSION_H
#define COMPILERS_NEWARRAYEXPRESSION_H

#include "Expression.h"

class NewArrayExpression : public Expression {
public:
    NewArrayExpression(Type *type, Expression *expr) : type_(type), in_paren_expr_(expr) {}

private:
    Type *type_;
    Expression *in_paren_expr_;
};

#endif //COMPILERS_NEWARRAYEXPRESSION_H
