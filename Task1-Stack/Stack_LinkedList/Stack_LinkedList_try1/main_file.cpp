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


	 //!\brief Тестирование на верное добавление одного элемента в стек.
	 //!
	 //!Given: Пустой стек типа int.
	 //!When: Кладём в стек число 3802, сравниваем число на вершине стека с числом 0xEDA, удаляем из стека один элемент, проверяем стек на пустоту.
	 //!Then: Все действия со стеком и проиходящие проверки успешно завершаются без вызова исключений.
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

	//!\briefТестирование на удаление элемента с вершины стека.
	//!
	//! Given: Стек типа int с одним хранимым значением.
	//! When: Удаляем из стека один элемент, проверяем стек на пустоту, удаляем из стека ещё один элемент.
	//! Then: Проверка на пустоту стека успешно завершается, но при последующем удалении элемента вызывается исключение с сообщением о работе с пустым стеком и выводится его содержимое.
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

	//!\briefТестирование на получение ссылки на верхний элемент.
	//!
	//! Given: Стек типа int с одним хранимым известным значением.
	//! When: Получаем ссылку на верхний элемент и сравниваем его с известным значением, удаляем из стека один элемент, проверяем стек на пустоту, получаем ссылку на следующий верхний элемент
	//! и выводим её содержимое.
	//! Then: Все действия и проверки успешно завершаются, кроме последнего получения ссылки на верхний элемент, при этом вызывается исключение с сообщением о работе с пустым стеком и выводится его содержимое.
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

	//!\briefТестирование на правильную работу конструктора копирования.
	//!
	//! Given: Стек типа int, заполненный известным количеством элементов.
	//! When: Создаём новый стек на основе первого при помощи конструктора копирования, проверяем что размеры данных массивов совпадают, последовательно проверяем, что элементы данных стеков, находящиеся на равной глубине
	//! имеют одинаковые данные, но хранятся по разным адресам в памяти.
	//! Then: Все проверки и действия успешно завершаются без вызова исключений.
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

	//!\briefТестирование на правильную работу операции присваивания.
	//!
	//! Given: Два стека типа int, заполненных разными известными количествомами элементов.
	//! When: Совершаем присваивание второму стеку первого, проверяем что размеры данных массивов совпадают, последовательно проверяем, что элементы данных стеков, находящиеся на равной глубине
	//! имеют одинаковые данные, но хранятся по разным адресам в памяти.
	//! Then: Все проверки и действия успешно завершаются без вызова исключений.
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

	//!\briefТестирование проверки стека на пустоту.
	//!
	//! Given: Пустой стек типа int.
	//! When: Проверяем стек на пустоту, кладём в стек один элемент типа int, проверяем что стек не пустой.
	//! Then: Все проиходящие проверки успешно завершаются без вызова исключений.
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

	//!\briefТестирование получения размера стека.
	//!
	//! Given: Пустой стек типа int, количество элементов для заполнения.
	//! When: Получаем размер стека и сравниваем его с нулём, кладём в стек данное количество элементов типа int, получаем размер стека и сравниваем его с известным количеством элементов.
	//! Then: Все проиходящие проверки успешно завершаются без вызова исключений.
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

	//!\briefТестирование обмена содержимым стеков.
	//!
	//! Given: Два стека типа int, заполненных разными известными количествомами известных элементов.
	//! When: Вызываем метод обмена элементами стеков, проверяем, что размеры стеков взаимно поменялись, а также то, что они взаимно обменялись элементами, находящимися на соответствующей глубине.
	//! Then: Все проверки и действия успешно завершаются без вызова исключений.
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
