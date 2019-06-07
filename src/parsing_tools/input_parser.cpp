//
// Created by frenchcommando on 6/6/2019.
//

#include "input_parser.h"

int input_parser::get_int(size_t i) {
    auto sum = 0;
    int num;
    for(size_t n = 0; n < i; n++){
        std::cout << "Please enter an integer - Remaining " << i - n << std::endl;
        std::cin >> num;
        std::cout << "Recorded integer : " << num << std::endl;
        sum += num;
        std::cout << "Current Sum : " << sum << std::endl;
    }
    return sum;
}

void input_parser::use_scanf() {
    int i;
    long l;
    char c;
    float f;
    double d;
    if(scanf("%d %ld %c %f %lf", &i, &l, &c, &f, &d))
        printf("%d %ld %c %f %lf", i, l, c, f, d);
    else
        printf("Big error in type");
}

std::string input_parser::digit(int n) {
    if (n > 9)
        return "Greater than 9";
    std::map<int, std::string> m = {
            {1, "one"},
            {2, "two"},
            {3, "three"},
            {4, "four"},
            {5, "five"},
            {6, "six"},
            {7, "seven"},
            {8, "eight"},
            {9, "nine"},
    };
    return m[n];
}

void input_parser::initials() {
    char first, last;

    std::cout << "Please, enter your first name followed by your surname: ";

    first = std::cin.get();     // get one character
    std::cin.ignore(256,' ');   // ignore until space

    last = std::cin.get();      // get one character

    std::cout << "Your initials are " << first << last << '\n';
}

void input_parser::parse_int(std::string str) {
    std::stringstream s(str);
    int n;
    char c;
    while (s >> n){
        std::cout << n << std::endl;
        s >> c;
    }
}
