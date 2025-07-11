#include "module_yyy.h"

X_String_RegexA::X_String_RegexA() {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	reint();
}
X_String_RegexA::X_String_RegexA(CXTextA r) {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	m_expression = r;
	reint();
}
X_String_RegexA::X_String_RegexA(CXTextA r, CXTextA SearchStr) {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	m_searchStr = SearchStr.get();
	m_expression = r;
	reint();
}
X_String_RegexA::~X_String_RegexA() {
	if (m_regex != NULL) {
		delete m_regex;
		m_regex = NULL;
	}
}
void X_String_RegexA::reint() {
	if (m_regex != NULL) {
		delete m_regex;
		m_regex = NULL;
	}
	m_regex = new std::regex(m_expression, m_option);
	m_option = m_icase?
		(std::regex_constants::ECMAScript| std::regex_constants::icase):
		(std::regex_constants::ECMAScript);

}

void X_String_RegexA::SetEexpression(CXTextA exp) {
	m_expression = exp;
	reint();
}

void X_String_RegexA::SetICase(bool icase){
	m_icase = icase;
	reint();
}

void X_String_RegexA::SetSearchStr(CXTextA str) {
	m_searchStr = str;
}

bool X_String_RegexA::CheckStr() {
	std::smatch match;
	if (std::regex_search(m_searchStr, match, *m_regex)) {
		if (match.size() > 0) {
			return true;
		}
		return false;
	}
	return false;
}

CXTextA X_String_RegexA::Search(UINT index, UINT begin) {
	if (begin >= m_searchStr.length()) { return 0; }
	std::string::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::string::const_iterator iend = m_searchStr.end();
	std::smatch m; //匹配的结果
	int i = 0;
	CXTextA r;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		if (i == index) {
			r = m[0].str().c_str();
			break;
		}
		i++;
	}
	return r;
}

CXTextA X_String_RegexA::SearchSub(UINT index,UINT SubIndex, UINT begin) {
	if (begin >= m_searchStr.length()) { return 0; }
	std::string::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::string::const_iterator iend = m_searchStr.end();
	std::smatch m; //匹配的结果
	int i = 0;
	CXTextA r;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		if (i == index) {
			if (SubIndex + 1 <= m.size()) {
				r = m[SubIndex + 1].str().c_str();
			}
			break;
		}
		i++;
	}
	return r;
}

UINT X_String_RegexA::SearchAll(CXVector<CXTextA>&ret, UINT index, UINT begin){
	if (begin >= m_searchStr.length()) { return 0; }
	std::string::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::string::const_iterator iend = m_searchStr.end();
	std::smatch m; //匹配的结果
	ret.clear();
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin== iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		ret.add(m[0].str().c_str()); //获得第n个捕获组，其中0表示匹配到的全部子字符串
	}
	return ret.size();
}

UINT X_String_RegexA::GetSearchCount() {
	UINT index=0, begin=0;
	if (begin >= m_searchStr.length()) { return 0; }
	std::string::const_iterator ibegin = m_searchStr.begin(); //开始迭代器
	std::string::const_iterator iend = m_searchStr.end();
	std::smatch m; //匹配的结果
	UINT ri = 0;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		ri++;
	}
	return ri;
}

//替换
CXTextA X_String_RegexA::Replace(CXTextA str) {
	return regex_replace(m_searchStr, *m_regex, str.get()).c_str();
}

//-------

X_String_Regex::X_String_Regex() {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	reint();
}
X_String_Regex::X_String_Regex(CXText r) {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	m_expression = r;
	reint();
}
X_String_Regex::X_String_Regex(CXText r, CXText SearchStr) {
	m_regex = NULL;
	m_option = std::regex_constants::ECMAScript;
	m_searchStr = SearchStr.get();
	m_expression = r;
	reint();
}
X_String_Regex::~X_String_Regex() {
	if (m_regex != NULL) {
		delete m_regex;
		m_regex = NULL;
	}
}
void X_String_Regex::reint() {
	if (m_regex != NULL) {
		delete m_regex;
		m_regex = NULL;
	}
	m_regex = new std::wregex(m_expression, m_option);
	m_option = m_icase ?
		(std::regex_constants::ECMAScript | std::regex_constants::icase) :
		(std::regex_constants::ECMAScript);

}

void X_String_Regex::SetEexpression(CXText exp) {
	m_expression = exp;
	reint();
}

void X_String_Regex::SetICase(bool icase) {
	m_icase = icase;
	reint();
}

void X_String_Regex::SetSearchStr(CXText str) {
	m_searchStr = str;
}

bool X_String_Regex::CheckStr() {
	std::wsmatch match;
	if (std::regex_search(m_searchStr, match, *m_regex)) {
		if (match.size() > 0) {
			return true;
		}
		return false;
	}
	return false;
}

CXText X_String_Regex::Search(UINT index, UINT begin) {
	if (begin >= m_searchStr.length()) { return 0; }
	std::wstring::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::wstring::const_iterator iend = m_searchStr.end();
	std::wsmatch m; //匹配的结果
	int i = 0;
	CXText r;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		if (i == index) {
			r = m[0].str().c_str();
			break;
		}
		i++;
	}
	return r;
}
CXText X_String_Regex::SearchSub(UINT index, UINT SubIndex, UINT begin) {
	if (begin >= m_searchStr.length()) { return 0; }
	std::wstring::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::wstring::const_iterator iend = m_searchStr.end();
	std::wsmatch m; //匹配的结果
	int i = 0;
	CXText r;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		if (i == index) {
			if (SubIndex+1 <= m.size()) {
				r = m[SubIndex+1].str().c_str();
			}
			break;
		}
		i++;
	}
	return r;
}

UINT X_String_Regex::SearchAll(CXVector<CXText>& ret, UINT index, UINT begin) {
	if (begin >= m_searchStr.length()) { return 0; }
	std::wstring::const_iterator ibegin = m_searchStr.begin() + begin; //开始迭代器
	std::wstring::const_iterator iend = m_searchStr.end();
	std::wsmatch m; //匹配的结果
	ret.clear();
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		ret.add(m[0].str().c_str()); //获得第n个捕获组，其中0表示匹配到的全部子字符串
	}
	return ret.size();
}

UINT X_String_Regex::GetSearchCount() {
	UINT index = 0, begin = 0;
	if (begin >= m_searchStr.length()) { return 0; }
	std::wstring::const_iterator ibegin = m_searchStr.begin(); //开始迭代器
	std::wstring::const_iterator iend = m_searchStr.end();
	std::wsmatch m; //匹配的结果
	UINT ri = 0;
	while (std::regex_search(ibegin, iend, m, *m_regex)) {
		if (ibegin == iend) {
			break;
		}
		ibegin = m[0].second; //更新开始迭代器的位置
		ri++;
	}
	return ri;
}

//替换
CXText X_String_Regex::Replace(CXText str) {
	return regex_replace(m_searchStr, *m_regex, str.get()).c_str();
}