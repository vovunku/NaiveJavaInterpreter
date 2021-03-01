#ifndef COMPILERS_IFSTATEMENT_H
#define COMPILERS_IFSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class IfStatement : public Statement {
public:
    IfStatement(Expression *expr, Statement *stmt) : expr_(expr), if_stmt_(stmt) {}

private:
    Expression *expr_;
    Statement *if_stmt_;
};

#endif //COMPILERS_IFSTATEMENT_H
