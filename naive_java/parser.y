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
    class PrintExpression;
    class IntExpression;
    class StringExpression;
    class BoolEpression;
    class IdentifierEpression;
    class ExpressionStatement;
    class Statement;
    class ExpressionStatement;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
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
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token <bool> BOOL "boolean"
%token <std::string> STRING "string"
%nterm <Expression *> exp
%nterm <Statement *> statement

%printer { yyo << $$; } <*>;

%%
%start wrap;
wrap: "public" "class" "identifier" "{" main_fun "}" {};

main_fun: "public" "static" "void" "main" "(" "String[]" "identifier" ")" "{" declarations_and_execute_statements "}" {};

declarations_and_execute_statements:
    %empty {}
    | declarations_and_execute_statements declaration {}
    | declarations_and_execute_statements execute_statement {};

// actually this is statement
// TODO: assertions about names
declaration:
    "int" "identifier" ";" { driver.int_variables[$2] = 0; }
    | "int" "identifier" "=" exp ";" {
    /*if(exp->get_type() != ValueType::INT) throw std::runtime_error("incorrect type");*/
    $4->evaluate(driver);
    driver.int_variables[$2] = driver.int_result;
    }
    | "bool" "identifier" ";" { driver.bool_variables[$2] = false; }
    | "bool" "identifier" "=" exp ";" {
    /*if(exp->get_type() != ValueType::BOOL) throw std::runtime_error("incorrect type");*/
    $4->evaluate(driver);
    driver.bool_variables[$2] = driver.bool_result;
    }
    | "String" "identifier" ";" { driver.string_variables[$2] = ""; }
    | "String" "identifier" "=" exp ";" {
    /*if(exp->get_type() != ValueType::STRING) throw std::runtime_error("incorrect type");*/
    $4->evaluate(driver);
    driver.string_variables[$2] = driver.string_result;
    };

execute_statement:
    statement {$1->execute(driver);};

statement:
    exp ";" {$$ = new ExpressionStatement($1);};

%left "+" "-";
%left "*" "/";

exp:
    "number" {/* std::cout << "HIE" << $1 << "BIE"; */ $$ = new IntExpression($1);}
    | "string" {$$ = new StringExpression($1);}
    | "boolean" {$$ = new BoolExpression($1);}
    | "identifier" {$$ = new IdentifierExpression(driver, $1);}
    | exp "+" exp {$$ = new PlusExpression($1, $3); }
    | "System.out.print" "(" exp ")" {$$ = new PrintExpression($3);}
    | "(" exp ")" {$$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}