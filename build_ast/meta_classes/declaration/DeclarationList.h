#ifndef COMPILERS_DECLARATIONLIST_H
#define COMPILERS_DECLARATIONLIST_H

#include "../base_element/BaseElement.h"
#include "Declaration.h"
#include <vector>

class DeclarationList : public BaseElement {
public:
    void add_declaration(Declaration *decl) {
        decl_list_.push_back(decl);
    }

private:
    std::vector<Declaration *> decl_list_;
};

#endif //COMPILERS_DECLARATIONLIST_H
