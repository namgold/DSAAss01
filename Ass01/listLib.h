/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#define ID_MAX_LENGTH   10
using namespace std;

extern string event0;
class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;

	L1Item() : data(0), pNext(NULL) {}
	L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
public:
	L1Item<T>   *_pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {}

	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T&      at(int i);
	T&		operator[](int i);

	bool    find(T& a, int& idx);
	int     insert(int i, T& a);
	int     remove(int i);

	int     push_back(T& a);
	int     insertHead(T& a);

	int     removeHead();
	int     removeLast();

	void    reverse();
	int destroyList();
	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void	traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}

};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(a);
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}

template <class T>
T& L1List<T>::operator[](int i) {
	L1Item<T> *temp = _pHead;
	for (; i > 0; i--) temp = temp->pNext;
	return temp->data;
}

// Prototype of char[] to index
int ctoi(char* ID);
// Prototype of distance Earth calculator
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
// TraceArray classes
template <class T>
struct timelineNode {
	T data, rBack;
	// 1: Stoping
	// 2: Stoping-Start to move
	// 3: Moving
	int movingStatus;
	timelineNode<T> *next, *back;
	timelineNode(T addrNode, int movingStatus) :
		data(addrNode),
		next(0),
		back(0),
		movingStatus(movingStatus),
		rBack(0) {	}
};

template <class T>
class NinjaTimeline {
public:
	timelineNode<T> *front, *rear;
	size_t _size;
	NinjaTimeline() {
		front = 0;
		rear = 0;
		_size = 0;
	}
	// Add node hien tai
	NinjaTimeline(T addrFirstNode) {
		this->front = new timelineNode<T>(addrFirstNode, 3);
		this->rear = front;
		_size = 1;
	}
	// Add cac node tiep theo bang pNext
	void append(T addrAddNode) {
		if (this->isEmpty()) {
			cout << "Error append";
			return;
		}
		if (this->rear->movingStatus == 1) {
			if (distanceEarth(this->rear->back->data->data.latitude, this->rear->back->data->data.longitude, addrAddNode->pNext->data.latitude, addrAddNode->pNext->data.longitude) <= 0.005) {
				if (this->rear->back->movingStatus == 2)
					cout << "Hmm..." << endl;
				T p = rear->data;
				rear->data = addrAddNode->pNext;
				rear->rBack->pNext = rear->data;
				delete p;
				p = 0;
				// Status: 1
				// B4: 3
			}
			else {
				this->rear->movingStatus = 2;
				this->rear->next = new timelineNode<T>(addrAddNode->pNext, 3);
				this->rear->next->back = this->rear;
				this->rear->next->rBack = addrAddNode;
				this->rear = this->rear->next;
				_size++;
			}
		}
		else {
			if (distanceEarth(this->rear->data->data.latitude, this->rear->data->data.longitude, addrAddNode->pNext->data.latitude, addrAddNode->pNext->data.longitude) <= 0.005) this->rear->next = new timelineNode<T>(addrAddNode->pNext, 1);
			else this->rear->next = new timelineNode<T>(addrAddNode->pNext, 3);
			this->rear->next->back = this->rear;
			this->rear->next->rBack = addrAddNode;
			this->rear = this->rear->next;
			_size++;
		}
	}
	bool isEmpty() {
		if (!this) return false;
		return !this->front;
	}
};

template <class T>
class element {
public:
	bool exist;
	char ID[ID_MAX_LENGTH];
	NinjaTimeline<T>* timeline;
	element<T>* _pNext, *_pBack;
	double travelDistance;
	element() {
		exist = false;
		ID[0] = '\0';
		timeline = 0;
		_pNext = 0;
		_pBack = 0;
		travelDistance = 0;
	}
};

template <class T>
class traceArray {
public:
	element<T>* a, *_pHead, *_pTail;
	char savedHead[ID_MAX_LENGTH], savedTail[ID_MAX_LENGTH];
	int count;
	traceArray(T addrFirstNode) {
		if (!addrFirstNode) {
			strcpy(savedHead, "NULLL");
			strcpy(savedTail, "NULLL");
			return;
		}
		a = new element<T>[36 * 36 * 36 * 36]();
		int index = ctoi(addrFirstNode->data.id);
		this->a[index].exist = true;
		count = 1;
		strcpy(this->a[index].ID, addrFirstNode->data.id);
		this->a[index].timeline = new NinjaTimeline<T>(addrFirstNode);
		this->_pHead = &a[index];
		strcpy(savedHead, _pHead->ID);
		this->_pTail = this->_pHead;
		strcpy(savedTail, _pTail->ID);
		// Add nodes
		T temp = addrFirstNode;
		T p = temp->pNext;
		while (temp->pNext) {
			p = temp->pNext;
			this->add(temp);
			strcpy(savedTail, p->data.id);
			temp = p;
		}
	}
	void add(T addrAddNode) {
		// Add addrAddNode->pNext
		int index = ctoi(addrAddNode->data.id);
		int index2 = ctoi(addrAddNode->pNext->data.id);
		if (this->a[index2].exist) {
			this->a[index2].travelDistance += distanceEarth(addrAddNode->pNext->data.latitude, addrAddNode->pNext->data.longitude, this->a[index2].timeline->rear->data->data.latitude, this->a[index2].timeline->rear->data->data.longitude);
			this->a[index2].timeline->append(addrAddNode);
		}
		else {
			this->a[index2].exist = true;
			count++;
			strcpy(this->a[index2].ID, addrAddNode->pNext->data.id);
			this->a[index2].timeline = new NinjaTimeline<T>(addrAddNode->pNext);
			this->a[index2].timeline->front->rBack = addrAddNode;
			this->_pTail->_pNext = &a[index2];
			this->_pTail->_pNext->_pBack = this->_pTail;
			this->_pTail = this->_pTail->_pNext;
		}
	}
	void del(int index) {
		if (index >= 0 && index <= 36 * 36 * 36 * 36) {
			while (a[index].timeline->front->next) {
				a[index].timeline->front->next->rBack->pNext = a[index].timeline->front->next->data->pNext;

				timelineNode<T>* p = a[index].timeline->front->next;
				a[index].timeline->front->next = a[index].timeline->front->next->next;
				if (a[index].timeline->front->next) {
					a[index].timeline->front->next->back = a[index].timeline->front;
					a[index].timeline->front->next->rBack = a[index].timeline->front->data;
				}
				delete p->data;
				delete p;
				a[index].timeline->_size--;
			}
			if (a[index].timeline->front->rBack)
				a[index].timeline->front->rBack->pNext = a[index].timeline->front->data->pNext;
			delete a[index].timeline->front->data;
			delete a[index].timeline->front;
			a[index].timeline->_size--; //It should be = 0
			delete a[index].timeline;
			a[index].timeline = 0;
			count--;
			a[index].exist = 0;

			if (!count) _pHead = _pTail = 0;
			else if (!this->a[index]._pBack) {
				this->_pHead = this->_pHead->_pNext;
				this->_pHead->_pBack = 0;
			}
			else if (!this->a[index]._pNext) {
				this->_pTail = this->_pTail->_pBack;
				this->_pTail->_pNext = 0;
			}
			else {
				this->a[index]._pBack->_pNext = this->a[index]._pNext;
				this->a[index]._pNext->_pBack = this->a[index]._pBack;
				this->a[index]._pBack = 0;
				this->a[index]._pNext = 0;
			}
			strcpy(a[index].ID, "");
		}
	}

};

#endif //A01_LISTLIB_H
