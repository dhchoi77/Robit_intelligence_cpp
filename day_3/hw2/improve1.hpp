#ifndef IMPROVE1_HPP
#define IMPORVE1_HPP
#include <iostream>
#include "User.hpp"


class UserRepository{
    public:
        void saveUser(const User& user){
            std::cout<<"User saved to database: "<<user.name<<std::endl;
        } 
};
class EmailService{
    public:
        void sendWelcomeEmail(const User& user){
                std::cout<<"Welcome email sent to: "<<user.name<<std::endl;
            }
};
class UserActivityLogger{
    public:
         void logUserActivity(const User& user){
            std::cout<<"Logging activity for user: "<<user.name<<std::endl;
        }
};
#endif