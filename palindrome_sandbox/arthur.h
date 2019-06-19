#include <utility>

//
// Created by frenchcommando on 6/13/2019.
//

#ifndef PERSOTOOLS_ARTHUR_H
#define PERSOTOOLS_ARTHUR_H

// Name        : practice_bis.cpp
// Author      : arthurarg
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <unordered_set>


namespace arthur {
    using namespace std;

        static const char kStop = '.';
        static const char kStart = 'S';

        class Node {
        public:
            using NodePtr = shared_ptr<Node>;
            char v;

        private:
            shared_ptr<map<char, NodePtr>> n;
            int id_ = -1;

        public:
            explicit Node(const int id, const char new_v=kStop) : n(nullptr) {
                v = new_v;
                id_ = id;
            }

            friend ostream& operator<<(ostream &stream, const Node& node){
                stream << '{' << endl;
                node.Print(stream);
                stream << '}';
                return stream;
            }

            NodePtr AddChild(int id, const char c){
                auto new_node = make_shared<Node>(id, c);
                AddChild(c, new_node);
                return new_node;
            }

            void AddChild(const NodePtr& child){
                AddChild(child->v, child);
            }

            void AddChild(const char c, NodePtr child){
                if(n == nullptr)
                    n = make_shared<map<char, NodePtr>>();
                (*n)[c] = std::move(child);
            }

            NodePtr getChild(const char c) const{
                if(n == nullptr)
                    return nullptr;
                auto child = n->find(c);
                if(child == n->end())
                    return nullptr;
                return child->second;
            }

            int getId() const {
                return id_;
            }

        private:
            void Print(ostream &stream, string prefix="") const {
                if(n == nullptr || v == kStop){
                    stream << prefix << endl;
                    return;
                }
                if(v != kStart)
                    prefix = prefix + v;
                for(const auto& child: *n)
                    child.second->Print(stream, prefix);
            }
        };

        using NodePtr = Node::NodePtr;

        struct NodeHashById {
        public:
            auto operator()(const NodePtr& node) const {
                return hash<int>()(node->getId());
            }
        };

        using NodeSet = unordered_set<NodePtr, NodeHashById>;

        class STrie {

        public:

            explicit STrie(const string& s, bool reverse=false){
                start_ = make_shared<Node>(getNewId(), kStart);
                Push(s, reverse);
            }

            friend ostream& operator<<(ostream &stream, const STrie& trie){
                stream << " : " << *trie.start_;
                return stream;
            }

            void Push(const string &s, bool reverse){
                if(reverse)
                    return Push(s.crbegin(), s.crend());
                return Push(s.cbegin(), s.cend());
            }

            template<typename Iterator>
            void Push(
                    const Iterator& begin,
                    const Iterator& end){
                NodeSet active_heads, prev_heads;
                Iterator it = begin;
                char prev = *it;
                NodePtr main_head = start_->AddChild(getNewId(), prev);

                // Add all the letters to the graph.
                for(it = next(it); it != end; ++it){
                    main_head = Push(*it, prev, main_head, active_heads, prev_heads);
                    prev = *it;
                }

                // Close the graph with terminal nodes.
                main_head = Push(kStop, prev, main_head, active_heads, prev_heads);
                for(const auto& head : active_heads)
                    head->AddChild(getNewId(), kStop);
            }

        private:
            NodePtr start_;
            int ids_ = -1;

            int getNewId(){
                ids_++;
                return ids_;
            }

            NodePtr Push(
                    const char nxt,
                    const char c,
                    NodePtr main_head,
                    NodeSet& active_heads,
                    NodeSet& new_heads){

                // Add the letter to the end of merged heads.
                main_head = main_head->AddChild(getNewId(), nxt);

                // Update active heads.
                new_heads.clear();
                for (auto& head: active_heads){
//                for(auto it = active_heads.begin(); it != active_heads.end(); ++it){
                    auto child = head->getChild(c);
                    if(child == nullptr)  // New child node, then combine head.
                        (head->AddChild(getNewId(), c))->AddChild(main_head);
                    else  // Move head down the graph to existing child node.
                        new_heads.insert(child);
                }
                new_heads.insert(start_);
                swap(active_heads, new_heads);
                return main_head;
            }
        };

        static string find(const string& a, const string& b){
            for(int i = 0; i < 2; i++){
                STrie ga(a);
                STrie gb(b);
            }
            return "";
        }



}


#endif //PERSOTOOLS_ARTHUR_H
