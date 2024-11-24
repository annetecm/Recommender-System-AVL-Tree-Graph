#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "DynamicArray_SR.hpp"
#include "KeyValueAVLTree.hpp"
#include "WeightedUndirectedGraph.hpp"

using namespace std;

string cleanString(const string& str) { //Se tuvo que recurrir a esta funcion para limpiar los caracteres ya que al parecer algunos tenian caracteres invisibles
    string cleaned;
    for (char c : str) {
        if (isdigit(c)) {
            cleaned += c;  // Solo agrega caracteres numéricos
        }
    }
    return cleaned;
}

void loadDataIntoArray(const string& filename, DynamicArray<Libro>& arr) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;  // Contador para el número de línea

    if (!file) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    while (getline(file, line)) {

        stringstream ss(line);
        string temp;
        Libro libro;

        getline(ss, temp, ',');
        temp = cleanString(temp);  // Limpia el ID de caracteres invisibles
        libro.id = stoi(temp);

        getline(ss, libro.title, ',');

        getline(ss, libro.author, ',');

        getline(ss, libro.genre, ',');

        getline(ss, temp, ',');
        libro.average_rating = stof(temp);

        getline(ss, temp, ',');
        libro.num_page = stoi(temp);

        getline(ss, libro.publication_date, ',');

        getline(ss, libro.publisher, ',');

        arr.push_back(libro);
    }

    file.close();
}

int main() {

    DynamicArray<Libro> libros_final;
    loadDataIntoArray("libro_superfinal.csv", libros_final);

    auto start_creation = std::chrono::high_resolution_clock::now();
    KeyValueAVLTree<std::string, int> avl;

    // Insertar los libros en el árbol AVL
    for (int i = 0; i < libros_final.size(); i++) {
        avl.insert(libros_final[i].title, i); // Clave: nombre del libro, Valor: índice
    }
    auto end_creation = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> creation_duration = end_creation - start_creation;
    std::cout << "Tiempo para construir el arbol de busqueda: " << creation_duration.count() << " segundos\n";

    std::string book_name;
    std::cout << "Ingrese el título del libro que desea buscar: ";
    std::getline(std::cin, book_name);

    try {
        // Intentar encontrar el nodo exacto
        auto start_find = std::chrono::high_resolution_clock::now();
        KeyValueAVLNode<std::string, int>* node = avl.find(book_name);
        auto end_find = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> find_duration = end_find - start_find;
        std::cout << "Busqueda en el arbol tardo: " << find_duration.count() << " segundos\n";

        if (node) {
            // Nodo exacto encontrado
            int index = node->value;
            std::cout << "\n¡Libro encontrado!\n";
            std::cout << "Índice del libro: " << index << std::endl;
            std::cout << "Información completa del libro:\n" << libros_final[index] << std::endl;
        } else {
            // Si no se encuentra, buscar el nodo más cercano
            std::cout << "\nLibro no encontrado. Buscando el nodo más cercano...\n";

            auto start_findClosest = std::chrono::high_resolution_clock::now();
            KeyValueAVLNode<std::string, int>* closest_node = avl.findClosest(book_name);
            auto end_findClosest = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> findClosest_duration = end_findClosest - start_findClosest;
            std::cout << "Busqueda del nodo mas cercano: " << findClosest_duration.count() << " segundos\n";

            if (closest_node) {
                std::cout << "\nNodo más cercano encontrado:\n";
                std::cout << "Título: " << closest_node->key << "\n";
                std::cout << "Índice: " << closest_node->value << "\n";
                std::cout << "Información completa del libro más cercano:\n"
                          << libros_final[closest_node->value] << std::endl;
            } else {
                std::cout << "\nNo se encontró ningún nodo cercano." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    double threshold = 0.6;
    Graph grafo;

    for (size_t i = 0; i < libros_final.size(); ++i) {
        for (size_t j = i + 1; j < libros_final.size(); ++j) {
            double similarity = calculateSimilarity(libros_final[i], libros_final[j]);
            if (similarity >= threshold) {
                double weight = 1.0 - similarity;
                grafo.addEdge(libros_final[i].title, libros_final[j].title, weight);
            }
        }
    }

    string titulo;
    cout << "Nombre del libro que te interesa para ver sus similares: ";
    getline(cin, titulo);
    grafo.displayAdjacent(titulo);

    return 0;
}

