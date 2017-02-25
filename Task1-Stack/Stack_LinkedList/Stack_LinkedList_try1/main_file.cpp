#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <iostream>
#include "stk_linked_list.h"

int main(){
	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	std::cout << "Detect memory leaks with C++ CRT:" << std::endl;

	Stack<int> my_int_ctack1;
	for (size_t i = 0; i < 50000; ++i){
		my_int_ctack1.push(i);
	}
	for (size_t i = 0; i < 50000; ++i){
		my_int_ctack1.pop();
	}

	{
		Stack<int> my_int_ctack2;
		for (size_t i = 0; i < 50000; ++i){
			my_int_ctack2.push(i);
		}
	}

	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

	_CrtMemDumpAllObjectsSince(&_ms);

	system("PAUSE");
	return 0;
}
