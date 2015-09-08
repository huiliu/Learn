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

	void			AppendItem(const char* itemName, const std::string& itemHelp);			/// 添加新项目
	void			StartWith(const char* prefix, std::vector<std::string>& vecGetItem);		/// 模糊匹配
	std::string		GetHelpInfo(const char* itemName);										/// 取得ItemHelp

private:

	typedef rtv::Trie<char, std::string> TRIE_TREE;
	TRIE_TREE m_dict;
};

#endif