#ifndef COMPILERS_IDENTARRAYLVALUE_H
#define COMPILERS_IDENTARRAYLVALUE_H

#include "Lvalue.h"

class IdentArrayLvalue : public Lvalue {
public:
    IdentArrayLvalue(const std::string &identifier, Expression *expr)
    : identifier_(identifier), in_paren_expr_(expr) {}

private:
    std::string identifier_;
    Expression *in_paren_expr_;
};

#endif //COMPILERS_IDENTARRAYLVALUE_H
