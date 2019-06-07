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

    template <typename ...Args> static auto vmax(Args&&... args) { return std::max({ std::forward<Args>(args)... }); }
    template <typename ...Args> static auto vmin(Args&&... args) { return std::min({ std::forward<Args>(args)... }); }
};


#endif //PERSOTOOLS_NUMERIC_HELPER_H
