// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 27-Nov-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include <iomanip>
#include <algorithm>

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	
	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	};

	CustomerOrder::CustomerOrder(const std::string& str) {
		size_t next_pos = 0;
		bool more = true;
		Utilities m_utilities;
		try {
			m_name = m_utilities.extractToken(str, next_pos, more);
			m_product = m_utilities.extractToken(str, next_pos, more);
			m_cntItem = std::count(str.begin(), str.end(), m_utilities.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++)		{
				m_lstItem[i] = new Item(m_utilities.extractToken(str, next_pos, more));
			}
			m_widthField = std::max(m_utilities.getFieldWidth(), m_widthField);
		}
		catch (std::string& msg) {
			std::cout << msg;
		}
		
	};

	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		throw "Exception throw";
	};
	CustomerOrder::CustomerOrder(CustomerOrder&& obj)noexcept {	
		m_lstItem = new Item*[obj.m_cntItem + 1];
		*this = std::move(obj);
		
	};
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj)noexcept {
		if (this != &obj) {
			if (m_name != "") {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
			}
			delete[] m_lstItem;
			    this->m_name = obj.m_name;
				this->m_product = obj.m_product;
				m_lstItem = new Item * [obj.m_cntItem + 1];
				for (size_t i = 0; i < obj.m_cntItem; i++) {
					this->m_lstItem[i] = obj.m_lstItem[i];
				}
				this->m_widthField = obj.m_widthField;
				this->m_cntItem = obj.m_cntItem;
				obj.m_cntItem = 0;
				for (size_t i = 0; i < obj.m_cntItem; i++) {
					obj.m_lstItem[i] = nullptr;
				}
				obj.m_name = "";
				obj.m_product = "";
		}
		return *this;
	};

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem != nullptr) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	};

	bool CustomerOrder::isFilled() const {
		bool ok = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				ok = false;
			}
		}
		return ok;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool ok = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					ok = false;
				};
			}
		}
		return ok;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		
		for (size_t i = 0; i < m_cntItem; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0) {
				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << ']' << std::endl;
			}
			else if(station.getItemName() == m_lstItem[i]->m_itemName){
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << ']' << std::endl;
			}
		}
	};


	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) os << "FILLED" << std::endl;
				else os << "TO BE FILLED" << std::endl;
		}
	};
}