#ifndef WEIGHTED_UNDIRECTED_GRAPH_HPP
#define WEIGHTED_UNDIRECTED_GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>

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

    friend std::ostream& operator<<(std::ostream& os, const Libro& libro) {
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

class Graph {
    unordered_map<string, vector<pair<string, double>>> adjacencyList;

public:
    void addEdge(const string& book1, const string& book2, double weight) {
        adjacencyList[book1].emplace_back(book2, weight);
        adjacencyList[book2].emplace_back(book1, weight); //Function of std vector to insert a new element at the end of a vector
    }

    void displayAdjacent(const string& book) {
        if (adjacencyList.find(book) != adjacencyList.end()) {
            cout << "Libros adyacentes a \"" << book << "\":" << endl;
            for (const auto& neighbor : adjacencyList[book]) {
                cout << " - " << neighbor.first << " (peso: " << neighbor.second << ")" << endl;
            }
        } else {
            cout << "El libro \"" << book << "\" no tiene libros adyacentes o no esta en el grafo." << endl;
        }
    }
};

double calculateSimilarity(const Libro& book1, const Libro& book2) {
    double similarity = 0.0;
    if (book1.author == book2.author) similarity += 0.3;
    if (book1.genre == book2.genre) similarity += 0.3;
    if (book1.publication_date == book2.publication_date) similarity += 0.3;
    return similarity;
}

#endif