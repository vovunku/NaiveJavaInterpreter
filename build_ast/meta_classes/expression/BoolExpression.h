#ifndef COMPILERS_BOOLEXPRESSION_H
#define COMPILERS_BOOLEXPRESSION_H

#include "Expression.h"

class BoolExpression : public Expression {
public:
    explicit BoolExpression(bool boolean) : boolean_(boolean) {}

private:
    bool boolean_;
};

#endif //COMPILERS_BOOLEXPRESSION_H
