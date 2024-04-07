#include "Matrix.h"
#include <stdexcept>
using namespace std;


/// <summary>
/// constructor
/// </summary>
/// <param name="nrLines"> number of rows </param>
/// <param name="nrCols"> number of columns </param>
Matrix::Matrix(int nrLines, int nrCols) : rows(nrLines), cols(nrCols){
	//Best Case: theta(1), when parameters are 0
	//Worst Case: theta(nrLines * nrCols), when parameters are large (resize and for)
	//Average Case: theta(nrLines * nrCols = cp) tight bound, grows at the same rate as the number of elements in the matrix
	head = -1; // first elem is -1
	firstEmpty = 0; 

	int cp = nrLines * nrCols; 
	e.resize(cp, NULL_TTRIPLE); //resizes vector e to cp elements, initializes with NULL_TTRIPLE
	nextLink.resize(cp, 0); //resizes vector nextLink to cp elements, initializes with 0

	for (int i = 0; i < cp - 1; i++) {
		nextLink[i] = i + 1; //set each element of nextLink to the index of the next element
	}
	nextLink[cp - 1] = -1; //set the last element of nextLink to -1
}


/// <summary>
/// used internally when adding new elements to the sparse matrix, 
/// ensuring that an available index is allocated for the new node
/// </summary>
/// <returns> N/A </returns>
int Matrix::allocate() {
	//Best Case: theta(1), occurs when firstEmpty is not equal to -1 and does not depend on size of the matrix
	//Worst Case: theta(1), when firstEmpty is equal to -1, exception thrown which has a constant time complexity, regardless of size of the matrix
	//Average Case: theta(1), whether an index is found or not, time complexity remains constant
	if (firstEmpty != -1) { //if there is an available index(empty node) in the array
		int index = firstEmpty;
		firstEmpty = nextLink[firstEmpty]; //move the firstEmpty to the next slot 
		return index; //index of newly allocated node
	}
	else {
		throw std::out_of_range("Out of memory.");
	}
}


/// <summary>
/// used internally when removing elements from the sparse matrix,
/// allowing the dellocated nodes to be reused
/// </summary>
/// <param name="i"> index of element </param>
void Matrix::deallocate(int i) {
	//Best Case: theta(1), valid index, does not depend on size of the matrix
	//Worst Case: theta(1)
	//Average Case: theta(1), always performs two constant-time operationsn
	nextLink[i] = firstEmpty; //make nextLink point to the previous firstEmpty
	firstEmpty = i; //new firstEmpty because we just deallocated the node
}


/// <summary>
/// creates a new node in the sparse matrix
/// </summary>
/// <param name="e"> element</param>
/// <returns> the newly created node </returns>
int Matrix::createNode(TElem e) {
	//Best Case: theta(1), when available index, a new node is created 
	//Worst Case: theta(1) same as BC
	//Average Case: theta(1) always performs a fixed number of constant_time operations
	int newNode = allocate(); //obtain an available index in the matrix, where the new node can be inserted
	if (newNode != -1) { //if valid index was obtained
		this->e[newNode] = std::make_tuple(0, 0, e); //create new node
		nextLink[newNode] = -1; //new node is the last node in the list
	}

	return newNode; //returns the index of the new node
}



/// <returns> rows </returns>
int Matrix::nrLines() const {
	return rows;
}


/// <returns> columns </returns>
int Matrix::nrColumns() const {
	return cols;
}


/// <summary>
/// retrieve an element from a given position
/// </summary>
/// <param name="i"> row </param>
/// <param name="j"> column </param>
/// <returns>  </returns>
TElem Matrix::element(int i, int j) const {
	//Best Case: theta(1), matrix empty or the element is the head
	//Worst Case: theta(n), when element is at the end, or isn't in the list
	//Average Case: O(n), grows linearly with the number of elements in the matrix
	if (i < 0 || i >= rows || j < 0 || j >= cols) //constant-time complexity
		throw std::out_of_range("Index out of range.");
	
	int current = head;
	while (current != -1) {
		if (std::get<0>(this->e[current]) == i && std::get<1>(this->e[current]) == j) //if element is found
			return std::get<2>(this->e[current]); //returns the value in the node
		current = nextLink[current]; //iterate through the list
	}

	return NULL_TELEM; //if no matching element was found
}


/// <summary>
/// modifies element at position (i,j)
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <param name="e"></param>
/// <returns></returns>
TElem Matrix::modify(int i, int j, TElem e) {
	//Best Case: theta(1), when the element being modified is positioned at the head or when the matrix is empty
	//Worst Case: theta(n), when the element being modified is at the end of the list or it isn't in the list
	//Average Case: O(n), grows linearly with the number of elements in the matrix
	if (i < 0 || i >= rows || j < 0 || j >= cols) {
		throw std::out_of_range("Invalid position!");
	}

	int current = head;
	int prev = -1;

	//traverse the list until the node is found or the list ends
	while (current != -1 && (std::get<0>(this->e[current]) != i || std::get<1>(this->e[current]) != j)) {
		prev = current;
		current = nextLink[current];
	}

	//if a node with the given position is found, update its value
	if (current != -1) {
		TElem previousValue = std::get<2>(this->e[current]);
		std::get<2>(this->e[current]) = e;
		return previousValue;
	}

	//if no node is found, create a new node
	int newNode = createNode(e);
	std::get<0>(this->e[newNode]) = i;
	std::get<1>(this->e[newNode]) = j;

	//new node is inserted lexicographically
	if (prev == -1) {
		//if the new node should be inserted at the beginning of the list
		nextLink[newNode] = head;
		head = newNode;
	}
	else {
		//if the new node should be inserted after a previous node
		nextLink[newNode] = nextLink[prev];
		nextLink[prev] = newNode;
	}

	return NULL_TELEM; //no previous value existed at the given position
}