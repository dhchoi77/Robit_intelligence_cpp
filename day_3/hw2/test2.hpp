#ifndef TEST2_HPP
#define TEST2_HPP
#include "User.hpp"
#include <iostream>

#include <iostream>
class ReportGenerator{
    public:
        void generateReport(const User& user){
            if (user.document=="PDF"){
                std::cout<<"Generating PDF document..."<<std::endl;

            }
            else if (user.document=="HTML"){
                std::cout<<"Generating HTML document..."<<std::endl;
            }
        }
};
#endif