#include <iostream>
#include <input_parser.h>
#include <numeric_helper.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    input_parser::get_int(1);
    input_parser::use_scanf();
    input_parser::initials();
    std::cout << input_parser::digit(8) << std::endl;
    std::cout << numeric_helper::vmax(12., 13., 20., 10.) <<std::endl;
    std::cout << numeric_helper::amax(12., 13., 20., 10.) <<std::endl;
    input_parser::parse_int("123h3213,12321ttt.3213");
    return 0;
}