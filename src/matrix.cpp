#include "math_stuff/matrix.h"

//Exceptions header
#include "math_stuff/MatrixIndexOutOfBoundsException.h"
#include "math_stuff/MatrixUninvertibleException.h"
#include "math_stuff/MatrixIncorrectDimensionsException.h"

#include <memory>
#include <cmath>

namespace Math {
	//Matrix stuff! :D

	//Constructors
	Matrix::Matrix(int rows, int columns, const float* data)
		: rows(rows), columns(columns), size(rows * columns), data(new float[columns * rows]) {

		for (int i = 0; i < this->size; ++i) {
			this->data[i] = data[i];
		}
	}

	Matrix::Matrix(int rows, int columns) 
		: rows(rows), columns(columns), size(rows * columns), data(new float[columns * rows]) {

		//Initialize array to 0
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = 0;
		}
	}

	//Copy Constructor
	Matrix::Matrix(const Matrix& copy)
		: rows(copy.getRows()), columns(copy.getColumns()), size(copy.getSize()), data(new float[copy.getSize()])
	{
		for (int i = 0; i < copy.getSize(); ++i) {
			this->data[i] = copy.getData(i);
		}
	}

	//Move Constructors
	Matrix::Matrix(Matrix&& move) noexcept
		: rows(move.getRows()), columns(move.getColumns()), size(move.getSize()), data(move.data)
	{
		move.data = nullptr;
		move.rows = 0;
		move.columns = 0;
		move.size = 0;
	}


	//Destructor
	Matrix::~Matrix() {
		delete[] this->data;
	}

	//Getters
	int Matrix::getRows() const {
		return this->rows;
	}

	int Matrix::getColumns() const {
		return this->columns;
	}

	size_t Matrix::getSize() const {
		return this->size;
	}

	float Matrix::getData(int index) const {
		return this->data[index];
	}

	float* Matrix::getDataPointer() const {
		return this->data;
	}

	//Setters
	void Matrix::setData(float data, int index) {
		//Makes sure user can't add elements that don't fit in the matrix.
		if (index >= this->rows * this->columns) {
			throw MatrixIndexOutOfBoundsException();
		}

		this->data[index] = data;
	}

	//TODO: Better error handling to ensure correct data size
	void Matrix::setData(const float* data) {
		for (int i = 0; i < this->size; ++i) {
			this->setData(data[i], i);
		}
	}

	//Functions
	//Print matrix. Just for testing purposes mostly
	void Matrix::printData() const {
		for (int i = 0; i < this->size; ++i) {
			std::cout << this->getData(i) << ", ";

			if ((i + 1) % this->columns == 0)
				std::cout << std::endl;
		}
	}

	//Operations
	
	//Assignemtn operators
	Matrix& Matrix::operator= (const Matrix& other) {
		if (other.getRows() != this->getRows() || other.getColumns() != this->getColumns()) {
			this->rows = other.getRows();
			this->columns = other.getColumns();

			//Size can still be the same even with different dimensions, so no need to reallocate if so
			if (other.size != this->size) {
				delete[] this->data;
				this->data = new float[other.size];
				this->size = other.getSize();
			}
		}

		for (int i = 0; i < other.getSize(); ++i) {
			this->data[i] = other.getData(i);
		}

		return *this;
	}

	Matrix& Matrix::operator= (const Matrix&& other) noexcept {
		if (other.getRows() != this->getRows() || other.getColumns() != this->getColumns()) {
			this->rows = other.getRows();
			this->columns = other.getColumns();

			//Size can still be the same even with different dimensions, so no need to reallocate if so
			if (other.size != this->size) {
				delete[] this->data;
				this->data = new float[other.size];
				this->size = other.getSize();
			}
		}

		for (int i = 0; i < other.getSize(); ++i) {
			this->data[i] = other.getData(i);
		}

		return *this;
	}

	//Addition
	Matrix Matrix::operator+ (const Matrix& other) const {
		//Checks if matrix dimensions are equal
		if (this->rows != other.rows || this->columns != other.columns) {
			throw MatrixIncorrectDimensionsException();
		}
		
		Matrix out(other.rows, other.columns);

		for (int i = 0; i < other.size; ++i) {
			out.setData((this->getData(i) + other.getData(i)), i);
		}

		return out;
	}

	//Subtraction
	Matrix Matrix::operator- (const Matrix& other) const {
		//Checks if matrix dimensions are equal
		if (this->rows != other.rows || this->columns != other.columns) {
			throw MatrixIncorrectDimensionsException();
		}

		Matrix out(other.rows, other.columns);

		for (int i = 0; i < other.size; ++i) {
			out.setData((this->getData(i) - other.getData(i)), i);
		}

		return out;
	}

	//Scalar multiplication
	Matrix Matrix::operator*(float scalar) const {
		Matrix out(this->rows, this->columns);
		
		for (int i = 0; i < this->size; ++i) {
			out.setData(this->getData(i) * scalar, i);
		}

		return out;
	}

	//Matrix Multiplication
	Matrix Matrix::operator*(const Matrix& other) const {
		/*
		* This matrix multiplication is inefficient and bad.
		* I MIGHT implement Strassen's algorithm for this for the 
		* IMPECCABLE speedup from O(n^3) to O(n^2.83), but I think I'll live for now.
		*/
		
		if (this->columns != other.rows)
			throw MatrixIncorrectDimensionsException();

		Matrix out(this->rows, other.columns);

		for (int i = 0; i < this->rows; ++i) {
			for (int j = 0; j < other.columns; ++j) {
				float sum = 0;
				for (int k = 0; k < this->columns; ++k) {
					sum += this->getData(i * this->columns + k) * other.getData(k * other.columns + j);
				}
				out.setData(sum, i * other.columns + j);
			}
		}

		return out;
	}

	//Transpose matrix
	Matrix Matrix::transpose() const {
		Matrix out(this->columns, this->rows);

		int outIndex = 0;
		for (int i = 0; i < this->columns; ++i) {
			for (int j = i; j < this->size; j += this->columns) {
				out.setData(this->getData(j), outIndex);
				++outIndex;
			}
		}

		return out;
	}

	//Get inverse matrix
	Matrix Matrix::inverse() const {
		//Only square matrices are invertible
		if (this->getRows() != this->getColumns()) {
			throw MatrixUninvertibleException();
		}

		//Calculate augmented matrix RREF
		Matrix identityMatrix(this->getRows(), this->getColumns());
		Matrix augmentedMatrix(this->getRows(), 2 * this->getColumns());

		for (int i = 0; i < identityMatrix.getSize(); i += 1 + identityMatrix.getColumns()) {
			identityMatrix.setData(1, i);
		}

		for (int i = 0; i < this->getSize(); i += this->getColumns()) {
			for (int j = 0; j < this->getColumns(); ++j) {
				augmentedMatrix.setData(this->getData(j + i), j + 2 * i);
				augmentedMatrix.setData(identityMatrix.getData(j + i), j + 2 * i + identityMatrix.getColumns());
			}
		}

		rowReductionResults results = augmentedMatrix.toReducedREF();

		//0 Determinant means uninvertible matrix
		if (results.totalScale == 0 || results.getElem(this->getRows() - 1, this->getColumns() - 1) == 0)
			throw MatrixUninvertibleException();

		//Move the Vec objects into a new std::vector. I realyl wanted to use vector::erase()
		//to make this less dumb, but I keep getting an error and I am toooo tirdf to debug that
		std::vector<Math::Vec> temp;
		temp.reserve(this->getColumns());

		for (int i = this->getColumns(); i < augmentedMatrix.getColumns(); ++i) {
			temp.push_back(results.reducedVecArray.at(i));
		}

		return rowReductionResults(temp).fromREFResults();
	}

	//Gets determinant of matrix
	float Matrix::getDeterminant() const {
		rowReductionResults temp = this->toReducedREF();

		if (temp.totalScale == 0 || temp.getElem(this->getRows() - 1, this->getColumns() - 1) == 0) {
			return 0;
		}

		return 1.0 / temp.totalScale * std::pow(-1, temp.numRowSwitches);
	}

	//Row Reduction Functions

	//Reduced Row Echelon.
	//This goes column by column to find the pivot and reduce the row.
	Matrix::rowReductionResults Matrix::toReducedREF() const {
		//Not sure sure why I spend so much time and brain power
		//relearning how all of this works. It is better for finding matrix determinant
		//and thus its inverse and all that fun stuff, but for now it is NOT necessary.
		//I believe this kind of calculation will come far more in handy if I deal with
		//post processing stuff, but even then who knows.

		rowReductionResults matrix = this->toREFResults();
		int numRows = this->rows;
		int numColumns = this->columns;

		int currentRow = 0;
		int currentCol = 0;

		while (currentCol < numColumns && currentRow < numRows) {
			//If current pivot is 0, find row with largest absolute value pivot value
			if (std::abs(matrix.getElem(currentRow, currentCol)) < 1e-9) {
				//Max pivot and initial row to swap
				float maxPivot = 0;
				int swapRow = -1;

				for (int i = currentRow; i < numRows; ++i) {
					//If pivot is found, swap rows, break out of the loop cuz we're done here
					if (std::abs(matrix.getElem(i, currentCol)) > maxPivot) {
						maxPivot = matrix.getElem(i, currentCol);
						swapRow = i;
					}
				}

				//Every row has a 0
				if (swapRow == -1) {
					++currentCol;

					//This basically just gives me a fast way to see if determinant is 0
					matrix.totalScale = 0;
				}
				else {
					Matrix::rowOperations::swap(swapRow, currentRow, matrix);
				}

				continue;
			}
			
			//Scale row so pivot is 1
			if (matrix.getElem(currentRow, currentCol) != 1)
				Matrix::rowOperations::scale(1.0/matrix.getElem(currentRow, currentCol), currentRow, matrix);

			//For every row in the column, subtract the row so that the whole column is 0
			for (int i = 0; i < numRows; ++i) {
				//Don't do this for pivot row
				if (i == currentRow)
					continue;

				//Subtract row from pivot row if not already 0
				if (std::abs(matrix.getElem(i, currentCol)) > 1e-9) {
					float scale = -1.0 * matrix.getElem(i, currentCol); //Scale so the row goes to 0
					Matrix::rowOperations::add(scale, i, currentRow, matrix);
				}
			}

			++currentCol;
			++currentRow;
		}

		return matrix;
	}

	//Turns matrix into array of column vectors
	Matrix::rowReductionResults Matrix::toREFResults() const {
		int numColumns = this->getColumns();
		int numRows = this->getRows();

		std::vector<Math::Vec> out;
		out.reserve(numColumns);

		for (int i = 0; i < numColumns; ++i) {
			std::unique_ptr<float[]> data = std::make_unique<float[]>(numRows);

			for (int j = 0; j < numRows; ++j) {
				data[j] = this->getData(i + (j * numColumns));
			}

			Vec temp(numRows, data.get());

			out.push_back(temp);
		}

		return rowReductionResults(out);
	}

	//Puts vector back into matrix form
	//Vector needs to have correct dimensions or else there will be some exception I'm sure

	//TODO Add better error handling
	Matrix Matrix::rowReductionResults::fromREFResults() const {
		int numColumns = this->reducedVecArray.size();
		int numRows = this->reducedVecArray.at(0).getSize();

		//Output data. Smart pointer for extra safety.
		std::unique_ptr<float[]> data = std::make_unique<float[]>(numColumns * numRows);

		for (int i = 0; i < numColumns; ++i) {
			for (int j = 0; j < numRows; ++j) {
				data[i + (j * numColumns)] = this->reducedVecArray.at(i).getData(j);
			}
		}

		return Matrix(numRows, numColumns, data.get());
	}

	void Matrix::rowOperations::scale(float scale, int rowNum, Matrix::rowReductionResults& columns) {
		int numRows = columns.reducedVecArray.at(0).getSize();
		int numCols = columns.reducedVecArray.size();
		
		for (int i = 0; i < numCols; ++i) {
			Vec& atIndex = columns.reducedVecArray.at(i);

			atIndex.setData(atIndex.getData(rowNum) * scale, rowNum);
		}

		columns.totalScale *= scale;
	}

	void Matrix::rowOperations::swap(int rowOne, int rowTwo, Matrix::rowReductionResults& columns) {
		int numRows = columns.reducedVecArray.at(0).getSize();
		int numCols = columns.reducedVecArray.size();
		std::vector<float> tempRowVals;
		tempRowVals.reserve(numRows);

		//Move row 1 into temp vector, move row 2 into row 1, move temp into row 2
		int currentRow = 0;
		for (int i = 0; i < numCols; ++i) {
			Vec& atIndex = columns.reducedVecArray.at(i);

			//Moves first row value from this column into temp
			tempRowVals.push_back(atIndex.getData(rowOne));

			//Moves row 2 data into row 1
			atIndex.setData(atIndex.getData(rowTwo), rowOne);

			//Moves temp data into row 2
			atIndex.setData(tempRowVals.at(currentRow), rowTwo);

			++currentRow;
		}

		++columns.numRowSwitches;
	}

	void Matrix::rowOperations::add(float scale, int rowToChange, int rowToAdd, Matrix::rowReductionResults& columns) {
		int numRows = columns.reducedVecArray.at(0).getSize();
		int numCols = columns.reducedVecArray.size();

		for (int i = 0; i < numCols; ++i) {
			Vec& atIndex = columns.reducedVecArray.at(i);

			atIndex.setData(atIndex.getData(rowToChange) + scale * atIndex.getData(rowToAdd), rowToChange);
		}
	}

	void Matrix::rowOperations::moveToBottom(int rowNum, Matrix::rowReductionResults& columns) {
		int numRows = columns.reducedVecArray.at(0).getSize();

		for (int i = rowNum; i < numRows - 1; ++i) {
			Matrix::rowOperations::swap(i, i + 1, columns);
		}
	}

	//Helper function to get Row,Column value from VecArray
	float Matrix::rowReductionResults::getElem(int row, int column) const {
		return this->reducedVecArray.at(column).getData(row);
	}
}