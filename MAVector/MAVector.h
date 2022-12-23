#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <string_view>
using namespace std;


template<class T>
class MAVector {
private:
	int m_size = 0;
	int m_capacity = 0;
	T* Data = nullptr;
private:
	void destroyAll() {
		for (size_t i = 0; i < size(); i++)
			Data[i].~T();
	}
public:
	using iterator = T*;
	MAVector() {
		reserve(2);
	}
	~MAVector() {
		clear();
		free(Data);
	}
	MAVector(T* t, int n) {
		reserve(n);
		for (size_t i = 0; i < n; i++)
			this->push_back(t[i]);
	}
	MAVector(int n) {
		reserve(n);
	}
	MAVector(const MAVector& vec) {
		reserve(vec.size());
		for (size_t i = 0; i < vec.size(); i++)
			this->push_back(vec.Data[i]);
	}

	MAVector& operator=(const MAVector& vec) {
		if (this->Data == vec.Data)
			return *this;

		clear();
		reserve(vec.size());
		for (size_t i = 0; i < vec.size(); i++)
			this->push_back(vec.Data[i]);


	}
	MAVector& operator=(MAVector&& vec) {
		if (this->Data == vec.Data)
			return *this;

		destroyAll();
		free(Data);
		Data = move(vec.Data);
		vec.Data = nullptr;
		m_size = vec.m_size;
		m_capacity = vec.m_capacity;
		vec.m_capacity = 0;
		vec.m_size = 0;
		return *this;
	}

	void resize(int new_size) {
		if (new_size < m_size) {
			for (size_t i = new_size; i < size(); i++)
				Data[i].~T();
			m_size = new_size;
		}
		else if (new_size > m_capacity) {
			T* newBlock = (T*)malloc((new_size) * sizeof(T));
			for (size_t i = 0; i < size(); i++)
				new(&newBlock[i])  T(move(Data[i]));

			for (size_t i = size(); i < new_size; i++)
				new(&newBlock[i])  T();

			destroyAll();
			if (Data != nullptr)
				free(Data);

			Data = move(newBlock);
			newBlock = nullptr;
			m_capacity = new_size;
			m_size = new_size;
		}
		else if (new_size < m_capacity) {
			for (size_t i = size(); i < new_size; i++)
				new(&Data[i])  T();
			
			m_size = new_size;
		}
	}
	void reserve(int new_capacity) {
		if (m_capacity < new_capacity) {
			T* newBlock = (T*)malloc(new_capacity * sizeof(T));
			for (size_t i = 0; i < m_size; i++)
				new(&newBlock[i])  T(move(Data[i]));

			destroyAll();
			if (Data != nullptr)
				free(Data);

			Data = move(newBlock);
			newBlock = nullptr;
			m_capacity = new_capacity;
		}
	}

	void push_back(const T& val) {
		if (m_size >= m_capacity)
			reserve(m_capacity * 2);
		new(&Data[m_size++]) T(val);
	}

	int size()  const { return m_size; }
	int capacity() const { return m_capacity; }
	bool empty() const { return m_size == 0; }
	T& operator[](int indx) {
		if (indx < 0 || indx >= m_size)
			throw std::out_of_range("Out of range");
		
		else
			return Data[indx];
	}
	T pop_back() {
		if (empty()) {
			throw std::out_of_range("Empty vector!!");
		}
		T temp = move(Data[m_size - 1]);
		Data[m_size - 1].~T();
		m_size--;
		return temp;
	}
	void clear() {
		destroyAll();
		m_size = 0;
	}

	void insert(iterator t1, const T& val) {
		if (t1 > this->end() || t1 < this->begin()) {
			throw std::out_of_range("Out of range");
		}

		int new_size = m_size + 1;
		T* newBlock = (T*)malloc((new_size) * sizeof(T));
		int flag = 0;
		for (size_t i = 0; i < new_size; i++) {
			if ((Data + i) == t1) {
				new(&newBlock[i++]) T(val);
				flag++;
				new(&newBlock[i]) T(Data[i - flag]);

			}
			new(&newBlock[i])  T(move(Data[i - flag]));
		}

		destroyAll();
		free(Data);
		Data = move(newBlock);
		newBlock = nullptr;
		m_capacity = new_size;
		m_size = new_size;


	}

	void erase(iterator t1, iterator t2) {
		if (t1 > this->end() || t1 < this->begin() || t2 > this->end() || t2 < this->begin()) {
			throw std::out_of_range("Out of range");
		}

		destroy(t1, t2);
		auto dis = std::distance(t1, t2);
		for (auto itr = t1; itr != (this->end() - dis); itr++) {
			*(itr) = std::move(*(itr + dis));

		}
		m_size -= dis;
		//destroy(t1 + count, this->end())
	}
	void erase(iterator t1) {
		if (t1 > this->end() || t1 < this->begin()) {
			throw std::out_of_range("Out of range");
		}

		std::destroy(t1, t1 + 1);
		auto dis = 1;
		for (auto itr = t1; itr != (this->end() - dis); itr++) {
			*(itr) = std::move(*(itr + dis));

		}
		m_size -= dis;
	}


	//erase by index & times
	/*void erase(int indx, int times) {
		for (size_t i = 0; i < times; i++)
			Data[indx + i].~T();
	}*/
	iterator begin() { return Data; }
	iterator end() { return Data + m_size; }


	bool operator< (const MAVector<T>& vec) {
		return (lexicographical_compare(this->begin(), this->end(), vec.begin(), vec.end()));
	}
	bool operator> (const MAVector<T>& vec) {
		return (vec < *this);
	}
	bool operator==(const MAVector<T>& vec) {
		return (this->size() == vec.size() && std::equal(this->begin(), this->end(), vec.end()));
	}

	friend ostream& operator<<(ostream& out, const MAVector<T>& vec) {
		for (int i = 0; i < vec.size(); i++)
			out << vec.Data[i] << "\n";

		return out;
	}
};