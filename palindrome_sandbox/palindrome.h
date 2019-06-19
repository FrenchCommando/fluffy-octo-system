//
// Created by frenchcommando on 6/11/2019.
//

#ifndef PERSOTOOLS_PALINDROME_H
#define PERSOTOOLS_PALINDROME_H

#include <string>
#include <iostream>
#include <map>
#include <vector>

struct SubSequenceSolution{ // nothing to do with palindromes
    size_t l; //length of matching subsequence
    int i, j; //(i,j) coordinates of last char used - (-1) if none
    std::string s; // current matching subsequence

    template <typename T1, typename T2>
    static std::string solve(const T1& s1b, const T1& s1e, const T2& s2b, const T2& s2e){
        const auto l = std::distance(s1b, s1e);
        if (l == 0)
            return "";
        if (l > std::distance(s2b, s2e))
            return solve(s2b, s2e, s1b, s1e);
        const auto l2 = std::distance(s2b, s2e);
        std::vector<SubSequenceSolution> v(l2, {0, -1, -1, ""});

        int i = 0;
        for (auto si = s1b; si != s1e; i++, si++){
            auto ci = *si;
            int j = 0;
            for(auto sj = s2b; sj != s2e; j++, sj++){
                auto cj = *sj;
                if (j == 0){
                    // there is no left
                    // do nothing if char don't match
                    if (ci == cj and v[j].j != j)
                        v[j] = SubSequenceSolution{v[j].l + 1, i, j, v[j].s + cj};
                }
                // up or left - add char or not
                else if (ci != cj){
                    const auto left_l = v[j - 1].l;
                    const auto up_l = v[j].l;
                    if (left_l > up_l or (left_l == up_l and v[j-1].s < v[j].s))
                        v[j] = v[j-1]; // copy
                }
                else{
                    // ci == cj - but we have to check for duplicates
                    const auto left_candidate = v[j-1].i == i? v[j-1]: SubSequenceSolution{v[j-1].l + 1, i, j, v[j-1].s + ci};
                    const auto up_candidate = v[j].j == j? v[j]: SubSequenceSolution{v[j].l + 1, i, j, v[j].s + ci};
                    if (left_candidate.l > up_candidate.l or (left_candidate.l == up_candidate.l and left_candidate.s < up_candidate.s))
                        v[j] = left_candidate;
                    else
                        v[j] = up_candidate;

                }

            }
        }
        return (*v.rbegin()).s; // uses dynamic programming
    }
};

class PalindromeSolver{
public:
    static std::string sub_palindrome(const std::string& s) {
        // returns largest sub-palindrome - with alphabetic priority in case of equality
        return SubSequenceSolution::solve(s.cbegin(), s.cend(), s.crbegin(), s.crend());
    }

    static std::string my_solve(const std::string::const_iterator& normalIterator,
                            const std::string::const_iterator& normalIteratorEnd,
                            const std::string::const_reverse_iterator& reverseIterator,
                            const std::string::const_reverse_iterator& reverseIteratorEnd) {
        std::string s;
        for(auto it = normalIterator + 1; it != normalIteratorEnd ; it ++)
            s += *it;
        for(auto it = reverseIteratorEnd - 1; it != reverseIterator ; it--)
            s += *it;
        return sub_palindrome(s);
    }

    static std::string solve(const std::string& s1, const std::string& s2){
        auto first = first_occurence(s1);
        auto last = last_occurence(s2);
//        for(const auto& p: first){
//            std::cout<< p.first << std::distance(s1.cbegin(), p.second) << std::endl;
//        }
//        for(const auto& p: last){
//            std::cout<< p.first << std::distance(s2.crbegin(), p.second) << std::endl;
//        }

        std::string s_rep; // solution candidate
        char c_rep = 0;
        // rep is c_rep + s_rep + c_rep

        for(auto& p: first){
            auto c = p.first;
            std::map<char, std::string::const_reverse_iterator>::const_iterator f;
            if ((f = last.find(c)) != last.end()){
                auto s_c = my_solve(p.second, s1.cend(), f->second, s2.crend());
                if (s_c.length() > s_rep.length() or (s_c.length() == s_rep.length() and c < c_rep)){
                    s_rep = s_c;
                    c_rep = c;
                }
            }
        }

        if (not c_rep)
            return "-1";
        return c_rep + s_rep + c_rep;
    } // this is the sub-sequence version

    static std::string solve2(const std::string& s1, const std::string& s2){
        return "";
    } // this is the substring version

    template <typename T>
    static auto gather_occurence(const T& sbegin, const T& send){
        std::map<char, T> m;
        for (auto it = sbegin; it != send; it++){
            auto c = *it;
            if (m.find(c) == m.end())
                m.emplace(c, it);
        }
        return m;
    }

    static std::map<char, std::string::const_iterator> first_occurence(const std::string& s){
        return gather_occurence(s.cbegin(), s.cend());
    }

    static std::map<char, std::string::const_reverse_iterator> last_occurence(const std::string& s){
        return gather_occurence(s.crbegin(), s.crend());
    }

    static void display_grid(const std::string& s){
        std::cout << " ";
        for (const auto& c: s){
            std::cout << c;
        }
        std:: cout << std::endl;
        for (auto it = s.crbegin(); it != s.crend(); it++){
            auto c = *it;
            std::cout << c;
            for (const auto& c0: s){
                if ( c == c0)
                    std::cout << c;
                else
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif //PERSOTOOLS_PALINDROME_H
