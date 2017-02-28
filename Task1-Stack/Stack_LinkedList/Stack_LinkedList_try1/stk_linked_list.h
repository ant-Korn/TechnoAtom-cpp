//!@file stk_linked_list.h
//!\brief ������������ ���� � ��������� ������ ����� �� ������ ���������� ������.
//!\brief ���� - ��� ��������� ������ � ������� ������� � ��������� LIFO (last in � first out). � ������ ��������� ���������� ������������ � ���� ���������� ������. ����� ����� ������ � ���� ����������
//! � ���������� ��������� (�������� ����� ���� ������������� ����, �� ������, ������������� �������), �������� � ������ ������ � ��, � ����� ��������� �� ������� (��������� ���������) ���� � ��. 
//! ���� �� ������ ���������� �� ����� �� ���������� ���������, � ����� ��������� �� ��������� ������� � �������: (��������� ����������)->...->(������ ����������).
//! 
//!@author �������� �����, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_H
#define STK_LINKED_LIST_H

#include <iostream>
#include <iomanip>

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) //!< ������ ��� ������ ������� ����, � ���������� ���������� �������� ��������� ������ ������ ���������� CRT.

#ifdef _MSC_VER
	#define FUNKNAME __FUNCTION__ //!< ������ ��� ������ ����� ������� ����������� �������, ��� ���������� � ����������� MVS.
#else
	#define FUNKNAME __func__ //!< ������ ��� ������ ����� ������� ����������� �������, ��� ���������� � ������������, �������� �� MVS.
#endif //_MSC_VER

//!������ �������� �� ������� �����. ���� �� �� ����, �� �������� ���������� � ������ �������, � ������� �� ��� ����������.
#define ASSERT_NOT_EMPTY() \
	if (empty()){     \
		dump();     \
		throw std::length_error("Error: Try to work with empty stack in: "FUNKNAME); \
	}	

//! \namespace stk_as_list � ������ ������������ ��� ������������ ���������� ������ ����� �� ������ ���������� ������.
namespace stk_as_list{
	//!����� �����, ������������� �� ������ �������� ������.
	template<class T>
	class Stack{
	public:
		void dump() const;
		Stack();
		Stack(const Stack & other_stack);
		Stack & operator=(Stack);
		~Stack();
		bool empty() const;
		size_t size() const;
		void push(const T&);
		void pop();
		T& top();
		void swap(Stack &);
	private:
		//! ��������� ���� �����.
		//! \brief������ �� ����� ������ �������� � ���� ����������, � ����� ��������� �� ��������� ����.
		struct Node{
			T data_;	  //!< ������ �������, ��������� � ����.
			Node * next_; //!< ��������� �� ��������� ���� �����. ���� ������ ���� ���������, �� ����� nullptr.
			Node(const T&, Node * = nullptr);
			~Node();
		};
		Node * top_;		//!< ������ ��������� �� ������� ������� �� ������� �����. ���� ��������� ���, �� �� ����� nullptr.
		size_t num_items_;  //!< ������ ������� ���������� ����� � �����.
	
		void clean();
	};

#include "stk_linked_list_realization.h"

}

#endif //STK_LINKED_LIST_H