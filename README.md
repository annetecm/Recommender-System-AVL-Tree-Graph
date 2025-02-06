## 📖 Overview
This project is a **book recommendation system** that suggests books similar to the one you search for. The recommendations are based on common attributes such as:
- **Author**
- **Genre**
- **Publication Date**

Each recommended book is assigned a **similarity weight**, where a higher weight indicates a greater similarity to the searched book.

## ⚡ Features
- Input a book title and get a list of similar books.
- Uses **author, genre, and publication date** as similarity factors.
- Preloaded database of books to provide quick recommendations.
- Assigns a **weighted score** to each recommendation based on similarity.
- Utilizes an **AVL tree structure** to optimize data retrieval and improve performance.

## 🛠️ Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/annetecm/Recommender-System-AVL-Tree-Graph.git
2. Navigate to the project directory:
   ```sh
   cd Recommender-System-AVL-Tree-Graph
3. Compile te program using g++:
   ```sh
   g++ -o Recommender-System-AVL-Tree-Graph sistema_recomendador_AVL.cpp
4. Run the program:
   ```sh
   ./Recommender-System-AVL-Tree-Graph

## 🚀 Usage
1. Start the program.
2. Enter the title of a book you are interested in.
3. The system will return a list of recommended books ranked by similarity.

## 🗄️ Database
The system relies on a **preloaded database** of books. If you want to update or expand the dataset, you can modify the libro_superfinal.csv file.
