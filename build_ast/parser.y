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
    class Statement;
    class StatementList;
    class Declaration;
    class DeclarationList;
    class ClassDecl;
    class ClassDeclList;
    class ExpressionList;
    class FormalsList;
    class Lvalue;
    class Program;
    class Type;
    class Visitor;
    class MainClassDecl;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "meta_classes/utils.h"
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
    HARDLPAREN "["
    HARDRPAREN "]"
    PUBLIC "public"
    CLASS "class"
    VOID "void"
    MAIN "main"
    NEW "new"
    THIS "this"
    STATIC "static"
    PRINT "System.out.print"
    ASSERT "assert"
    LENGTH "length"
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
    DOT "."
    RETURN "return"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token <bool> BOOL "boolean"
%token <std::string> STRING "string"
%nterm <Program *> program
%nterm <MainClassDecl *> main_class
%nterm <ClassDecl *> class_decl
%nterm <ClassDeclList *> class_decl_list
%nterm <Expression *> exp
%nterm <Expression *> method_invocation
%nterm <ExpressionList *> expression_list
%nterm <Statement *> statement
%nterm <StatementList *> statement_list
%nterm <Declaration *> declaration
%nterm <Declaration *> variable_declaration
%nterm <Declaration *> method_declaration
%nterm <DeclarationList *> declaration_list
%nterm <FormalsList *> formals_list
%nterm <Type *> type
%nterm <Type *> simple_type
%nterm <Type *> array_type
%nterm <Type *> type_identifier
%nterm <Lvalue *> lvalue
%nterm <Lvalue *> field_invocation

%printer { yyo << $$; } <*>;

%%
%start program;
program: main_class class_decl_list {driver.program = new Program($1, $2); }

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statement_list "}" "}"
     	{$$ = new MainClassDecl($2, $11); }

statement_list:
    %empty {$$ = new StatementList();}
    | statement_list statement {$1->add_statement($2); $$ = $1;};

class_decl_list:
    %empty {$$ = new ClassDeclList(); }
    | class_decl_list class_decl {$1->add_declaration($2); $$ = $1; }

class_decl:
    "class" "identifier" "{" declaration_list "}" {$$ = new ClassDecl($2, "", $4); }
    | "class" "identifier" "extends" "identifier" "{" declaration_list "}" {$$ = new ClassDecl($2, $4, $6); }

declaration_list:
    %empty {$$ = new DeclarationList(); }
    | declaration_list declaration {$1->add_declaration($2); $$ = $1; }

declaration:
    variable_declaration {$$ = $1; }
    | method_declaration {$$ = $1; }

method_declaration:
    "public" type "identifier" "(" formals_list ")" "{" statement_list "}" {$$ = new MethodDeclaration($2, $3, $5, $8); }

variable_declaration:
    type "identifier" ";" {$$ = new VariableDeclaration($1, $2); }

formals_list:
    %empty {$$ = new FormalsList(); }
    | type "identifier" {$$ = new FormalsList(); $$->add_formal(new Formal($1, $2)); }
    | formals_list "," type "identifier" {$1->add_formal(new Formal($3, $4)); $$ = $1; }

type:
    simple_type {$$ = $1; }
    | array_type {$$ = $1; }


simple_type:
    "int" {$$ = new IntType(); }
    | "boolean" {$$ = new BoolType(); }
    | "void" {$$ = new VoidType(); }
    | "String" {$$ = new StringType(); }
    | type_identifier {$$ = $1; }

array_type:
    simple_type "[" "]" {$$ = new ArrayType($1); } // why not all???

type_identifier:
    "identifier" {$$ = new IdentifierType($1); }

statement:
    exp ";" {$$ = new ExpressionStatement($1);}
    | "{" statement_list "}" {$$ = $2;}
    | "if"  "(" exp ")" statement {$$ = new IfStatement($3, $5);}
    | "if" "(" exp ")" statement "else" statement {$$ = new IfElseStatement($3, $5, $7);}
    | "while" "(" exp ")" statement {$$ = new WhileStatement($3, $5);}
    // | "for" "(" ";" exp ";" exp ")" statement {$$ = new ForStatement($4, $6, $8);};
    | "assert" "(" exp ")" ";" {$$ = new AssertStatement($3); }
    | "System.out.print" "(" exp ")" ";" {$$ = new PrintStatement($3); }
    | lvalue "=" exp ";" {$$ = new AssignmentStatement($1, $3); }
    | "return" exp ";" {$$ = new ReturnStatement($2); }
    // | method_invocation ";" // already have in exp ;
    | variable_declaration {$$ = new LocalVariableDeclStatement($1); } // local

method_invocation:
    exp "." "identifier" "(" expression_list ")" {$$ = new MethodInvocExpression($1, $5); }

expression_list:
    %empty {$$ = new ExpressionList(); }
    | exp {$$ = new ExpressionList(); $$->add_expression($1); }
    | expression_list "," exp {$1->add_expression($3); $$ = $1; }

field_invocation: // basically lvalue, but can be exp
    exp "." "identifier" {$$ = new FieldInvocLvalue($3); } // TODO: PROBLEM WITH THIS
    | exp "." "identifier" "[" exp "]" {$$ = new FieldArrayInvocLvalue($3, $5); } // TODO: PROBLEM WITH THIS

lvalue:
    "identifier" {$$ = new IdentLvalue($1); }
    | "identifier" "[" exp "]" {$$ = new IdentArrayLvalue($1, $3); }
    | field_invocation {$$ = $1; }

%right "=";
%left "&&";
%left "||";
%left "==" "!=";
%left "<" ">" "<=" ">=";
%left "+" "-";
%left "*" "/";
%left "!";

exp:
    "this" {$$ = new ThisExpression(); }
    | "number" {/* std::cout << "HIE" << $1 << "BIE"; */ $$ = new IntExpression($1);}
    | "string" {$$ = new StringExpression($1);}
    | "boolean" {$$ = new BoolExpression($1);}
    | "identifier" {$$ = new IdentifierExpression($1);}
    // | "identifier" "=" exp {$$ = new AssignmentExpression($1, $3);}
    | exp "+" exp {$$ = new PlusExpression($1, $3); }
    | exp "-" exp {$$ = new MinusExpression($1, $3); }
    | exp "*" exp {$$ = new MulExpression($1, $3); }
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
    // | "System.out.print" "(" exp ")" {$$ = new PrintExpression($3);}
    | "(" exp ")" {$$ = $2; };
    | exp "[" exp "]" {$$ = new HardParenExpression($1, $3); }
    | exp "." "length" {$$ = new LengthExpression($1); }
    | "new" simple_type "[" exp "]" {$$ = new NewArrayExpression($2, $4); }
    | method_invocation {$$ = $1; }
    | field_invocation {$$ = new FieldInvocExpression($1); }
    | "new" type_identifier "(" ")" {$$ = new NewExpression($2); }

%%

/*
<program> ::=	<main class> <class declaration>*

<main class> ::=	class <identifier> "{" public static void main "(" ")" "{" <statement>* "}"   "}"

<class declaration> ::=	class <identifier> [ extends <identifier> ] "{" <declaration>* "}"

<declaration> ::=	<variable declaration> | <method declaration>

<method declaration> ::=	public <type> <identifier> "(" [ <formals> ] ")" "{" <statement>* "}"

<variable declaration> ::=	<type> <identifier> ";"

<formals> ::=	<type> <identifier> ( "," <type> <identifier> )*

<type> ::=	<simple type> | <array type>

<simple type> ::=	int | boolean | void | <type identifier>

<array type> ::=	<simple type> "[" "]"

<type identifier> ::=	<identifier>

<statement> ::=	assert "(" expr ")"  |
                <local variable declaration>  |
                "{" <statement>* "}"  |
                if  "(" <expr> ")" <statement>  |
                if  "(" <expr> ")" <statement> else <statement>  |
                while  "(" <expr> ")" <statement>  |
                System.out.println "(" <expr> ")" ";"  |
                <lvalue> "=" <expr> ";"  |
                return <expr> ";"  |
                <method invocation> ";"


<local variable declaration> ::=	<variable declaration>

<method invocation> ::=	<expr> "." <identifier> "(" [ <expr> ("," <expr>)* ] ")"

<field invocation>  ::= this "." <identifier> | this "." <identifier> "[" <expr> "]"

<lvalue> ::=	<identifier> | <identifier> "[" <expr> "]" | <field invocation>

<expr> ::=	<expr> <binary operator> <expr>  |
            <expr> "[" <expr> "]"  |
            <expr> "." length  |
            new <simple type> "[" <expr> "]"  |
            new <type identifier> "(" ")"  |
            "!" <expr>  |
            "(" <expr> ")"  |
            <identifier>  | <integer literal>  |
            this  | true  | false  |
            <method invocation>    | <field invocation>


<binary operator> ::=	"&&"   |  "||"   |  "<"   | ">"   |  "=="   | "+"   |  "-"   | "*"  | "/"  | "%"
*/

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}