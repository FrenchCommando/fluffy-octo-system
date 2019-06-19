//
// Created by frenchcommando on 6/7/2019.
//

#include <iostream>
#include <input_parser.h>
#include <numeric_helper.h>

void run_input_parser(){
    input_parser::get_int(1);
    input_parser::use_scanf();
    input_parser::initials();
    std::cout << input_parser::digit(8) << std::endl;
    input_parser::parse_int("123h3213,12321ttt.3213");
}

void run_numeric_helper(){
    std::cout << numeric_helper::vmax(12., 13., 20., 10.) <<std::endl;
    std::cout << numeric_helper::amax(12., 13., 20., 10.) <<std::endl;
}

void run_one();

void run_two();

void run_loop();


int main() {
    std::cout << "Hello, World!" << std::endl;
//    run_input_parser();
    run_numeric_helper();
//    run_one();
//    run_two();
    run_loop();
    return 0;
}