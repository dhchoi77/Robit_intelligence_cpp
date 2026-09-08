#ifndef DOT_H
#define DOT_H
struct dot_xy{
    int x;
    int y;
};
struct distance{
    float dis;
    int dot1_index;
    int dot2_index;
};
class dot_dis {
    private:
        int len;
        int max_coor;
        int min_coor;
        struct dot_xy *xy= nullptr;
        struct distance max;
        struct distance min;
    public:
        dot_dis();
        ~dot_dis();
        void dot_len();     //dot구조체 크기 입력받기
        void remake_dot();  //dot구조체 동적할당
        void coor(); //x,y값 최소, 최대 정하기
        void random_dot();  //dot구조체에 랜덤으로 x,y값 할당하기
        void random_dot_print();   //dot x,y값 출력하기
        void max_min_init();    //max,min의 거리값 초기화해주기
        void dot_calc();    //max, min구하기
        void print_max_min();
};

#endif
