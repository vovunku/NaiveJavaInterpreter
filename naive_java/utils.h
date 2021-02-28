#ifndef COMPILERS_UTILS_H
#define COMPILERS_UTILS_H

#include "driver.hh"


enum ValueType {
    INT,
    BOOL,
    STRING
};

int count_id(const Driver& driver, const std::string& id) {
    return driver.int_variables.count(id) +
           driver.string_variables.count(id) +
           driver.bool_variables.count(id);
}

ValueType get_id_type(const Driver& driver, const std::string& id) {
    if(driver.int_variables.count(id) == 1)
        return INT;
    else if(driver.string_variables.count(id) == 1)
        return STRING;
    else if(driver.bool_variables.count(id) == 1)
        return BOOL;
    throw std::runtime_error("there is no such variable");
}

class Expression {
public:
    virtual void evaluate(Driver& driver) = 0;

    ValueType get_type() {
        return type_;
    }

protected:
    ValueType type_;
};

class IntExpression : public Expression {
public:
    IntExpression(int value) : value_(value) {type_ = INT;}

    void evaluate (Driver& driver) override {
        driver.int_result = value_;
    }

private:
    int value_;
};

class StringExpression : public Expression {
public:
    StringExpression(std::string& value) : value_(value) {type_ = STRING;}

    void evaluate (Driver& driver) override {
        driver.string_result = value_;
    }

private:
    std::string value_;
};

class BoolExpression : public Expression {
public:
    BoolExpression(bool value) : value_(value) {type_ = BOOL;}

    void evaluate (Driver& driver) override {
        driver.bool_result = value_;
    }

private:
    bool value_;
};

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(Driver& driver, std::string& value) : value_(value) {
        if(count_id(driver, value) != 1) throw std::runtime_error("incorrect identifier");
        type_ = get_id_type(driver, value);
    }

    void evaluate (Driver& driver) override {
        switch(type_) {
            case INT :
                driver.int_result = driver.int_variables[value_];
                break;
            case STRING :
                driver.string_result = driver.string_variables[value_];
                break;
            case BOOL :
                driver.bool_result = driver.bool_variables[value_];
                break;
        }
    }

private:
    std::string value_;
};

class PlusExpression : public Expression {
public:
    PlusExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type()) {
            throw std::runtime_error("invalid arguments in plus expression");
        }
        type_ = left->get_type();
    }

    void evaluate (Driver& driver) override {
        switch (type_) {
            case INT : {
                left_->evaluate(driver);
                int left = driver.int_result;
                right_->evaluate(driver);
                int right = driver.int_result;
                driver.int_result = left + right;
            }
                break;
            case STRING : {
                left_->evaluate(driver);
                std::string left = driver.string_result;
                right_->evaluate(driver);
                std::string right = driver.string_result;
                driver.string_result = left + right;
            }
                break;
            case BOOL: {
                left_->evaluate(driver);
                bool left = driver.bool_result;
                right_->evaluate(driver);
                bool right = driver.bool_result;
                driver.bool_result = left + right;
            }
                break;
        }
    }

    ~PlusExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class MinusExpression : public Expression {
public:
    MinusExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type()) {
            throw std::runtime_error("invalid arguments in plus expression");
        }
        type_ = left->get_type();
    }

    void evaluate (Driver& driver) override {
        switch (type_) {
            case INT : {
                left_->evaluate(driver);
                int left = driver.int_result;
                right_->evaluate(driver);
                int right = driver.int_result;
                driver.int_result = left - right;
            }
                break;
            case STRING : {
                throw std::runtime_error("no minus for strings");
            }
                break;
            case BOOL: {
                left_->evaluate(driver);
                bool left = driver.bool_result;
                right_->evaluate(driver);
                bool right = driver.bool_result;
                driver.bool_result = left - right;
            }
                break;
        }
    }

    ~MinusExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class MultExpression : public Expression {
public:
    MultExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type()) {
            throw std::runtime_error("invalid arguments in plus expression");
        }
        type_ = left->get_type();
    }

    void evaluate (Driver& driver) override {
        switch (type_) {
            case INT : {
                left_->evaluate(driver);
                int left = driver.int_result;
                right_->evaluate(driver);
                int right = driver.int_result;
                driver.int_result = left * right;
            }
                break;
            case STRING : {
                throw std::runtime_error("no multiplication for strings");
            }
                break;
            case BOOL: {
                left_->evaluate(driver);
                bool left = driver.bool_result;
                right_->evaluate(driver);
                bool right = driver.bool_result;
                driver.bool_result = left * right;
            }
                break;
        }
    }

    ~MultExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class DivExpression : public Expression {
public:
    DivExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type()) {
            throw std::runtime_error("invalid arguments in plus expression");
        }
        type_ = left->get_type();
    }

    void evaluate (Driver& driver) override {
        switch (type_) {
            case INT : {
                left_->evaluate(driver);
                int left = driver.int_result;
                right_->evaluate(driver);
                int right = driver.int_result;
                driver.int_result = left / right;
            }
                break;
            case STRING : {
                throw std::runtime_error("no division for strings");
            }
                break;
            case BOOL: {
                left_->evaluate(driver);
                bool left = driver.bool_result;
                right_->evaluate(driver);
                bool right = driver.bool_result;
                driver.bool_result = left / right;
            }
                break;
        }
    }

    ~DivExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class PrintExpression : public Expression {
public:
    PrintExpression(Expression *value): value_(value) {type_ = value->get_type();}

    void evaluate (Driver& driver) override {
        value_->evaluate(driver);
        switch (type_) {
            case INT :
                std::cout << driver.int_result;
                break;
            case STRING :
                std::cout << driver.string_result;
                break;
            case BOOL:
                if(driver.bool_result == true)
                    std::cout << "true";
                else
                    std::cout << "false";
                break;
        }
    }

    ~PrintExpression() {
        delete value_;
    }

private:
    Expression *value_;
};

class AssignmentExpression : public Expression {
public:
    AssignmentExpression(Driver& driver, std::string& value, Expression *exp) : value_(value), exp_(exp) {
        if(count_id(driver, value) != 1) throw std::runtime_error("incorrect identifier");
        type_ = get_id_type(driver, value);
        if(type_ != exp->get_type()) throw std::runtime_error("incorrect expression");
    }

    void evaluate (Driver& driver) override {
        exp_->evaluate(driver);
        switch(type_) {
            case INT :
                driver.int_variables[value_] = driver.int_result;
                break;
            case STRING :
                driver.string_variables[value_] = driver.string_result;
                break;
            case BOOL :
                driver.bool_variables[value_] = driver.bool_result;
                break;
        }
    }

    ~AssignmentExpression() {
        delete exp_;
    }
private:
    std::string value_;
    Expression *exp_;
};

/* --------------------- COMPARISION STATEMENTS ----------------------- */

class EqualExpression : public Expression {
public:
    EqualExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type()) {
            throw std::runtime_error("invalid arguments in equality expression");
        }
        type_ = BOOL;
    }

    void evaluate (Driver& driver) override {
        switch (left_->get_type()) {
            case INT : {
                left_->evaluate(driver);
                int left = driver.int_result;
                right_->evaluate(driver);
                int right = driver.int_result;
                driver.bool_result = left == right;
            }
                break;
            case STRING : {
                left_->evaluate(driver);
                std::string left = driver.string_result;
                right_->evaluate(driver);
                std::string right = driver.string_result;
                driver.bool_result = left == right;
            }
                break;
            case BOOL: {
                left_->evaluate(driver);
                bool left = driver.bool_result;
                right_->evaluate(driver);
                bool right = driver.bool_result;
                driver.bool_result = left == right;
            }
                break;
        }
    }

    ~EqualExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class NotEqualExpression : public EqualExpression {
public:
    using EqualExpression::EqualExpression;

    void evaluate (Driver& driver) override {
        EqualExpression::evaluate(driver);
        driver.bool_result = !driver.bool_result;
    }
};

class IntComparisionExpression : public Expression {
public:
    IntComparisionExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type() || left_->get_type() != INT) {
            throw std::runtime_error("invalid arguments in equality expression");
        }
        type_ = BOOL;
    }

    std::pair<int, int> evaluate_parts(Driver &driver) {
        left_->evaluate(driver);
        int left = driver.int_result;
        right_->evaluate(driver);
        int right = driver.int_result;
        return std::pair<int, int>(left, right);
    }

    // dummy
    void evaluate (Driver& driver) override {
        auto result = evaluate_parts(driver);
        driver.bool_result = result.first == result.second;
    }

    ~IntComparisionExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class GreaterExpression : public IntComparisionExpression {
public:
    using IntComparisionExpression::IntComparisionExpression;

    void evaluate (Driver& driver) override {
        auto result = IntComparisionExpression::evaluate_parts(driver);
        driver.bool_result = result.first > result.second;
    }
};

class LessExpression : public IntComparisionExpression {
public:
    using IntComparisionExpression::IntComparisionExpression;

    void evaluate (Driver& driver) override {
        auto result = IntComparisionExpression::evaluate_parts(driver);
        driver.bool_result = result.first < result.second;
    }
};

class GreaterEqualExpression : public IntComparisionExpression {
public:
    using IntComparisionExpression::IntComparisionExpression;

    void evaluate (Driver& driver) override {
        auto result = IntComparisionExpression::evaluate_parts(driver);
        driver.bool_result = result.first >= result.second;
    }
};

class LessEqualExpression : public IntComparisionExpression {
public:
    using IntComparisionExpression::IntComparisionExpression;

    void evaluate (Driver& driver) override {
        auto result = IntComparisionExpression::evaluate_parts(driver);
        driver.bool_result = result.first <= result.second;
    }
};

/* ---------------- BOOL OPERATORS ----------------- */

class AndExpression : public Expression {
public:
    AndExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type() || left_->get_type() != BOOL) {
            throw std::runtime_error("invalid arguments in and-expression");
        }
        type_ = BOOL;
    }

    void evaluate (Driver& driver) override {
        left_->evaluate(driver);
        bool left = driver.bool_result;
        right_->evaluate(driver);
        bool right = driver.bool_result;
        driver.bool_result = left && right;
    }

    ~AndExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class OrExpression : public Expression {
public:
    OrExpression(Expression *left, Expression *right): left_(left), right_(right) {
        if(left_->get_type() != right_->get_type() || left_->get_type() != BOOL) {
            throw std::runtime_error("invalid arguments in or-expression");
        }
        type_ = BOOL;
    }

    void evaluate (Driver& driver) override {
        left_->evaluate(driver);
        bool left = driver.bool_result;
        right_->evaluate(driver);
        bool right = driver.bool_result;
        driver.bool_result = left || right;
    }

    ~OrExpression() {
        delete left_;
        delete right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class NotExpression : public Expression {
public:
    NotExpression(Expression *exp): exp_(exp) {
        if(exp_->get_type() != BOOL) {
            throw std::runtime_error("invalid arguments in not-expression");
        }
        type_ = BOOL;
    }

    void evaluate (Driver& driver) override {
        exp_->evaluate(driver);
        driver.bool_result = !driver.bool_result;
    }

    ~NotExpression() {
        delete exp_;
    }

private:
    Expression *exp_;
};

/*####################################### STATEMENTS ############################################*/

class Statement {
public:
    virtual void execute (Driver& driver) = 0;
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(Expression *expression) : expression_(expression) {}

    void execute (Driver& driver) {
        expression_->evaluate(driver);
    }

    ~ExpressionStatement() {
        delete expression_;
    }
private:
    Expression *expression_;
};

class StatementList : public Statement {
public:
    void push_back_statement(Statement *stmt) {
        stmts_.push_back(stmt);
    }

    void execute (Driver& driver) override {
        for(auto stmt_ptr : stmts_) {
            stmt_ptr->execute(driver);
        }
    }

    ~StatementList() {
        for(auto stmt_ptr : stmts_) {
            delete stmt_ptr;
        }
    }
private:
    std::vector<Statement *> stmts_;
};

class IfElseStatement : public Statement {
public:
    IfElseStatement(Expression *if_expr, Statement *if_stmt, Statement *else_stmt)
    : if_expr_(if_expr), if_stmt_(if_stmt), else_stmt_(else_stmt) {
        if(if_expr->get_type() != BOOL) throw std::runtime_error("incorrect if statement");
    }

    void execute(Driver &driver) override {
        if_expr_->evaluate(driver);
        if(driver.bool_result) {
            if_stmt_->execute(driver);
        } else {
            else_stmt_->execute(driver);
        }
    }

    ~IfElseStatement() {
        delete if_expr_;
        delete if_stmt_;
        delete else_stmt_;
    }
private:
    Expression *if_expr_;
    Statement *if_stmt_;
    Statement *else_stmt_;
};

class WhileStatement : public Statement {
public:
    WhileStatement(Expression *while_expr, Statement *while_stmt)
            : while_expr_(while_expr), while_stmt_(while_stmt) {
        if(while_expr->get_type() != BOOL) throw std::runtime_error("incorrect if statement");
    }

    void execute(Driver &driver) override {
        while_expr_->evaluate(driver);
        while(driver.bool_result) {
            while_stmt_->execute(driver);
            while_expr_->evaluate(driver);
        }
    }

    ~WhileStatement() {
        delete while_expr_;
        delete while_stmt_;
    }
private:
    Expression *while_expr_;
    Statement *while_stmt_;
};

class ForStatement : public Statement {
public:
    ForStatement(Expression *bool_expr, Expression *repetition_exp, Statement *for_stmt)
            : bool_expr_(bool_expr), repetition_exp_(repetition_exp), for_stmt_(for_stmt) {
        if(bool_expr->get_type() != BOOL) throw std::runtime_error("incorrect if statement");
    }

    void execute(Driver &driver) override {
        bool_expr_->evaluate(driver);
        while(driver.bool_result) {
            for_stmt_->execute(driver);
            repetition_exp_->evaluate(driver);
            bool_expr_->evaluate(driver);
        }
    }

    ~ForStatement() {
        delete bool_expr_;
        delete repetition_exp_;
        delete for_stmt_;
    }
private:
    Expression *bool_expr_;
    Expression *repetition_exp_;
    Statement *for_stmt_;
};

#endif //COMPILERS_UTILS_H
