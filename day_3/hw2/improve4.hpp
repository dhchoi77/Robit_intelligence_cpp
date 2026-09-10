#ifndef IMPROVE4_HPP
#define IMPROVE4_HPP
#include "User.hpp"
#include <iostream>

class Workable{
    public:
        virtual void work()=0;
        
};
class Eatable{
    public:
        virtual void eat()=0;
};

class Employee1 : public Workable, public Eatable{
    public:
        void work(){
            std::cout<<"Employee is working"<<std::endl;

        }
        void eat(){
            std::cout<<"Employee is eating"<<std::endl;
        }
};
class Robot1 : public Workable{
    public:
        void work(){
            std::cout<<"Robot is working"<<std::endl;
        }
};
#endif