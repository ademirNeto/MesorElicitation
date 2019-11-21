#pragma once

#ifndef NODE_H
#define NODE_H
#include<iostream>
#include<string>
#include<vector>
//#include"NonParametric.h"

namespace Engine{
	using namespace std;
	class Node {
	protected:
		int id, order, generation;
		bool added;
		string label;
		vector<Node*> children, parents;
		void addParent(Node* parent);
		void updateDescendents();
	public:
		//NonParametric* density;
		string str_xfx, str_pair;
		int xSize;
		double lower, upper, center, credibility;
		void setGeneration(int generation);
		bool wasVisited;
		char	NODE_TYPE; 
		void addChild(Node* child);
		void addChild(Node* child, bool isOrdered);
		virtual ~Node(void);
		Node(double lower, double center, double upper, double credibility);
		Node();
		Node(string label);
		string getLabel();
		int getId();
		vector<Node*> getParents();
		vector<Node*> getChildren();
		int getChildrenCount();
		int getParentsCount();
		Node* getChild(int index);
		int getGeneration();
		int getOrder();
		Node* getParent(int index);
		Node* getParent(double lower, double upper, int index);
		bool isAdded();
		void removeChildren();
		void removeChild(int index);
		void removeChild(Node* node);
		void removeParent(Node* node);
		void setAdded(bool added);
		void setId(int id);
		void setLabel(string pLabel);
		void setOrder(int order);
		void readAllNodes(vector<Node*> vec);
		void readCharacteristics();
	};
}

#endif
