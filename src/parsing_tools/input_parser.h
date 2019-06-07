//
// Created by frenchcommando on 6/6/2019.
//

#ifndef PERSOTOOLS_INPUT_PARSER_H
#define PERSOTOOLS_INPUT_PARSER_H


#include <iostream>
#include <map>
#include <sstream>

class input_parser {

public:
    static int get_int(size_t i = 1);
    static void use_scanf();
    static void initials();
    static std::string digit(int n);
    static void parse_int(std::string str);
};


#endif //PERSOTOOLS_INPUT_PARSER_H
