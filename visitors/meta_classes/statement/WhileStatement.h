#ifndef COMPILERS_WHILESTATEMENT_H
#define COMPILERS_WHILESTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class WhileStatement : public Statement {
public:
    WhileStatement(Expression *expr, Statement *while_stmt) : expr_(expr), while_stmt_(while_stmt) {}

private:
    Expression *expr_;
    Statement *while_stmt_;
};


#endif //COMPILERS_WHILESTATEMENT_H
