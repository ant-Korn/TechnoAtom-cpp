//!@file stk_linked_list.h
//!\brief Заголовочный файл с описанием класса стека на основе связанного списка.
//!\brief Стек - это структура данных с методом доступа к элементам LIFO (last in — first out). В данном случаеего реализация представлена в виде связанного списка. Класс стека хранит в себе информацию
//! о количестве элементов (элементы могут быть произвольного типа, но одного, передаваемого шаблону), хранимых в данный момент в нём, а также указатель на верхний (последний занесённый) узел в нём. 
//! Узел же хранит информацию об одном из переданных элементов, а также указатель на следующий элемент в порядке: (последний переданный)->...->(первый переданный).
//! 
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

#ifndef STK_LINKED_LIST_H
#define STK_LINKED_LIST_H

#include <iostream>
#include <iomanip>

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) //!< Макрос для вывода участка кода, в результате выполнения которого произошла утечка памяти средствами CRT.

#ifdef _MSC_VER
	#define FUNKNAME __FUNCTION__ //!< Макрос для вывода имени текущей выполняемой функции, при компиляции в компиляторе MVS.
#else
	#define FUNKNAME __func__ //!< Макрос для вывода имени текущей выполняемой функции, при компиляции в компиляторах, отличных от MVS.
#endif //_MSC_VER

//!Макрос проверки на пустоту стека. Если он не пуст, то кидается исключение с именем функции, в которой он был подставлен.
#define ASSERT_NOT_EMPTY() \
	if (empty()){     \
		dump();     \
		throw std::length_error("Error: Try to work with empty stack in: "FUNKNAME); \
	}	

//! \namespace stk_as_list В данном пространстве имён представлена реализация класса стека на основе связанного списка.
namespace stk_as_list{
	//!Класс стека, реализованный на основе связного списка.
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
		//! Структура узла стека.
		//! \briefКаждый из узлов хранит занесёную в стек информацию, а также указатель на следующий узел.
		struct Node{
			T data_;	  //!< Хранит элемент, переданый в стек.
			Node * next_; //!< Указатель на следующий узел стека. Если данный узел последний, то равна nullptr.
			Node(const T&, Node * = nullptr);
			~Node();
		};
		Node * top_;		//!< Хранит указатель на текущий элемент на вершине стека. Если элементов нет, то он равен nullptr.
		size_t num_items_;  //!< Хранит текущее количество узлов в стеке.
	
		void clean();
	};

#include "stk_linked_list_realization.h"

}

#endif //STK_LINKED_LIST_H