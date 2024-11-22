#include <iostream>
#include <fstream>
#include <sstream>
#include "DynamicArray_SR.hpp"
#include "KeyValueAVLTree.hpp"

using namespace std;

struct Libro {
    int id;
    string title;
    string author;
    string genre;
    float average_rating;
    int num_page;
    int ratings_count;
    string publication_date;
    string publisher;

    friend ostream& operator<<(ostream& os, const Libro& libro) {
        os << "ID: " << libro.id << "\n"
           << "Titulo: " << libro.title << "\n"
           << "Autor: " << libro.author << "\n"
           << "Genero: " << libro.genre << "\n"
           << "Calificacion promedio: " << libro.average_rating << "\n"
           << "Numero de paginas: " << libro.num_page << "\n"
           << "Numero de calificaciones: " << libro.ratings_count << "\n"
           << "Fecha de publicacion: " << libro.publication_date << "\n"
           << "Publisher: " << libro.publisher << "\n";
        return os;
    }
};

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
        //temp = cleanString(temp);  // Limpia el ID de caracteres invisibles
        libro.id = stoi(temp);

        getline(ss, libro.title, ',');

        getline(ss, libro.author, ',');

        getline(ss, libro.genre, ',');

        getline(ss, temp, ',');
        libro.average_rating = stof(temp);

        getline(ss, temp, ',');
        libro.num_page = stoi(temp);

        getline(ss, temp, ',');
        libro.ratings_count = stoi(temp);

        getline(ss, libro.publication_date, ',');

        getline(ss, libro.publisher, ',');

        arr.push_back(libro);
    }

    file.close();
}

int main() {

    DynamicArray<Libro> libros_final;
    loadDataIntoArray("libro_final.csv", libros_final);

    KeyValueAVLTree<std::string, int> avl;

    for (int i = 0; i < libros_final.size(); i++) {//Inserta los libros y sus indices al arbol
        avl.insert(libros_final[i].title, i); // Clave: nombre del libro, Valor: índice
    }

    std::string book_name = "Harry_Potter_and_the_Half-Blood_Prince_(Harry_Potter__#6)";

    try {
        // Intentar encontrar el nodo exacto
        KeyValueAVLNode<std::string, int>* node = avl.find(book_name);

        if (node) {
            // Nodo encontrado
            int index = node->value;
            std::cout << "Índice del libro: " << index << std::endl;
            std::cout << "Información completa del libro:\n" << libros_final[index] << std::endl;
        } else {
            // Si no se encuentra, buscar el nodo más cercano
            std::cout << "Libro no encontrado. Buscando el nodo más cercano..." << std::endl;

            KeyValueAVLNode<std::string, int>* closest_node = avl.find(book_name);
            if (closest_node) {
                std::cout << "Nodo más cercano encontrado:\n";
                std::cout << "Título: " << closest_node->key << "\n";
                std::cout << "Índice: " << closest_node->value << "\n";
                std::cout << "Información completa del libro más cercano:\n"
                          << libros_final[closest_node->value] << std::endl;
            } else {
                std::cout << "No se encontró ningún nodo cercano." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
