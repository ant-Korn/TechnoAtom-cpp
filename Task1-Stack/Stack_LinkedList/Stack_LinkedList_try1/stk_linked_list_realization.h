//!@file stk_linked_list_realization.h
//!\brief Реализация класса стека на основе связанного списка в отдельном файле.
//! 
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_REALIZATION_H
#define STK_LINKED_LIST_REALIZATION_H

	/*! Конструктор узла стека.
	\param[in] new_data Хранимая узлом информация.
	\param[in] next_node Указатель на следующий узел.
	*/
	template<class T>
	Stack<T>::Node::Node(const T& new_data, Node * next_node = nullptr) : data_(new_data), next_(next_node) {}


	/*! Деструктор узла стека
	*/
	template<class T>
	Stack<T>::Node::~Node(){
		//std::cout << "delete " << data_ << std::endl;
		next_ = nullptr;
	}

//--------------------------------------------

	/*! Вывод полной информации о стеке.
	*/
	template<class T>
	void Stack<T>::dump() const{
		const unsigned num_dashes = 50, num_chars1 = 11, num_chars2 = 21, num_chars3 = 8;
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
		std::cout << "   Stack:\n\tnum. of items:" << std::setw(num_chars1) << num_items_ << "\n\ttop:" << std::setw(num_chars2);
		if (top_==nullptr){
			std::cout << "nullptr" << std::endl;
		}
		else std::cout << std::hex << top_ << std::dec << " value: " << top_->data_ << std::endl;
		std::cout << "    All nodes:" << std::endl;
		Node * node_iter = top_;
		size_t i = 0;
		while (node_iter != nullptr){
			std::cout << "\t[" << i << "] " << std::hex << node_iter << " link to: " << std::setw(num_chars3);
			if (node_iter->next_ == nullptr)
				std::cout << "nullptr";
			else std::cout << node_iter->next_;
			std::cout << std::dec << " value: " << node_iter->data_ << std::endl;
			node_iter = node_iter->next_;
			++i;
		}
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
	}


	/*! Конструктор стека по умолчанию.
	*/
	template<class T>
	Stack<T>::Stack() : top_(nullptr), num_items_(0) {}


	/*!Метод очищения стека. Включает в себя зануление количества узлов и удаление всех узлов с освобождением памяти. Используется в методах ~Stack() и Stack & operator=(const Stack &) данного класса.
	*/
	template<class T>
	void Stack<T>::clean(){
		Node * next_node;
		num_items_ = 0;
		while (top_ != nullptr){
			next_node = top_->next_;
			delete top_;
			top_ = next_node;
		}
	}


	/*!Метод обмена содержимым стеков
	\param[in] other_stack Стек, информацией с которым необходимо поменяться.
	*/
	template<class T>
	void Stack<T>::swap(Stack & other_stack){
		std::swap(num_items_, other_stack.num_items_);
		std::swap(top_, other_stack.top_);
	}


	/*! Конструктор копирования стека.
	\param[in] other_stack Стек, всю информацию из которого необходимо перенести в создаваемый.
	*/
	template<class T>
	Stack<T>::Stack(const Stack & other_stack) : num_items_(other_stack.num_items_), top_(nullptr){
		Node * node_iter = other_stack.top_, * tmp_top = nullptr;    
		if (node_iter != nullptr){
			top_ = new Node(node_iter->data_);
			tmp_top = top_;
			node_iter = node_iter->next_;
		}
		while (node_iter != nullptr){
			tmp_top->next_ = new Node(node_iter->data_);
			node_iter = node_iter->next_;
			tmp_top = tmp_top->next_;
		}
	}


	/*! Операция присваивания.
	\param[in] other_stack Стек, всю информацию из которого необходимо перенести в текущий.
	\return Ссылку на текущий стек с перенесённой информацией.
	*/
	template<class T>
	Stack<T> & Stack<T>::operator=(Stack other_stack){
		swap(other_stack);
		return *this;
	}


	/*! Деструктор стека.
	*/
	template<class T>
	Stack<T>::~Stack(){
		clean();
	}


	/*! Добавление элемента.
	\param[in] element Ссылка на элемент, информацию из которого необходимо хранить в стеке.
	*/
	template<class T>
	void Stack<T>::push(const T& element){
		Node * new_top = new Node(element, top_);
		top_ = new_top;
		++num_items_;
	}


	/*! Проверка на пустоту стека.
	\return Логическую переменную, которая говорит о том, является ли стек пустым или нет.
	*/
	template<class T>
	bool Stack<T>::empty() const{
		return top_ == nullptr;
	}


	/*! Метод определения размера стека.
	\return Размер стека.
	*/
	template<class T>
	size_t Stack<T>::size() const{
		return num_items_;
	}


	/*! Удаление узла с вершины стека.
	\throw length_error В случае, если стек оказался пустым.
	*/
	template<class T>
	void Stack<T>::pop(){
		ASSERT_NOT_EMPTY();
		Node * prev_top = top_;
		top_ = top_->next_;
		prev_top->next_ = nullptr;
		delete prev_top;
		--num_items_;
	}


	/*! Доступ к верхнему элементу стека.
	\return Ссылку на хранимую информацию на вершине стека.
	\throw length_error В случае, если стек оказался пустым.
	*/
	template<class T>
	T& Stack<T>::top(){
		ASSERT_NOT_EMPTY();
		return top_->data_;
	}
	;
#endif //STK_LINKED_LIST_REALIZATION_H