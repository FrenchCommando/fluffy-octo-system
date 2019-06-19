//
// Created by frenchcommando on 6/6/2019.
//

#ifndef PERSOTOOLS_NUMERIC_HELPER_H
#define PERSOTOOLS_NUMERIC_HELPER_H


#include <algorithm>

class numeric_helper {

public:
    // variadic template for max
    template <typename ...T, typename U>
    static U amax(U t0, T ... t){
        return std::max(t0, amax(t...));
    }
    template <typename T>
    static T amax(T t){
        return t;
    }

#define vectorize(my_function) template <typename ...Args> \
static auto v##my_function(Args&&... args) { return std::my_function({ std::forward<Args>(args)... }); }
    vectorize(min)
    vectorize(max)

};


#endif //PERSOTOOLS_NUMERIC_HELPER_H
