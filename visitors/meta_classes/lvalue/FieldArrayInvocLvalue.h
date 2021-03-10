#ifndef COMPILERS_FIELDARRAYINVOCLVALUE_H
#define COMPILERS_FIELDARRAYINVOCLVALUE_H

#include "Lvalue.h"
#include <string>

class FieldArrayInvocLvalue : public Lvalue {
public:
    FieldArrayInvocLvalue(const std::string &ident, Expression *expr) : identifier_(ident), in_paren_expr_(expr) {}

private:
    std::string identifier_;
    Expression *in_paren_expr_;
};

#endif //COMPILERS_FIELDARRAYINVOCLVALUE_H
