#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

class CDataChain
{
public:
	CDataChain(void);
	virtual ~CDataChain(void);
	//віртуальна функція, що має генерувати повну послідовність цифр.
	virtual void Generate(int nDepth, int nMaxLength = 0) = 0;
	//повертає довжину згенерованої послідовності цифр.
	size_t GetLength();
	//повертає позицію входження підстрічки sSubStr починаючи із nPos.
	// -1, якщо підстрічки не знайдено
	int Find(const char* sSubStr, int nPos = 0);
	//повертає підстрічку починаючи із nPos довжиною nLength. або до кінця послідовності
	string GetSubStr(int nPos, int nLength = -1);
	//повертає всю згенеровану послідовність цифр
	const char* GetFullString();
protected:
	//стрічка із згенерованою послідовністю цифр
	string m_sChain;
};
CDataChain::CDataChain(){};
CDataChain::~CDataChain(){};

int CDataChain::Find(const char* sSubStr, int nPos) {
    int pos = m_sChain.find(sSubStr, nPos);
    return ( pos == string::npos) ? -1 : pos;
}

size_t CDataChain::GetLength() {
    return m_sChain.length();
}

string CDataChain::GetSubStr(int nPos, int nLength) {
    return m_sChain.substr(nPos, nLength);
}

const char* CDataChain::GetFullString() {
    return m_sChain.c_str();
}


class CDataSimple : public CDataChain
{
private:
	// поертає довжину числа 
	int _numberLength(int number);
	// 123 => ['1', '2', '3'];
	char* _intToChars(int number);
public:
	CDataSimple(void);
	~CDataSimple(void);
	//Реалізація генератора повної послідовності цифр
	void Generate(int nDepth, int nMaxLength = 0);
};
CDataSimple::CDataSimple(){};
CDataSimple::~CDataSimple(){};

int CDataSimple::_numberLength(int number) {
	if (number == 0) {
		return 1;
	}
	return floor(log10(number)) + 1;
};

char* CDataSimple::_intToChars(int number) {
	char nums[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	int len = _numberLength(number);
	char* result = new char[len];

	
	for (int i = len - 1; i >= 0; i--) {
		int last = number % 10;
		result[i] = nums[last];
		number /= 10;
	}
	result[len] = '\0';

	return result;
}

void CDataSimple::Generate(int nDepth, int nMaxLength) {
	string s;
	int i = 0, j = 0;
	while (i < nDepth && j < nMaxLength) {
		char* add = _intToChars(i);
		int k = 0;

		while(add[k] != '\0' && j < nMaxLength) {
			s += add[k];
			k++;
			j++;
		}
		i++;
	}

	m_sChain = s;
}



int main (int argc, char* argv[]) {
	CDataSimple simple;
	simple.Generate(15, 20);

	cout << simple.GetFullString() << endl;
	return 0;
}