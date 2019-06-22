//
// Created by frenchcommando on 6/11/2019.
//

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "palindrome.h"
#include "palindrome_substring.h"
#include "arthur.h"

#define watch(x) std::cout << (#x) << "\t:\t" << (x) << std::endl

void check_rep(const std::string& s1, const std::string& s2, const std::string& s_ref){
//    watch(s1);
//    watch(s2);
//    watch(s_ref);
//    std::cout << s1.length() << "\t" << s2.length() << std::endl;

    auto s_rep = palindrome::palindrome_substring::solve(s1, s2);
//    std::cout << s_rep.length() << std::endl;

    //    watch(s_rep);
    if (s_ref == s_rep)
        std::cout << "\tMatch !!!" << std::endl;
    else{
        watch(s_rep);
        std::cout << "\tERROR ::  NO Match !!!" << std::endl;
    }
    std::cout << std::endl;
}

void test_files(const std::string& f1, const std::string& f2){
//    std::cout << f1 << std::endl;
    std::string dir = "/mnt/c/Users/marti/CLionProjects/PersoTools/palindrome_sandbox/";
    std::ifstream infile_test (dir + f1);
    std::ifstream infile_rep (dir + f2);
    int n;
    std::string s1, s2, s_ref;
    infile_test >> n;
//    watch(n);
    while (infile_test >> s1){
//        watch(s1);
        infile_test >> s2;
        infile_rep >> s_ref;
        check_rep(s1, s2, s_ref);
    }
}

void test_num(size_t n){
    std::cout << "Test " << n << std::endl;
    test_files("test" + std::to_string(n), "rep" + std::to_string(n));
}

void test_txt(){
    test_num(0);
    test_num(10);
    test_num(18);
    test_num(20);
    test_num(23);
    test_num(24);

}

void test_palindrome(){
    std::vector<std::pair<std::string, std::string>> v;
    v.emplace_back("jdfh", "fds");
    std::string s = "pb\n"
                    "kkb\n"
                    "zlc\n"
                    "zdw\n"
                    "w\n"
                    "d";
    std::stringstream ss(s);
    std::string s1, s2;
    while(ss >> s1){
        ss >> s2;
        v.emplace_back(s1, s2);
    }

    for (const auto& p : v){
        std::cout << "Solving : " << p.first << "  -  " << p.second << std::endl;
        std::cout << " -> " << PalindromeSolver::solve(p.first, p.second) << std::endl;
        std::cout << " -> " << palindrome::palindrome_substring::solve(p.first, p.second) << std::endl;
//        PalindromeSolver::display_grid(p.first + p.second);
    }

}

int main() {
//    test_palindrome();
    test_txt();

//    std::cout << arthur::STrie("aabbaa");
//    arthur::printGraph(arthur::createGraph("aaa"));
    return 0;
}
