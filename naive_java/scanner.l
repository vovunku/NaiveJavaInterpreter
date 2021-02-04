%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
  // A boolean symbol corresponding to the value in S.
  yy::parser::symbol_type make_BOOL(
    const std::string &s,
    const yy::parser::location_type& loc
  );
  // A String symbol corresponding to the value in S.
  yy::parser::symbol_type make_STRING(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

number   [0-9]+
String \"([^\\\"]|\\.)*\"
blank [ \t\r]
id    [a-zA-Z][a-zA-Z_0-9]*

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"public"   return yy::parser::make_PUBLIC(loc);
"class"    return yy::parser::make_CLASS(loc);
"void"     return yy::parser::make_VOID(loc);
"static"   return yy::parser::make_STATIC(loc);
"main"     return yy::parser::make_MAIN(loc);
"String[]" return yy::parser::make_STRING_PTR(loc);
"System.out.print" return yy::parser::make_PRINT(loc);
"-"        {
              //std::cout << loc.begin.line << " " << loc.end.line << std::endl;
              return yy::parser::make_MINUS  (loc);
           }
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"="        return yy::parser::make_ASSIGN (loc);

"=="       return yy::parser::make_EQUAL         (loc);
"!="       return yy::parser::make_NOT_EQUAL     (loc);
">="       return yy::parser::make_GREATER_EQUAL (loc);
"<="       return yy::parser::make_LESS_EQUAL    (loc);
">"        return yy::parser::make_GREATER       (loc);
"<"        return yy::parser::make_LESS          (loc);

"&&"       return yy::parser::make_AND     (loc);
"||"       return yy::parser::make_OR      (loc);
"!"        return yy::parser::make_NOT     (loc);

"{"        {
                //std::cout << loc.begin.line << " " << loc.end.line << " Ohi! " << std::endl;
                return yy::parser::make_CURLLPAREN (loc);
            }
"}"        return yy::parser::make_CURLRPAREN (loc);
";"        return yy::parser::make_SEMICOLON  (loc);
"int"      return yy::parser::make_INTT       (loc);
"bool"      return yy::parser::make_BOOLT     (loc);
"String"      return yy::parser::make_STRINGT (loc);


"if" return yy::parser::make_IF(loc);
"else" return yy::parser::make_ELSE(loc);
"while" return yy::parser::make_WHILE(loc);
"for" return yy::parser::make_FOR(loc);

"true" return make_BOOL("true", loc);
"false" return make_BOOL("false", loc);
{number}      return make_NUMBER(yytext, loc);
{String}   return make_STRING(yytext, loc);
{id}       return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}

yy::parser::symbol_type make_BOOL(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  if(s == "true") {
    return yy::parser::make_BOOL(true, loc);
  } else if(s == "false") {
       return yy::parser::make_BOOL(false, loc);
  } else {
    throw yy::parser::syntax_error(loc, "incorrect value" + s);
  }
}

void replace_all(std::string &s, const std::string &from, const std::string &to) {
    size_t pos = s.find(from);

        while( pos != std::string::npos)
        {
            s.replace(pos, from.size(), to);
            pos = s.find(from, pos + to.size());
        }
}

yy::parser::symbol_type make_STRING(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  std::string result = s.substr(1, s.length() - 2);
  replace_all(result, "\\n", "\n");
  replace_all(result, "\\b", "\b");
  replace_all(result, "\\t", "\t");
  replace_all(result, "\\\'", "\\\'");
  replace_all(result, "\\\"", "\\\"");
  replace_all(result, "\\\\", "\\");
  return yy::parser::make_STRING(result, loc);
}