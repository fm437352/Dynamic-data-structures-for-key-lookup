#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <chrono>//tiempo
#include <fstream>//abrir archivo
#include <string>
#include <random>

using namespace std;

#define overHead 0.2 // porcentaje de celdas adicional

typedef unsigned char uchar;

int main() {
    //crear vector
    std::vector<unsigned char*> ArregloDinamico;

    // Abrir archivo D1.txt
    ifstream archivoD1("Datos/D1.txt");
    if (!archivoD1)
        return 1;

    // Comparador de palabras char*
    //auto deduce automaticamente el tipo de variable
    auto comparador = [](uchar* a, uchar* b) {
        if (std::strcmp((char*)a, (char*)b) < 0)
            return true;
        return false;
    };

    int capacidad_act = 0;
    string leer_pa;

    while (archivoD1 >> leer_pa) {
        //crear un nuevo uchar*
        uchar* palabra = new uchar[leer_pa.length() + 1];
        std::strcpy((char*)palabra, leer_pa.c_str());
        //capacidad de el vector
        if (ArregloDinamico.size() >= (size_t)capacidad_act) {
            if (capacidad_act != 0) {
                capacidad_act = capacidad_act + (capacidad_act * overHead);
            } else {
                capacidad_act = 10;//capacidad inicial
            }
            ArregloDinamico.reserve(capacidad_act);
        }
        auto insertar = std::lower_bound(ArregloDinamico.begin(), ArregloDinamico.end(), palabra, comparador);
        ArregloDinamico.insert(insertar, palabra);
    }

    archivoD1.close();

    // Búsqueda
    std::vector<int> ValoresK = {8, 32, 128, 512};
    auto inicio_busqueda = chrono::high_resolution_clock::now();
    for (int k : ValoresK) {
        for (int i = 0; i < k; i++) {
            if (!ArregloDinamico.empty()) {
                uchar* palabra_rand = ArregloDinamico[rand() % ArregloDinamico.size()];
                
                bool encontrado = std::binary_search(ArregloDinamico.begin(), ArregloDinamico.end(), palabra_rand, comparador);
                if (encontrado == true) {
                    auto busque = std::lower_bound(ArregloDinamico.begin(), ArregloDinamico.end(), palabra_rand, comparador);
                    int posicion = std::distance(ArregloDinamico.begin(), busque);
                } else {
                    std::cout << "la palabra no esta";
                }
            }
        }
    }
    auto fin_busqueda = chrono::high_resolution_clock::now();
    chrono::duration<double> busqueda_duracion = fin_busqueda - inicio_busqueda;
    cout << "Tiempo busqueda: " << busqueda_duracion.count() << "s" << endl;
    
    size_t memoria_busqueda = (ArregloDinamico.capacity() * sizeof(uchar*));
    cout << "Bytes: " << memoria_busqueda << " bytes" << endl;

    // Abrir archivo D2.txt
    ifstream archivoD2("Datos/D2.txt");
    if (!archivoD2)
        return 1;

    string palabra2;
    bool ya_esta = false; // true para insertar, false para eliminar

    double tiempo_total_insercion = 0.0;
    double tiempo_total_eliminacion = 0.0;
    
    size_t memoria_final_insercion = 0;
    size_t memoria_final_eliminacion = 0;

    while (archivoD2 >> palabra2) {
        uchar* palabra_d2 = new uchar[palabra2.length() + 1];
        std::strcpy((char*)palabra_d2, palabra2.c_str());

        if (ya_esta == true) {
            // Medir inserción por separado
            auto inicio_ins = chrono::high_resolution_clock::now();
            
            if (ArregloDinamico.size() >= (size_t)capacidad_act) {
                capacidad_act = capacidad_act + (capacidad_act * overHead);
                ArregloDinamico.reserve(capacidad_act);
            }
            auto insercion_it = std::lower_bound(ArregloDinamico.begin(), ArregloDinamico.end(), palabra_d2, comparador);
            ArregloDinamico.insert(insercion_it, palabra_d2);
            
            auto fin_ins = chrono::high_resolution_clock::now();
            tiempo_total_insercion += chrono::duration<double>(fin_ins - inicio_ins).count();
            memoria_final_insercion = ArregloDinamico.capacity() * sizeof(uchar*);
        } else {
            // Medir eliminación por separado
            auto inicio_elim = chrono::high_resolution_clock::now();
            
            auto eliminar = std::lower_bound(ArregloDinamico.begin(), ArregloDinamico.end(), palabra_d2, comparador);
            if (eliminar != ArregloDinamico.end() && std::strcmp((char*)*eliminar, (char*)palabra_d2) == 0) {
                delete[] *eliminar;
                ArregloDinamico.erase(eliminar);
            } else {
                delete[] palabra_d2;
            }
            
            auto fin_elim = chrono::high_resolution_clock::now();
            tiempo_total_eliminacion += chrono::duration<double>(fin_elim - inicio_elim).count();
            memoria_final_eliminacion = ArregloDinamico.capacity() * sizeof(uchar*);
        }
        ya_esta = !ya_esta;
    }

    archivoD2.close();
    std::cout << "tiempo insercion: " << tiempo_total_insercion << " segundos" << endl;
    std::cout << "Bytes " << memoria_final_insercion << " bytes" << endl;
    
    std::cout << "tiempo eliminacion: " << tiempo_total_eliminacion << " segundos" << endl;
    std::cout << "Bytes: " << memoria_final_eliminacion << " bytes" << endl;

    // Liberar memoria final del vector en el heap
    size_t memoria_total = ArregloDinamico.capacity() * sizeof(uchar*);
    for (uchar* p : ArregloDinamico) {
        memoria_total += std::strlen((char*)p) + 1;
        delete[] p;
    }
    
    std::cout << "Memoria total: " << memoria_total << " bytes" << endl;

    return 0;
}
