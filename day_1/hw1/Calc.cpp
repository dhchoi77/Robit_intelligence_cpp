#include <iostream>
#include <cstdlib>
#include "Calc.h"
Calc::Calc(){
    input_len();
    remake_arr();
    input_element();
    max=arr[0];
    min=arr[0];
    Calc_main();
    print_result();
}
void Calc::input_len(){
    std::cout<<"몇개의 원소를 할당하시겠습니까?: ";
    std::cin>>len;
}
void Calc::remake_arr(){
    arr = (int*)realloc(arr, sizeof(int)*len);
}
void Calc::input_element(){
    for (int i=0;i<len;i++){
        std::cout<<i+1<<"번째 원소를 입력해주세요: ";
        std::cin>>arr[i];
    }
}
void Calc::Calc_main(){
    for (int i=0;i<len;i++){
        sum+=arr[i];
        if (max<=arr[i]){
            max=arr[i];
        }
        if (min>=arr[i]){
            min=arr[i];
        }
    }
}
void Calc::print_result(){
    std::cout<<"최댓값: "<<max<<std::endl;
    std::cout<<"최솟값: "<<min<<std::endl;
    std::cout<<"전체합: "<<sum<<std::endl;
    std::cout<<"평균: "<<(float)sum/len<<std::endl;
}
Calc::~Calc(){
    free(arr);
}