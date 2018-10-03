#ifndef ADJACENCY_MATRIX_HPP
#define ADJACENCY_MATRIX_HPP

// Adjacency matrix representation of ADT Graph
// Used in TourismSystem
class AdjacencyMatrix
{
private:
    int** matrix;
    int size;

public:
    AdjacencyMatrix(int size);
    AdjacencyMatrix(int** matrix, int size);
    ~AdjacencyMatrix();

    int getSize() const;
    int getEdge(int row, int col) const;

    void appendZeros(); // Append and initialise new row and column to zero
    void removeRowColAt(int index); // Remove row and column corresponded to index

    void addEdge(int src, int dest);
    void removeEdge(int src, int dest);

    bool isEdge(int src, int dest);
    bool isPath(int src, int dest); // Check whether path exists between src and dest. Edge between src and dest is not counted

    void printMatrix();
};

#endif // ADJACENCY_MATRIX_HPP
