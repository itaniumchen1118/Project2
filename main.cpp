#include "CricketTeam.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	CricketTeam rajasthanRoyals;
	rajasthanRoyals.addCricketer("Sanju", "Samson", "11");
	rajasthanRoyals.addCricketer("Jos", "Buttler", "63");
	rajasthanRoyals.addCricketer("Yashavi", "Jaiswal", "19");
	rajasthanRoyals.addCricketer("Shimron", "Hetmeyer", "189");
	rajasthanRoyals.addCricketer("Trent", "Boult", "18");
	rajasthanRoyals.addCricketer("Ravichandran", "Ashwin", "99");
	rajasthanRoyals.addCricketer("Yuzvendra", "Chahal", "3");
	for (int n = 0; n < rajasthanRoyals.cricketerCount(); n++)
	{
		string first;
		string last;
		string val;
		rajasthanRoyals.checkTeamForCricketer(n, first, last,
			val);
		cout << first << " " << last << " " << val << endl;
	}

	return 0;
}