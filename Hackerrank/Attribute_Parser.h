#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <regex>



// A HRML Node in the tree. It consists of 2 maps:
// >	nodes - The nodes, consisting of the parent node, and child node(s)
// >	attributes - Attributes associated with this node
struct HRML_Node {
	std::unordered_map <std::string, HRML_Node* > nodes;
	std::unordered_map <std::string, std::string > attributes;
};



//	Function declaration
std::vector< std::pair<std::string, std::string> > parseAttributes(const std::string&);
std::pair< std::string, std::string> seperateTagNameAndAttribute(const std::string&);
std::pair< std::vector<std::string>, std::string > parseQuery(const std::string&);


void attribute_parser() {

	int N, Q;
	std::cin >> N >> Q;

	std::string line;
	std::getline( std::cin, line );		//	Since last reading of 2 integers, the newline character \n hasn't been eliminated

	//	The root of the HRML tree
	HRML_Node* root = new HRML_Node();
	HRML_Node* curr = root;

	while (N-- > 0) {
		std::getline( std::cin, line );

		//	If the line is actually a closing tag
		//	Since assumed correctly nested, just exit to the parent node.
		if (line[1] == '/') {
			curr = curr->nodes.at("parent");
		}

		//	Otherwise, it shall be a opening tag which may have attributes. Capture the name of the tag, and
		//	the attributes to put into the node.
		else {

			//	Obtain the pair of tagName and attributes - (unparsed)
			std::pair< std::string, std::string > seperated = seperateTagNameAndAttribute(line);
		
			std::string& tagName = seperated.first;
			//	Obtain the vector of attribute key and value pairs
			std::vector< std::pair<std::string, std::string> > attributePairs = parseAttributes( seperated.second );

			//	New node to be inserted
			HRML_Node* newNode = new HRML_Node();
			//	Set the parent to point to the current node.
			newNode->nodes["parent"] = curr;
			//	Add the new node to the current node's node list
			curr->nodes[tagName] = newNode;

			//	Insert key value pairs for attributes into the newNode
			for (std::pair< std::string, std::string> p : attributePairs) {
				newNode->attributes[ p.first ] = p.second;
			}

			//	Traverse into the new Node
			curr = newNode;
		}
	}


	while (Q-- > 0) {
		std::getline( std::cin, line);

		//	Will return a pair, which first is the vector of strings consisting of tagNames, chained together will form a path
		//	second is the name of attribute to find
		std::pair< std::vector<std::string>, std::string > pairs = parseQuery(line);

		//	Start from the root
		HRML_Node* curr = root;

		//	Traverse the tagNames
		for (std::string s : pairs.first) {
			std::unordered_map< std::string, HRML_Node*>::const_iterator ifContain = curr->nodes.find(s);

			//	If it points to end(), means the tagName is not found. We will print Not Found, and set pointer to NULL, break.
			if (ifContain == curr->nodes.end()) {
				curr = nullptr;
				std::cout << "Not Found!" << "\n";
				break;
			}
			else {
				curr = ifContain->second;
			}
		}

		//	curr pointer is NULL only if traversing one of the tagNames failed. 
		if (curr != nullptr) {
			std::unordered_map< std::string, std::string>::const_iterator ifAttr = curr->attributes.find(pairs.second);
			if (ifAttr == curr->attributes.end()) {
				std::cout << "Not Found!" << "\n";
			}
			else {
				std::cout << ifAttr->second << "\n";
			}
		}
	}
}


//	Seperate the tagName and attributes string into a pair
std::pair< std::string, std::string> seperateTagNameAndAttribute(const std::string& str) {
	static std::regex HTML_regex = std::regex("<(\\S+)\\s*(.*)>");
	static std::smatch matches;

	std::regex_match(str, matches, HTML_regex);

	return std::make_pair(matches[1], matches[2]);
}

//	Take in a string consisting of attributes. Will parse it and return a vector of key value pairs
std::vector< std::pair<std::string, std::string> > parseAttributes(const std::string& str) {
	std::vector < std::pair<std::string, std::string> > pairs;
	static std::regex attributeRegex("(\\S+?)\\s*?=\\s*?\"(.*?)\"");
	static std::smatch matches;
	std::string copy = str;				//	Uses copy constructor to copy the string

	while (std::regex_search(copy, matches, attributeRegex) ) {
		pairs.emplace_back( std::make_pair(matches[1], matches[2] ) );

		copy = matches.suffix().str();
	}

	return pairs;
}


//	Take in a query string, return a pair of
//	1. Vector of tagName(s) in order
//	2. The attribute name
std::pair< std::vector<std::string> , std::string > parseQuery(const std::string& str) {
	static std::regex pathRegex("(.*)~(.*)");
	static std::regex tagNameRegex("(\\w+)");
	static std::smatch matches;

	std::vector<std::string> vector = std::vector<std::string>();

	std::regex_match(str, matches, pathRegex);
	std::string path = matches[1];
	std::string attr = matches[2];
	
	while (std::regex_search(path, matches, tagNameRegex)) {
		vector.push_back( matches[1] );
		path = matches.suffix().str();
	}

	return std::make_pair(vector, attr);
}