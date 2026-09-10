#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <iostream>
#include <fstream>

template<class T>
class DataFrame {
protected:
    T* data_;
    size_t size_;
public:
    DataFrame() : data_(nullptr), size_(0) {}
    virtual ~DataFrame() {           // 다형 기반 클래스이므로 virtual 필수
        delete[] data_;              // nullptr 삭제는 안전
    }
    virtual size_t size() = 0;
    virtual void clear() = 0;
};

template<class T>
class cdh : public DataFrame<T> {
private:
    size_t capacity;
    void grow() {
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
    using iterator = T*;

    cdh() {
        this->data_ = nullptr;
        this->size_ = 0;
        capacity = 0;
    }

    // ================= Rule of Three =================
    // (1) 복사 생성자 : 깊은 복사
    cdh(const cdh& other) {
        this->size_ = other.size_;
        capacity    = other.capacity;
        if (capacity > 0) {
            this->data_ = new T[capacity];
            for (size_t i = 0; i < this->size_; i++)
                this->data_[i] = other.data_[i];
        } else {
            this->data_ = nullptr;
        }
    }
    // (2) 복사 대입 연산자 : v3 = v1 + v2 같은 대입에서 호출됨
    cdh& operator=(const cdh& other) {
        if (this == &other) return *this;    // 자기 자신 대입 방어
        delete[] this->data_;                // 내 기존 배열부터 정리
        this->size_ = other.size_;
        capacity    = other.capacity;
        if (capacity > 0) {
            this->data_ = new T[capacity];
            for (size_t i = 0; i < this->size_; i++)
                this->data_[i] = other.data_[i];
        } else {
            this->data_ = nullptr;
        }
        return *this;
    }
    // (3) 소멸자는 부모 DataFrame 이 virtual 로 처리
    // =================================================

    void push_back(const T& element) {       // 임시값도 받을 수 있게 const&
        grow();
        this->data_[this->size_] = element;
        this->size_++;
    }

    T& at(int index) {
        return this->data_[index];
    }

    iterator begin() { return this->data_; }
    iterator end()   { return this->data_ + this->size_; }

    bool empty() {
        return this->size_ == 0;
    }

    void erase(iterator it) {
        for (iterator I = it; I + 1 != end(); I++)
            *I = *(I + 1);
        this->size_--;
    }

    void insert(iterator it, const T& element) {
        size_t index = it - this->data_;      // grow 전에 위치를 인덱스로 저장
        grow();                               // 재할당돼도 index 는 유효
        for (size_t i = this->size_; i > index; --i)
            this->data_[i] = this->data_[i - 1];
        this->data_[index] = element;
        this->size_++;
    }

    size_t size() { return this->size_; }

    void clear() { this->size_ = 0; }

    void file_open() {
        std::ifstream fin("arr.txt");
        if (!fin) { std::cout << "failed to open arr.txt\n"; return; }
        clear();                              // 기존 내용 비우고 새로 채움
        T value;
        while (fin >> value) push_back(value);
        fin.close();
    }

    void file_out() {
        std::ofstream fout("arr.txt");
        if (!fout) { std::cout << "failed to open arr.txt\n"; return; }
        for (size_t i = 0; i < this->size_; i++)
            fout << this->data_[i] << " ";
        fout.close();
    }

    // 두 객체를 "원소별"로 더해 새 객체를 반환.
    // 길이가 다르면 짧은 쪽 원소는 0 으로 취급.
    cdh operator+(const cdh& other) const {
        cdh result;
        size_t n = (this->size_ > other.size_) ? this->size_ : other.size_;
        for (size_t i = 0; i < n; i++) {
            T sum = T();                      // int 면 0
            if (i < this->size_)  sum += this->data_[i];
            if (i < other.size_)  sum += other.data_[i];
            result.push_back(sum);
        }
        return result;                        // 값 반환 → 복사 생성자(또는 최적화)
    }
};

#endif