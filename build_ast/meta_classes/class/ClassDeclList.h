#ifndef COMPILERS_CLASSDECLLIST_H
#define COMPILERS_CLASSDECLLIST_H

#include "ClassDecl.h"
#include <vector>

class ClassDeclList : public  BaseElement {
public:
    void add_declaration(ClassDecl *class_decl_) {
        class_decl_list_.push_back(class_decl_);
    }

private:
    std::vector<ClassDecl *> class_decl_list_;
};

#endif //COMPILERS_CLASSDECLLIST_H
