#ifndef COMPILERS_FORMAL_H
#define COMPILERS_FORMAL_H

#include "../base_element/BaseElement.h"
#include "../type/Type.h"
#include <string>

class Formal : public BaseElement {
public:
    Formal(Type *type, const std::string& ident) : type_(type), identifier_(ident) {}

private:
    Type * type_;
    std::string identifier_;
};

#endif //COMPILERS_FORMAL_H
