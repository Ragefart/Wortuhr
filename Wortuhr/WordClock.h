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

	void addWord(int v, string m);					// f�ge Wort dem W�rternetz zu
	void addConnection(int v, int w, int m);		// f�ge Verbindung zw. W�rtern zu
													// m ist die Markierung der
													// Kante als Integer/Bitmuster,
													// mit deren Hilfe Pfade im Graphen
													// gezielt ausgew�hlt werden k�nnen
													// (in etwa vergleichbar mit den
													// Kosten bei Dijkstra, Floyd etc.)
	string word(int v);							// gib Wort zur Nummer als string zur�ck
	string getWordNetPath(int v, int mask);			// Gibt einen bestimmten Pfad aus
													// dem W�rternetz als Satz zur�ck,
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
