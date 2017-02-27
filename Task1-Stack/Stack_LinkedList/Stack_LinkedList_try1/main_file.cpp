//!@file main_file.cpp
//!������������ �����, �������������� � ����� stk_linked_list.h.
//!
//!@author �������� �����, 2017
//!@date 24.02.2017

// ���������� ��� ������������ ������ ������ � MVS ���������� CRT.
#ifdef _MSC_VER

//! ������������� ������������ ������ ������ ���������� CRT. */
#define INIT_CRT_MEM_CHECK()\
	_CrtMemState _ms;       \
	_CrtMemCheckpoint(&_ms);

//! ����� � ������� ������ �� ������� ������. */
#define CRT_SET_REPORT()																	\
	std::cout << std::endl;																	\
	std::cout << std::setfill('-') << std::setw(50) << "" << std::setfill(' ') << std::endl;\
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );										\
	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );									\
	_CrtMemDumpAllObjectsSince(&_ms);	

#ifdef _DEBUG
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#else
	#define INIT_CRT_MEM_CHECK() ;
	#define CRT_SET_REPORT() ;
#endif // _MSC_VER


#include <iostream>
#include "stk_linked_list.h"


//! \namespace stk_test � ������ ������������ ��� ������������ �������� ������������ ������ Stack.
namespace stk_test{
	//! \enum tests ��������� �����.
	enum tests { PushSingleNumber,//!<������������ �� ������ ���������� ������ �������� � ���� ���������� int.
		CannotPushMore,//!<������������ �� ���������� ��������� ������ ���������� ���������, ������ ��� ������� �� ����� ���� �������� ��� 32-������ �������.
		PopFromEmpty,//!<������������ �� �������� ���� �� ������� �����.
		TopFromEmpty,//!<������������ �� ��������� ������ �� ������� �����.
		CopyStack,//!<������������ �� ���������� ������ ������������ �����������.
		AssignmentOperatorOfStack//!<������������ �� ���������� ������ �������� ������������.
	};

	//! ������ �������� �������. ���� ��� �� �����, �� ��������� ����������.
	#define ASSERT_EQ( condition ) \
		if (! (condition) )		   \
			throw std::exception("Test failed: "#condition);

	/*! \fn void TEST(int test_case) ������� ������������ ������ Stack
	 * \param[in] test_case ������������� ������ �� ������������ ������. */
	template< template <class Type_of_stack> class T >
	void TEST(int test_case){
		switch(test_case){													  
			case PushSingleNumber:  {                                        
				T<int> s_i;													
				try{																								
					s_i.push(3802);											
					ASSERT_EQ(s_i.top() == 0xEDA);
					s_i.pop();
					ASSERT_EQ(s_i.size() == 0);
					ASSERT_EQ(s_i.empty());
					std::cout << "Test is successfully completed!" << std::endl;
				}																
				catch(std::exception & ex){	                                               
					std::cout << ex.what() << std::endl;
					s_i.dump();
				} 
									}															
				break; 
			case CannotPushMore:{ /*< ��� ���������� ������� ����� ��������� ��� "runtime error", ��� ��� �������� �������� ��� ���� ������ ������, ��� ��������� 32-������� ��������,
								   ����� ����������� ������� ����� ������ ��������� �������																						 
								   ��� ��������� ����� ��������� ��������� �������� ASSERT_OK() � ������ push.*/
				T<int> s_i; 
				int value = 1;
				try{
					for(size_t i = 0; i < SIZE_MAX; ++i){
						s_i.push(value);
					}
				}
				catch(std::bad_alloc & ex){
					std::cout << "Error: bad alloc caught!"<< ex.what() << std::endl;
					s_i.dump();	
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
				}
								}
				break;
			case PopFromEmpty:{
				T<int> s_i;
				try{
					ASSERT_EQ(s_i.size() == 0);
					s_i.pop();
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					std::cout << "Test is successfully completed!" << std::endl;
				}
							  }
				break;
			case TopFromEmpty:{
				T<int> s_i;
				try{
					ASSERT_EQ(s_i.size() == 0);
					int var = s_i.top();
					std::cout << "Top variable = " << var << std::endl;
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					std::cout << "Test is successfully completed!" << std::endl;
				}
							  }
				break;
			case CopyStack:{
				auto num_of_elements = 5;
				T<int> s_i1;
				try{
					for(auto i=0;i<num_of_elements;++i){
						s_i1.push(i);
					}
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					s_i1.dump();
				}
				T<int> s_i2(s_i1);
				try{
					ASSERT_EQ(s_i1.size() == s_i2.size());
					while(s_i2.size()){
						ASSERT_EQ(s_i1.top() == s_i2.top());   //��������� �������� � ����� ������
						ASSERT_EQ(&s_i1.top() != &s_i2.top()); //��������� ������� ����� �����
						s_i1.pop();
						s_i2.pop();
					}
					ASSERT_EQ(s_i1.empty());
					std::cout << "Test is successfully completed!" << std::endl;
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					s_i1.dump();
					s_i2.dump();
				}
							  }
				break;
			case AssignmentOperatorOfStack:{
				auto num_of_elements1 = 5;
				auto num_of_elements2 = 3;
				T<int> s_i1;
				try{
					for(auto i=0;i<num_of_elements1;++i){
						s_i1.push(i);
					}
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					s_i1.dump();
				}
				T<int> s_i2;
				try{
					for(auto i=0;i<num_of_elements2;++i){
						s_i2.push(i);
					}
					s_i2 = s_i1;                               //�������� ������������
					ASSERT_EQ(s_i1.size() == s_i2.size());
					while(s_i2.size()){
						ASSERT_EQ(s_i1.top() == s_i2.top());   //��������� �������� ������
						ASSERT_EQ(&s_i1.top() != &s_i2.top()); //��������� ������� ����� �����
						s_i1.pop();
						s_i2.pop();
					}
					ASSERT_EQ(s_i1.empty());
					std::cout << "Test is successfully completed!" << std::endl;
				}
				catch(std::exception & ex){
					std::cout << ex.what() << std::endl;
					s_i1.dump();
					s_i2.dump();
				}
										   }
				break;
			default: std::cout << "Error: Don't have such test!" << std::endl; break; 
		}
	}
}


int main(){
	//! ������������� ������������ ������ ������.
	INIT_CRT_MEM_CHECK();

	/*! ���������� ������ �� ������.
	    ��������� ��������: PushSingleNumber, CannotPushMore, PopFromEmpty, TopFromEmpty, CopyStack, AssignmentOperatorOfStack.*/
	try{
		stk_test::TEST<Stack>(stk_test::PushSingleNumber);
	}
	catch(...){
		std::cout<<"Bad testing";
	}

	
    CRT_SET_REPORT();

	system("PAUSE");
	return 0;
}
