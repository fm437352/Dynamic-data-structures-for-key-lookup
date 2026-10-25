#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <chrono>// tiempo
#include <fstream>//abrir archivo
#include <string>

using namespace std;

#define overHead 0.2//porcentaje de celdas adicional


typedef unsigned char uchar;

int main() {
    //vector 
    std::vector<unsigned char*> ArregloDinamico;

    // abrir archivo D1.txt
    ifstream archivoD1("Dato/D1.txt");
    if (!archivoD1)
        return 1;

    //comparar las palabras char*
    //auto deduce automaticamente el tipo de variable
    auto comparador= [](uchar *a, uchar *b){
        if (std:: strcmp((char*)a, (char*)b)< 0)
            return true;
        return false;
    };

    int capacidad_act=0;
    string leer_pa;
    
    while(archivoD1 >> leer_pa){
        //crear un nuevo uchar*
        uchar* palabra= new uchar[leer_pa.length()+1];
        std:: strcpy((char*)palabra, leer_pa.c_str());

        //capacidad del vector
        if (ArregloDinamico.size()>=capacidad_act){
            if (capacidad_act !=0){
                capacidad_act= capacidad_act+ (capacidad_act * overHead);
            }else{
                capacidad_act=10;//capacidad incial 
            }
            ArregloDinamico.reserve(capacidad_act);
        }
        auto insertar= std::lower_bound(ArregloDinamico.begin(),ArregloDinamico.end(),palabra,comparador);
        ArregloDinamico.insert(insertar, palabra);
    
    }
    //buscar como hacer lo del k y el puntero p
    int k[]= {8,32,128,512};
    
    // busqueda 
    bool busqueda = std::binary_search(ArregloDinamico.begin(), ArregloDinamico.end(), /cambiar/,comparador);
    if (busqueda == true){
        auto busque= std::lower_bound(ArregloDinamico.begin(),ArregloDinamico.end(),/cambiar por el k/,comparador);
        int posicion = std::distance(ArregloDinamico.begin(),busque);

    }
    archivoD1.close();

    // abrir archivo D2.txt
    ifstream archivoD2("Datos/D2.txt");
    if (!archivoD2)
        return 1;
    //insercion

    //eliminacion 
    archivoD2.close();

}
