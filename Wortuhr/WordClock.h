#ifndef WORDCLOCK_H_
#define WORDCLOCK_H_

#include <string>
#include <iostream>
#include <vector>
#include "Node.h"
#include "stdafx.h"

using namespace std;

class WordClock
{
public:
	WordClock();
	~WordClock();

	void addWord(int v, string m);					// füge Wort dem Wörternetz zu
	void addConnection(int v, int w, int m);		// füge Verbindung zw. Wörtern zu
													// m ist die Markierung der
													// Kante als Integer/Bitmuster,
													// mit deren Hilfe Pfade im Graphen
													// gezielt ausgewählt werden können
													// (in etwa vergleichbar mit den
													// Kosten bei Dijkstra, Floyd etc.)
	string word(int v);							// gib Wort zur Nummer als string zurück
	string getWordNetPath(int v, int mask);			// Gibt einen bestimmten Pfad aus
													// dem Wörternetz als Satz zurück,
													// festgelegt durch eine Codierung
													// der Zeit in Mask
	void initiate();
	int encodeTime(int hours, int minutes);
	int FirstMatchingArc(int c);
private:
	vector<Node> nodes;
	vector<vector<int>> arcs;
};

#endif /* WORDCLOCK_H_ */
