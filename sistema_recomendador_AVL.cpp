#include <iostream>
#include <fstream>
#include <sstream>
#include "DynamicArray_SR.hpp"
#include "KeyValueAVLTree.hpp"
#include <unordered_map>
#include <chrono>


using namespace std;

struct Libro {
    int id;
    string title;
    string author;
    string genre;
    float average_rating;
    int num_page;
    string publication_date;
    string publisher;

    friend ostream& operator<<(ostream& os, const Libro& libro) {
        os << "ID: " << libro.id << "\n"
           << "Titulo: " << libro.title << "\n"
           << "Autor: " << libro.author << "\n"
           << "Genero: " << libro.genre << "\n"
           << "Calificacion promedio: " << libro.average_rating << "\n"
           << "Numero de paginas: " << libro.num_page << "\n"
           << "Fecha de publicacion: " << libro.publication_date << "\n"
           << "Publisher: " << libro.publisher << "\n";
        return os;
    }
};

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
 // Paso 2 - Optimización de búsquedas por categorías
 template<typename Func>
auto medirTiempo(Func&& f) {
    auto inicio = chrono::high_resolution_clock::now();
    f();
    auto fin = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
}

void construirAVLDeCategorias(const DynamicArray<Libro>& libros, KeyValueAVLTree<string, unordered_map<int, Libro>>& avl) {
    for (int i = 0; i < libros.size(); i++) {
        const string& categoria = libros[i].genre;

        KeyValueAVLNode<string, unordered_map<int, Libro>>* nodo = avl.find(categoria);

        if (nodo) {
            nodo->value[i] = libros[i];  // Añadir libro al mapa asociado
        } else {
            unordered_map<int, Libro> mapa;
            mapa[i] = libros[i];
            avl.insert(categoria, mapa);  // Insertar nueva categoría
        }
    }
}

void buscarPorCategoria(const string& categoria, KeyValueAVLTree<string, unordered_map<int, Libro>>& avl) {
    auto inicio = chrono::high_resolution_clock::now();

    KeyValueAVLNode<string, unordered_map<int, Libro>>* nodo = avl.find(categoria);

    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio).count();

    if (nodo) {
        cout << "Categoría encontrada: " << categoria << "\n";
        cout << "Libros en esta categoría:\n";
        for (const auto& [index, libro] : nodo->value) {
            cout << libro << "\n";
        }
    } else {
        cout << "Categoría no encontrada: " << categoria << "\n";
    }

    cout << "Tiempo de búsqueda: " << duracion << " microsegundos\n";
}

int main() {

    DynamicArray<Libro> libros_final;
    loadDataIntoArray("libro_superfinal.csv", libros_final);

    KeyValueAVLTree<std::string, int> avl;

    // Insertar los libros en el árbol AVL
    for (int i = 0; i < libros_final.size(); i++) {
        avl.insert(libros_final[i].title, i); // Clave: nombre del libro, Valor: índice
    }

    std::string book_name;
    std::cout << "Ingrese el título del libro que desea buscar: ";
    std::getline(std::cin, book_name);

    try {
        // Intentar encontrar el nodo exacto
        KeyValueAVLNode<std::string, int>* node = avl.find(book_name);

        if (node) {
            // Nodo exacto encontrado
            int index = node->value;
            std::cout << "\n¡Libro encontrado!\n";
            std::cout << "Índice del libro: " << index << std::endl;
            std::cout << "Información completa del libro:\n" << libros_final[index] << std::endl;
        } else {
            // Si no se encuentra, buscar el nodo más cercano
            std::cout << "\nLibro no encontrado. Buscando el nodo más cercano...\n";

            KeyValueAVLNode<std::string, int>* closest_node = avl.findClosest(book_name);
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

     // Parte 2: Crear el árbol AVL para gestionar categorías de libros
    KeyValueAVLTree<string, unordered_map<int, Libro>> tree;

    // Insertar los libros en el árbol AVL
    auto tiempoConstruccion = medirTiempo([&]() {
        construirAVLDeCategorias(libros_final, tree);
    });
    cout << "Tiempo para construir el árbol AVL: " << tiempoConstruccion << " microsegundos\n";

    // Menú para buscar categorías
    while (true) {
        string categoria;
        cout << "\nIngrese la categoría que desea buscar (o escriba 'salir' para terminar): ";
        getline(cin, categoria);

        if (categoria == "salir") {
            break;
        }

        buscarPorCategoria(categoria, tree);
    }


    return 0;
}

