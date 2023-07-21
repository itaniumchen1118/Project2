#include "CricketTeam.h"
using namespace std;
#include <string>

CricketTeam::CricketTeam() {
	
}

CricketTeam::~CricketTeam() {
	Player* p = head;
	while (p != nullptr) {
		Player* next = p->next;
		delete p;
		p = next;
	}
}

CricketTeam::CricketTeam(const CricketTeam& other) {
	Player* p = other.head;
	while (p != nullptr) {
		addCricketer(p -> firstName, p->lastName, p->value);
		p = p->next;
	}
}

bool CricketTeam::noTeam() const {
	return head == nullptr;
}

int CricketTeam::cricketerCount() const {
	return size;
}

bool CricketTeam::addCricketer(const std::string& firstName, const std::string&
	lastName, const CricketType& value) {
	Player* p = head;
	while (p != nullptr) {
		if (p->firstName == firstName && p->lastName == lastName) {
			return false;
		}
		if (p->lastName > lastName || p->lastName == lastName && p->firstName > firstName) {
			break;
		}
		p = p->next; 
	}
	Player* newPlayer = new Player(firstName, lastName, value);
	if (p == nullptr) {
		head = tail = newPlayer;
	}
	else {
		if (p == head) {
			head->prev = newPlayer;
			newPlayer->next = head;
			head = newPlayer;
		}
		else {
			p->prev->next = newPlayer;
			newPlayer->prev = p->prev;
			newPlayer->next = p;
			p->prev = newPlayer;
		}
	}
	size++;
	return true;
}

bool CricketTeam::substituteCricketer(const std::string& firstName, const
	std::string& lastName, const CricketType& value) {
	for (Player* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			p->value = value;
			return true;
		}
	}
	return false;
}

bool CricketTeam::addOrSubstitute(const std::string& firstName, const
	std::string& lastName, const CricketType& value) {
	for (Player* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			p->value = value;
			return true;
		}
	}
	addCricketer(firstName, lastName, value);
	return true;
}

bool CricketTeam::releaseCricketer(const std::string& firstName, const
	std::string& lastName) {
	for (Player* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			return true;
		}
	}
	return false;
}

bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const
	std::string& lastName) const {
	for (Player* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			return true;
		}
	}
	return false;
}

bool CricketTeam::searchForCricketer(const std::string& firstName, const
	std::string& lastName, CricketType& value) const {
	for (Player* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			value = p->value;
			return true;
		}
	}
	return false;
}

bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName,
	std::string& lastName, CricketType& value) const {
	if (i < 0 || i >= size) {
		return false;
	}
	Player* p = head;
	for (; i > 0; i--) {
		p = p->next;
	}
	firstName = p->firstName;
	lastName = p->lastName;
	value = p->value;
	return true;
}

void CricketTeam::tradeCricketTeams(CricketTeam& other) {
	Player* temp = head;
	head = other.head;
	other.head = temp;

	int tempSize = size;
	size = other.size;
	other.size = tempSize;
}

bool mergeCricketers(const CricketTeam& odOne,
	const CricketTeam& odTwo,
	CricketTeam& odJoined) {

	odJoined.~CricketTeam();

	std::string oneFirst;
	std::string oneLast;
	CricketType oneVal;
	std::string twoFirst;
	std::string twoLast;
	CricketType twoVal;
	bool sameVal = true;

	int i = 0;
	int j = 0;
	while (i < odOne.cricketerCount() || j < odTwo.cricketerCount()) {
		odOne.checkTeamForCricketer(i, oneFirst, oneLast, oneVal);
		odTwo.checkTeamForCricketer(j, twoFirst, twoLast, twoVal);
		if (oneFirst == twoFirst && oneLast == twoLast && oneVal == twoVal) {
			odJoined.addCricketer(oneFirst, oneLast, oneVal);
			i++;
			j++;
		}
		else if (oneFirst == twoFirst && oneLast == twoLast && oneVal != twoVal) {
			sameVal = false;
			i++;
			j++;
		}
		else if (oneLast > twoLast || (oneLast == twoLast && oneFirst > twoFirst) || i == odOne.cricketerCount()) {
			odJoined.addCricketer(twoFirst, twoLast, twoVal);
			j++;
		}
		else if (oneLast < twoLast || (oneLast == twoLast && oneFirst < twoFirst) || j == odTwo.cricketerCount()) {
			odJoined.addCricketer(oneFirst, oneLast, oneVal);
			i++;
		}
	}
	return sameVal;
}

void checkCricketers(const std::string& fsearch,
	const std::string& lsearch,
	const CricketTeam& odOne,
	CricketTeam& odResult) {

	odResult.~CricketTeam();

	std::string first = fsearch;
	std::string last = lsearch;
	CricketType val;

	for (int i = 0; i < odOne.cricketerCount(); i++) {
		std::string tempFirst = "*";
		std::string tempLast = "*";
		if (odOne.searchForCricketer(first, tempLast, val)) {
			odResult.addCricketer(first, tempLast, val);
		}
		if (odOne.searchForCricketer(tempFirst, last, val)) {
			odResult.addCricketer(tempFirst, last, val);
		}
	}
}