#ifndef COMPILERS_IDENTIFIERTYPE_H
#define COMPILERS_IDENTIFIERTYPE_H

#include "Type.h"
#include <string>

class IdentifierType : public Type {
public:
    IdentifierType(const std::string &identifier) : identifier_(identifier) {}

private:
    std::string identifier_;
};

#endif //COMPILERS_IDENTIFIERTYPE_H
