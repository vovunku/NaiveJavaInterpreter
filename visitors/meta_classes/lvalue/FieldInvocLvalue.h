#ifndef COMPILERS_FIELDINVOCLVALUE_H
#define COMPILERS_FIELDINVOCLVALUE_H

#include "Lvalue.h"
#include <string>

class FieldInvocLvalue: public Lvalue {
public:
    FieldInvocLvalue(const std::string& ident) : identifier_(ident) {}

private:
    std::string identifier_;
};

#endif //COMPILERS_FIELDINVOCLVALUE_H
