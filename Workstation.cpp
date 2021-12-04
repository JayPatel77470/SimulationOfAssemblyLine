// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 3-Dec-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
namespace sdds {
	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};


	Workstation::Workstation(const std::string& str) : Station(str) { m_pNextStation = nullptr; };
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder() {
		bool ok = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) {
				if (m_pNextStation != nullptr) {
					*m_pNextStation += std::move(m_orders.front());
					m_orders.pop_front();
					ok = true;
				}
				else if (m_orders.front().isFilled()) {
					completed.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
					ok = true;
				}
				else if (!m_orders.front().isFilled()) 
				{
					incomplete.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
					ok = true;
				}
			}
		}

		return ok;
	};
	void Workstation::setNextStation(Workstation* station) {
		if (m_pNextStation != station)
			m_pNextStation = station;
		else
			m_pNextStation = nullptr;
	};

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	};
	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> ";
		if (m_pNextStation == nullptr) {
			os << "End of Line";
		}
		else {
			os << m_pNextStation->getItemName();
		}
		os << std::endl;
	};
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	};
}
