// vector.h
//---------------------------------------------------------------------------------
#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
//--------------------------------------------------------------------------------

	/**
	 * @class Vector
	 * @brief  Self growing array that uses any data type
	 *
	 * Dyanmic array that self grows
	 *
	 * @author Devante Ayris
	 * @version 01
	 * @date 11/04/2019 Devante Ayris, Started
	 *
	 * @todo N/A
	 *
	 * @bug N/A
	 */

template<class T>
class Vector
{
private:

	/// Current max size of array
	int cap;

	/// Current no. of elements inside array
	int nrOfEl;

	/// Array that holds T data
	T **arr;

	/// Default size of array
	int defaultSize = 5;


public:

	/**
	 * @brief  Default Constructor for Vector
	 *
	 * This will set all members of Vector class default
	 * and initialize an array
	 *
	 * @return void
	 */
	Vector();

	/**
	 * @brief  Constructor for Vector
	 *
	 * This will set all members of Vector class default
	 * except for cap which will be assigned the value
	 * of param size.
	 *
	 * @param size - size of array
	 *
	 * @return void
	 */
	Vector(int size);

	/**
	 * @brief  Destructor for Vector
	 *
	 * Deletes memory on heap that was made by this class
	 * which is the array that was initialized by the
	 * constructors
	 *
	 * @return void
	 */
	~Vector();

	/**
	 * @brief  Copy Constructor for Vector
	 *
	 * When another same object tries to use '='
	 * it will call this method to copy the data
	 *
	 * @param obj - vector object
	 * @return void
	 */
	Vector(const Vector& obj);

	/**
	 * @brief  Operator for arr array of vector
	 *
	 * Checks if param entered is not out of bounds of array
	 * and then returns the object that is stored at index
	 *
	 * @param index - index used for getting object from array
	 *
	 * @return arr[index] - object at location index
	 */
	T& operator[](const int index) const;

	/**
	 * @brief  Operator for arr array of vector
	 *
	 * This operator is similar to the copy constructor, this operator
	 * is used to copy all elements to another object that is the same.
	 *
	 * @param obj - object being copied
	 *
	 * @return void
	 */
	T& operator=(const Vector &obj);

	/**
	 * @brief  Initializes array of vector to nullptrs
	 *
	 * Uses param to determine where to start assigning nullptrs to array
	 *
	 * @param from - from where to start initializing null on arr
	 *
	 * @return void
	 */
	void initialize(int from);

	/**
	 * @brief  Expands arr
	 *
	 * Expands when limit of array has been reached
	 *
	 * @return void
	 */
	void expand();

	/**
	 * @brief  Adds object to top of array
	 *
	 * Checks if array is at it's max size, if so it will
	 * call to expand the array and then assign the new object.
	 * If not max size, it will assign the new object.
	 *
	 * @param obj - object thats being added
	 * @return void
	 */
	void push(const T& obj);

	/**
	 * @brief  Deletes an object at index
	 *
	 * Delete an object at index location
	 *
	 * @param index - the index of object to be deleted
	 *
	 * @return void
	 */
	void pop(int index);

	/**
	 * @brief  Gets current amount of elements in array
	 *
	 * Gets current amount and then returns it
	 *
	 * @return nrOfEl - the number of elements in the array
	 */
	const int& size() const;


};

template<class T>
Vector<T>::Vector()
{
	this->cap = defaultSize; // size of default array
	this->nrOfEl = 0;
	this->arr = new T*[this->cap]; // create new memory on heap for array
	initialize(0);
}

template<class T>
Vector<T>::Vector(int size)
{
	this->cap = size; // size of constructor array
	this->nrOfEl = 0;
	this->arr = new T*[this->cap]; // create new memory on heap for array
	initialize(0);
}

template<class T>
Vector<T>::~Vector()
{
	for (int i = 0; i < this->nrOfEl; i++)
	{
		delete this->arr[i];
		// frees all memory in array each position
	}
	delete[] this->arr;
}


template<class T>
Vector<T>::Vector(const Vector& obj)
{
	this->cap = obj.cap;
	this->nrOfEl = obj.nrOfEl;
	this->arr = new T*[this->cap];

	for (int i = 0; i < this->nrOfEl; i++)
	{
		this->arr[i] = new T(*obj.arr[i]);
		// copies all objects into new array
	}

	initialize(0);
}

template<class T>
T& Vector<T>::operator[](const int index) const
{
	if (index < 0 || index >= this->nrOfEl)
	{
		throw("OUT OF BOUNDS!");
		// bounds checking
	}

	return *this->arr[index];
}

template<class T>
T& Vector<T>::operator=(const Vector &obj)
{
	this->cap = obj.cap;
	this->nrOfEl = obj.nrOfEl;
	this->arr = new T*[this->cap];

	for (int i = 0; i < this->nrOfEl; i++)
	{
		this->arr[i] = new T(*obj.arr[i]);
		// copies all objects into new array
	}

	initialize(0);
}

template<class T>
void Vector<T>::initialize(int from)
{
	for (int i = 0; i < this->cap; i++)
	{
		this->arr[i] = nullptr;
		// sets all array objects to nullptr
	}

}

template<class T>
void Vector<T>::expand()
{
	this->cap *= 2;

	T **tempArr = new T*[this->cap]; // create temp array

	for (int i = 0; i < this->nrOfEl; i++)
	{
		tempArr[i] = this->arr[i];
		// copy all objects into temp array
	}

	delete[]this->arr; // deleta old array
	this->arr = tempArr; // old array is assigns all new objects with it's new size
}

template<class T>
void Vector<T>::push(const T& obj)
{
	if (this->nrOfEl >= this->cap)
	{
		expand();
		// when the number of elements
		// larger than the size of array
		// call expand() method
	}

	this->arr[this->nrOfEl++] = new T(obj);
	// add new object on top of array
}

template<class T>
void Vector<T>::pop(int index)
{
	if (index < 0 || index >= this->nrOfEl)
	{
		throw("OUT OF BOUNDS!!!!");
		// bounds checking
	}

	delete this->arr[index]; // delete the object at location index

	for (int i = index; i < this->nrOfEl - 1; i++)
	{
		this->arr[i] = this->arr[i + 1];
		// reorganise array so there
		// is no missing location
	}

	this->arr[this->nrOfEl--] = nullptr; // set the top location as nullptr, because there is nothing there

}

template<class T>
const int& Vector<T>::size() const
{
	return this->nrOfEl;
}


#endif // VECTOR_H_INCLUDED

