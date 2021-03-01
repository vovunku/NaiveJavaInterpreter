#ifndef COMPILERS_PROGRAM_H
#define COMPILERS_PROGRAM_H

#include "../base_element/BaseElement.h"
#include "../class/MainClassDecl.h"
#include "../class/ClassDeclList.h"

class Program : public BaseElement {
public:
    Program(MainClassDecl *main_class, ClassDeclList *classes) : main_class_(main_class), classes_(classes) {}

private:
    MainClassDecl* main_class_;
    ClassDeclList* classes_;
};

#endif //COMPILERS_PROGRAM_H
