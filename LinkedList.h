#pragma once
#include <stddef.h>

template<typename T>
class LinkedList {
public:
	LinkedList();
	LinkedList(const T* data, size_t size);
	LinkedList(const LinkedList& list);

	T GetFirst() const;
	T GetLast() const;
	T Get(size_t index) const;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	size_t GetSize() const;

	void PopFirst();
	void PopLast();

	LinkedList* GetSubList(size_t first_index, size_t second_index) const;

	void Append(const T& elem);
	void Prepend(const T& elem);
	void InsertAt(const T& elem, size_t index);
	LinkedList* Concat(const LinkedList* list) const;

	~LinkedList();
private:
	struct _Node {
		T data;
		_Node* prev;
		_Node* next;
	};
private:
	size_t _size;
	_Node* _first;
	_Node* _last;
};

template<typename T>
LinkedList<T>::LinkedList() : _size(0), _first(nullptr), _last(nullptr) {}

template<typename T>
LinkedList<T>::LinkedList(const T* data, size_t size) : _size(size) {
	if (_size == 0) {
		_first = nullptr;
		_last = nullptr;
		return;
	}
	_first = new _Node{ data[0], nullptr, nullptr };
	_last = _first;
	for (size_t i = 1; i < _size; ++i) {
		_last->next = new _Node{ data[i], _last, nullptr };
		_last = _last->next;
	}
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& list) : _size(list._size) {
	if (_size == 0) {
		_first = nullptr;
		_last = nullptr;
		return;
	}
	_Node* current = list._first;
	_first = new _Node{ current->data , nullptr, nullptr };
	_last = _first;
	current = current->next;
	for (size_t i = 1; i < _size; ++i) {
		_last->next = new _Node{ current->data, _last, nullptr };
		_last = _last->next;
		current = current->next;
	}
}

template<typename T>
T LinkedList<T>::GetFirst() const {
	if (_size == 0) {
		throw std::out_of_range("");
	}
	return _first->data;
}

template<typename T>
size_t LinkedList<T>::GetSize() const {
	return _size;
}

template<typename T>
T LinkedList<T>::GetLast() const {
	if (_size == 0) {
		throw std::out_of_range("");
	}
	return _last->data;
}

template<typename T>
T LinkedList<T>::Get(size_t index) const {
	if (_size <= index) {
		throw std::out_of_range("");
	}
	_Node* current = _first;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template<typename T>
void LinkedList<T>::Append(const T& elem) {
	++_size;
	if (_size == 1) {
		_first = new _Node{ elem, nullptr, nullptr };
		_last = _first;
		return;
	}
	_last->next = new _Node{ elem, _last, nullptr };
	_last = _last->next;
}

template<typename T>
void LinkedList<T>::Prepend(const T& elem) {
	++_size;
	if (_size == 1) {
		_first = new _Node{ elem, nullptr, nullptr };
		_last = _first;
		return;
	}
	_first->prev = new _Node{ elem, nullptr, _first };
	_first = _first->prev;
}

template<typename T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t first_index, size_t second_index) const {
	if (first_index > second_index) {
		throw std::out_of_range("");
	}
	if (second_index >= _size) {
		throw std::out_of_range("");
	}
	LinkedList<T>* result = new LinkedList;
	_Node* current = _first;
	for (size_t i = 0; i < first_index; ++i) {
		current = current->next;
	}
	for (size_t i = first_index; i <= second_index; ++i) {
		result->Append(current->data);
		current = current->next;
	}
	return result;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	_Node* current = _first;
	while (current != nullptr) {
		_Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
void LinkedList<T>::InsertAt(const T& elem, size_t index) {
	if (index >= _size) {
		throw std::out_of_range("");
	}
	++_size;
	_Node* current = _first;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	_Node* new_node = new _Node{ elem, nullptr, nullptr };
	if (current == 0) {
		new_node->next = _first->next;
		_first->prev = new_node;
		_first = new_node;
		return;
	}
	new_node->next = current->next;
	new_node->prev = current;
	current->next = new_node;
	new_node->next->prev = new_node;
}

template<typename T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList* list) const {
	LinkedList<T>* result = new LinkedList(*this);
	_Node* current = list->_first;
	while (current != nullptr) {
		result->Append(current->data);
		current = current->next;
	}
	return result;
}

template<typename T>
T& LinkedList<T>::operator[](size_t index) {
	if (_size <= index) {
		throw std::out_of_range("");
	}
	_Node* current = _first;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template<typename T>
const T& LinkedList<T>::operator[](size_t index) const {
	if (_size <= index) {
		throw std::out_of_range("");
	}
	_Node* current = _first;
	for (size_t i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template<typename T>
void LinkedList<T>::PopFirst() {
	if ((--_size) == 0) {
		delete _first;
		_first = nullptr;
		_last = nullptr;
		return;
	}
	_first = _first->next;
	delete _first->prev;
	_first->prev = nullptr;
}

template<typename T>
void LinkedList<T>::PopLast() {
	if ((--_size) == 0) {
		delete _first;
		_first = nullptr;
		_last = nullptr;
		return;
	}
	_last = _last->prev;
	delete _last->next;
	_last->next = nullptr;
}