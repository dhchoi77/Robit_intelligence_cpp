#ifndef IMPROVE2_HPP
#define IMPROVE2_HPP
#include "User.hpp"
#include <iostream>
class Report{
    public:
        void generate();
    
};
class PDFReport : public Report{
    public:
        void generate(){
            std::cout<<"Generating PDF report..."<<std::endl;
        }
};
class HTMLReport : public Report{
    public:
        void generate(){
            std::cout<<"Generating HTML report..."<<std::endl;
        }
};
class XMLReport : public Report{
    public:
        void generate(){
            std::cout<<"Generating XML report..."<<std::endl;
        }
};
#endif