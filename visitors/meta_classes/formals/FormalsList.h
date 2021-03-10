#ifndef COMPILERS_FORMALSLIST_H
#define COMPILERS_FORMALSLIST_H

#include "../base_element/BaseElement.h"
#include "Formal.h"
#include <vector>

class FormalsList : public BaseElement {
public:
    void add_formal(Formal *formal) {
        formals_list_.push_back(formal);
    }

private:
    std::vector<Formal *> formals_list_;
};

#endif //COMPILERS_FORMALSLIST_H
