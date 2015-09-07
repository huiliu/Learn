// ConsoleApplicationTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "trie.h"
#include <iostream>

int main()
{
	rtv::Trie<char, std::string> dictionary('\0');

	dictionary.insert("karma", "Destiny or fate, following as effect from cause");
	dictionary.insert("karabc", "Destiny or fate, following as effect from cause");
	dictionary.insert("kardef", "Destiny or fate, following as effect from cause");
	dictionary.insert("kaabc", "Destiny or fate, following as effect from cause");
	rtv::Trie<char, std::string>::Iterator iter = dictionary.startsWith("kar");

	std::cout << "Keys with prefix kar are " << std::endl;

	for (; iter != dictionary.end(); ++iter) {
		std::cout << iter->first << " : " << iter->second->c_str() << std::endl;
	}

	return 0;
	return 0;
}
