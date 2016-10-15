
#include "common.h"
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>

// ����for�е�auto
/*
 * ע��std::unordered_map<T1, T2>��value_typeΪ std::pair<const T1, T2>
 *
 * �������ʹ��auto��iterator������ָ��std::pair<T1,T2>ȥ����map����������
 * ��Ҫ������ת�������������������
 */
void
test_for_auto()
{
	typedef std::unordered_map<std::string, int> UORDER_MAP_STRING_INT;
	UORDER_MAP_STRING_INT m;
	std::cout << std::is_const<UORDER_MAP_STRING_INT::value_type::first_type>::value << std::endl;
	m.emplace("ABC", 1);
	m.emplace("ABD", 2);
	m.emplace("ABE", 3);
	m.emplace("ABF", 5);

	std::unordered_map<std::string, int>::iterator it = m.begin();
	for (; m.end() != it; ++it)
	{
		std::cout << &(*it) << "\t" << it->first << "\t" << it->second << "\tis_const: "<< std::is_const<decltype(it)>::value << std::endl;
	}

	for (const auto& item : m)
	{
		std::cout << &item << "\t" << item.first << "\t" << item.second << "\tis_const: " << std::is_const<decltype(item)>::value << std::endl;
	}

	for (const std::pair<std::string, int>& p : m)
	{
		std::cout << &p << "\t" << p.first << "\t" << p.second << "\tis_const: " << std::is_const<decltype(p)>::value << std::endl;
	}
}