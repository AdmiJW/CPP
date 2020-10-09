#pragma once


#include <vector>
#include <algorithm>
#include <string>
#include <iostream>



class Message {
private:
	std::string msg;
	int order;			//Other than message itself, we need to keep an variable like id to maintain the order
public:
	Message(int order, const std::string& s) : order(order), msg(s) {}

	std::string get_text() {
		return msg;
	}

	//	Operator overloading for sorting
	bool operator< (const Message& another) {
		return this->order < another.order;
	}
};


class MessageFactory {
private:
	int next_order;
public:
	MessageFactory() : next_order(1) {}
	Message create_message( const std::string& text ) {
		Message msg(next_order++, text);
		return msg;
	}
};




class Recipent {
private:
	std::vector< Message > messages;
	void fix_order() {
		std::sort(messages.begin(), messages.end());
	}

public:
	Recipent() {}
	void receive(const Message& msg) {
		messages.push_back(msg);
	}
	void print_messages() {
		fix_order();
		for (Message& m : messages) {
			std::cout << m.get_text() << "\n";
		}
		messages.clear();
	}
};


class Network {
public:
	static void send_messages(std::vector<Message&> messages, Recipent& recipent) {
		std::random_shuffle(messages.begin(), messages.end());
		for (Message& m : messages) {
			recipent.receive(m);
		}
	}
};