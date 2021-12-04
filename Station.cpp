// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 19-Nov-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include <iomanip>
using namespace std;
namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const string& record) {
		id_generator++;
		Id = id_generator;
		bool more = false;
		size_t next_pos = 0;
		string temp = record;

		Name = m_utilities.extractToken(temp, next_pos, more);
		serialNumber = stoi(m_utilities.extractToken(temp, next_pos, more));
		itemsInStock = stoi(m_utilities.extractToken(temp, next_pos, more));

		if (Station::m_widthField < m_utilities.getFieldWidth()) {
			Station::m_widthField = m_utilities.getFieldWidth();
		}
		Description = m_utilities.extractToken(temp, next_pos, more);
	}
	const std::string& Station::getItemName() const {
		return Name;
	};
	size_t Station::getNextSerialNumber() {
		return serialNumber++;
	}
	size_t Station::getQuantity() const {
		return itemsInStock;
	}
	void Station::updateQuantity() {
		if (itemsInStock - 1 >= 0) {
			itemsInStock = itemsInStock - 1;
		}
	}
	void Station::display(std::ostream& os, bool full) const {
		os << "[" << setw(3) << setfill('0') << right << Id << setfill(' ') << "] Item: " << setw(m_widthField) << left << Name << " [" << setw(6) << setfill('0') << right << serialNumber << "]";
		if(full) {
			os << " Quantity: " << setfill(' ') << setw(m_widthField) << left << itemsInStock << " Description: " << left << Description;
		}
		os << endl;
	};

}