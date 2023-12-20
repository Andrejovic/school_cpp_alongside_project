#ifndef LAB_06_12_STRETCHYARRAY_H
#define LAB_06_12_STRETCHYARRAY_H

#include <memory>
#include <vector>



template<typename T> class Pole {
public:
    explicit Pole( size_t chunk = 100): chunk_(chunk){
        hrabe_.push_back(std::make_unique<T[]>(chunk_));
    };

    struct m_iterator {
        m_iterator(Pole<T>& arr, size_t index) : pole_(arr), index_(index) {};
        T& operator* () {
            return pole_[index_];
        }
        m_iterator& operator++(){
            ++index_;
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
