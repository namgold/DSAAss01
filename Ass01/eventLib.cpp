/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"
#define ENDLINE "\n"
string event0;
/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	ifstream infile(fName);
	stringstream iss;
	iss << infile.rdbuf();
	infile.close();
	event0.clear();
	string data;
	while (iss >> data) {
		if (data[data.size() - 1] == ';')
			data.erase(data.size() - 1, 1);
		event0.append(" " + data);
		ninjaEvent tail(data);
		eList.push_back(tail);
	}
}