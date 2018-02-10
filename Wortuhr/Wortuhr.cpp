#include "stdafx.h"
#include <iostream>
#include <string>

#include "WordClock.h"
#include "WordNetDeutsch.h"


using namespace std;

int main()
{
	WordClock clock;
	clock.initiate();

	// gib alle Zeitangaben aus
	for (int h = 0; h<12; h++)
		for (int m = 0; m<59; m += 5)
			cout << clock.getWordNetPath(0, clock.encodeTime(h, m)) << endl;

	// zwei einfache Tests, ob die Wörter behalten wurden
	cout << "Wort Nr. 0  = " << clock.word(0) << endl;
	cout << "Wort Nr. 18 = " << clock.word(18) << endl;
	system("pause");
	return 0;
}
