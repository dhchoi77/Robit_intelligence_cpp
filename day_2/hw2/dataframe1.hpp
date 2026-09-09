#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

template<class T>
class DataFrame{
protected:
    T* data_;
    size_t size_;
public:
    DataFrame():data_(nullptr)
    {}
    ~DataFrame()
    {
        if (data_!=nullptr){
            delete[]data_;
        }
        
    }
    virtual size_t size()=0;
    virtual void clear()=0;
};

template<class T>  
class cdh: public DataFrame<T>{
    private:
        size_t capacity;
        void grow(){
            if (this->size_ < capacity) return;
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_cap];
            for (size_t i = 0; i < this->size_; i++)
                new_data[i] = this->data_[i];
            delete[] this->data_;
            this->data_ = new_data;
            capacity = new_cap;
        }
    public:
        using iterator = T*;        //뭔지 잘 모르겠다. 
        cdh(){
            this->size_=0;
            capacity=0;
        }
        
        void push_back(const T& element){
            grow();
            this->data_[this->size_]=element;
            this->size_++;
            return ;
        };        //마지막에 요소 추가
        T& at(int index){
            return this->data_[index];
        };      //index 위치의 원소에 대한 참조 리턴
        iterator begin(){
            return this->data_;
        };            //백터의 첫 번째 원소에 대한 참조 리턴
        iterator end(){
            return this->data_+this->size_;
        };              //백터의 끝(마지막 원소 다음)을 가리키는 참조 리턴
        int empty(){
            if (this->size_==0){
                return 1;
            }
            else{
                return 0;
            }
        };            //비어 있으면 true 리터
        void erase(iterator it){
            for (iterator I=it; I+1 != end(); I++){
                *I=*(I+1);
            }
            this->size_--;
        };            //it이 가리키는 원소 삭제, 삭제 후 자동으로 크기 조절
        void insert(iterator it,const T& element){
            size_t index = it - this->data_;   // grow 전에 위치를 인덱스로 저장
            grow();                            // 재할당돼도 인덱스는 유효
            // 뒤에서부터 오른쪽으로 한 칸씩 밀어 자리 확보
            for (size_t i = this->size_; i > index; --i) {
                this->data_[i] = this->data_[i - 1];
            }
            this->data_[index] = element;
            this->size_++;
            
        };           //data_내 it위치에 요소 삽입
        size_t size(){
            return this->size_;
        };             //data_에 들어 있는 원소의 개수 리턴
        void clear(){
            
            this->size_=0;
        }; 
        void file_open(){
            std::ifstream fin("arr.txt");
            if (!fin){
                std::cout << "failed to open arr.txt\n";
                return;
            }
            clear();                    // 기존 내용 비우고 새로 채움
            T value;
            while (fin >> value){       // 읽기 성공하는 동안 계속
                push_back(value);
            }
            fin.close();
        }
        void file_out(){
            // raw string R"(...)" 이라 백슬래시를 그대로 씀
            std::ofstream fout("arr.txt");
            if (!fout){
                std::cout << "failed to open arr.txt\n";
                return;
            }
            for (size_t i = 0; i < this->size_; i++){   // size() 대신 멤버 직접 접근, < 사용
                fout << this->data_[i] << " ";           // std:: 빼기
            }
            fout.close();
        }       //비우기?
        // operator();         //지정된 원소에 대한 참조 리턴
        // operator();         //이 백터를 다른 백터에 치환(복사)
};

#endif