#pragma once

#include <string>

using namespace std;


class Node
{
public:
	Node();
	virtual ~Node();
	void setname(string newname);
	void setnumber(int number);
	string getname() {
		return name;
	}
	int getnumber() {
		return number;
	}
private:
	string name;
	int number;
};

