#ifndef euc_dist_hpp
#define euc_dist_hpp

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <map>

using namespace std;

class RNG
{
public:
    // Seeds the mt19937.
    RNG() : gen(random_device()()) {} 

    int getRandom(){  
        return dis(gen);
    }
    uniform_int_distribution<> dis;
private:
    mt19937 gen;   
};


template <class T>
class euc_dist
{
private:
    int N; // N-dimensions
    int S; // sample size
    int min, max, pivot;
    vector< vector<T> > data;
    double dist, sum, tmp, min_dist;
    //vector< double > dist_array;
    RNG rng_;

public:
    vector< double > dist_array;
    euc_dist(int dim, int size, double mi, double ma) 
    {
        N = dim;
        S = size;
        min = mi;
        max = ma;
        //gen_data();
        rng_.dis.param(uniform_int_distribution<>::param_type(min, max));
        //dist_array.resize(S, vector<T>(N));
    }

    void calc_distance();

    void gen_data();
    void define_data(int,int);
    double max_distance();
    double min_distance();

    void print_data();
    void print_dist_array();

    ~euc_dist();
};

template<class T>
void euc_dist<T>::calc_distance(){
    pivot = S/2;
    tmp = 0;
    // N-dims solution
    for (int i = 0; i < S; i++)
    {
        sum = 0;
        tmp = 0;
        for (int k = 0; k < N; k++) // distance operation
        {
            //cout << "x_i: " << data[i][k] << " " << "y_i: " << data[j][k] << endl;
            tmp = data[pivot][k] - data[i][k];     
            sum += tmp*tmp;
        }
        dist = sqrt(sum);
        if (i == 0) min_dist = dist;
        else if (i != pivot && dist < min_dist)
            min_dist = dist;
        dist_array.push_back(dist); 
        //cout << "(" << i << "," << j << "):" << dist << " "; 
        //cout << endl;
    }
}


template<class T>
void euc_dist<T>::gen_data()
{
    // N-dim
    for (int i = 0; i < S; ++i) {
        vector<T> tmp;
        for (int j = 0; j < N; ++j)
        {
            tmp.push_back(rng_.getRandom());
        }
        data.push_back(tmp);
    }
}

template<class T>
void euc_dist<T>::define_data(int dim, int size)
{ 
    //N = dim;
    S = size;
    //remove al vectors inside data
    data.clear();
    data.resize(0);
    //gen_data();
}

template<class T>
double euc_dist<T>::max_distance()
{ 
    return *max_element(dist_array.begin(), dist_array.end());
}

template<class T>
double euc_dist<T>::min_distance()
{ 
    //return *min_element(dist_array.begin(), dist_array.end());
    return min_dist;
}


template<class T>
void euc_dist<T>::print_data()
{
    for (vector<T> row: data) {
        for (T val: row) {
            cout << val << " ";
        }
        cout << '\n';
    }
}

template<class T>
void euc_dist<T>::print_dist_array()
{
    cout << "Distancias desde el pivot: " << endl;
    for (auto d: dist_array) {
        cout << d << endl; 
    }
}

template<class T>
euc_dist<T>::~euc_dist()
{
    cout << "Object deleted" << endl;
}


#endif /* euc_dist_hpp */
