#ifndef IMPROVE3_HPP
#define IMPROVE3_HPP
#include "User.hpp"
#include <iostream>
class Flyable1{
    public:
        virtual void fly1()=0;
};
class Bird1{
    public:
        void eat1(){
            std::cout<<"Bird is eating"<<std::endl;
        }
};
class Sparrow1 : public Bird1 , public Flyable1{
    public:
        void fly1(){
            std::cout<<"Sparrow is flying"<<std::endl;
        }
};
class Penguin1 : public Bird1{
    
};
#endif