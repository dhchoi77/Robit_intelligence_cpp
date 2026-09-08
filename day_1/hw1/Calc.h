#ifndef CALC_H
#define CALC_H
class Calc {
    private:
        int *arr= nullptr;  //원소를 저장할 배열
        int len;            //배열의 길이(동적할당)
        int max;            //원소의 최댓값
        int min;            //원소의 최솟값
        int sum=0;          //원소 전체합
    public:
        Calc();
        ~Calc();
        void input_len();       //배열이 길이 입력
        void remake_arr();      //배열 동적할당하기
        void input_element();   //원소 입력받기
        void Calc_main();       //max, min, sum, avg 구하기
        void print_result();    //출력하기
};

#endif