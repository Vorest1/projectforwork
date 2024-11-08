#pragma once
#include <iostream>
#include "Sequence.h"
#include "DynamicArray.h"
#include <stdexcept>

using namespace std;

template<typename T>
class Shared_Ptr {
private:
	T* _ptr;
	size_t* _count;
public:
	//конструктор
	explicit Shared_Ptr(T* new_ptr = nullptr) : _ptr(new_ptr), _count(new size_t(1)) {}

	//конструктор копирования
	Shared_Ptr(const Shared_Ptr& other) : _ptr(other._ptr), _count(other._count) {
		if (_count) {
			(*_count)++;
		}
	}

	//деструктор
	~Shared_Ptr() {
		if (_count) {
			(*_count)--;
			if (*_count <= 0) {
				delete _ptr;
				delete _count;
			}
		}
	}


	//перегруз операторов
	Shared_Ptr& operator=(const Shared_Ptr& other) {
		if (this != &other) {
			if (_count && (*_count) - 1 <= 0) {
				delete _ptr;
				delete _count;
			}
			else if (_count) {
				delete _ptr;
				--(*_count);
			}
			_ptr = other._ptr;
			_count = other._count;
			if (_count) {
				(*_count)++;
			}
		}
		return *this;
	}

	Shared_Ptr<T>& operator=(T* other) {
		if (_count) {
			(*_count)--;
			if (*_count <= 0) {
				delete _ptr;
				delete _count;
			}
		}
		this->_ptr = other;
		this->_count = new size_t(1);
		return *this;
	}

	T& operator*() const noexcept {
		if (_ptr == nullptr) {
			throw runtime_error("ERROR: Dereferencing a null pointer");
		}
		return *_ptr;
	}

	T* operator->() const noexcept { return _ptr; }

	T& operator[](int Index) {
		if (Index < 0) {
			throw std::out_of_range("Out of range");
		}
		return *_ptr[Index];
	}

	//методы
	T& Get() const noexcept { return *_ptr; }
	size_t Get_count() const noexcept { return *_count; }
	void Swap(Shared_Ptr<T>& other) {
		T* temp = this->_ptr;
		size_t* temp_count = this->_count;
		this->_ptr = other._ptr;
		other._ptr = temp;
		this->_count = other._count;
		other._count = temp_count;
	}

	void Del() {
		if (*_count && --(*_count) <= 0) {
			delete _ptr;
			delete _count;
		}
		this->_ptr = nullptr;
		this->_count = nullptr;
	}

	bool Uniq() {
		return *this->_count == 1;
	}
};

template<typename T>
class Uniqe_Ptr {
private:
	T* _ptr;
public:
	//конструктор
	Uniqe_Ptr() noexcept : _ptr(nullptr) {}
	Uniqe_Ptr(T* new_ptr) noexcept : _ptr(new_ptr) {}

	Uniqe_Ptr(Uniqe_Ptr<T>&& other) {
		this->_ptr = other._ptr;
		other._ptr = nullptr;
	}

	Uniqe_Ptr(Uniqe_Ptr<T>& other) {
		this->_ptr = other._ptr;
		other._ptr = nullptr;
	}

	Uniqe_Ptr(const Uniqe_Ptr&) = delete;
	Uniqe_Ptr& operator=(const Uniqe_Ptr&) = delete;

	//деструктор
	~Uniqe_Ptr() noexcept { Del(); }

	//перегруз операторов
	T& operator*() const noexcept {
		if (_ptr == nullptr) {
			throw runtime_error("ERROR: Dereferencing a null pointer");
		}
		return *_ptr;
	}

	T* operator->() const noexcept { return _ptr; }

	Uniqe_Ptr& operator=(Uniqe_Ptr&& other) noexcept {
		if (this != &other) {
			Del();
			_ptr = other.Release();
		}
		return *this;
	}

	Uniqe_Ptr<T>& operator=(T* other) {
		delete _ptr;
		this->_ptr = other;
		return *this;
	}

	bool operator==(const Uniqe_Ptr& other) const noexcept {
		if (_ptr != nullptr && other._ptr != nullptr) {
			return *_ptr == *other._ptr;
		}
		else {
			return _ptr == other._ptr;
		}
	}

	bool operator!=(const Uniqe_Ptr& other) const noexcept {
		return !(*this == other);
	}

	//методы
	void Del() noexcept { delete _ptr;  _ptr = nullptr; }

	void Swap(Uniqe_Ptr& other) noexcept {
		T* temp = _ptr;
		_ptr = other._ptr;
		other._ptr = temp;
	}

	T* Release() noexcept {
		T* n_ptr = _ptr;
		_ptr = nullptr;
		return n_ptr;
	}

	T* Get() const noexcept { return _ptr; }
};


