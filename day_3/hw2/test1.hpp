#ifndef TEST1_HPP
#define TEST1_HPP
#include "User.hpp"
#include <iostream>


class UserService{
    public:
        void saveUser(const User& user){
            std::cout<<"User saved to database: "<<user.name<<std::endl;
        }
        void sendWelcomeEmail(const User& user){
            std::cout<<"Welcome email sent to: "<<user.name<<std::endl;
        }
        void logUserActivity(const User& user){
            std::cout<<"Logging activity for user: "<<user.name<<std::endl;
        }
};

#endif