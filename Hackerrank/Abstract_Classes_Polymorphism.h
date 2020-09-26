#pragma once

//https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem

#include <iostream>
#include <string>
#include <unordered_map>


//	Key and value must be stored. Value to retrieve the value itself, key to use in deletion of the key value pair in the map
struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
	std::unordered_map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};



class LRUCache : public Cache {
public:
	//	Constructor. Set to an empty linked list of size 0
	LRUCache(int c) : Cache(), size(0) {
		cp = c;
		tail = nullptr;
		head = nullptr;
	}

	//	Get the value of the node with the key K
	virtual int get(int k) {
		if (mp.count(k)) {
			return mp.at(k)->value;
		}
		return -1;
	}

	virtual void set(int k, int v) {

		//	If the key is present in the cache, move the node to the head of linked list.
		if (mp.count(k)) {
			Node* tomove = mp.at(k);
			tomove->value = v;

			if (size == 1) return;

			//	Deattaching from the tomove's next and previous
			if (tomove->next)
				tomove->next->prev = tomove->prev;
			if (tomove->prev)
				tomove->prev->next = tomove->next;

			//	Attaching the tomove to the head of linked list.
			head->next = tomove;
			tomove->prev = head;
			head = tomove;
		}
		//	If the key is not present in the cache, insert into the head of the linked list. If exceeds the size, remove last
		else {
			Node* toinsert = new Node(k, v);
			
			if (head == nullptr) {
				head = toinsert;
				tail = toinsert;
			}
			else {
				head->next = toinsert;
				toinsert->prev = head;
				head = toinsert;
			}
			mp[k] = toinsert;
			size++;

			if (size > cp) {
				deleteLast();
			}
		}
	}

private:
	int size;

	//	Helper method that deletes the node at the tail of the linked list
	void deleteLast() {
		if (size == 0) return;
		if (size == 1) {
			mp.clear();
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* todel = tail;
			tail = todel->next;
			tail->prev = nullptr;

			mp.erase(todel->key);
			delete todel;
		}
		size--;
	}
};