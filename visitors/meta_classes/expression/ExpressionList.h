#ifndef COMPILERS_EXPRESSIONLIST_H
#define COMPILERS_EXPRESSIONLIST_H

#include "../base_element/BaseElement.h"
#include "Expression.h"
#include <vector>

class ExpressionList : public BaseElement {
public:
    void add_expression(Expression *expr) {
        expression_list_.push_back(expr);
    }
private:
    std::vector<Expression *> expression_list_;
};

#endif //COMPILERS_EXPRESSIONLIST_H
