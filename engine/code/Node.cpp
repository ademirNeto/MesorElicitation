#include "stdafx.h"
#include "Node.h"

//Memory Leak Detection Enabling    
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif
#include "General_Auxiliar.h"

namespace Engine{
Node::~Node(void){
	//if(this->density!=NULL){
	//	delete this->density;
	//	this->density = NULL;
	//}
	int n = this->getChildrenCount();
	for(int i=0; i<n; i++){
		delete this->getChild(i);
	}
	this->children.clear();
	this->parents.clear();
//	delete(this);
}

void Node::addChild(Node* child){
	//General_Auxiliar::addSortedNodes(this->children, child);
	this->children.push_back(child);
	child->addParent(this);
	if(this->generation >= child->getGeneration()){
		child->setGeneration(this->generation+1);
		child->updateDescendents();
	}

}
void Node::addChild(Node* child, bool isOrdered){
	child->addParent(this);
	this->children.push_back(child);
	child->setGeneration(this->generation+1);
}
void Node::addParent(Node* parent){
	//General_Auxiliar::addSortedNodes(this->parents, parent);
	this->parents.push_back(parent);
}

Node::Node(double lower, double center, double upper, double credibility){
//	this->density = NULL;
//	General_Auxiliar::nodesToDelete.push_back(this);
	this->center = center;
	this->id=General_Auxiliar::id;
	this->children.resize(0);
	this->generation = 0;
	General_Auxiliar::id++;
	char string[4000];
	_itoa(this->id,  string, 1000); 
	this->label = "X";
	if (this->id<10)
		this->label+="000"; 
	else if (this->id<100)
		this->label+="00"; 
	else if (this->id<1000)
		this->label+="0"; 
	this->label +=string;
	this->lower = lower;
	this->upper = upper;
	this->credibility =credibility;
	this->xSize = 0;
}
Node::Node(){
//	General_Auxiliar::nodesToDelete.push_back(this);
	this->id=General_Auxiliar::id;
	this->children.resize(0);
	this->generation = 0;
	General_Auxiliar::id++;
	char string[4000];
	_itoa(this->id,  string, 1000); 
	this->label = "X";
	if (this->id<10)
		this->label+="000"; 
	else if (this->id<100)
		this->label+="00"; 
	else if (this->id<1000)
		this->label+="0"; 
	this->label +=string;
}
Node::Node(string label){
//	General_Auxiliar::nodesToDelete.push_back(this);
	this->id=General_Auxiliar::id;
	this->generation = 0;
	General_Auxiliar::id++;
	this->label = label;
}
int Node::getGeneration(){
	return this->generation;
}
int Node::getId(){
	return this->id;
}
string Node::getLabel(){
	return this->label;
}
vector<Node*> Node::getParents(){
	return this->parents;
}
vector<Node*> Node::getChildren(){
	return this->children;
}
int Node::getChildrenCount(){
	return this->children.size();
}
int Node::getParentsCount(){
	int n = this->parents.size();
	return n;
}
bool Node::isAdded() {
	return added;
}

Node* Node::getChild(int index){
	return this->children[index];
}
int Node::getOrder(){
	return this->order;
}

Node* Node::getParent(int index){
	return this->parents[index];
}
Node* Node::getParent(double lower, double upper, int index){
	return this->parents[index];
}
void Node::readAllNodes(vector<Node*> vec){
	int n = vec.size();
	for (int i=0; i<n; i++)
		cout<<vec[i]->getLabel()<<", ";
	cout<<endl;
}


void Node::readCharacteristics(){
	cout<<this->getId()<<": "<<this->getLabel()<<endl;
	int pSize=this->parents.size();
	int cSize=this->children.size();
	cout<<"parents: (";
	for(int i=0; i<pSize; i++)
		cout<<this->getParent(i)->getLabel()<<", ";
	cout<<")"<<endl;
	cout<<"children: (";
	for(int i=0; i<cSize; i++)
		cout<<this->getChild(i)->getLabel()<<", ";
	cout<<")"<<endl;
	//for(int i=0; i<cSize; i++)
	//	this->getChild(i)->readBBN();
}
void Node::removeChildren(){
	int n = this->getChildrenCount();
	for(int i=0; i<n; i++){
		Node* chi = this->children[i];
		chi->removeChildren();
		delete chi;
	}
	this->children.clear();
}

void Node::removeChild(int index){
	this->children.erase(this->children.begin()+index);
}

void Node::removeChild(Node* node){
	General_Auxiliar::removeSortedNodes(this->children, node);
	node->removeParent(this);
}
void Node::removeParent(Node* node){
	General_Auxiliar::removeSortedNodes(this->parents, node);
}

//SETTING ATTRIBUTES
void Node::setLabel(string label){
	this->label=label;
}
void Node::setOrder(int order){
	this->order = order;
}
void Node::setAdded(bool added) {
	this->added = added;
}
void Node::setGeneration(int generation){
	this->generation = generation;
}

void Node::setId(int id){
	this->id=id;
}
void Node::updateDescendents(){
	int nC = this->getChildrenCount();
	int thisUpdatedGeneration = this->generation;
	for(int i=0; i<nC; i++){
		Node* ci = this->getChild(i);
		if(thisUpdatedGeneration == ci->getGeneration()){
			ci->setGeneration(thisUpdatedGeneration+1);
			ci->updateDescendents();
		}
	}
	if(thisUpdatedGeneration>General_Auxiliar::maxGeneration)
		General_Auxiliar::maxGeneration = thisUpdatedGeneration;
}

}