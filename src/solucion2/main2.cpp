#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <chrono>

using namespace std;

typedef unsigned char uchar;

// Función comparadora lexicográfica
bool comparador(const uchar* a, const uchar* b) {
    return std::strcmp((const char*)a, (const char*)b) < 0;
}

int main() {
    // Medición del tiempo construcción 
    auto inicio_tiempo = std::chrono::high_resolution_clock::now();
    std::list<uchar*> listaDoble
  
    ifstream archivoD1("Datos/D1.txt");
    if (!archivoD1) {
        cerr << "Error al abrir D1.txt" << endl;
        return 1;
    }

    string leer_d1;
    while (archivoD1 >> leer_d1) {
        uchar* palabra = new uchar[leer_d1.length() + 1];
        std::strcpy((char*)palabra, leer_d1.c_str());
        
        // Inserción manteniendo el orden lexicográfico
        auto it = listaDoble.begin();
        while (it != listaDoble.end() && comparador(*it, palabra)) {
            ++it;
        }
        listaDoble.insert(it, palabra);
    }
    archivoD1.close();
    //busqueda
   
    
    
    ifstream archivoD2("Datos/D2.txt");
    if (!archivoD2) {
        cerr << "Error al abrir D2.txt" << endl;
        return 1;
    }
    //inserción 

    //eliminación

    archivoD2.close();
    
    // Medición tiempo palabras
    auto fin_tiempo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin_tiempo - inicio_tiempo;

    cout << "Tiempo de construccion: " << duracion.count() << " ms" << endl;
    cout << "Cantidad final de palabras almacenadas: " << listaDoble.size() << endl;

    // Limpieza final de memoria dinámica
    for (auto ptr : listaDoble) {
        delete[] ptr;
    }
    listaDoble.clear();

    return 0;
}
