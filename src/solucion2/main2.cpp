#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <chrono>

using namespace std;

typedef unsigned char uchar;

//Comparación lexicográfica
bool comparador(const uchar* a, const uchar* b) {
    return std::strcmp((const char*)a, (const char*)b) < 0;
}

//Función búsqueda
bool search(std::list<uchar*>::iterator &P, const uchar* x, bool derecha, std::list<uchar*> &lista) {
    if (lista.empty()) return false;
    
    auto it = P;
    int comp = 0;

    if (derecha) {
        while (it != lista.end()) {
            comp = std::strcmp((const char*)*it, (const char*)x);
            if (comp == 0) {
                P = it;
                return true;
            } else if (comp > 0) {
                P = it;
                break;
            }
            ++it;
        }
        if (it == lista.end()) {
            P = std::prev(lista.end());
        }
    } else {
        while (true) {
            comp = std::strcmp((const char*)*it, (const char*)x);
            if (comp == 0) {
                P = it;
                return true;
            } else if (comp < 0) {
                P = it;
                break;
            }
            if (it == lista.begin()) break;
            --it;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    //Validar parámetros K y REP
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <K> <REP>" << endl;
        return 1;
    }

    int K = std::stoi(argv[1]);
    int REP = std::stoi(argv[2]);

    //Construcción
    auto inicio_tiempo = std::chrono::high_resolution_clock::now();
    std::list<uchar*> listaDoble;
  
    ifstream archivoD1("Datos/D1.txt");
    if (!archivoD1) {
        cerr << "Error al abrir D1.txt" << endl;
        return 1;
    }

    string leer_d1;
    size_t memoria_bytes = 0;
    while (archivoD1 >> leer_d1) {
        size_t len = leer_d1.length() + 1;
        uchar* palabra = new uchar[len];
        std::strcpy((char*)palabra, leer_d1.c_str());
        
        memoria_bytes += sizeof(uchar*) + len;

        //Inserción en orden lexicográfico
        auto it = listaDoble.begin();
        while (it != listaDoble.end() && comparador(*it, palabra)) {
            ++it;
        }
        listaDoble.insert(it, palabra);
    }
    archivoD1.close();
    
    auto fin_construccion = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion_construccion = fin_construccion - inicio_tiempo;
    

    //Búsqueda
    auto inicio_busqueda = std::chrono::high_resolution_clock::now();
    
    auto P = listaDoble.begin();
    bool direccion_der = true;
    int exitosas = 0;

    if (!listaDoble.empty()) {
        auto it_aux = listaDoble.begin();
        for (int r = 0; r < REP; ++r) {
            uchar* clave_a_buscar = *it_aux;
            if (search(P, clave_a_buscar, direccion_der, listaDoble)) {
                exitosas++;
            }
            direccion_der = !direccion_der;
            ++it_aux;
            if (it_aux == listaDoble.end()) it_aux = listaDoble.begin();
        }
    }

    auto fin_busqueda = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion_busqueda = fin_busqueda - inicio_busqueda;


    //Inserción - Eliminación
    auto inicio_ins_elim = std::chrono::high_resolution_clock::now();

    ifstream archivoD2("Datos/D2.txt");
    if (!archivoD2) {
        cerr << "Error al abrir D2.txt" << endl;
        return 1;
    }

    string leer_d2;
    int contador_op = 0;
    long long ins_cant = 0, del_exito = 0, del_fallo = 0;

    while (archivoD2 >> leer_d2) {
        size_t len_d2 = leer_d2.length() + 1;
        uchar* palabra_d2 = new uchar[len_d2];
        std::strcpy((char*)palabra_d2, leer_d2.c_str());

        if (contador_op % 2 == 0) {
            //Inserción intercalada
            auto it = listaDoble.begin();
            while (it != listaDoble.end() && comparador(*it, palabra_d2)) {
                ++it;
            }
            listaDoble.insert(it, palabra_d2);
            memoria_bytes += sizeof(uchar*) + len_d2;
            ins_cant++;
        } else {
            //Eliminación intercalada
            auto it = listaDoble.begin();
            bool encontrada = false;
            while (it != listaDoble.end()) {
                if (std::strcmp((const char*)*it, (const char*)palabra_d2) == 0) {
                    memoria_bytes -= (sizeof(uchar*) + std::strlen((const char*)*it) + 1);
                    delete[] *it;
                    listaDoble.erase(it);
                    encontrada = true;
                    break;
                }
                ++it;
            }
            if (encontrada) {
                del_exito++;
                delete[] palabra_d2;
            } else {
                del_fallo++;
                delete[] palabra_d2;
            }
        }
        contador_op++;
    }
    archivoD2.close();

    auto fin_ins_elim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion_ins_elim = fin_ins_elim - inicio_ins_elim;

    
    cout << "K = " << K << ", REP = " << REP << endl;
    cout << "Tiempo de construccion: " << duracion_construccion.count() << " s" << endl;
    cout << "Tiempo de busqueda: " << duracion_busqueda.count() << " s (Exitosas: " << exitosas << ")" << endl;
    cout << "Tiempo de insercion/eliminacion: " << duracion_ins_elim.count() << " s (Ins: " << ins_cant << ", Del: " << del_exito << ")" << endl;
    cout << "Cantidad final de palabras almacenadas: " << listaDoble.size() << endl;
    cout << "Memoria dinamica RAM aproximada: ~" << (memoria_bytes / 1024.0) << " KB" << endl;

    // Limpieza memoria dinámica
    for (auto ptr : listaDoble) {
        delete[] ptr;
    }
    listaDoble.clear();

    return 0;
}
