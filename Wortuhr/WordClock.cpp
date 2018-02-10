#include "stdafx.h"
/*
* WordClock.cpp
*/

#include "WordClock.h"

using namespace std;

/*
* Konstructor
*
* ggfs. Initialisierung, zum Beispiel für Digraph.
*/

WordClock::WordClock()
{

}

/*
* Destructor
*
* ggfs. delete-Operationen
*/
WordClock::~WordClock()
{

}

/*
* addWord
*
* Füge ein Wort der WordClock hinzu.
* Dieses wird als Knoten dem Wörtergraphen hinzugefügt.
* Parameter:
* v Knotennummer
* m Wort
*/
void WordClock::addWord(int v, string m)
{
	Node n;
	n.setnumber(v);
	n.setname(m);
	nodes.push_back(n);
	vector<int> vec;
	arcs.push_back(vec);
	if (nodes.size() > 1){
		for (int i = 0; i < nodes.size() - 1; i++) {
			arcs[arcs.size() - 1].push_back(-1);
		}
	}
	for (int i = 0; i < nodes.size(); i++) {
		arcs[i].push_back(-1);
	}

}

/*
* addConnection
*
* füge eine Verbindung ein. Eine Verbindung besagt, dass die beiden Verbundenen Wörter direkt aufeinanderfolgen
* Die Verbindung wird als gerichtete Kante dem Wörtergraphen hinzugefügt. Die Markierung wird auch zum Auswählen
* eines bestimmten Pfades im Wörtergraphen genutzt, siehe unten.
* Parameter:
* v Knotennummer des vorangehenden Wortes
* w Knotennummer des nachfolgenden Wortes
* m Markierung der Kante
*/
void WordClock::addConnection(int v, int w, int m)
{
	arcs[v][w] = m;
}

/*
* word
*
* Gib Name des Wortes als string zurück.
* Parameter:
* v Knotennummer des Wortes
*/
string WordClock::word(int v)
{
	if ((v < nodes.size()) && (v > -1)) {
		return nodes[v].getname();
	}
	else {
		return "";
	}
}

/*
* getWordNetPath
*
* gibt die Knoten entlang eines ausgewählten Pfades im Graphen als string.
* Die Auswahl erfolgt durch die übergebene Bitmaske, anhand derer
* ein ganz bestimmter Pfad durch den Graphen ausgewählt werden kann.
* Bei koorekter Aufstellung des Graphen (der Kantenmarkierungen) gibt
* es nur eine solche Kante für jeden Knoten, (der weitere Weg ist
* eindeutig) -- deshalb muss nur FirstMatchingArc() aufgerufen werden
* und nicht NextMatchingArc()
*/
string WordClock::getWordNetPath(int v, int mask)
{
	//return word(0) + "_IST_ZWÖLF";	// mit '+' können Sie zwei Strings aneinanderhängen.
	string result;
	while (v != -1) {
		result = result + word(v);
		v = FirstMatchingArc(v);
	}
	return result;
}


void WordClock::initiate() {
	
	addWord(0, "ES");
	addWord(1, "_");
	addWord(2, "IST");
	addWord(3, "_");
	addWord(4, "FÜNF");
	addWord(5, "ZEHN");
	addWord(6, "VIERTEL");
	addWord(7, "ZWANZIG");
	addWord(8, "_");
	addWord(9, "NACH");
	addWord(10, "VOR");
	addWord(11, "_");
	addWord(12, "HALB");
	addWord(13, "_");
	addWord(14, "EINS");
	addWord(15, "ZWEI");
	addWord(16, "DREI");
	addWord(17, "VIER");
	addWord(18, "FÜNF");
	addWord(19, "SECHS");
	addWord(20, "SIEBEN");
	addWord(21, "ACHT");
	addWord(22, "NEUN");
	addWord(23, "ZEHN");
	addWord(24, "ELF");
	addWord(25, "ZWÖLF");

	addConnection(0, 1, 0x0fff0fff);
	addConnection(1, 2, 0x0fff0fff);
	addConnection(2, 3, 0x00000fbe);	// es ist fünf/zehn...
	addConnection(2, 11, 0x00000040);	// es ist halb...
	addConnection(2, 13, 0x00000001);	// es ist eins/zwei...
	addConnection(3, 4, 0x000008a2);	// fünf
	addConnection(3, 5, 0x00000404); // zehn
	addConnection(3, 6, 0x00000208); // viertel
	addConnection(3, 7, 0x00000110); // zwanzig
	addConnection(4, 8, 0x000008a2);
	addConnection(5, 8, 0x00000404);
	addConnection(6, 8, 0x00000208);
	addConnection(7, 8, 0x00000110);
	addConnection(8, 9, 0x0000009f);	// nach
	addConnection(8, 10, 0x00000f20);	// vor
	addConnection(9, 13, 0x00000f7f);	// nach eins/zwei...
	addConnection(9, 11, 0x00000080);	// nach halb
	addConnection(10, 13, 0x00000fdf);	// vor eins/zwei...
	addConnection(10, 11, 0x00000020);	// vor halb
	addConnection(11, 12, 0x000000e0);
	addConnection(12, 13, 0x000000e0);
	addConnection(13, 14, 0x00010000);
	addConnection(13, 15, 0x00020000);
	addConnection(13, 16, 0x00040000);
	addConnection(13, 17, 0x00080000);
	addConnection(13, 18, 0x00100000);
	addConnection(13, 19, 0x00200000);
	addConnection(13, 20, 0x00400000);
	addConnection(13, 21, 0x00800000);
	addConnection(13, 22, 0x01000000);
	addConnection(13, 23, 0x02000000);
	addConnection(13, 24, 0x04000000);
	addConnection(13, 25, 0x08000000);
}

int WordClock::encodeTime(int hours, int minutes)
{
	int result;

	// check hours and minutes bounds;
	if ((hours < 0) || (minutes < 0)) return 0;


	//normalize minutes to 0..59
	minutes = minutes % 60;

	if (minutes >= 25) hours++; // in German, 'half' is said with following hour, and (here) it starts with 'five to half'

	//normalize hours to 12h format (1..12)
	hours = hours % 12;
	if (0 == hours) hours = 12;

	// hours are coded as bits in the high 16bit, bit0=eins, bit1=zwei,...
	result = 0x8000 << hours;

	// minutes are coded as bits in the low 16bit bit0=5 min, bit1=10...
	result |= 0x1 << minutes / 5;

	return result;
}

int WordClock::FirstMatchingArc(int v) {
	for (int i = 0; i < arcs.size(); i++) {
		if (arcs[v][i] != -1) {
			return i;
		}
	}
	return -1;
}