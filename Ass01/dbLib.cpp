/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0
#define ENDLINE "\r\n"
using namespace std;

void    strPrintTime(char* des, time_t& t) {
	tm *pTime = localtime(&t);
	strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

int find(char* a, char b) {
	if (!a) return -1;
	for (int i = 0; a[i] != '\0'; i++)
		if (a[i] == b) return i;
	return -1;
}

void fix(char*a) {
	if (!a) return;
	int length;
	for (length = -1; a[++length] != '\0';);
	if (length > 4) return;
	for (int i = 5; --i >= 0;)
		a[i] = a[i - (4 - length)];
	for (; length < 4; length++)
		a[3 - length] = '0';
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {

	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen(fName, "rb");
	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	//buffer = (char*)malloc(sizeof(char)*lSize + 1);
	buffer = new char[lSize + 1];

	// copy the file into the buffer
	result = fread(buffer, 1, lSize, pFile);
	buffer[lSize] = '\0';

	// the whole file is now loaded in the memory buffer
	char * line = strtok(buffer, ENDLINE);
	line = strtok(NULL, ENDLINE);

	// Parsing data from buffer
	char *aline;
	char element[100];
	struct tm tmdate;
	L1Item<NinjaInfo>* itemTail;
	NinjaInfo* dataTail = new NinjaInfo();
	while (line) {
		//Ignore the first collumn
		aline = strchr(line, ',') + 1;

		//Time
		strncpy(element, aline, find(aline, ','));
		element[find(aline, ',')] = element[2] = element[5] = element[10] = element[13] = element[16] = '\0';
		//tmdate = { 0 };
		tmdate.tm_mon = atoi(&element[0]) - 1;
		tmdate.tm_mday = atoi(&element[3]);
		tmdate.tm_year = atoi(&element[6]) - 1900;
		tmdate.tm_hour = atoi(&element[11]);
		tmdate.tm_min = atoi(&element[14]);
		tmdate.tm_sec = atoi(&element[17]);
		dataTail->timestamp = mktime(&tmdate);
		aline = strchr(aline + 1, ',') + 1;

		//ID
		strncpy(element, aline, find(aline, ','));
		element[find(aline, ',')] = '\0';
		fix(element);								//Fix ID to 00xx
		strcpy(dataTail->id, element);				//ID
		aline = strchr(aline + 1, ',') + 1;

		//Long
		strncpy(element, aline, find(aline, ','));
		element[find(aline, ',')] = '\0';
		dataTail->longitude = atof(element);
		aline = strchr(aline + 1, ',') + 1;

		//Lat
		strncpy(element, aline, find(aline, ','));
		element[find(aline, ',')] = '\0';
		dataTail->latitude = atof(element);
		aline = strchr(aline + 1, ',') + 1;

		//Push back
		if (!db.getSize()) {
			db.push_back(*dataTail);
			itemTail = db._pHead;
		}
		else {
			itemTail->pNext = new L1Item<NinjaInfo_t>(*dataTail);
			itemTail = itemTail->pNext;
			db._size++;
		}
		//Next line
		line = strtok(NULL, ENDLINE);
	}

	// clean up
	fclose(pFile);
	delete buffer;
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
	// TODO: write code to parse information from a string buffer, ignore if you don't use it
	return true;
}

void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
	void*   pGData = NULL;
	initNinjaGlobalData(&pGData);
	pGData = new traceArray<L1Item<NinjaInfo>*>(bList._pHead);

	while (!eventList.isEmpty()) {
		if (!processEvent(eventList[0], bList, pGData))
			cout << eventList[0].code << " is an invalid event\n";
		eventList.removeHead();
	}
	releaseNinjaGlobalData(pGData);
}

int ctoi(char* ID) {
	if (!ID) return 0;
	//fix(ID);
	int addr = 0;
	if (ID[0] > '9') addr += (max(toupper(ID[0]) - 'A', 0) + 10) * 36 * 36 * 36;
	else addr += (ID[0] - '0') * 36 * 36 * 36;
	if (ID[1] > '9') addr += (max(toupper(ID[1]) - 'A', 0) + 10) * 36 * 36;
	else addr += (ID[1] - '0') * 36 * 36;
	if (ID[2] > '9') addr += (max(toupper(ID[2]) - 'A', 0) + 10) * 36;
	else addr += (ID[2] - '0') * 36;
	if (ID[3] > '9') addr += (max(toupper(ID[3]) - 'A', 0) + 10);
	else addr += (ID[3] - '0');
	return addr;
}

bool initNinjaGlobalData(void** pGData) {
	/// TODO: You should define this function if you would like to use some extra data
	/// the data should be allocated and pass the address into pGData
	return true;
}

void releaseNinjaGlobalData(void* pGData) {
	/// TODO: You should define this function if you allocated extra data at initialization stage
	/// The data pointed by pGData should be released
}

void printNinjaInfo(NinjaInfo_t& b) {
	printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}