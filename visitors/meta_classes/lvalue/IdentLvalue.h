#ifndef COMPILERS_IDENTLVALUE_H
#define COMPILERS_IDENTLVALUE_H

#include "Lvalue.h"

class IdentLvalue : public Lvalue {
public:
    IdentLvalue(const std::string &identifier) : identifier_(identifier) {}

private:
    std::string identifier_;
};

#endif //COMPILERS_IDENTLVALUE_H
