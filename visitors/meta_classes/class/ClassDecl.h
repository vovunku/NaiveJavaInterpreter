#ifndef COMPILERS_CLASSDECL_H
#define COMPILERS_CLASSDECL_H

#include "../base_element/BaseElement.h"
#include "../declaration/DeclarationList.h"
#include <string>

class ClassDecl : public BaseElement {
public:
    ClassDecl(const std::string& identifier, const std::string& extends, DeclarationList *statements)
    : identifier_(identifier), extends_(extends), statement_list_(statements) {}

private:
    std::string identifier_;
    std::string extends_;
    DeclarationList *statement_list_;
};

#endif //COMPILERS_CLASSDECL_H
