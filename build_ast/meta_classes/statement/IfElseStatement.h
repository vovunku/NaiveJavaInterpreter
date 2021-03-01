#ifndef COMPILERS_IFELSESTATEMENT_H
#define COMPILERS_IFELSESTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class IfElseStatement : public Statement {
public:
    IfElseStatement(Expression *expr, Statement *if_stmt, Statement *else_stmt)
    : expr_(expr), if_stmt_(if_stmt), else_stmt_(else_stmt) {}

private:
    Expression *expr_;
    Statement *if_stmt_;
    Statement *else_stmt_;
};

#endif //COMPILERS_IFELSESTATEMENT_H
