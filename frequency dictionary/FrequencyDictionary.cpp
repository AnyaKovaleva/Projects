#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <cctype>
#include <algorithm>
#include "FrequencyDictionary.h"

using std::string;
using std::cout;
using std::vector;


FrequencyDictionary::FrequencyDictionary() :
	root_(nullptr),
	frequensyDict_()
{}


void FrequencyDictionary::insert(string k)
{
	if (!isWord(k)) // проверяем является ли словом
	{
		cout << "Cant add '" << k << "' becuse it contains illegal characters\n";
		return;
	}

	if (root_ == nullptr) // случай когда дерево пустое
	{
		root_ = new Node(k);
		addToDicrionary(root_, k);
	}
	else
	{
		Node *check = SEARCH(k);
		if (check != nullptr)
		{
			check->insertToNode(k); // случай когда в дереве уже есть ключ k
			addToDicrionary(check, k);
		}
		else
		{
			Node *current = root_; // случай когда k - новое слово. Ищем подходящее место для вставки
			if (current->isLeaf()) // корень - лист
			{
				current->insertToNode(k);
				split(current);
				addToDicrionary(SEARCH(k), k);
			}
			else
			{
				while (!current->isLeaf())
				{
					if (current->key[0] >= k)
					{
						current = current->first;
					}
					else
					{
						if ((current->size == 1) || ((current->size == 2) && (current->key[1]) >= k))
						{
							current = current->second;
						}
						else
						{
							current = current->third;
						}
					}
				}
				current->insertToNode(k);
				split(current);
				addToDicrionary(SEARCH(k), k);

			}
		}
	}
}

void FrequencyDictionary::INSEART(string k, int timesAdded)
{
	if (!isWord(k))
	{
		cout << "Cant add '" << k << "' becuse it contains illegal characters\n";
		return;
	}

	if (root_ == nullptr)
	{
		root_ = new Node();
		root_->insertToNode(k, timesAdded);
		addToDicrionary(root_, k);

	}
	else
	{
		Node *check = SEARCH(k);
		if (check != nullptr)
		{
			check->insertToNode(k, timesAdded);
			addToDicrionary(check, k);
		}
		else
		{
			Node *current = root_;
			if (current->isLeaf())
			{
				current->insertToNode(k, timesAdded);
				split(current);
				addToDicrionary(SEARCH(k), k);

			}
			else
			{
				while (!current->isLeaf())
				{
					if (current->key[0] >= k)
					{
						current = current->first;
					}
					else
					{
						if ((current->size == 1) || ((current->size == 2) && (current->key[1]) >= k))
						{
							current = current->second;
						}
						else
						{
							current = current->third;
						}
					}
				}
				current->insertToNode(k, timesAdded);
				split(current);
				addToDicrionary(SEARCH(k), k);

			}
		}
	}
}

void FrequencyDictionary::split(Node * node) // пункт1
{
	if (node->size >= 3)  // пункт1
	{
		Node *x = new Node;   // пункт2
		x->insertToNode(node->key[0]);
		x->first = node->first;
		x->second = node->second;
		x->parent = node->parent;
		if (x->first != nullptr)
		{
			x->first->parent = x;
		}
		if (x->second != nullptr)
		{
			x->second->parent = x;
		}


		Node *y = new Node;
		y->insertToNode(node->key[2]);
		y->first = node->third;
		y->second = node->fourth;
		y->parent = node->parent;
		if (y->first != nullptr)
		{
			y->first->parent = y;
		}
		if (y->second != nullptr)
		{
			y->second->parent = y;
		}

		if (node->parent != nullptr)  // пункт3
		{
			node->parent->insertToNode(node->key[1]);

			if (node->parent->first == node)
			{
				node->parent->first = nullptr;
			}
			else
			{
				if (node->parent->second == node)
				{
					node->parent->second = nullptr;
				}
				else
				{
					if (node->parent->third == node)
					{
						node->parent->third = nullptr;
					}

				}
			}

			if (node->parent->first == nullptr)  //  пункт 3.1
			{
				node->parent->fourth = node->parent->third;
				node->parent->third = node->parent->second;
				node->parent->second = y;
				node->parent->first = x;
			}
			else
			{
				if (node->parent->second == nullptr)  //  пункт3.2
				{
					node->parent->fourth = node->parent->third;
					node->parent->third = y;
					node->parent->second = x;
				}
				else
				{
					node->parent->fourth = y;  //  пункт3.3
					node->parent->third = x;
				}
			}
			if (node->parent->size == 3)
			{
				split(node->parent);  //  пункт3.4
			}
			delete node;

		}
		else
		{
			Node *temp = new Node; //  пункт 4
			temp->insertToNode(node->key[1]);
			if (node == root_)
			{
				root_ = temp;
			}
			else
			{
				temp->parent = node->parent;
			}
			delete node;
			temp->first = x;
			temp->second = y;

			x->parent = temp;
			y->parent = temp;
		}
	}
}


void FrequencyDictionary::printTree(Node * node, int space)
{
	if (node != nullptr)
	{
		space += 15;

		printTree(node->first, space);

		cout << std::endl;
		for (int i = 15; i < space; i++)
		{
			cout << " ";
		}
		if (node == root_)
		{
			cout << "r-> ";
		}
		if (node->size == 2)
		{
			cout << node->key[0] << "(" << node->key[0].timesAdded << ");\n";
			for (int i = 15; i < space; i++)
			{
				cout << " ";
			}
			cout << node->key[1] << "(" << node->key[1].timesAdded << ")\n";
		}
		if (node->size == 1)
		{
			cout << node->key[0] << "(" << node->key[0].timesAdded << ")" << std::endl;
		}

		printTree(node->second, space);

		printTree(node->third, space);
	}
	else
	{
		return;
	}
}

void FrequencyDictionary::printTree()
{
	if (root_ == nullptr)
	{
		cout << "Tree is emty \n";
	}
	else
	{
		printTree(root_, 0);
	}
}

void FrequencyDictionary::printDict()
{
	if (root_ == nullptr)
	{
		cout << "Dictionary is emty \n";
	}
	else
	{
		vector<Data>::iterator it = frequensyDict_.begin();
		for (int i = 0; i < frequensyDict_.size(); i++)
		{
			cout << frequensyDict_.at(i).word << "(" << frequensyDict_.at(i).timesAdded << ")" << std::endl;	
		}
	}
}

void FrequencyDictionary::printThreeMostFrequentWords()
{
	cout << "3 most frequent words:\n";
	for (int i = 0; i < 3; i++)
	{
		cout << frequensyDict_.at(i).word << " : " << frequensyDict_.at(i).timesAdded << "\n";
	}
}

Node * FrequencyDictionary::SEARCH(string key)
{
	if (root_ == nullptr) //  пункт 1
	{
		cout << "Tree is empty.\n";
		return nullptr;
	}

	Node *current = root_;
	while (current != nullptr)
	{
		if (current->find(key))//  пункт 2
		{
			return current;
		}
		if (key < current->key[0])//  пункт 3
		{
			current = current->first;
		}
		else
		{
			if (((current->size == 2) && (key < current->key[1])) || (current->size == 1))
			{
				current = current->second;
			}
			else
			{
				if (current->size == 2)
				{
					current = current->third;
				}
			}
		}
	}

	return nullptr;
}

void FrequencyDictionary::DELETE(string key)
{
	Node *node = SEARCH(key);
	if (node == nullptr) //  пункт 1
	{
		cout << "No such node in tree\n";
	}
	else
	{
		removeFromDictionary(node, key);
		Node *min = nullptr;
		if (node->key[0] == key) //  пункт 2
		{
			min = findMin(node->second);
		}
		else
		{
			min = findMin(node->third);
		}

		if (min != nullptr) //  пункт 3
		{
			if (node->key[0] == key)
			{
				node->key[0] = min->key[0];
			}
			else
			{
				node->key[1] = min->key[0];
			}
			min->removeFromNode(min->key[0], min->key[0].timesAdded);
			fix(min);
		}
		else
		{
			if (node->key[0] == key) //  пункт 4
			{
				node->removeFromNode(node->key[0], node->key[0].timesAdded);
			}
			else
			{
				node->removeFromNode(node->key[1], min->key[1].timesAdded);
			}
			fix(node);
		}

	}
}


Node * FrequencyDictionary::findMin(Node *node)
{
	if (node == nullptr)
	{
		return node;
	}
	if (node->first == nullptr)
	{
		return node;
	}
	else
	{
		return findMin(node->first);
	}
}


Node * FrequencyDictionary::fix(Node * node)
{
	if (node->size == 0 && node->parent == nullptr)
	{
		delete node;
		return nullptr;
	}

	if (node->size != 0)
	{
		if (node->parent != nullptr)
		{
			return fix(node->parent);
		}
		else
		{
			return node;
		}
	}

	Node *parent = node->parent;
	if ((parent->first->size == 2) || (parent->second->size == 2) || (parent->size == 2))
	{
		node = redestribute(node);
	}
	else
	{
		if (parent->size == 2 && parent->third->size == 2)
		{
			node = redestribute(node);
		}
		else
		{
			node = merge(node);
		}
	}
	return fix(node);
}


Node * FrequencyDictionary::redestribute(Node* node)
{
	Node *parent = node->parent;
	Node *first = parent->first;
	Node *second = parent->second;
	Node *third = parent->third;

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) { //  пункт 1
		if (first == node) { //  пункт 1.1
			parent->first = parent->second;
			parent->second = parent->third;
			parent->third = nullptr;
			parent->first->insertToNode(parent->key[0], parent->key[0].timesAdded);
			parent->first->third = parent->first->second;
			parent->first->second = parent->first->first;

			if (node->first != nullptr) parent->first->first = node->first;
			else if (node->second != nullptr) parent->first->first = node->second;

			if (parent->first->first != nullptr) parent->first->first->parent = parent->first;

			parent->removeFromNode(parent->key[0], parent->key[0].timesAdded);
			delete first;
		}
		else if (second == node) { //  пункт 1.2
			first->insertToNode(parent->key[0], parent->key[0].timesAdded);
			parent->removeFromNode(parent->key[0], parent->key[0].timesAdded);
			if (node->first != nullptr) first->third = node->first;
			else if (node->second != nullptr) first->third = node->second;

			if (first->third != nullptr) first->third->parent = first;

			parent->second = parent->third;
			parent->third = nullptr;

			delete second;
		}
		else if (third == node) {//  пункт 1.3
			second->insertToNode(parent->key[1], parent->key[1].timesAdded);
			parent->third = nullptr;
			parent->removeFromNode(parent->key[1], parent->key[1].timesAdded);
			if (node->first != nullptr) second->third = node->first;
			else if (node->second != nullptr) second->third = node->second;

			if (second->third != nullptr)  second->third->parent = second;

			delete third;
		}
	}
	else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) { //  пункт 2
		if (third == node) { //  пункт 2.1
			if (node->first != nullptr) {
				node->second = node->first;
				node->first = nullptr;
			}

			node->insertToNode(parent->key[1], parent->key[1].timesAdded);
			if (second->size == 2) {
				parent->key[1] = second->key[1];
				second->removeFromNode(second->key[1], second->key[1].timesAdded);
				node->first = second->third;
				second->third = nullptr;
				if (node->first != nullptr) node->first->parent = node;
			}
			else if (first->size == 2) {
				parent->key[1] = second->key[0];
				node->first = second->second;
				second->second = second->first;
				if (node->first != nullptr) node->first->parent = node;

				second->key[0] = parent->key[0];
				parent->key[0] = first->key[1];
				first->removeFromNode(first->key[1], first->key[1].timesAdded);
				second->first = first->third;
				if (second->first != nullptr) second->first->parent = second;
				first->third = nullptr;
			}
		}
		else if (second == node) { //  пункт 2.2
			if (third->size == 2) {
				if (node->first == nullptr) {
					node->first = node->second;
					node->second = nullptr;
				}
				second->insertToNode(parent->key[1], parent->key[1].timesAdded);
				parent->key[1] = third->key[0];
				third->removeFromNode(third->key[0], third->key[0].timesAdded);
				second->second = third->first;
				if (second->second != nullptr) second->second->parent = second;
				third->first = third->second;
				third->second = third->third;
				third->third = nullptr;
			}
			else if (first->size == 2) {
				if (node->second == nullptr) {
					node->second = node->first;
					node->first = nullptr;
				}
				second->insertToNode(parent->key[0], parent->key[0].timesAdded);
				parent->key[0] = first->key[1];
				first->removeFromNode(first->key[1], first->key[1].timesAdded);
				second->first = first->third;
				if (second->first != nullptr) second->first->parent = second;
				first->third = nullptr;
			}
		}
		else if (first == node) { //  пункт 2.3
			if (node->first == nullptr) {
				node->first = node->second;
				node->second = nullptr;
			}
			first->insertToNode(parent->key[0], parent->key[0].timesAdded);
			if (second->size == 2) {
				parent->key[0] = second->key[0];
				second->removeFromNode(second->key[0], second->key[0].timesAdded);
				first->second = second->first;
				if (first->second != nullptr) first->second->parent = first;
				second->first = second->second;
				second->second = second->third;
				second->third = nullptr;
			}
			else if (third->size == 2) {
				parent->key[0] = second->key[0];
				second->key[0] = parent->key[1];
				parent->key[1] = third->key[0];
				third->removeFromNode(third->key[0], third->key[0].timesAdded);
				first->second = second->first;
				if (first->second != nullptr) first->second->parent = first;
				second->first = second->second;
				second->second = third->first;
				if (second->second != nullptr) second->second->parent = second;
				third->first = third->second;
				third->second = third->third;
				third->third = nullptr;
			}
		}
	}
	else if (parent->size == 1) { //  пункт 3
		node->insertToNode(parent->key[0]);

		if (first == node && second->size == 2) { //  пункт 3.1
			parent->key[0] = second->key[0];
			second->removeFromNode(second->key[0], second->key[0].timesAdded);

			if (node->first == nullptr) node->first = node->second;

			node->second = second->first;
			second->first = second->second;
			second->second = second->third;
			second->third = nullptr;
			if (node->second != nullptr) node->second->parent = node;
		}
		else if (second == node && first->size == 2) { // пункт 3.2
			parent->key[0] = first->key[1];
			first->removeFromNode(first->key[1], first->key[1].timesAdded);

			if (node->second == nullptr) node->second = node->first;

			node->first = first->third;
			first->third = nullptr;
			if (node->first != nullptr) node->first->parent = node;
		}
	}
	return parent;
}


Node * FrequencyDictionary::merge(Node * node)
{
	Node *parent = node->parent;

	if (parent->first == node) { //  пункт 1
		parent->second->insertToNode(parent->key[0], parent->key[0].timesAdded);
		parent->second->third = parent->second->second;
		parent->second->second = parent->second->first;

		if (node->first != nullptr) parent->second->first = node->first;
		else if (node->second != nullptr) parent->second->first = node->second;

		if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

		parent->removeFromNode(parent->key[0], parent->key[0].timesAdded);
		delete parent->first;
		parent->first = nullptr;
	}
	else if (parent->second == node) { //  пункт 2
		parent->first->insertToNode(parent->key[0], parent->key[0].timesAdded);

		if (node->first != nullptr) parent->first->third = node->first;
		else if (node->second != nullptr) parent->first->third = node->second;

		if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

		parent->removeFromNode(parent->key[0], parent->key[0].timesAdded);
		delete parent->second;
		parent->second = nullptr;
	}

	if (parent->parent == nullptr) { //  пункт 3
		Node *temp = nullptr;
		if (parent->first != nullptr) temp = parent->first;
		else temp = parent->second;
		temp->parent = nullptr;
		delete parent;
		root_ = temp;
		return temp;
	}
	return parent;
}


void FrequencyDictionary::deleteTree(Node * node)
{
	if (node->first != nullptr)
	{
		deleteTree(node->first);
	}
	if (node->second != nullptr)
	{
		deleteTree(node->second);
	}
	if (node->third != nullptr)
	{
		deleteTree(node->third);
	}
	if (node->size == 2)
	{
		delete node;
	}
	else
	{
		if (node->size == 1)
		{
			delete node;
		}
	}

}


void FrequencyDictionary::deleteTree()
{
	deleteTree(root_);
}


bool FrequencyDictionary::isWord(string& k)
{
	if (((*k.begin() == '(') || (*k.begin() == '"')) && (k.size() > 1))
	{
		k.erase(k.begin());
	}
	if ((*k.begin() == '"') && (k.size() > 1))
	{
		k.erase(k.begin());
	}
	if (((k[k.size() - 1] == ')') || (k[k.size() - 1] == ',') || (k[k.size() - 1] == '.') || (k[k.size() - 1] == '!') || (k[k.size() - 1] == '?') || (k[k.size() - 1] == ':') || (k[k.size() - 1] == ';') || (k[k.size() - 1] == '"')) && (k.size() > 1))
	{
		k.erase(k.size() - 1);
	}
	if (((k[k.size() - 1] == ')') || (k[k.size() - 1] == '"')) && (k.size() > 1))
	{
		k.erase(k.size() - 1);
	}
	if ((k[k.size() - 1] == '"') && (k.size() > 1))
	{
		k.erase(k.size() - 1);
	}
	transform(k.begin(), k.end(), k.begin(), ::tolower);
	int sign = 0;
	for (int i = 0; k[i] != '\0'; i++)
	{
		if (isalpha(k[i]) == 0)
		{
			if ((k[i] == '-'))
			{
				if (!((i != 0) && (isalpha(k[i - 1]) != 0) && (isalpha(k[i + 1]) != 0)))
				{
					return false;
				}
			}
			else
			{
				if (k[i] == 39 && (sign == 0)) // 39 = '
				{
					sign++;
					if (!((i == (k.size() - 2)) && (isalpha(k[i - 1]) != 0) && (isalpha(k[i + 1]) != 0)))
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}


		}
	}
	return true;

}

void FrequencyDictionary::addToDicrionary(Node * node, string key)
{
	if (node != nullptr)
	{
		vector<Data>::iterator it = frequensyDict_.begin();
		bool found = false;
		int j = 0;
		if ((node->size == 2) && (node->key[1] == key))
		{
			j = 1;
		}
		for (int i = 0 ; it != frequensyDict_.end(); it ++, i++)
		{
			if (frequensyDict_.at(i) == node->key[j])
			{
				frequensyDict_.at(i) = node->key[j];
				found = true;
				break;
			}
		}
		if (!found)
		{
			frequensyDict_.push_back(node->key[j]);
		}
		struct greater_than_key
		{
			inline bool operator() (const Data& data1, const Data& data2)
			{
				return (data1.timesAdded > data2.timesAdded);
			}
		};
		std::sort(frequensyDict_.begin(), frequensyDict_.end(), greater_than_key());
	}
}

void FrequencyDictionary::removeFromDictionary(Node * node, string key)
{
	if (node != nullptr)
	{
		vector<Data>::iterator it = frequensyDict_.begin();
		bool found = false;
		int j = 0;
		if ((node->size == 2) && (node->key[1] == key))
		{
			j = 1;
		}
		for (int i = 0; it != frequensyDict_.end(); it++, i++)
		{
			if (frequensyDict_.at(i) == node->key[j])
			{
				frequensyDict_.at(i) = node->key[j];
				found = true;
				break;
			}
		}
		if (found)
		{
			frequensyDict_.erase(it);
		}
		struct greater_than_key
		{
			inline bool operator() (const Data& data1, const Data& data2)
			{
				return (data1.timesAdded > data2.timesAdded);
			}
		};
	}
}


FrequencyDictionary::~FrequencyDictionary()
{
	if (root_ != nullptr)
	{
		deleteTree();
	}
}


Node::Node(string k) :
	size(1),
	key{ {k}, {}, {} },
	first(nullptr),
	second(nullptr),
	third(nullptr),
	fourth(nullptr),
	parent(nullptr)
{}


Node::Node() :
	size(0),
	key{},
	first(nullptr),
	second(nullptr),
	third(nullptr),
	fourth(nullptr),
	parent(nullptr)
{}


void Node::sort()
{
	if (size == 1)
	{
		return;
	}
	if (size == 2)
	{
		if (key[0] > key[1])
		{
			std::swap(key[0], key[1]);
		}
	}
	if (size == 3)
	{
		if (key[0] > key[1])
		{
			std::swap(key[0], key[1]);
		}
		if (key[0] > key[2])
		{
			std::swap(key[0], key[2]);
		}
		if (key[1] > key[2])
		{
			std::swap(key[1], key[2]);
		}
	}
}


void  Node::insertToNode(string k)
{
	if (find(k))
	{
		if (k == key[0])
		{
			key[0].timesAdded++;
		}
		if (k == key[1])
		{
			key[1].timesAdded++;
		}
	}
	else
	{
		key[size] = k;
		size++;
		sort();
	}

}

void Node::insertToNode(string k, int timesAdded)
{
	Data newData(k);
	if (find(k))
	{
		if (k == key[0])
		{
			key[0].timesAdded = timesAdded + 1;
		}
		if (k == key[1])
		{
			key[1].timesAdded = timesAdded + 1;
		}
	}
	else
	{
		key[size] = k;
		key[size].timesAdded = timesAdded;
		size++;
		sort();
	}
}

void  Node::insertToNode(Data k)
{
	if (find(k))
	{
		if (k == key[0])
		{
			key[0].timesAdded++;
		}
		if (k == key[1])
		{
			key[1].timesAdded++;

		}
	}
	else
	{
		key[size] = k;
		size++;
		sort();
	}

}

void  Node::insertToNode(Data k, int timesAdded)
{
	if (find(k))
	{
		if (k == key[0])
		{
			key[0].timesAdded = timesAdded + 1;
		}
		if (k == key[1])
		{
			key[1].timesAdded = timesAdded + 1;
		}
	}
	else
	{
		key[size] = k;
		key[size].timesAdded = timesAdded;
		size++;
		sort();
	}
}


bool  Node::isLeaf()
{
	return (first == nullptr) && (second == nullptr) && (fourth == nullptr);
}


bool Node::find(Data k)
{
	for (int i = 0; i < size; i++)
	{
		if (key[i] == k)
		{
			return true;
		}
	}
	return false;
}


void  Node::removeFromNode(Data k)
{
	if ((k == key[0] && key[0].timesAdded == 1) || (k == key[1] && key[1].timesAdded == 1) || (k == key[2] && key[2].timesAdded == 1))
	{
		if (k == key[0])
		{
			key[0].timesAdded--;
		}
		if (k == key[1])
		{
			key[1].timesAdded--;
		}
		if (k == key[2])
		{
			key[2].timesAdded--;
		}
		if (size >= 1 && key[0] == k) {
			key[0] = key[1];
			key[1] = key[2];
			size--;
		}
		else if (size == 2 && key[1] == k) {
			key[1] = key[2];
			size--;
		}
	}
	else
	{
		if (k == key[0])
		{
			key[0].timesAdded--;
		}
		if (k == key[1])
		{
			key[1].timesAdded--;
		}
		if (k == key[2])
		{
			key[2].timesAdded--;
		}
	}

}


void Node::removeFromNode(Data k, int timesAdded)
{

	if (k == key[0])
	{
		key[0].timesAdded -= timesAdded;
	}
	if (k == key[1])
	{
		key[1].timesAdded -= timesAdded;
	}
	if (k == key[2])
	{
		key[2].timesAdded -= timesAdded;
	}
	if (size >= 1 && key[0] == k) {
		key[0] = key[1];
		key[1] = key[2];
		size--;
	}
	else if (size == 2 && key[1] == k) {
		key[1] = key[2];
		size--;
	}

}


Data::Data(string k) :
	word(k),
	timesAdded(1)
{}

Data::Data() :
	word(""),
	timesAdded(0)
{}

int Data::compare(string word1, string word2)
{
	if (word1 == word2)
	{
		return 0;
	}
	for (int i = 0; word1[i] != '\0' || word2[i] != '\0'; i++)
	{
		if (word1[i] < word2[i])
		{
			return -1;
		}
		if (word1[i] > word2[i])
		{
			return 1;
		}
	}
	if (word1.size() > word2.size())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool Data::operator < (Data &other)
{
	if (compare(word, other.word) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool operator < (string &str, Data &data)
{
	if (data.compare(str, data.word) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Data::operator > (Data &other)
{
	if (compare(word, other.word) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator > (string &str, Data &data)
{
	if (data.compare(str, data.word) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Data::operator <= (string other)
{
	if (compare(word, other) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Data::operator >= (string other)
{
	if (compare(word, other) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Data::operator == (string other)
{
	return (word == other);
}
bool operator == (Data &dataL, Data &dataR)
{
	return (dataL.word == dataR.word);
}
bool operator == (string &other, Data& data)
{
	return (other == data.word);
}

std::ostream& operator<<(std::ostream & out, Data &data)
{
	out << data.word;
	return out;
}

