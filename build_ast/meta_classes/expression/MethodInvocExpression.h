#ifndef COMPILERS_METHODINVOCEXPRESSION_H
#define COMPILERS_METHODINVOCEXPRESSION_H

#include "Expression.h"
#include "ExpressionList.h"

class MethodInvocExpression : public Expression {
public:
    MethodInvocExpression(Expression *from_expr, ExpressionList *args) : from_expr_(from_expr), args_(args) {}

private:
    Expression *from_expr_;
    ExpressionList *args_;
};

#endif //COMPILERS_METHODINVOCEXPRESSION_H
