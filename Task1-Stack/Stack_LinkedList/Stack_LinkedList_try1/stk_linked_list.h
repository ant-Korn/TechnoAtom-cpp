#ifndef STK_LINKED_LIST_H
#define STK_LINKED_LIST_H

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)

#include <iostream>
#include <cassert>
#include <iomanip> 

template<class T>
class Stack{
public:
	void dump() const;
	Stack();
	Stack(const Stack &);
	Stack & operator=(const Stack &);
	~Stack();
	bool empty() const;
	size_t size() const;
	void push(const T&);
	void pop();
	T& top();
	bool ok() const;
	//size_t max_size() const;
private:
	struct Node{
		T data_;
		Node * link_;
		Node(const T&, Node * = nullptr);
		~Node();
	} * top_;
	size_t num_items_;
};


//--------------------------------------------
//! Конструктор узла стека
template<class T>
Stack<T>::Node::Node(const T& new_data, Node * next_node = nullptr) : data_(new_data), link_(next_node) {}

//! Деструктор узла стека
template<class T>
Stack<T>::Node::~Node(){
	//std::cout << "Delete " << data_ << std::endl;
	link_ = nullptr;
}

//--------------------------------------------
//! Вывод полной информации о стеке
template<class T>
void Stack<T>::dump() const{
	std::cout << std::setfill('-') << std::setw(50) << "" << std::setfill(' ') << std::endl;
	std::cout << "   Stack:\n\tnum. of items:" << std::setw(11) << num_items_ << "\n\ttop:" << std::setw(21);
	if (empty()){
		std::cout << "nullptr" << std::endl;
	}
	else std::cout << std::hex << top_ << std::dec << " value: " << top_->data_ << std::endl;
	std::cout << "    All nodes:" << std::endl;
	Node * node_iter = top_;
	size_t i = 0;
	while (node_iter != nullptr){
		std::cout << "\t[" << i << "] " << std::hex << node_iter << " link to: " << std::setw(8);
		if (node_iter->link_ == nullptr)
			std::cout << "nullptr";
		else std::cout << node_iter->link_;
		std::cout << std::dec << " value: " << node_iter->data_ << std::endl;
		node_iter = node_iter->link_;
		++i;
	}
	std::cout << std::setfill('-') << std::setw(50) << "" << std::setfill(' ') << std::endl;
}

//! Конструктор стека
template<class T>
Stack<T>::Stack() : top_(nullptr), num_items_(0) {}

//! Конструктор копирования стека
template<class T>
Stack<T>::Stack(const Stack & other_stack) : num_items_(other_stack.size()), top_(nullptr){
	Node * node_iter = other_stack.top_, * tmp_top;    
	if (node_iter != nullptr){
		top_ = new Node(node_iter->data_);
		tmp_top = top_;
		node_iter = node_iter->link_;
	}
	while (node_iter != nullptr){
		tmp_top->link = new Node(node_iter->data_);
		node_iter = node_iter->link_;
		tmp_top = tmp_top->link;
	}
}

//! Операция присваивания
template<class T>
Stack<T> & Stack<T>::operator=(const Stack & other_stack){
	if (this != &other_stack){
		Node * node_iter = top_, * next_node;
		num_items_ = other_stack.size();  
		while (node_iter != nullptr){
			next_node = node_iter->link_;
			delete node_iter;
			node_iter = next_node;
		}
		node_iter = other_stack.top_;
		if (node_iter != nullptr){
			top_ = new Node(node_iter->data_);
			next_node = top_;
			node_iter = node_iter->link_;
		}
		while (node_iter != nullptr){
			next_node->link = new Node(node_iter->data_);
			node_iter = node_iter->link_;
			next_node = next_node->link;
		}
	}
	return *this;
}

//! Деструктор стека
template<class T>
Stack<T>::~Stack(){
	Node * node_iter = top_, * next_node;
	num_items_ = 0;
	while (node_iter != nullptr){
		next_node = node_iter->link_;
		delete node_iter;
		node_iter = next_node;
	}
}

/*
//! Максимальное количество узлов стека
template<class T>
size_t Stack<T>::max_size() const{
	std::allocator<Node> alloc;
	return alloc.max_size();
}
*/

//! Добавление элемента
template<class T>
void Stack<T>::push(const T& element){
	try{
		Node * new_top = new Node(element, top_);
		top_ = new_top;
		++num_items_;
	}
	catch (std::bad_alloc &e){ // Возникает при переполнении кучи, для 32-битного процесса 2GB
		std::cerr << "bad_alloc caught: " << e.what() << std::endl;
		abort();
	}
}

//! Проверка на пустоту стека
template<class T>
bool Stack<T>::empty() const{
	return top_ == nullptr;
}

//! Размер стека
template<class T>
size_t Stack<T>::size() const{
	try{
		if (ok())
			return num_items_;
		else throw std::length_error("Error: Length of stack doesnt match for size variable!");
	}
	catch (std::length_error &e){
		std::cerr << e.what() << std::endl;
		dump();
		abort();
	}
}

//! Удаление узла с вершины стека
template<class T>
void Stack<T>::pop(){  // or: T Stack<T>::pop(){
	try{
		if (empty()){			 
			throw std::range_error("Error: Try to pop element from empty stack!");
		}
		//T ret_element = top_->data_; // Возвращаемое значение (информация с вершины стека)
		Node * prev_top = top_;      // Указатель на удаляемый узел вершины стека
		top_ = top_->link_;          // Смещение вершины стека на его следующий узел
		prev_top->link_ = nullptr;   // Зануление указателя на следующий за удаляемым узлом (для того, чтобы не вызвались последовательно деструкторы узлов всего стека)
		delete prev_top;
		--num_items_;
		//return ret_element;
	}
	catch (std::range_error &e){
		std::cerr << e.what() << std::endl;
		dump();
		abort();
	}
}

//! Доступ к верхнему элементу стека
template<class T>
T& Stack<T>::top(){
	try{
		if (empty()){
			throw std::range_error("Error: Try to return top element from empty stack!");
		}
		return top_->data_;
	}
	catch (std::range_error &e){
		std::cerr << e.what() << std::endl;
		dump();
		abort();
	}
}

//! Проверка совпадения хранящегося размера стека и реального
template<class T>
bool Stack<T>::ok() const{
	Node * node_iter = top_;
	size_t i = 0;
	while (node_iter != nullptr){
		node_iter = node_iter->link_;
		++i;
	}
	return num_items_ == i;
}


#endif