#include "TextAutoComplete.h"


void TextAutoComplete::AppendItem(const char* itemName, const std::string& itemHelp)
{
	m_dict.insert(itemName, itemHelp);
}

void TextAutoComplete::StartWith(const char* prefix, std::vector<std::string>& vecGetItem)
{
	TRIE_TREE::Iterator it = m_dict.startsWith(prefix);
	for (; it != m_dict.end(); ++it)
	{
		vecGetItem.push_back(it->first);
	}
}

std::string TextAutoComplete::GetHelpInfo(const char* itemName)
{
	TRIE_TREE::Iterator it = m_dict.find(itemName);
	if (m_dict.end() != it)
	{
		return *it->second;
	}
	return std::string();
}