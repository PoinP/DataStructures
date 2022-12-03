//// Memory leaks test
//
//#ifdef _DEBUG
//#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#else
//#define new new
//#endif
//
//#include <iostream>
//#include "Dictionary.h"
//#include <string>
//
//int main()
//{
//	{
//		Dictionary<std::string, int> dic = { {"One", 1}, {"Two", 2}, {"Three", 3}, {"Four", 4} };
//
//		for (auto el : dic)
//		{
//			std::cout << el << " ";
//		}
//
//		std::cout << "\n\n" << dic["Two"];
//
//		dic.erase(dic.find("Four"), dic.find("Two"));
//
//		std::cout << "\n\n";
//
//		for (auto el : dic)
//		{
//			std::cout << el << " ";
//		}
//	}
//
//	_CrtDumpMemoryLeaks();
//}