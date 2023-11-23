#ifndef PRIBISA_COUNTER_H
#define PRIBISA_COUNTER_H


class counter {
private:
    int c_count; //chars
    int w_count; //words
    int s_count; //sentences
    int r_count; //rows

    int n_count;
    int sum_of_r; //self-explanatory

    int counters [6] = {c_count, w_count, s_count, r_count, n_count,sum_of_r};
public:
    void reading_from_stream( std::istream& s);


};


#endif
