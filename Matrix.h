#pragma once
#include<tuple>
#include<iostream>
#include<vector>
#include<algorithm>
//DO NOT CHANGE THIS PART
typedef int TElem;
typedef std::tuple<int,int,TElem> TTriple;
#define NULL_TELEM -111111
#define NULL_TTRIPLE std::make_tuple(0,0,-111111)

/*struct Node {
	TElem elem;
	int row;
	int col;
	TTriple triple;

	Node(int r, int c, const TElem& e) : row(r), col(c), elem(e), triple(std::make_tuple(r, c, e)) {}
};*/


class Matrix {

private:
	//static const int cp = 10000;
	std::vector<TTriple> e; 
	std::vector<int> nextLink;
	int head;
	int firstEmpty;
	int rows, cols; 
	
	int allocate();
	void deallocate(int i);
	int createNode(TElem e);
	
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
