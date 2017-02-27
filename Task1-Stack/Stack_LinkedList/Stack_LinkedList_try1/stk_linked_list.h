//!@file stk_linked_list.h
//!\brief ������������ ���� � ��������� �������.
//!\brief ���������� ������ ����� �� ������ ���������� ������.
//!\brief ���� - ��� ��������� ������ � ������� ������� � ��������� LIFO (last in � first out). � ������ ��������� ���������� ������������ � ���� ���������� ������. ����� ����� ������ � ���� ����������
//! � ���������� ��������� (�������� ����� ���� ������������� ����, �� ������, ������������� �������), �������� � ������ ������ � ��, � ����� ��������� �� ������� (��������� ���������) ���� � ��. 
//! ���� �� ������ ���������� �� ����� �� ���������� ���������, � ����� ��������� �� ��������� ������� � �������: (��������� ����������)->...->(������ ����������).
//! 
//!@author �������� �����, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_H
#define STK_LINKED_LIST_H

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) //!< ������ ��� ������ ������� ����, � ���������� ���������� �������� ��������� ������ ������ ���������� CRT.

#include <iostream>
#include <iomanip> 

#ifdef _MSC_VER
	#define FUNKNAME __FUNCTION__ //!< ������ ��� ������ ����� ������� ����������� �������, ��� ���������� � ����������� MVS.
#else
	#define FUNKNAME __func__ //!< ������ ��� ������ ����� ������� ����������� �������, ��� ���������� � ������������, �������� �� MVS.
#endif //_MSC_VER

//!������ ����������� �����. ���� �� �� �������� �����������, �� �������� ���������� � ������ �������, � ������� �� ��� ����������.
#define ASSERT_OK() \
	if (!ok()){     \
		dump();     \
		throw std::length_error("Error: Length of stack doesnt match for size variable in: "FUNKNAME); \
	}		
//!������ �������� �� ������� �����. ���� �� �� ����, �� �������� ���������� � ������ �������, � ������� �� ��� ����������.
#define ASSERT_EMPTY() \
	if (empty()){     \
		dump();     \
		throw std::length_error("Error: Try to work with empty stack in: "FUNKNAME); \
	}	

//!����� �����, ������������� �� ������ �������� ������.
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
	//! ��������� ���� �����.
	//! \brief������ �� ����� ������ �������� � ���� ����������, � ����� ��������� �� ��������� ����.
	struct Node{
		T data_; //!< ������ �������, ��������� � ����.
		Node * link_; //!< ��������� �� ��������� ���� �����. ���� ������ ���� ���������, �� ����� nullptr.
		Node(const T&, Node * = nullptr);
		~Node();
	} * top_; //!< ������ ��������� �� ������� ������� �� ������� �����. ���� ��������� ���, �� �� ����� nullptr.
	size_t num_items_; //!< ������ ������� ���������� ����� � �����.
	
	void clean_obj(); 
};


//--------------------------------------------
/*! ����������� ���� �����.
\param[in] new_data �������� ����� ����������.
\param[in] next_node ��������� �� ��������� ����.
*/
template<class T>
Stack<T>::Node::Node(const T& new_data, Node * next_node = nullptr) : data_(new_data), link_(next_node) {}

/*! ���������� ���� �����
*/
template<class T>
Stack<T>::Node::~Node(){
	//std::cout << "delete " << data_ << std::endl;
	link_ = nullptr;
}

//--------------------------------------------
/*! ����� ������ ���������� � �����.
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

/*! ����������� ����� �� ���������.
*/
template<class T>
Stack<T>::Stack() : top_(nullptr), num_items_(0) {}

/*! ����������� ����������� �����.
\param[in] other_stack ����, ��� ���������� �� �������� ���������� ��������� � �����������.
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

/*!����� �������� �����. �������� � ���� ��������� ���������� ����� � �������� ���� ����� � ������������� ������. ������������ � ������� ~Stack() � Stack & operator=(const Stack &) ������� ������.
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

/*! �������� ������������.
\param[in] other_stack ����, ��� ���������� �� �������� ���������� ��������� � �������.
\return ������ �� ������� ���� � ����������� �����������.
*/
template<class T>
Stack<T> & Stack<T>::operator=(const Stack & other_stack){
	if (this != &other_stack){ //!1 ���������, ��������� �� ������������ ������ �� ������ ����.
		clean_obj(); //!2 ������� �������� ����.
		num_items_ = other_stack.size();  //!3 �������� ���������� �� ������� ����� � ��������
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

/*! ���������� �����.
*/
template<class T>
Stack<T>::~Stack(){
	clean_obj();
}

/*! ���������� ��������.
\param[in] element ������ �� �������, ���������� �� �������� ���������� ������� � �����.
\throw std::length_error � ������, ���� �� ������ ����������� �������� ASSERT_OK().
*/
template<class T>
void Stack<T>::push(const T& element){
	ASSERT_OK();
	Node * new_top = new Node(element, top_);
	top_ = new_top;
	++num_items_;
}

/*! �������� �� ������� �����.
\return ���������� ����������, ������� ������� � ���, �������� �� ���� ������ ��� ���.
\throw std::length_error � ������, ���� �� ������ ����������� �������� ASSERT_OK().
*/
template<class T>
bool Stack<T>::empty() const{
	ASSERT_OK();
	return top_ == nullptr;
}

/*! ����� ����������� ������� �����.
\return ������ �����.
\throw std::length_error � ������, ���� �� ������ ����������� �������� ASSERT_OK().
*/
template<class T>
size_t Stack<T>::size() const{
	ASSERT_OK();
	return num_items_;
}

/*! �������� ���� � ������� �����.
\throw std::length_error � ������, ���� ������ �������� �� ������� �������� ASSERT_EMPTY().
*/
template<class T>
void Stack<T>::pop(){
	ASSERT_EMPTY();
	Node * prev_top = top_;      //!1 �������� ���������� ��������� �� ������� ������� ���� (�� ��������� ����).
	top_ = top_->link_;          //!2 �������� ������� ����� �� ��� ��������� ����.
	prev_top->link_ = nullptr;   //!3 ��������� ��������� �� ��������� ���� � ��������� ����.
	delete prev_top;			 //!4 �������� ����������� ���������� ���� ��� ������ ���������� ���������.
	--num_items_;				 //!5 ���������� ���������� ��������� �� �������.
}

/*! ������ � �������� �������� �����.
\return ������ �� �������� ���������� �� ������� �����.
\throw std::length_error � ������, ���� ������ �������� �� ������� �������� ASSERT_EMPTY().
*/
template<class T>
T& Stack<T>::top(){
	ASSERT_EMPTY();
	return top_->data_;
}

/*! �������� ���������� ����������� ������� ����� � ��������� (�����������).
\return ���������� ����������, ������� ������� � ���, �������� �� ���� ����������������.
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