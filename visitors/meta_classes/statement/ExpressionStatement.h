#ifndef COMPILERS_EXPRESSIONSTATEMENT_H
#define COMPILERS_EXPRESSIONSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(Expression *expr) : expr_(expr) {}

private:
    Expression *expr_;
};

#endif //COMPILERS_EXPRESSIONSTATEMENT_H
