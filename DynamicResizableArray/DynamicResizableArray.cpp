#include <iostream>
#include "Vector.h"

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock = nullptr; // example memory block

	// constructors
	Vector3()
	{
		m_MemoryBlock = new int[5]; // for example
	}
	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5]; // for example
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		m_MemoryBlock = new int[5]; // for example
	}

	// don't call the copy constructor anywhere in this code
	Vector3(const Vector3& other) = delete;
	// move constructor
	Vector3(Vector3&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;

		std::cout << "Move" << std::endl;
	}

	// destructor
	~Vector3()
	{
		std::cout << "Destroy" << std::endl;

		delete[] m_MemoryBlock;
	}

	// don't call the copy operator anywhere in this code
	Vector3& operator=(const Vector3& other) = delete;
	// move operator
	Vector3& operator=(Vector3&& other)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;

		std::cout << "Move" << std::endl;

		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

int main()
{
	Vector<Vector3> vector;

	//vector.PushBack(Vector3(1.0f));
	//vector.PushBack(Vector3(2.0f,3.0f,4.0f));
	//vector.PushBack(Vector3());

	///*
	vector.EmplaceBack(1.0f);
	vector.EmplaceBack(2.0f, 3.0f, 4.0f);
	vector.EmplaceBack(1.0f, 3.0f, 4.0f);
	vector.EmplaceBack();
	PrintVector(vector);

	vector.PopBack();
	vector.PopBack();
	PrintVector(vector);

	vector.EmplaceBack(6.0f, 4.0f, 7.0f);
	vector.EmplaceBack(0.0f, 9.0f, 2.0f);
	PrintVector(vector);

	vector.Clear();
	PrintVector(vector);

	vector.EmplaceBack(6.0f, 4.0f, 7.0f);
	vector.EmplaceBack(0.0f, 9.0f, 2.0f);
	PrintVector(vector);
	//*/

	/*
	Vector<int> intVector;
	intVector.PushBack(5);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	PrintVector(intVector);
	intVector.PopBack();
	PrintVector(intVector);
	intVector.Clear();
	PrintVector(intVector);
	*/

	/*
	Vector<std::string> stringVector;
	stringVector.PushBack("One");
	stringVector.EmplaceBack("Two");
	stringVector.EmplaceBack("Three");
	stringVector.EmplaceBack("Four");
	stringVector.EmplaceBack("Five");
	stringVector.EmplaceBack("Six");
	PrintVector(stringVector);
	stringVector.PopBack();
	PrintVector(stringVector);
	stringVector.Clear();
	PrintVector(stringVector);
	*/
}