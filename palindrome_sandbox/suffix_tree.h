//
// Created by frenchcommando on 6/15/2019.
//

#ifndef PERSOTOOLS_SUFFIX_TREE_H
#define PERSOTOOLS_SUFFIX_TREE_H

#include <string>
#include <map>
#include <set>

namespace suffix{
    using StringIndex = size_t;
    using ItType = std::string::const_iterator;

    class Node
    { // let's make it clean
        // what do I do with internal nodes
        // meaning a node representing both
        //  ABCD$ and AB$ - incrementing the terminal iterator should trigger some checks
        //  to decide whether you have to create another internal node

        const ItType begin;
        ItType& end; // std::string(begin, end) is the string represented by the node
        std::map<char, Node> m;
        std::map<StringIndex, std::set<size_t>> i; // represents the index of the StringIndex at the beginning of the node
        const std::string s; // string at beginning of the node

    public:
        Node(const ItType& begin, ItType& end)
        :
        begin(begin)
        , end(end)
        {}

        void add_node(const ItType& it0, ItType& it_end){
            if(m.find(*it0) == m.cend())
                m.emplace(*it0, Node(it0, it_end));
            else{

            }

        }

    };

    // let's try to make it linear
    // and put several strings in the same tree
    class suffix_tree {
        Node head;
    public:
        void add_string(const std::string::const_iterator& begin, const std::string::const_iterator& end){
            auto it_end = begin + 1;
            for(auto it = begin; it != end; it++){
                // it represents the terminal sentinel
                ++it_end;
                head.add_node(it, it_end);
            }
        }
        void add_string(const std::string& s){
            add_string(s.cbegin(), s.cend());
        } // add the suffixes of the input string to the tree

        const Node& get_head() const{
            return head;
        }
    };
}


#endif //PERSOTOOLS_SUFFIX_TREE_H
