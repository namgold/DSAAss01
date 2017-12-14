/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#include <algorithm>

bool Event0(ninjaEvent_t& event) {
	cout << event.code << ":" << event0 << endl;
	return true;
}

bool Event1(void* pGData) {
	cout << "1: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!strcmp(tracePtr->savedHead, "NULLL")) cout << "empty" << endl;
	else cout << tracePtr->savedHead << endl;
	return true;
}

bool Event2(void*pGData) {
	cout << "2: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!strcmp(tracePtr->savedTail, "NULLL")) cout << "empty" << endl;
	else cout << tracePtr->savedTail << endl;
	return true;
}

bool Event3(void*pGData) {
	cout << "3: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	cout << tracePtr->count << endl;
	return true;
}

bool Event4(void* pGData) {
	cout << "4: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << "empty" << endl;
		return true;
	}
	char max[ID_MAX_LENGTH] = "";
	for (element<L1Item<NinjaInfo>*>*temp = tracePtr->_pHead; temp; temp = temp->_pNext)
		if (strcmp(temp->ID, max) > 0)
			strcpy(max, temp->ID);

	cout << max << endl;
	return true;
}

bool Event5(ninjaEvent_t& event, void* pGData) {
	cout << event.code << ": ";
	int index = ctoi(&event.code[1]);
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count || !tracePtr->a[index].exist) {
		cout << -1 << endl;
		return true;
	}
	timelineNode<L1Item<NinjaInfo>*>* i(tracePtr->a[index].timeline->front);
	if (!i->next || (i->next &&	distanceEarth(i->data->data.latitude, i->data->data.longitude, i->next->data->data.latitude, i->next->data->data.longitude) > 0.005)) {
		char* output = new char[100];
		strPrintTime(output, i->data->data.timestamp);
		cout << output << endl;
		return true;
	}
	i = i->next;
	for (; i->next; i = i->next) {
		if (i->movingStatus == 2) {
			char* output = new char[100];
			strPrintTime(output, i->next->data->data.timestamp);
			cout << output << endl;
			return true;
		}
	}
	cout << "empty" << endl;
	return true;
}

bool Event6(ninjaEvent_t& event, void* pGData) {
	cout << event.code << ": ";
	int index = ctoi(&event.code[1]);
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count || !tracePtr->a[index].exist) {
		cout << -1 << endl;
		return true;
	}
	timelineNode<L1Item<NinjaInfo>*>* i(tracePtr->a[index].timeline->rear);
	if (!i->back) {
		cout << "Non-stop" << endl;
		return true;
	}
	for (; i->back; i = i->back) {
		if (i->movingStatus < 3 && i->back->movingStatus == 3) {
			char* output = new char[100];
			strPrintTime(output, i->back->data->data.timestamp);
			cout << output << endl;
			return true;
		}
	}
	if (distanceEarth(i->data->data.latitude, i->data->data.longitude, i->next->data->data.latitude, i->next->data->data.longitude) < 0.005) {
		char* output = new char[100];
		strPrintTime(output, i->data->data.timestamp);
		cout << output << endl;
	}
	else cout << "Non-stop" << endl;
	return true;
}

bool Event7(ninjaEvent_t& event, void* pGData) {
	cout << event.code << ": ";
	int index = ctoi(&event.code[1]);
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count || !tracePtr->a[index].exist) {
		cout << -1 << endl;
		return true;
	}
	if (tracePtr->a[index].timeline->_size == 0) {
		//WTF is this???? Really nigga?
	}
	if (tracePtr->a[index].timeline->_size == 1) {
		cout << 0 << endl;
		return true;
	}
	timelineNode<L1Item<NinjaInfo>*>* i(tracePtr->a[index].timeline->front);
	timelineNode<L1Item<NinjaInfo>*>* j = i;
	int stopTimes = 0;
	bool isWalking = 1;
	for (; i->next; i = i->next)
		if (distanceEarth(i->next->data->data.latitude, i->next->data->data.longitude, j->data->data.latitude, j->data->data.longitude) <= 0.005) {
			if (isWalking)
				stopTimes++;
			isWalking = 0;
		}
		else {
			isWalking = 1;
			j = i->next;
		}
		cout << stopTimes << endl;
		return true;
}

bool Event8(ninjaEvent_t& event, void* pGData) {
	cout << event.code << ": ";
	int index = ctoi(&event.code[1]);
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count || !tracePtr->a[index].exist) {
		cout << -1 << endl;
		return true;
	}
	cout << tracePtr->a[index].travelDistance << endl;
	return true;
}

bool Event9(void* pGData) {
	cout << "9: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << -1 << endl;
		return true;
	}
	element<L1Item<NinjaInfo>*>*temp = tracePtr->_pHead;
	if (!temp) {
		cout << -1 << endl;
		return true;
	}
	double max = 0;
	char maxID[ID_MAX_LENGTH];
	strcpy(maxID, temp->ID);
	while (temp) {
		double s = 0;
		timelineNode<L1Item<NinjaInfo>*>* i(temp->timeline->front->next);
		while (i) {
			s += distanceEarth(i->data->data.latitude, i->data->data.longitude, i->back->data->data.latitude, i->back->data->data.longitude);
			if (s > max) {
				max = s;
				strcpy(maxID, temp->ID);
			}
			i = i->next;
		}
		temp = temp->_pNext;
	}
	cout << maxID << endl;
	return true;
}

bool Event10(void* pGData) {
	cout << "10: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << -1 << endl;
		return true;
	}
	element<L1Item<NinjaInfo>*>*temp = tracePtr->_pHead;
	if (!temp) {
		cout << -1 << endl;
		return true;
	}
	double max = 0;
	char maxID[ID_MAX_LENGTH] = "";
	strcpy(maxID, temp->ID);
	while (temp) {
		double s = 0;
		int dem = 0;
		timelineNode<L1Item<NinjaInfo>*>* i(temp->timeline->front->next);
		if (!i) {
			temp = temp->_pNext;
			continue;
		}
		if (i->movingStatus == 1 && i->back->movingStatus == 3)
			s = difftime(i->data->data.timestamp, i->back->data->data.timestamp);
		while (i) {
			if (i->movingStatus == 3) {
				s += difftime(i->data->data.timestamp, i->back->data->data.timestamp);
				dem++;
			}
			i = i->next;
		}
		if (s > max) {
			max = s;
			strcpy(maxID, temp->ID);
		}
		temp = temp->_pNext;
	}
	cout << maxID << endl;
	return true;
}

bool Event11(ninjaEvent_t& event, void* pGData, L1List<NinjaInfo_t>& nList) {
	cout << event.code << ": ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << -1 << endl;
		return true;
	}
	char chunin[5];
	memcpy(chunin, &event.code[2], 4);
	chunin[4] = '\0';
	int index = ctoi(chunin);
	for (; --index >= 0;)
		if (tracePtr->a[index].exist) {
			nList._size -= tracePtr->a[index].timeline->_size;
			cout << tracePtr->a[index].ID << endl;
			tracePtr->del(index);
			return true;
		}
	cout << -1 << endl;
	return true;
}

bool Event12(void* pGData) {
	cout << "12: ";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << -1 << endl;
		return true;
	}
	element<L1Item<NinjaInfo>*>*temp = tracePtr->_pHead;
	double max = 0;
	char maxID[ID_MAX_LENGTH];
	strcpy(maxID, "-1");
	while (temp) {
		double s = 0;
		int dem = 0;
		timelineNode<L1Item<NinjaInfo>*>* i(temp->timeline->front->next);
		while (i) {
			if (i->movingStatus < 3)
			{
				s += difftime(i->data->data.timestamp, i->back->data->data.timestamp);
				dem++;
				if (s > max) {
					max = s;
					strcpy(maxID, temp->ID);
				}
			}
			i = i->next;
		}
		temp = temp->_pNext;
	}
	cout << maxID << endl;
	return true;
}

bool Event13() {
	return true;
}

bool Oops(element<L1Item<NinjaInfo>*>* temp, timelineNode<L1Item<NinjaInfo>*>* i) {
	timelineNode<L1Item<NinjaInfo>*>* j = temp->timeline->front;
	if (distanceEarth(i->data->data.latitude, i->data->data.longitude, j->data->data.latitude, j->data->data.longitude) <= 0.005) {
		cout << " " << i->data->data.id;
		return 1;
	}
	j = j->next;
	for (; j->next != i; j = j->next)
		if (j->next->movingStatus == 3)
			if (distanceEarth(i->data->data.latitude, i->data->data.longitude, j->next->data->data.latitude, j->next->data->data.longitude) <= 0.005) {
				cout << " " << i->data->data.id;
				return 1;
			}
	return 0;
}

bool Event14(void* pGData) {
	cout << "14:";
	traceArray<L1Item<NinjaInfo>*>* tracePtr = (traceArray<L1Item<NinjaInfo>*>*)pGData;
	if (!tracePtr->count) {
		cout << " -1" << endl;
		return true;
	}
	int count = 0;
	for (element<L1Item<NinjaInfo>*> *temp = tracePtr->_pHead; temp; temp = temp->_pNext) {
		if (temp->timeline->_size < 3) continue;
		timelineNode<L1Item<NinjaInfo>*>* i(temp->timeline->front->next->next);
		for (; i; i = i->next)
			if (i->movingStatus == 3)
				if (Oops(temp, i)) {
					count++;
					break;
				}
	}
	if (!count) cout << " -1" << endl;
	else cout << endl;
	//cout << count << endl;
	return true;
}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
	if (event.code[0] == '0') return Event0(event);
	if (!strcmp(event.code, "1")) return Event1(pGData);
	if (!strcmp(event.code, "2")) return Event2(pGData);
	if (!strcmp(event.code, "3")) return Event3(pGData);
	if (!strcmp(event.code, "4")) return Event4(pGData);
	if (!strcmp(event.code, "9")) return Event9(pGData);
	if (!strcmp(event.code, "10")) return Event10(pGData);
	if (!strcmp(event.code, "12")) return Event12(pGData);
	if (!strcmp(event.code, "14")) return Event14(pGData);
	// Event with long code: 5 6 7 8 11 13
	if (string(event.code).length() > 1)
		if (event.code[0] == '5') return Event5(event, pGData);
		else if (event.code[0] == '6') return Event6(event, pGData);
		else if (event.code[0] == '7') return Event7(event, pGData);
		else if (event.code[0] == '8') return Event8(event, pGData);
		else
			if (string(event.code).length() > 2)
				if (string(event.code).substr(0, 2) == "11") return Event11(event, pGData, nList);
				else if (string(event.code).substr(0, 2) == "13") return Event13();
				return false;
}

void releaseNinjaGlobalData() {}