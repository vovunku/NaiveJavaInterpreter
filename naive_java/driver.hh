#pragma once

#include <map>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.hh"


class Driver {
public:
    Driver();
    std::map<std::string, int> int_variables;
    std::map<std::string, std::string> string_variables;
    std::map<std::string, bool> bool_variables;

    int result;

    int int_result;
    std::string string_result;
    bool bool_result;

    int parse(const std::string& f);
    std::string file;
    bool trace_parsing;

    void scan_begin();
    void scan_end();

    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
private:
    std::ifstream stream;

};


enum ValueType {
    INT,
    BOOL,
    STRING
};

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
        if(driver.int_variables.count(value) +
           driver.string_variables.count(value) +
           driver.bool_variables.count(value) != 1)
            throw std::runtime_error("incorrect identifier");
        if(driver.int_variables.count(value) == 1)
            type_ = INT;
        else if(driver.string_variables.count(value) == 1)
            type_ = STRING;
        else
            type_ = BOOL;
        value_ = value;
    }

    void evaluate (Driver& driver) override {
        switch(type_) {
            case INT :
                driver.int_result = driver.int_variables[value_];
            case STRING :
                driver.string_result = driver.string_variables[value_];
            case BOOL :
                driver.bool_result = driver.bool_variables[value_];
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