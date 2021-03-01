#ifndef COMPILERS_FIELDINVOCEXPRESSION_H
#define COMPILERS_FIELDINVOCEXPRESSION_H

#include "Expression.h"
#include "../lvalue/Lvalue.h"

class FieldInvocExpression : public Expression {
public:
    explicit FieldInvocExpression(Lvalue *lvalue) : field_(lvalue) {}

private:
    Lvalue *field_;
};

#endif //COMPILERS_FIELDINVOCEXPRESSION_H
