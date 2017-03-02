//!@file main_file.cpp
//!Тестирование стеков, описанных в файле stk.h.
//!
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

// Объявления для отслеживания утечек памяти в MVS средствами CRT.
#ifdef _MSC_VER

//! Инициализация отслеживания утечек памяти средствами CRT. 
#define INIT_CRT_MEM_CHECK()\
	_CrtMemState _ms;       \
	_CrtMemCheckpoint(&_ms);

//! Вывод в консоль отчёта об утечках памяти. 
#define CRT_SET_REPORT() {																			\
	std::cout << std::endl;																			\
	const unsigned num_dashes = 50;																	\
	std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;\
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );												\
	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );											\
	_CrtMemDumpAllObjectsSince(&_ms);																\
}

#ifdef _DEBUG
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#else
	#define INIT_CRT_MEM_CHECK() ;
	#define CRT_SET_REPORT() ;
#endif // _MSC_VER


#include <iostream>
#include "stk.h"


//! \namespace stk_test В данном пространстве имён представлены средства тестирования классов StackAsList и StackAsMass.
namespace stk_test{

	//! Макрос проверки условия. Если оно не верно, то бросается исключение.
	#define ASSERT_TRUE( condition ) \
		if (! (condition) )			 \
			throw std::exception("Testing of " FUNKNAME " false in "#condition);

	//! Макрос для сообщения о удачном завершении теста.
	#define TEST_PASSED()	\
		std::cout << FUNKNAME " is successfully complete!" << std::endl << std::endl;
	#define TEST_FAILED()	\
		std::cout << "When trying to " FUNKNAME " failed!" << std::endl << std::endl;


	//!Тестирование на верное добавление одного элемента в стек переменных int.
	template <template <class T> class StackType>
	void TestPush(){
		StackType<int> s_i;													
		try{																								
			s_i.push(3802);											
			ASSERT_TRUE(s_i.top() == 0xEDA);
			s_i.pop();
			ASSERT_TRUE(s_i.size() == 0);
			ASSERT_TRUE(s_i.empty());
			TEST_PASSED();
		}																
		catch(std::exception & ex){	  
			std::cout << ex.what() << std::endl;
			s_i.dump();
			TEST_FAILED();
		} 
	}

	//!Тестирование на удаление узла из пустого стека.
	template <template <class T> class StackType>
	void TestPop(){
		StackType<int> s_i;
		const int value = 1;
		try{
			s_i.push(value);
			s_i.pop();
			ASSERT_TRUE(s_i.size() == 0);
			s_i.pop();
			TEST_FAILED();
			s_i.dump();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			TEST_PASSED();
		}
	}

	//!Тестирование на получение ссылки на верхний элемент пустого стека.
	template <template <class T> class StackType>
	void TestTop(){
		StackType<int> s_i;
		const int value = 1;
		try{
			s_i.push(value);
			ASSERT_TRUE(s_i.top() == 1);
			s_i.pop();
			ASSERT_TRUE(s_i.size() == 0);
			int var = s_i.top();
			std::cout << "Top variable = " << var << std::endl;
			TEST_FAILED();
			s_i.dump();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			TEST_PASSED();
		}
	}

	//!Тестирование на правильную работу конструктора копирования.
	template <template <class T> class StackType>
	void TestCopyConstructor(){
		auto num_of_elements = 5;
		StackType<int> s_i1;
		try{
			for(auto i=0;i<num_of_elements;++i){
				s_i1.push(i);
			}
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i1.dump();
		}
		StackType<int> s_i2(s_i1);
		try{
			ASSERT_TRUE(s_i1.size() == s_i2.size());
			while(s_i2.size()){
				ASSERT_TRUE(s_i1.top() == s_i2.top());   
				ASSERT_TRUE(&s_i1.top() != &s_i2.top()); 
				s_i1.pop();
				s_i2.pop();
			}
			ASSERT_TRUE(s_i1.empty());
			TEST_PASSED();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i1.dump();
			s_i2.dump();
			TEST_FAILED();
		}
	}

	//!Тестирование на правильную работу операции присваивания.
	template <template <class T> class StackType>
	void TestAssignmentOperator(){
		auto num_of_elements1 = 5;
		auto num_of_elements2 = 3;
		StackType<int> s_i1;
		try{
			for(auto i=0;i<num_of_elements1;++i){
				s_i1.push(i);
			}
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i1.dump();
		}
		StackType<int> s_i2;
		try{
			for(auto i=0;i<num_of_elements2;++i){
				s_i2.push(i);
			}
			s_i2 = s_i1;                               
			ASSERT_TRUE(s_i1.size() == s_i2.size());
			while(s_i2.size()){
				ASSERT_TRUE(s_i1.top() == s_i2.top());  
				ASSERT_TRUE(&s_i1.top() != &s_i2.top()); 
				s_i1.pop();
				s_i2.pop();
			}
			ASSERT_TRUE(s_i1.empty());
			TEST_PASSED();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i1.dump();
			s_i2.dump();
			TEST_FAILED();
		}
	}

	//!Тестирование проверки стека на пустоту.
	template <template <class T> class StackType>
	void TestEmpty(){
		StackType<int> s_i;
		const int push_num = 1;
		try{
			ASSERT_TRUE(s_i.empty());
			s_i.push(push_num);
			ASSERT_TRUE(!s_i.empty());
			TEST_PASSED();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i.dump();
			TEST_FAILED();
		}
	}

	//!Тестирование получения размера стека.
	template <template <class T> class StackType>
	void TestSize(){
		StackType<int> s_i;
		const int num_of_elements = 3;
		try{
			ASSERT_TRUE(s_i.size()==0);
			for(auto i=0; i<num_of_elements; ++i){
				s_i.push(i);
			}
			ASSERT_TRUE(s_i.size()==num_of_elements);
			TEST_PASSED();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i.dump();
			TEST_FAILED();
		}
	}

	//!Тестирование обмена содержимым стеков.
	template <template <class T> class StackType>
	void TestSwap(){
		StackType<int> s_i1, s_i2;
		const int num_of_elements1 = 3, num_of_elements2 = 5;
		try{
			for(auto i=0; i<num_of_elements1; ++i){
				s_i1.push(i);
			}
			for(auto i=0; i<num_of_elements2; ++i){
				s_i2.push(i);
			}

			s_i1.swap(s_i2);

			for(auto i=(num_of_elements2-1); i>=0; --i){
				ASSERT_TRUE(s_i1.top()==i);
				s_i1.pop();
			}
			ASSERT_TRUE(s_i1.empty());

			for(auto i=(num_of_elements1-1); i>=0; --i){
				ASSERT_TRUE(s_i2.top()==i);
				s_i2.pop();
			}
			ASSERT_TRUE(s_i2.empty());

			TEST_PASSED();
		}
		catch(std::exception & ex){
			std::cout << ex.what() << std::endl;
			s_i1.dump();
			s_i2.dump();
			TEST_FAILED();
		}
	}

}


int main(){
	//! Инициализация отслеживания утечек памяти.
	INIT_CRT_MEM_CHECK();

	/*! Проведение тестов для стеков на основе списка и на основе массивов:
	    TestPush, TestPop, TestTop, TestCopyConstructor, TestAssignmentOperator, TestEmpty, TestSize , TestSwap.*/
	void (* tests[])() = {stk_test::TestPush<stk::StackAsList>, stk_test::TestPop<stk::StackAsList>,	\
		stk_test::TestTop<stk::StackAsList>, stk_test::TestCopyConstructor<stk::StackAsList>, 			\
		stk_test::TestAssignmentOperator<stk::StackAsList>, stk_test::TestEmpty<stk::StackAsList>,		\
		stk_test::TestSize<stk::StackAsList>, stk_test::TestSwap<stk::StackAsList>,						\
																										\
		stk_test::TestPush<stk::StackAsMass>, stk_test::TestPop<stk::StackAsMass>,						\
		stk_test::TestTop<stk::StackAsMass>, stk_test::TestCopyConstructor<stk::StackAsMass>, 			\
		stk_test::TestAssignmentOperator<stk::StackAsMass>, stk_test::TestEmpty<stk::StackAsMass>,		\
		stk_test::TestSize<stk::StackAsMass>, stk_test::TestSwap<stk::StackAsMass>,						\
	};

	for(auto test: tests){
		(*test)();
	}

	//! Вывод в консоль отчёта об утечках памяти.
    CRT_SET_REPORT();

	system("PAUSE");
	return 0;
}
