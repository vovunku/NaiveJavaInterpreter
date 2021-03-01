#ifndef COMPILERS_MAINCLASSDECL_H
#define COMPILERS_MAINCLASSDECL_H

#include "../base_element/BaseElement.h"
#include "../statement/StatementList.h"

class MainClassDecl : public BaseElement {
public:
    MainClassDecl(const std::string &identifier, StatementList *statements)
    : identifier_(identifier), statements_(statements) {}

private:
    std::string identifier_;
    StatementList *statements_;
};

#endif //COMPILERS_MAINCLASSDECL_H
