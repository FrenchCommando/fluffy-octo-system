//
// Created by frenchcommando on 6/10/2019.
//

#include <iostream>
#include <vector>
#include <memory>

class SampleObject{
    double value;
public:
    explicit SampleObject(double value) : value(value) {}

    friend std::ostream &operator<<(std::ostream &os,
            const SampleObject &object) {
        os << "SampleObject -- value: " << object.value;
        return os;
    }
};

void run_loop(){
    std::cout << "Running the loop" << std::endl;
    auto v_ptr = std::make_shared<SampleObject>(10.);
    SampleObject object(10.);
    std::cout << object << std::endl;
    std::vector<double> v {1., 2., 3.};
    for(const auto p: v)
        v_ptr = std::make_shared<SampleObject>(p);
    std::cout << *v_ptr << std::endl;
}
