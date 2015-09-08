#pragma once

#ifndef __WX_SIZER_CLI_AUTOCOMPLETE__
#define __WX_SIZER_CLI_AUTOCOMPLETE__


#include <string>
#include <vector>
#include "trie.h"

class TextAutoComplete
{
public:
	TextAutoComplete() : m_dict('\0') {}
	~TextAutoComplete() {}

	void			AppendItem(const char* itemName, const std::string& itemHelp);			/// �������Ŀ
	void			StartWith(const char* prefix, std::vector<std::string>& vecGetItem);		/// ģ��ƥ��
	std::string		GetHelpInfo(const char* itemName);										/// ȡ��ItemHelp

private:

	typedef rtv::Trie<char, std::string> TRIE_TREE;
	TRIE_TREE m_dict;
};

#endif