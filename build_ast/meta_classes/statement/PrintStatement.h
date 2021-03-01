#ifndef COMPILERS_PRINTSTATEMENT_H
#define COMPILERS_PRINTSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class PrintStatement : public Statement {
public:
    PrintStatement(Expression *expr) : expr_(expr) {}

private:
    Expression *expr_;
};

#endif //COMPILERS_PRINTSTATEMENT_H
