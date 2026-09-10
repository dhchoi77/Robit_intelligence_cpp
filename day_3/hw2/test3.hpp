#ifndef TEST3_HPP
#define TEST3_HPP
#include "User.hpp"
#include <iostream>

class Bird{
    public:
        void fly(){
            std::cout<<"Bird is flying"<<std::endl;
        }
};
class Penguin : public Bird{
    public:
        void fly(){
            std::cout<<"Peguins cannot fly"<<std::endl;
        }
};
#endif
