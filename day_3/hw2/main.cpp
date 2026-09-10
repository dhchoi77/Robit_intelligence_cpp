#include<iostream>
#include "User.hpp"
#include "test1.hpp"
#include "improve1.hpp"
#include "test2.hpp"
#include "improve2.hpp"
#include "test3.hpp"
#include "improve3.hpp"
#include "test4.hpp"
#include "improve4.hpp"

int main (void){
    User u1;
    u1.name="chlehdgus";
    UserService US;
    US.saveUser(u1);
    US.sendWelcomeEmail(u1);
    US.logUserActivity(u1);
    std::cout<<"\n";

    UserRepository UR;
    EmailService ES;
    UserActivityLogger UA;
    UR.saveUser(u1);
    ES.sendWelcomeEmail(u1);
    UA.logUserActivity(u1);
    std::cout<<"\n";


    ReportGenerator RG;
    u1.document="PDF";
    RG.generateReport(u1);
    std::cout<<"\n";

    Bird* bird = new Bird();
    bird->fly();
    Bird* penguin = new Penguin();
    penguin->fly();
    delete bird;
    delete penguin;
    std::cout<<"\n";

    Sparrow1* sparrow1 = new Sparrow1();
    sparrow1->eat1();
    Bird1* penguin1 = new Penguin1();
    penguin1->eat1();
    delete sparrow1;
    delete penguin1;
    std::cout<<"\n";


    Worker* employee = new Employee();
    employee->work();
    employee->eat();
    Worker* robot = new Robot();
    robot->work();
    robot->eat();
    std::cout<<"\n";

    Employee1* employee1 = new Employee1();
    employee1->work();
    employee1->eat();
    Workable* robot1 = new Robot1();
    robot1->work();
    std::cout<<"\n";
    return 0;
}