//
// Created by frenchcommando on 6/12/2019.
//

#ifndef PERSOTOOLS_PALINDROME_SUBSTRING_H
#define PERSOTOOLS_PALINDROME_SUBSTRING_H


#include <string>
#include <set>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <queue>

namespace palindrome{

    using ItType = std::string::const_iterator;
    using StringIndexType = size_t;

struct Node{
    ItType start, end; // the string it represents it std::string(start, end)
    std::map<char, Node> s; // mapping first char of children nodes
    std::map<StringIndexType, std::set<size_t>> i; // the info if I stop here
    size_t score = 0; // size of substring before start
    std::string str; // string before start

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "String_from_iterator:\t" << std::string(node.start, node.end) << std::endl;
        os << "Score:\t" << node.score << std::endl;
        os << "String:\t" << node.str << std::endl;
        if (not node.s.empty()){
            os << "\tChildren: ";
            for (const auto& p : node.s){
                os << "char:\t" << p.first << "\t" << p.second << std::endl;
            }
            os << std::endl;
        }
        if (not node.i.empty()){
            os << "\tInfo:\t";
            for(const auto& p: node.i){
                os << p.first << "\t:\t";
                for(const auto& pp: p.second)
                    os << pp << ", ";
            }
            os << std::endl;
        }
        return os;
    }

    void add_string(const ItType& iteratorStart, const ItType& iteratorEnd,
            const StringIndexType string_index,
            const size_t init_index){
        auto p0 = start;
        auto p1 = iteratorStart;
        size_t add_score = 0;
        while(p0 != end and p1 != iteratorEnd and *p0 == *p1){
            ++p0;
            ++p1;
            ++add_score;
        }
        std::string str_s(start, p0);
        // each score in the node should be the same

        if (p0 == end and p1 == iteratorEnd){
            i[string_index].emplace(init_index);
        }
        else if (p0 == end){
            i[string_index].emplace(init_index);
            if (s.find(*p1) != s.cend()){
                s[*p1].add_string(p1, iteratorEnd, string_index, init_index);
            }
            else{
                s[*p1] = Node{p1, iteratorEnd, {}, {{string_index, {init_index}}}, score + add_score, str + str_s};
            }
        }
        else if (p1 == iteratorEnd){
            auto ii = i;
            ii[string_index].emplace(init_index);
            *this = Node{iteratorStart, iteratorEnd,
                     {{*p0, Node{p0, end, std::move(s), i, score + add_score, str + str_s}}},
                     ii,
                     score, str};
        }
        else{
            auto c0 = *p0;
            auto c1 = *p1;
            auto ii = i;
            ii[string_index].emplace(init_index);
            *this = Node{start, p0, {{*p0, Node{p0, end, std::move(s), i, score + add_score, str + str_s}},
                                 {*p1, Node{p1, iteratorEnd, {}, {{string_index, {init_index}}}, score + add_score, str + str_s}}},
                     ii, score, str};
        }

    }

    std::string get_string() const{
        return str + std::string(start, end);
    }
    std::string get_reverse_string() const{
        std::string s_s = get_string();
        return std::string(s_s.crbegin(), s_s.crend());
    }
};

class suffix_tree{

    Node head;
public:
    const Node& get_head() const{
        return head;
    }

//    void add_string(const std::string& s, const Info& info){
//        head.add_string(s.cbegin(), s.cend(), info);
//    }

    void add_suffix_string(const std::string::const_iterator& s_begin, const std::string::const_iterator& s_end,
            const size_t& string_index, const size_t init_index = 0){
        size_t j = init_index;
        for(auto it = s_begin; it != s_end; it++){
            head.add_string(it, s_end, string_index, j++);
        }
    }

    void add_suffix_string(const std::string& s, const size_t& string_index, const size_t init_index = 0){
        add_suffix_string(s.cbegin(), s.cend(), string_index, init_index);
    }

    void add_suffix_alphabet(const std::string::const_iterator& s_begin, const std::string::const_iterator& s_end,
                             const size_t string_index, const size_t init_index,
                             const std::set<char>& alphabet){
        if(s_begin == s_end)
            return;
        auto it = s_begin;
        size_t index = init_index;
        while(it != s_end and alphabet.find(*it) != alphabet.cend()){
            ++it;
            ++index;
        }
        add_suffix_string(s_begin, it, string_index, init_index);

        while(it != s_end and alphabet.find(*it) == alphabet.cend()){
            ++it;
            ++index;
        }
        add_suffix_alphabet(it, s_end, string_index, index, alphabet);
    }
    void add_suffix_alphabet(const std::string& s, const size_t s_index,
                                    const std::set<char>& alphabet){
        add_suffix_alphabet(s.cbegin(), s.cend(), s_index, 0, alphabet);
    }

    friend std::ostream &operator<<(std::ostream &os, const suffix_tree &tree) {
        os << "head: " << tree.head;
        return os;
    }
};

template <typename T>
class palindrome_substring_ending{
    using distance_type = size_t;
    using iterator_type = T;

    std::vector<std::set<iterator_type>> m; // m[i] contains the set of all the iterator_ends where each palindrome ends
    iterator_type it0;
    std::vector<size_t> longest_length;
    std::vector<iterator_type> longest_it;
public:
    explicit palindrome_substring_ending(const T& begin, const T& end)
        : it0(begin)
    {
        const auto n = std::distance(begin, end);
        m.reserve(n);
        for(auto it = begin; it != end; it++){
            auto c = *it;
            std::set<iterator_type> s;
            s.emplace(it); // current one char is a palindrome
            if (it != begin){
                if (c == *(it - 1))
                    s.emplace(it - 1); // for "AA"
                const auto& s0 = m.back();
                for(const auto& i0: s0){
                    if(i0 != begin) {
                        const auto i1 = i0 - 1;
                        if (c == *i1)
                            s.emplace(i1);
                    }
                }
            }
            m.emplace_back(s);
        }
        longest_length.reserve(n);
        longest_it.reserve(n);
        for(const auto& s : m){
            longest_it.emplace_back(*std::min_element(s.cbegin(), s.cend()));
        }

        for(auto it = begin; it != end; it++){
            longest_length.emplace_back(std::distance(longest_palindrome_substring_ending(it), it + 1));
        }
    }

    auto longest_palindrome_substring_ending(const T& it) const {
        const auto index = std::distance(it0, it);
        return longest_it.at(index);
    }

    auto longest_palindrome_substring_ending(size_t i) const{
        return std::string(longest_it.at(i), it0 + i + 1);
    }

    auto longest_palindrome_substring_ending_length(size_t i) const{
        return longest_length.at(i);
    }

    friend std::ostream &operator<<(std::ostream &os, const palindrome_substring_ending &start) {
        auto i = start.it0;
        for (const auto& v: start.m){
            for(const auto& ii: v){
                os << std::string(ii, i + 1) << ", ";
            }
            ++i;
            os << std::endl;
        }
        return os;
    }
};

class palindrome_substring_object{
    size_t n;
    palindrome_substring_ending<std::string::const_iterator> pe;
    palindrome_substring_ending<std::string::const_reverse_iterator> ps;

public:
    explicit palindrome_substring_object(const std::string& s)
    :
    n(s.length())
    , pe(s.cbegin(), s.cend())
    , ps(s.crbegin(), s.crend())
    {};

    auto length() const{
        return n;
    }

    auto longest_palindrome_substring_ending(size_t i) const
    {
        return pe.longest_palindrome_substring_ending(i);
    }
    std::string longest_palindrome_substring_starting(size_t i) const
    {
        if (i == n)
            return "";
        return ps.longest_palindrome_substring_ending(n - i - 1);
    }

    auto longest_palindrome_substring_ending_length(size_t i) const
    {
        return pe.longest_palindrome_substring_ending_length(i);
    }
    size_t longest_palindrome_substring_starting_length(size_t i) const
    {
        if (i == n)
            return 0;
        return ps.longest_palindrome_substring_ending_length(n - i - 1);
    }

};

class palindrome_substring {
public:
    static void show_palindromes(const std::string& s){
        palindrome_substring_object p1(s);
        for (size_t i = 0 ; i < p1.length(); i++){
            std::cout << i << "\t" << p1.longest_palindrome_substring_ending(i) << std::endl;
            std::cout << i << "\t" << p1.longest_palindrome_substring_starting(i) << std::endl;
        }
    }
    static void show_suffix_tree(const std::string& s){
        suffix_tree t;
//        t.add_string(s, {0, 0});
//        t.add_string("ABADADA", {1, 2});
        t.add_suffix_string(s, 0);
        std::cout << t << std::endl;
    }
    static std::string solve(const std::string& s1, const std::string& s2){
        return solve_v(s1, std::string(s2.crbegin(), s2.crend()));
//        return *std::min_element(v.cbegin(), v.cend());
    }

    static auto build_common_alphabet(const std::string& s1, const std::string& s2,
            const size_t s1_index, const size_t s2_index){
        std::map<char, std::set<size_t>> alphabet;
        for(const auto& p: s1)
            alphabet[p].emplace(s1_index);
        for(const auto& p: s2)
            alphabet[p].emplace(s2_index);
        std::set<char> common_alphabet;
        for(const auto& p : alphabet){
            if(p.second.size() == 2)
                common_alphabet.emplace(p.first);
        }
        return common_alphabet;
    }

    static void update_str_palindrome(std::string &s_candidate, const palindrome_substring_object& p,
            const size_t n, int &threshold) {
        auto n_ss = p.longest_palindrome_substring_starting_length(n);
//        std::cout << ss << "\t" << s_candidate << "\t" << threshold << std::endl;
        if(n_ss == threshold){
            auto ss = p.longest_palindrome_substring_starting(n);
            if(s_candidate.empty())
                s_candidate = ss;
            else if (s_candidate.compare(ss) > 0)
                s_candidate = ss;
        }
        else if(n_ss > threshold){
            auto ss = p.longest_palindrome_substring_starting(n);
            threshold = n_ss;
            s_candidate = ss;
        }
//        std::cout << "Post\t" << ss << "\t" << s_candidate << "\t" << threshold << std::endl;
    }

    static std::string solve_v(const std::string& s1, const std::string& s2){
//        show_palindromes(s1);
//        show_palindromes(s2);
//        show_suffix_tree(s1);
        suffix_tree t;
        size_t s1_index = 0;
        size_t s2_index = 1;

        const auto common_alphabet = build_common_alphabet(s1, s2, s1_index, s2_index);
        // split strings into sub-strings with common alphabet

        if (common_alphabet.empty())
            return {"-1"};

        t.add_suffix_alphabet(s1, s1_index, common_alphabet);
        t.add_suffix_alphabet(s2, s2_index, common_alphabet);

//        std::cout << t << std::endl;
        palindrome_substring_object p1(s1), p2(s2);

        size_t n = 0;
        std::string s;

        std::queue<std::reference_wrapper<const Node>> q;
        q.emplace(t.get_head());

        while(not q.empty()){
            auto node = q.front();
            q.pop();
//            std::cout << "looking at node\t" << node.get().get_string() << std::endl;
            bool has_s1 = node.get().i.find(s1_index) != node.get().i.cend();
            bool has_s2 = node.get().i.find(s2_index) != node.get().i.cend();
            if (has_s1 and has_s2){
                for(const auto& p: node.get().s){
                    q.emplace(p.second);
                }
                size_t nn = node.get().score + std::distance(node.get().start, node.get().end);
                if (nn > 0){
                    int n_threshold = n - nn * 2;
                    if(n_threshold < 0)
                        n_threshold = 0;
                    std::string s_candidate;
                    size_t n_candidate = 0;
                    for (const auto& p : node.get().i){
                        std::string ss;
//                        for(const auto& pp: p.second)
//                            std::cout << pp << "\t";
//                        std::cout << std::endl;
                        if(p.first == s1_index) {
                            for(const auto& pp: p.second){
                                update_str_palindrome(s_candidate, p1, pp + nn, n_threshold);
                            }
                        } // some branch and bound here ?
                        if(p.first == s2_index) {
                            for(const auto& pp: p.second){
                                update_str_palindrome(s_candidate, p2, pp + nn, n_threshold);
                            }
                        }
                    }
                    size_t real_nn = 2 * nn + s_candidate.length();
                    std::string real_str = node.get().get_string()
                            + s_candidate
                            + node.get().get_reverse_string();
                    if (real_nn > n){
//                        std::cout << s << "\t" << real_str << std::endl;
                        n = real_nn;
                        s = real_str;
                    }
                    else if (real_nn == n){
//                        std::cout << s << "\t" << real_str << std::endl;
                        if (s.compare(real_str) > 0)
                            s = real_str;
                    }
                }
            }
        }
        if (n != 0)
            return s;
        return "-1";
    }
    // for each of the strings, find the largest palindrome starting at each index
    // the solution is a matching substring problem between s1 and s2[::-1]
    // with weight increased by the length of the largest palindrome
    // starting at the end of the substring in either of the 2 strings

    // let's do some variadic template for fun
};
}


#endif //PERSOTOOLS_PALINDROME_SUBSTRING_H
