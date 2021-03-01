#ifndef COMPILERS_RETURNSTATEMENT_H
#define COMPILERS_RETURNSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class ReturnStatement : public Statement {
public:
    ReturnStatement(Expression *expr) : expr_(expr) {}

private:
    Expression *expr_;
};

#endif //COMPILERS_RETURNSTATEMENT_H
