#ifndef COMPILERS_LOCALVARIABLEDECLSTATEMENT_H
#define COMPILERS_LOCALVARIABLEDECLSTATEMENT_H

#include "Statement.h"
#include "../declaration/Declaration.h"

class LocalVariableDeclStatement : public Statement {
public:
    LocalVariableDeclStatement(Declaration *variable_declaration) : variable_declaration(variable_declaration) {}

private:
    Declaration *variable_declaration;
};

#endif //COMPILERS_LOCALVARIABLEDECLSTATEMENT_H
