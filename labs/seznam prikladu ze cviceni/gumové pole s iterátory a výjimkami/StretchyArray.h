#ifndef LAB_06_12_STRETCHYARRAY_H
#define LAB_06_12_STRETCHYARRAY_H

#include <memory>
#include <vector>
#include <iostream>

class at_err : std::out_of_range{
public:
    at_err(const std::string &arg, int index) : out_of_range(arg),s(arg),_index(index){
        s += std::to_string(index);
    };
    int getIndex() const {return _index;}
    virtual const char * what() const noexcept override {return s.c_str();}
private:
    std::string s;
    int _index;
};

class end_err : std::out_of_range{
public:
    end_err(const std::string &arg,size_t size) : out_of_range(arg),s(arg),_size(size){};
    int getSize() const {return _size;}
    virtual const char * what() const noexcept override {return s.c_str();}

private:
    size_t _size;
    std::string s;
};


template<typename T> class Pole {
public:
    explicit Pole( size_t chunk = 100): chunk_(chunk){
        hrabe_.push_back(std::make_unique<T[]>(chunk_));
    };

    struct m_iterator {
        m_iterator(Pole<T>& arr, size_t index) : pole_(arr), index_(index) {};
        T& operator* () {
            if (index_ >= pole_.size() ){
                throw end_err("accessing end with iterator",pole_.size());
            }
            return pole_[index_];
        }
        m_iterator& operator++(){
            ++index_;
            if (index_ > pole_.size()){
                throw end_err("accessing end with iterator",pole_.size());
            }
            return *this;
        }
        bool operator!=(const m_iterator& it2){
            return !(*this == it2);
        }

        bool operator==(const m_iterator& it2){
            return this->index_==it2.index_ && &this->pole_==&it2.pole_;
        }
    private:
        Pole<T>& pole_;
        size_t index_;
    };

    m_iterator begin() {return m_iterator(*this, 0); }
    m_iterator end() {return m_iterator(*this, size()); }

    void push_back( const T& x){
        if(current_chunk == chunk_){
            hrabe_.push_back(std::make_unique<T[]>(chunk_));
            current_chunk = 0;
            current_peak++;
            hrabe_[current_peak][current_chunk] = x;
            current_chunk++;
        }
        else{
            hrabe_[current_peak][current_chunk] = x;
            current_chunk++;
        }
    };
    T& at( size_t i){
        size_t element = i % chunk_;
        size_t peak = i / chunk_;
        if ( i > this->size() - 1){
            throw at_err("wrong at() usage on index: ",i);
            throw std::out_of_range("wrong at() usage");
        }

        return hrabe_[peak][element];
    }
    T& operator[] ( size_t i){
        size_t element = i % chunk_;
        size_t peak = i / chunk_;
        return hrabe_[peak][element];
    }

private:
    void resize(size_t i);

    std::vector< std::unique_ptr<T[]>> hrabe_;
    size_t chunk_;
    size_t current_chunk = 0;
    size_t current_peak = 0;
    size_t size() const {
        return current_peak * chunk_ + current_chunk;
    }
};



#endif //LAB_06_12_STRETCHYARRAY_H
