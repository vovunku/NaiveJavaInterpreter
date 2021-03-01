#ifndef COMPILERS_VARIABLEDECLARATION_H
#define COMPILERS_VARIABLEDECLARATION_H

#include "Declaration.h"
#include "../type/Type.h"
#include <string>

class VariableDeclaration : public Declaration {
public:
    VariableDeclaration(Type *type, const std::string &ident)
    : type_(type), identifier_(ident) {}

private:
    Type *type_;
    std::string identifier_;
};

#endif //COMPILERS_VARIABLEDECLARATION_H
