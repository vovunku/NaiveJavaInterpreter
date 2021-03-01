#ifndef COMPILERS_ASSIGNMENTSTATEMENT_H
#define COMPILERS_ASSIGNMENTSTATEMENT_H

#include "Statement.h"
#include "../expression/Expression.h"
#include "../lvalue/Lvalue.h"

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(Lvalue *lvalue, Expression *expr) : lvalue_(lvalue), expr_(expr) {}

private:
    Lvalue *lvalue_;
    Expression *expr_;
};

#endif //COMPILERS_ASSIGNMENTSTATEMENT_H
