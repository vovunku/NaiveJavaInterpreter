%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <stdexcept>
    class Scanner;
    class Driver;
    class Expression;
    class PlusExpression;
    class MinusExpression;
    class MultExpression;
    class DivExpression;
    class PrintExpression;
    class IntExpression;
    class StringExpression;
    class BoolEpression;
    class IdentifierExpression;
    class AsignmentExpression;

    class ExpressionStatement;
    class Statement;
    class ExpressionStatement;
    class StatementList;
    class IfElseStatement;
    class WhileStatement;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "utils.h"
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    CURLLPAREN "{"
    CURLRPAREN "}"
    PUBLIC "public"
    CLASS "class"
    VOID "void"
    STRING_PTR "String[]"
    MAIN "main"
    STATIC "static"
    PRINT "System.out.print"
    SEMICOLON ";"
    INTT "int"
    STRINGT "String"
    BOOLT "bool"
    IF "if"
    ELSE "else"
    WHILE "while"
    FOR "for"
    EQUAL "=="
    NOT_EQUAL "!="
    GREATER ">"
    LESS "<"
    GREATER_EQUAL ">="
    LESS_EQUAL "<="
    AND "&&"
    OR "||"
    NOT "!"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token <bool> BOOL "boolean"
%token <std::string> STRING "string"
%nterm <Expression *> exp
%nterm <Statement *> statement
%nterm <StatementList *> statement_list

%printer { yyo << $$; } <*>;

%%
%start wrap;
wrap: "public" "class" "identifier" "{" main_fun "}" {};

main_fun: "public" "static" "void" "main" "(" "String[]" "identifier" ")" "{" declarations_and_execute_statements "}" {};

declarations_and_execute_statements:
    %empty {}
    | declarations_and_execute_statements declaration {}
    | declarations_and_execute_statements execute_statement {};

declaration:
    "int" "identifier" ";" { driver.int_variables[$2] = 0; }
    | "int" "identifier" "=" exp ";" {
    if(count_id(driver, $2) != 0) throw std::runtime_error("there is such identifier");
    if($4->get_type() != ValueType::INT) throw std::runtime_error("incorrect type");
    $4->evaluate(driver);
    driver.int_variables[$2] = driver.int_result;
    }
    | "bool" "identifier" ";" { driver.bool_variables[$2] = false; }
    | "bool" "identifier" "=" exp ";" {
    if(count_id(driver, $2) != 0) throw std::runtime_error("there is such identifier");
    if($4->get_type() != ValueType::BOOL) throw std::runtime_error("incorrect type");
    $4->evaluate(driver);
    driver.bool_variables[$2] = driver.bool_result;
    }
    | "String" "identifier" ";" { driver.string_variables[$2] = ""; }
    | "String" "identifier" "=" exp ";" {
    if(count_id(driver, $2) != 0) throw std::runtime_error("there is such identifier");
    if($4->get_type() != ValueType::STRING) throw std::runtime_error("incorrect type");
    $4->evaluate(driver);
    driver.string_variables[$2] = driver.string_result;
    };

execute_statement:
    statement {$1->execute(driver);};

statement:
    exp ";" {$$ = new ExpressionStatement($1);}
    | "{" statement_list "}" {$$ = $2;}
    | "if" "(" exp ")" statement "else" statement {$$ = new IfElseStatement($3, $5, $7);}
    | "while" "(" exp ")" statement {$$ = new WhileStatement($3, $5);}
    | "for" "(" ";" exp ";" exp ")" statement {$$ = new ForStatement($4, $6, $8);};

statement_list:
    %empty {$$ = new StatementList;}
    | statement_list statement {$1->push_back_statement($2); $$ = $1;};

%right "=";
%left "&&";
%left "||";
%left "==" "!=";
%left "<" ">" "<=" ">=";
%left "+" "-";
%left "*" "/";
%left "!";

exp:
    "number" {/* std::cout << "HIE" << $1 << "BIE"; */ $$ = new IntExpression($1);}
    | "string" {$$ = new StringExpression($1);}
    | "boolean" {$$ = new BoolExpression($1);}
    | "identifier" {$$ = new IdentifierExpression(driver, $1);}
    | "identifier" "=" exp {$$ = new AssignmentExpression(driver, $1, $3);}
    | exp "+" exp {$$ = new PlusExpression($1, $3); }
    | exp "-" exp {$$ = new MinusExpression($1, $3); }
    | exp "*" exp {$$ = new MultExpression($1, $3); }
    | exp "/" exp {$$ = new DivExpression($1, $3); }
    | exp "==" exp {$$ = new EqualExpression($1, $3); }
    | exp "!=" exp {$$ = new NotEqualExpression($1, $3); }
    | exp ">=" exp {$$ = new GreaterEqualExpression($1, $3); }
    | exp "<=" exp {$$ = new LessEqualExpression($1, $3); }
    | exp ">" exp {$$ = new GreaterExpression($1, $3); }
    | exp "<" exp {$$ = new LessExpression($1, $3); }
    | exp "&&" exp {$$ = new AndExpression($1, $3); }
    | exp "||" exp {$$ = new OrExpression($1, $3); }
    | "!" exp {$$ = new NotExpression($2); }
    | "System.out.print" "(" exp ")" {$$ = new PrintExpression($3);}
    | "(" exp ")" {$$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}