#ifndef COMPILERS_NEWEXPRESSION_H
#define COMPILERS_NEWEXPRESSION_H

#include "Expression.h"

class NewExpression : public Expression {
public:
    explicit NewExpression(Type *type) : type_identifier_(type) {}

private:
    Type * type_identifier_;
};

#endif //COMPILERS_NEWEXPRESSION_H
