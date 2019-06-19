//
// Created by frenchcommando on 6/7/2019.
//

#include <iostream>
#include <map>
#include <memory>

using NodeKey = std::string;
using NodeValue = char;

struct Node{
    NodeValue name;
    std::map<NodeKey, std::shared_ptr<Node>> nodes;

    explicit Node(NodeValue name) : name(name) {}

    void add_child(const NodeKey& key, const std::shared_ptr<Node>& child){
        nodes[key] = child;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "name: " << node.name;
        os << " nodes: " << node.nodes.size() << std::endl;
        for (const auto& p: node.nodes){
            os << "Key : " << p.first;
            os << "Value : " << *(p.second);
        }
        return os;
    }
};

void run_one(){
    std::cout << "I'm here" << std::endl;
    const auto n_ptr = std::make_shared<Node>('n');
    const auto a_ptr = std::make_shared<Node>('a');
    const auto b_ptr = std::make_shared<Node>('b');
    std::cout << "Here\t" << *n_ptr << std::endl;
    n_ptr->add_child("my_key_a", a_ptr);
    std::cout << "Here - a\t" << *n_ptr << std::endl;
    n_ptr->add_child("my_key_b", b_ptr);
    std::cout << "Here - b\t" << *n_ptr << std::endl;
}
