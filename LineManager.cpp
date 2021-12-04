// Name: Jay Girishkumar Patel
// Seneca Student ID: 158741199 
// Seneca email: jgpatel10@myseneca.ca
// Date of completion: 3-Dec-2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		try
		{

			std::fstream fs(file);
			std::string Mainstring, firstRecord, SecondRecord;
			Utilities m_utilities;
			bool more = false;
			m_firstStation = nullptr;
			m_cntCustomerOrder = pending.size();

			while (getline(fs, Mainstring))
			{
				size_t pos = 0;
				firstRecord = m_utilities.extractToken(Mainstring, pos, more);

				if (more)
					SecondRecord = m_utilities.extractToken(Mainstring, pos, more);
				else 
					SecondRecord = "";


				std::for_each(stations.begin(), stations.end(), [&](Workstation* ws1)
					{
						if (ws1->getItemName() == firstRecord)
						{
							std::for_each(stations.begin(), stations.end(), [&](Workstation* ws2)
								{
									if (ws2->getItemName() == SecondRecord) ws1->setNextStation(ws2);
								});
							activeLine.push_back(ws1);
						}
					});
			}
			m_firstStation = activeLine.front();
		}
		catch (...)
		{
			std::cerr << "An Error Occurred!!";
		}
	}
	void LineManager::linkStations() {
		std::vector<Workstation*> tempStation{};
		Workstation* v_currentStation;
		v_currentStation = m_firstStation;
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws1) {
			if (v_currentStation) {
				tempStation.push_back(v_currentStation);
				v_currentStation = v_currentStation->getNextStation();
			}
			});
		activeLine = tempStation;
	}
	bool LineManager::run(std::ostream& os) {
		static size_t iterNum = 1;
		bool ok = false;
		size_t beforeOrder = completed.size() + incomplete.size();
		os << "Line Manager Iteration: " << iterNum << std::endl;
		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
			w->fill(os);
			});
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
			w->attemptToMoveOrder();
			});
		size_t afterOrder = completed.size() + incomplete.size();
		m_cntCustomerOrder -= (afterOrder - beforeOrder);
		if (m_cntCustomerOrder <= 0) ok = true;

		iterNum++;

		return ok;
	
		
	}
	void LineManager::display(std::ostream& os) const {

		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* ws) {
			ws->display(os); });
	}
}
