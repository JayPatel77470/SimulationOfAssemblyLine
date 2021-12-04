// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 19-Nov-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include "Utilities.h"
namespace sdds {
	class Station {
		int Id = 0;
		std::string Name;
		std::string Description;
		unsigned int serialNumber;
		unsigned int itemsInStock;
		static size_t m_widthField;
		static size_t id_generator;
		Utilities m_utilities;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H
