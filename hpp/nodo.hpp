#ifndef NODO_H
#define NODO_H

#include <vector>
#include <utility>
#include <cmath>

class Nodo {
    private:

        float h = 0;
        float coste = 0; // g
        int padrex_ = 0;
        int padrey_ = 0;
        bool obstaculo = 0;
    public: 
        Nodo();
        Nodo(bool obst, float g, int padrex, int padrey); //Constructor
        ~Nodo();  //Destructor

        void set_coste(float g);
        void set_padre(int padrex, int padrey);
        void set_h(float distancia);
        void set_obstaculo();
        float get_g();
        float get_h();
        bool get_obstaculo();
        std::vector<int> get_padre();
};

#endif
