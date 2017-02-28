//!@file stk_linked_list_realization.h
//!\brief ���������� ������ ����� �� ������ ���������� ������ � ��������� �����.
//! 
//!@author �������� �����, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_REALIZATION_H
#define STK_LINKED_LIST_REALIZATION_H

	/*! ����������� ���� �����.
	\param[in] new_data �������� ����� ����������.
	\param[in] next_node ��������� �� ��������� ����.
	*/
	template<class T>
	Stack<T>::Node::Node(const T& new_data, Node * next_node = nullptr) : data_(new_data), next_(next_node) {}


	/*! ���������� ���� �����
	*/
	template<class T>
	Stack<T>::Node::~Node(){
		//std::cout << "delete " << data_ << std::endl;
		next_ = nullptr;
	}

//--------------------------------------------

	/*! ����� ������ ���������� � �����.
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


	/*! ����������� ����� �� ���������.
	*/
	template<class T>
	Stack<T>::Stack() : top_(nullptr), num_items_(0) {}


	/*!����� �������� �����. �������� � ���� ��������� ���������� ����� � �������� ���� ����� � ������������� ������. ������������ � ������� ~Stack() � Stack & operator=(const Stack &) ������� ������.
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


	/*!����� ������ ���������� ������
	\param[in] other_stack ����, ����������� � ������� ���������� ����������.
	*/
	template<class T>
	void Stack<T>::swap(Stack & other_stack){
		std::swap(num_items_, other_stack.num_items_);
		std::swap(top_, other_stack.top_);
	}


	/*! ����������� ����������� �����.
	\param[in] other_stack ����, ��� ���������� �� �������� ���������� ��������� � �����������.
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


	/*! �������� ������������.
	\param[in] other_stack ����, ��� ���������� �� �������� ���������� ��������� � �������.
	\return ������ �� ������� ���� � ����������� �����������.
	*/
	template<class T>
	Stack<T> & Stack<T>::operator=(Stack other_stack){
		swap(other_stack);
		return *this;
	}


	/*! ���������� �����.
	*/
	template<class T>
	Stack<T>::~Stack(){
		clean();
	}


	/*! ���������� ��������.
	\param[in] element ������ �� �������, ���������� �� �������� ���������� ������� � �����.
	*/
	template<class T>
	void Stack<T>::push(const T& element){
		Node * new_top = new Node(element, top_);
		top_ = new_top;
		++num_items_;
	}


	/*! �������� �� ������� �����.
	\return ���������� ����������, ������� ������� � ���, �������� �� ���� ������ ��� ���.
	*/
	template<class T>
	bool Stack<T>::empty() const{
		return top_ == nullptr;
	}


	/*! ����� ����������� ������� �����.
	\return ������ �����.
	*/
	template<class T>
	size_t Stack<T>::size() const{
		return num_items_;
	}


	/*! �������� ���� � ������� �����.
	\throw length_error � ������, ���� ���� �������� ������.
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


	/*! ������ � �������� �������� �����.
	\return ������ �� �������� ���������� �� ������� �����.
	\throw length_error � ������, ���� ���� �������� ������.
	*/
	template<class T>
	T& Stack<T>::top(){
		ASSERT_NOT_EMPTY();
		return top_->data_;
	}
	;
#endif //STK_LINKED_LIST_REALIZATION_H