// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 19-Nov-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
using namespace std;
namespace sdds {
	char Utilities::m_delimiter{};
	void Utilities::setFieldWidth(size_t newWidth){
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		string tempToken{};
			if (str[next_pos] == m_delimiter) {
				more = false;
				throw string("error");
			}
			else {

				size_t next_delimeter_pos = str.find(m_delimiter, next_pos + 1);
				tempToken = str.substr(next_pos, next_delimeter_pos - next_pos);
				next_pos = tempToken.size() + next_pos + 1;
				if (next_pos -1 == str.length()) {
					more = false;
				}
				else {
					more = true;
				}
					if (m_widthField < tempToken.size())
						setFieldWidth(tempToken.size());
			}
		
		return tempToken;
	}

    void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
    
	char Utilities::getDelimiter() {
		return m_delimiter;		
	}
}