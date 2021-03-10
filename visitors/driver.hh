#pragma once

#include <map>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.hh"
#include "meta_classes/program/Program.h"


class Driver {
public:
    Driver();
    Program *program;

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