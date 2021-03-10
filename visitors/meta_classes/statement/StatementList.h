#ifndef COMPILERS_STATEMENTLIST_H
#define COMPILERS_STATEMENTLIST_H

#include "Statement.h"
#include <vector>

class StatementList : public Statement {
public:
    void add_statement(Statement *statement) {
        statements_.push_back(statement);
    }

private:
    std::vector<Statement *> statements_;
};

#endif //COMPILERS_STATEMENTLIST_H
