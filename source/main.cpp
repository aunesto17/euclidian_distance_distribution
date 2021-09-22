/*  
    - Curso : Estructuras de Datos Avanzadas - Laboratorio
    - Alumno: Alexander Baylon
    - Fecha : 21/09/2021
    - Distancia euclidiana entre puntos en varias dimensiones y su distribucion
*/

#include "euc_dist.hpp"

int main () {
    // N-dimension, Sample Size
    int N,S,i;
    // 2, 5, 10, 15, 20, 25
    cout << "Ingrese el numero de dimensiones: ";
    cin >> N;
    S = 20000;
    
    double min, max, j, tmp;
    
    //vector< vector<double> > time_matrix;
    chrono::time_point<chrono::steady_clock> start, end;
    //time_matrix.resize(4, vector<double>(4));

    euc_dist<int> A(N, S, 0, 1000);

    A.gen_data();
    //A.print_data();
    A.calc_distance();
    //A.print_dist_array();

    max = A.max_distance();
    min = A.min_distance();

    cout << "min: " << '\t' <<min << " max: " << max << endl;
    
    // gen distribution map
    map<string, int> distribution;
    for (i = 0,j = 0.0; i <= 10; ++i, j+=0.1)
    {
        distribution.insert(pair<string, int>(to_string(j),0));
    }

    map<string, int>::iterator itr;
    
    for (int i = 0; i < S; ++i)
    {
        tmp = A.dist_array[i];
        // rounded to one decimal
        tmp = tmp / max;
        tmp = static_cast<int>(tmp * 10) / 10.0;
        //cout << "tmp: " << tmp << endl;
        // count the ratio in the distribution
        itr = distribution.find(to_string(tmp));
        if (itr != distribution.end()){
            (*itr).second++;
        } 
    }

    for (itr = distribution.begin(); itr != distribution.end(); ++itr) {
        cout << itr->first << '\t' << "->" << '\t' << itr->second << endl;
    }

    return 0;
}
