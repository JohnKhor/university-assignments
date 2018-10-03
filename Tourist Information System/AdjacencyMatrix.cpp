#include "AdjacencyMatrix.hpp"
#include <iostream>
#include "LinkedStack.cpp"
#include <cassert>

AdjacencyMatrix::AdjacencyMatrix(int size): size(size)
{
    // Empty matrix
    matrix = new int*[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
}

AdjacencyMatrix::AdjacencyMatrix(int** matrix, int size) : matrix(matrix), size(size)
{
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    // Release memory allocated to matrix
    for (int i = 0; i < size; i++)
        delete [] matrix[i];
    delete [] matrix;
}

int AdjacencyMatrix::getSize() const
{
    return size;
}

int AdjacencyMatrix::getEdge(int row, int col) const
{
    assert(row >= 0 && row < size);
    assert(col >= 0 && col < size);

    return matrix[row][col];
}

// Append and initialise new row and column to zero
void AdjacencyMatrix::appendZeros()
{
    // Copy matrix to new matrix and append zeros to it
    int** tempMatrix = new int*[size + 1];
    for (int row = 0; row < size + 1; row++)
    {
        tempMatrix[row] = new int[size + 1];
        for (int col = 0; col < size + 1; col++)
        {
            if (row == size || col == size)
                tempMatrix[row][col] = 0; // Initialise new row and column to zero
            else
                tempMatrix[row][col] = matrix[row][col]; // Copy previous values
        }
    }
    // Release memory to previous matrix
    for (int i = 0; i < size; i++)
        delete [] matrix[i];
    delete [] matrix;
    // Points to new matrix and increase size by one
    matrix = tempMatrix;
    size = size + 1;
}

// Remove row and column corresponded to index
void AdjacencyMatrix::removeRowColAt(int index)
{
    assert(index >= 0 && index < size);

    // Copy matrix to new matrix except at row and column corresponded to index
    int** tempMatrix = new int*[size - 1];
    for (int row = 0; row < size; row++)
    {
        tempMatrix[row] = new int[size - 1];
        for (int col = 0; col < size; col++) // Copy previous values except row/column at index
        {
            if (row < index && col < index)
                tempMatrix[row][col] = matrix[row][col];
            else if (row < index && col > index)
                tempMatrix[row][col - 1] = matrix[row][col];
            else if (row > index && col < index)
                tempMatrix[row - 1][col] = matrix[row][col];
            else if (row > index && col > index)
                tempMatrix[row - 1][col - 1] = matrix[row][col];
        }
    }
    // Release memory to previous matrix
    for (int i = 0; i < size; i++)
        delete [] matrix[i];
    delete [] matrix;
    // Points to new matrix and decrease size by one
    matrix = tempMatrix;
    size = size - 1;
}

void AdjacencyMatrix::addEdge(int src, int dest)
{
    assert(src >= 0 && src < size);
    assert(dest >= 0 && dest < size);

    // Direct flight is available from src to dest and vice versa
    matrix[src][dest] = 1;
    matrix[dest][src] = 1;
}

void AdjacencyMatrix::removeEdge(int src, int dest)
{
    assert(src >= 0 && src < size);
    assert(dest >= 0 && dest < size);

    // Direct flight is not available from src to dest and vice versa
    matrix[src][dest] = 0;
    matrix[dest][src] = 0;
}

bool AdjacencyMatrix::isEdge(int src, int dest)
{
    assert(src >= 0 && src < size);
    assert(dest >= 0 && dest < size);

    // Return true if direct flight is available from src to dest
    return matrix[src][dest] == 1;
}

// Do depth-first search to check whether path exists between src and dest. Edge between src and dest is not counted
bool AdjacencyMatrix::isPath(int src, int dest)
{
    assert(src >= 0 && src < size);
    assert(dest >= 0 && dest < size);

    // Mark all vertices as not visited
    bool* visited = new bool[size];
    for (int i = 0; i < size; i++)
        visited[i] = 0;

    // Push source vertex to stack
    LinkedStack<int> connection;
    connection.push(src);

    while(!connection.isEmpty())
    {
        // Current vertex
        int start = connection.peek();
        connection.pop();

        // If current vertex is not visited
        if (!visited[start])
        {
            // Mark current vertex as visited
            visited[start] = 1;
            // Check all adjacent vertices of current vertex
            for (int adjacent = 0; adjacent < size; adjacent++)
            {
                // If there's an edge between current vertex and an adjacent vertex
                if (isEdge(start, adjacent))
                {
                    // Push adjacent vertex to stack for backtracking
                    connection.push(adjacent);
                    // Path (indirect flight) exists when
                    // (1) there's an edge (direct flight) between current vertex and destination vertex
                    // (2) current vertex is not source vertex as edge (direct flight) between source vertex and
                    // destination vertex is not considered
                    if (start != src && adjacent == dest)
                    {
                        delete [] visited; // Release memory
                        return true;
                    }
                }
            }
        }
    }

    delete [] visited; // Release memory
    return false; // No path (indirect flight) exists
}

void AdjacencyMatrix::printMatrix()
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
            std::cout << matrix[row][col] << " ";
        std::cout << "\n";
    }
}
