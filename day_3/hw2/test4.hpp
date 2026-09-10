#ifndef TEST4_HPP
#define TEST4_HPP
#include "User.hpp"
#include <iostream>

class Worker{
    public:
        virtual void work()=0;
        virtual void eat()=0;
};

class Employee : public Worker{
    public:
        void work(){
            std::cout<<"Employee is working"<<std::endl;

        }
        void eat(){
            std::cout<<"Employee is eating"<<std::endl;
        }
};
class Robot : public Worker{
    public:
        void work(){
            std::cout<<"Robot is working"<<std::endl;
        }
        void eat(){
            std::cout<<"RObot do not eat"<<std::endl;
        }
};
#endif