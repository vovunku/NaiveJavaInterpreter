#ifndef COMPILERS_ASSERTSTATEMENT_H
#define COMPILERS_ASSERTSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"

class AssertStatement : public Statement {
public:
    AssertStatement(Expression *expr) : expr_(expr) {}

private:
    Expression *expr_;
};


#endif //COMPILERS_ASSERTSTATEMENT_H
