//!@file stk_linked_list.h
//!\brief Заголовочный файл с описанием классов.
//!\brief Реализация класса стека на основе связанного списка.
//!\brief Стек - это структура данных с методом доступа к элементам LIFO (last in — first out). В данном случаеего реализация представлена в виде связанного списка. Класс стека хранит в себе информацию
//! о количестве элементов (элементы могут быть произвольного типа, но одного, передаваемого шаблону), хранимых в данный момент в нём, а также указатель на верхний (последний занесённый) узел в нём. 
//! Узел же хранит информацию об одном из переданных элементов, а также указатель на следующий элемент в порядке: (последний переданный)->...->(первый переданный).
//! 
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_H
#define STK_LINKED_LIST_H

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) //!< Макрос для вывода участка кода, в результате выполнения которого произошла утечка памяти средствами CRT.

#include <iostream>
#include <iomanip> 

#ifdef _MSC_VER
	#define FUNKNAME __FUNCTION__ //!< Макрос для вывода имени текущей выполняемой функции, при компиляции в компиляторе MVS.
#else
	#define FUNKNAME __func__ //!< Макрос для вывода имени текущей выполняемой функции, при компиляции в компиляторах, отличных от MVS.
#endif //_MSC_VER

//!Макрос верификации стека. Если он не проходит верификацию, то кидается исключение с именем функции, в которой он был подставлен.
#define ASSERT_OK() \
	if (!ok()){     \
		dump();     \
		throw std::length_error("Error: Length of stack doesnt match for size variable in: "FUNKNAME); \
	}		
//!Макрос проверки на пустоту стека. Если он не пуст, то кидается исключение с именем функции, в которой он был подставлен.
#define ASSERT_EMPTY() \
	if (empty()){     \
		dump();     \
		throw std::length_error("Error: Try to work with empty stack in: "FUNKNAME); \
	}	

//!Класс стека, реализованный на основе связного списка.
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
	//! Структура узла стека.
	//! \briefКаждый из узлов хранит занесёную в стек информацию, а также указатель на следующий узел.
	struct Node{
		T data_; //!< Хранит элемент, переданый в стек.
		Node * link_; //!< Указатель на следующий узел стека. Если данный узел последний, то равна nullptr.
		Node(const T&, Node * = nullptr);
		~Node();
	} * top_; //!< Хранит указатель на текущий элемент на вершине стека. Если элементов нет, то он равен nullptr.
	size_t num_items_; //!< Хранит текущее количество узлов в стеке.
	
	void clean_obj(); 
};


//--------------------------------------------
/*! Конструктор узла стека.
\param[in] new_data Хранимая узлом информация.
\param[in] next_node Указатель на следующий узел.
*/
template<class T>
Stack<T>::Node::Node(const T& new_data, Node * next_node = nullptr) : data_(new_data), link_(next_node) {}

/*! Деструктор узла стека
*/
template<class T>
Stack<T>::Node::~Node(){
	//std::cout << "delete " << data_ << std::endl;
	link_ = nullptr;
}

//--------------------------------------------
/*! Вывод полной информации о стеке.
*/
template<class T>
void Stack<T>::dump() const{
	std::cout << std::setfill('-') << std::setw(50) << "" << std::setfill(' ') << std::endl;
	std::cout << "   Stack:\n\tnum. of items:" << std::setw(11) << num_items_ << "\n\ttop:" << std::setw(21);
	if (top_==nullptr){
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

/*! Конструктор стека по умолчанию.
*/
template<class T>
Stack<T>::Stack() : top_(nullptr), num_items_(0) {}

/*! Конструктор копирования стека.
\param[in] other_stack Стек, всю информацию из которого необходимо перенести в создаваемый.
*/
template<class T>
Stack<T>::Stack(const Stack & other_stack) : num_items_(other_stack.size()), top_(nullptr){
	Node * node_iter = other_stack.top_, * tmp_top = nullptr;    
	if (node_iter != nullptr){
		top_ = new Node(node_iter->data_);
		tmp_top = top_;
		node_iter = node_iter->link_;
	}
	while (node_iter != nullptr){
		tmp_top->link_ = new Node(node_iter->data_);
		node_iter = node_iter->link_;
		tmp_top = tmp_top->link_;
	}
}

/*!Метод очищения стека. Включает в себя зануление количества узлов и удаление всех узлов с освобождением памяти. Используется в методах ~Stack() и Stack & operator=(const Stack &) данного класса.
*/
template<class T>
void Stack<T>::clean_obj(){
	Node * next_node;
	num_items_ = 0;
	while (top_ != nullptr){
		next_node = top_->link_;
		delete top_;
		top_ = next_node;
	}
}

/*! Операция присваивания.
\param[in] other_stack Стек, всю информацию из которого необходимо перенести в текущий.
\return Ссылку на текущий стек с перенесённой информацией.
*/
template<class T>
Stack<T> & Stack<T>::operator=(const Stack & other_stack){
	if (this != &other_stack){ //!1 Проверяем, указывает ли передаваемая ссылка на данный стек.
		clean_obj(); //!2 Очищаем исходный стек.
		num_items_ = other_stack.size();  //!3 Копируем информацию из другого стека в исходный
		Node * node_iter = other_stack.top_, * next_node = nullptr;
		if (node_iter != nullptr){
			top_ = new Node(node_iter->data_);
			next_node = top_;
			node_iter = node_iter->link_;
		}
		while (node_iter != nullptr){
			next_node->link_ = new Node(node_iter->data_);
			node_iter = node_iter->link_;
			next_node = next_node->link_;
		}
	}
	return *this;
}

/*! Деструктор стека.
*/
template<class T>
Stack<T>::~Stack(){
	clean_obj();
}

/*! Добавление элемента.
\param[in] element Ссылка на элемент, информацию из которого необходимо хранить в стеке.
\throw std::length_error В случае, если не прошла верификация макросом ASSERT_OK().
*/
template<class T>
void Stack<T>::push(const T& element){
	ASSERT_OK();
	Node * new_top = new Node(element, top_);
	top_ = new_top;
	++num_items_;
}

/*! Проверка на пустоту стека.
\return Логическую переменную, которая говорит о том, является ли стек пустым или нет.
\throw std::length_error В случае, если не прошла верификация макросом ASSERT_OK().
*/
template<class T>
bool Stack<T>::empty() const{
	ASSERT_OK();
	return top_ == nullptr;
}

/*! Метод определения размера стека.
\return Размер стека.
\throw std::length_error В случае, если не прошла верификация макросом ASSERT_OK().
*/
template<class T>
size_t Stack<T>::size() const{
	ASSERT_OK();
	return num_items_;
}

/*! Удаление узла с вершины стека.
\throw std::length_error В случае, если прошла проверка на пустоту макросом ASSERT_EMPTY().
*/
template<class T>
void Stack<T>::pop(){
	ASSERT_EMPTY();
	Node * prev_top = top_;      //!1 Создание временного указателя на текущий верхний узел (на удаляемый узел).
	top_ = top_->link_;          //!2 Смещение вершины стека на его следующий узел.
	prev_top->link_ = nullptr;   //!3 Зануление указателя на следующий узел в удаляемом узле.
	delete prev_top;			 //!4 Удаление предыдущего вершинного узла при помощи созданного указателя.
	--num_items_;				 //!5 Уменьшение количества элементов на единицу.
}

/*! Доступ к верхнему элементу стека.
\return Ссылку на хранимую информацию на вершине стека.
\throw std::length_error В случае, если прошла проверка на пустоту макросом ASSERT_EMPTY().
*/
template<class T>
T& Stack<T>::top(){
	ASSERT_EMPTY();
	return top_->data_;
}

/*! Проверка совпадения хранящегося размера стека и реального (верификатор).
\return Логическую переменную, которая говорит о том, является ли стек верифицированным.
*/
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


#endif //STK_LINKED_LIST_H