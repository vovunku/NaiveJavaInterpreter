#ifndef COMPILERS_METHODDECLARATION_H
#define COMPILERS_METHODDECLARATION_H

#include "Declaration.h"
#include <string>
#include "../formals/FormalsList.h"
#include "../statement/StatementList.h"

class MethodDeclaration : public Declaration {
public:
    MethodDeclaration(Type *type, const std::string& ident, FormalsList* formals, StatementList *stmts)
    : type_(type), identifier_(ident), formals_list_(formals), statement_list_(stmts) {}

private:
    Type *type_;
    std::string identifier_;
    FormalsList *formals_list_;
    StatementList *statement_list_;
};

#endif //COMPILERS_METHODDECLARATION_H
