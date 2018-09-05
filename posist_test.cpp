#include<bits/stdc++.h>
using namespace std;

class Node{
public:
	int nodeNumber;		//Node Number
	int data;			//Data
	string nodeId;		//Node Id equals Node Number but stored in string form
	Node* refNodeId;		//parent Node Id address
	vector<Node*> childRef;		//Child Node Ids address
	Node* genNodeId;		//Genesis Node Id address
	
	//Constructor to initialize Node
	Node(int num,int d,Node* ref,Node* gen){
		nodeNumber = num;
		data = d;
		nodeId = to_string(nodeNumber);
		refNodeId = ref;
		genNodeId = gen;
	}
	
	int getSumChild(){
		int val = 0;
		for(auto i = childRef.begin();i!=childRef.end();i++){
			val += (*i)->data;
		}
		return val;
	}
};
class Hash{
public:
	int ownerId;
	int value;
	string name;
	Hash(){
	}
	Hash(int owner,int val,string n1){
		ownerId = owner;
		value = val;
		name = n1;
	}
};

class Data{
public:
	int ownerId;
	int value;
	string ownerName;
	Hash h;
	Data(int o,int v,string n,Hash h1){
		ownerId = o;
		value = v;
		ownerName = n;
		h = h1;
	}
};
int longestChain(Node* p){
	if(p == NULL){
		return 0;
	}
	if(p->childRef.size() == 0){
		return 1;
	}
	int longest= INT_MIN;
	for(auto i = p->childRef.begin();i!=p->childRef.end();i++){
		longest = max(longest,longestChain(*i));
	}
	return longest + 1;
}

/** Adds Node to given Parent Node **/
bool addNode(int data,Node* p,int num,Node* gen){
	Node* r;
	if(data + p->getSumChild() < p->data){
		r = new Node(num,data,p,gen);
		p->childRef.push_back(r);
		return true;
	}
	for(auto i = p->childRef.begin();i!=p->childRef.end();i++){
		bool flag = addNode(data,*i,num,gen);
		if(flag){
			return true;
		}
	}
	return false;
}

/** Adds Node to certain Node and return false if not possible **/
bool addToCertainNode(int data,Node* p,int num,Node* gen){
	Node* r;
	if(data + p->getSumChild() < p->data){
		r = new Node(num,data,p,gen);
		p->childRef.push_back(r);
		return true;
	}
	return false;
}
void mergeNode(Node* node1,Node* node2){
	if(longestChain(node1) > longestChain(node2)){
		node1->data += node2->data;
		delete node2;
		return ;
	}
	node1->data += node2->data;
	delete node2;
}

/** Finding Node with given data and address of genesis node or parent node **/
Node* findNode(int data,Node* check){
	if(check->data == data){
		return p;
	}
	if(check == NULL){
		return NULL;
	}
	for(auto i = check->childRef.begin(); i!= check->childRef.end(); i++){
		if((*i)->data == data){
			return *i;
		}
	}
	if(check->childRef.size() == 0){
		return NULL;
	}
	Node* x;
	for(auto i = check->childRef.begin(); i!= check->childRef.end(); i++){
		 x = findNode(*i);
	}
	return x;
}

int main(){
	int num = 0;
	int data;
	cout<<"Enter Data for genesis node : ";
	cin>>data;
	Node gen(++num,data,NULL,NULL);
	int values;
	do{
		cout<<"Options Possible :"<<endl;
		cout<<"1 : Add Node to genesis node"<<endl;
		cout<<"Enter value : ";
		cin>>values;
		switch(values){
			case 1: 
				cout<<"Enter data : ";
				cin>>data;
				bool add = addNode(data,&gen,++num,&gen);
				add ? cout<<"Add Successful"<<endl : cout<<"Add Not Possible"<<endl;
				break;
			
		} 
	}
	while(values != 6);
	return 0;
}

