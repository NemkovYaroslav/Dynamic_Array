#pragma once

template<typename T>
class Vector
{
public:
	Vector()
	{
		ReAlloc(2);
	}

	~Vector()
	{
		Clear();
		//delete[] m_Data;
		::operator delete(m_Data, m_Capacity * sizeof(T)); // don't call any destructors
	}

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2); // resize by 1.5 factor

		//m_Data[m_Size] = value;
		new(&m_Data[m_Size]) T(std::move(value));
		m_Size++;
	}

	void PushBack(T&& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		//m_Data[m_Size] = std::move(value);
		new(&m_Data[m_Size]) T(std::move(value));
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);            // exists the memory
		new(&m_Data[m_Size]) T(std::forward<Args>(args)...); // create an object in place of actual memory
		//m_Data[m_Size] = T(std::forward<Args>(args)...);   // construct an object here (forward all the arguments)
		return m_Data[m_Size++];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}
	const T& operator[](size_t index) const
	{
		if (index >= m_Size)
		{
			// assert
		}
		return m_Data[index];
	}

	size_t Size() const { return m_Size; }
private:
	void ReAlloc(size_t newCapacity)
 	{
		//T* newBlock = new T[newCapacity]; // don't have to call the constructor or destructor
		T* newBlock = (T*)::operator new (newCapacity * sizeof(T)); // that's why use it

		// if allocation is downsize
		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			//newBlock[i] = std::move(m_Data[i]); // a move constructor for moving more complex types correctly
			new(&newBlock[i]) T(std::move(m_Data[i]));

		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		//delete[] m_Data;
		::operator delete(m_Data, m_Capacity * sizeof(T)); // don't call any destructors

		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
private:
	T* m_Data = nullptr;

	size_t m_Size = 0;     // actual amount of elements
	size_t m_Capacity = 0; // capacity for elements
};