#ifndef matrix_h
#define matrix_h

#include <vector>
#include <iostream>
#include "math_stuff/vec.h"
#include "math_stuff/matrix4.h"

namespace Math {
	class Matrix {
	//Private garbafe
	private: 
		int rows;
		int columns;
		size_t size;
		float* data;

		//Everything private below this is for getting RREF for inverse and determinant

		//Returns number of row switches and total scaling
		//This information is necessary to get the determinant from REF
		struct rowReductionResults {
			int numRowSwitches = 0;
			float totalScale = 1;
			std::vector<Math::Vec> reducedVecArray;

			//Constructor
			rowReductionResults(std::vector<Vec> vecs) : reducedVecArray(vecs) {}

			//Helper functions to make RREF easier
			Matrix fromREFResults() const; //Turns matrix into this stuct
			float getElem(int row, int column) const; //Gets element from specific index
		};

		rowReductionResults toREFResults() const;

		//Row operations struct. This is just for organization/readability
		struct rowOperations {
			static void scale(float scale, int rowNum, rowReductionResults& columns);
			static void swap(int rowOne, int rowTwo, rowReductionResults& columns);
			static void add(float scale, int rowToChange, int rowToAdd, rowReductionResults& columns);
			static void moveToBottom(int rowNum, rowReductionResults& columns);
		};

		//RREF function
		rowReductionResults toReducedREF() const;

	public:
		//Friend Matrix4 so I can have efficient conversion
		friend class Matrix4;

		//Constructors
		Matrix(int rows, int columns, const float* data);
		Matrix(int rows, int columns);

		//Copy Constructor
		Matrix(const Matrix& copy);

		//Move Constructor
		Matrix(Matrix&& move) noexcept;
		Matrix(Matrix4&& move) noexcept;

		//Destructor
		~Matrix();

		//Getters
		int getRows() const;
		int getColumns() const;
		size_t getSize() const;
		float getData(int index) const;
		float* getDataPointer() const;

		//Setters
		void setData(float data, int index);
		void setData(const float* data);

		//Functions
		void printData() const;

		//Operations
		//I'm not gonna add lvalue and rvalue overrides for EVERYTHING
		//But if I am going through and realizing it would make itm ore convenient, I will.
		//Currently I just dont think its worth sacrificing this (already kinda big) class' readability
		Matrix& operator=(const Matrix& other);
		Matrix& operator=(const Matrix&& other) noexcept;
		Matrix operator+(const Matrix& other) const;
		Matrix operator-(const Matrix& other) const;
		Matrix operator*(float scalar) const;
		Matrix operator*(const Matrix& other) const;

		Matrix transpose() const;
		Matrix inverse() const;
		float getDeterminant() const;
	};
}

#endif