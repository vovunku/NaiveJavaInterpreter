#ifndef COMPILERS_ARRAYTYPE_H
#define COMPILERS_ARRAYTYPE_H

#include "Type.h"

class ArrayType : public Type {
public:
    ArrayType(Type *base_type) : base_type_(base_type) {}

private:
    Type *base_type_;
};

#endif //COMPILERS_ARRAYTYPE_H
