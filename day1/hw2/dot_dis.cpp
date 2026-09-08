#include "dot_dis.h"     
#include <iostream>   
#include <cstdlib> 
#include <ctime>   
#include <cmath>
dot_dis::dot_dis(){
    dot_len();
    remake_dot();
    coor();
    random_dot();
    random_dot_print();
    max_min_init();
    dot_calc();
    print_max_min();
}
void dot_dis::dot_len(){
    std::cout<<"how many dot do you want?: ";
    std::cin>>len;
}
void dot_dis::remake_dot(){
    xy = (dot_xy*)realloc(xy, sizeof(dot_xy)*len);
}
void dot_dis::coor(){
    std::cout<<"how do you set coor_min?: ";
    std::cin>>min_coor;
    std::cout<<"how do you set coor_max?: ";
    std::cin>>max_coor;
}
void dot_dis::random_dot(){
    std::srand(std::time(nullptr)); // 시드값을 설정한다.
    for (int i=0;i<len;i++){
        xy[i].x=std::rand()%(max_coor-min_coor+1)+min_coor;
        xy[i].y=std::rand()%(max_coor-min_coor+1)+min_coor;
    }
}
void dot_dis:: random_dot_print(){
    for (int i=0;i<len;i++){
        std::cout<<"DOT "<<i+1<<" X:"<<xy[i].x<<", Y:"<<xy[i].y<<std::endl;
    }
}
void dot_dis:: max_min_init(){
    max.dis=0;
    min.dis=sqrt(2*pow(max_coor-min_coor,2));
}
void dot_dis:: dot_calc(){
    for (int i=0;i<len;i++){
        for (int j=0;j<len;j++){
            if (i==j){
                continue;
            }
            if (max.dis<=sqrt(pow(xy[i].x-xy[j].x,2)+pow(xy[i].y-xy[j].y,2))){
                max.dis=sqrt(pow(xy[i].x-xy[j].x,2)+pow(xy[i].y-xy[j].y,2));
                max.dot1_index=i;
                max.dot2_index=j;
            }
            if (min.dis>=sqrt(pow(xy[i].x-xy[j].x,2)+pow(xy[i].y-xy[j].y,2))){
                min.dis=sqrt(pow(xy[i].x-xy[j].x,2)+pow(xy[i].y-xy[j].y,2));
                min.dot1_index=i;
                min.dot2_index=j;
            }
        }
    }
}
void dot_dis::print_max_min(){
    std::cout<<"MinDist: "<<min.dis<<"\nMin(x,y): Dot1("<<xy[min.dot1_index].x<<","<<xy[min.dot1_index].y<<") , Dot2("<<xy[min.dot2_index].x<<","<<xy[min.dot2_index].y<<")\n";
    std::cout<<"MaxDist: "<<max.dis<<"\nMax(x,y): Dot1("<<xy[max.dot1_index].x<<","<<xy[max.dot1_index].y<<") , Dot2("<<xy[max.dot2_index].x<<","<<xy[max.dot2_index].y<<")\n";
}
dot_dis::~dot_dis(){
    free(xy);
}


