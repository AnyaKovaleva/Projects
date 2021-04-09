#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;


struct Data
{
	string word; // слово
	int timesAdded = 0; // сколько раз это слово встретилось
	Data(string k);
	Data();
	int compare(string word1, string word2); // сравнивает 2 слова
	bool operator < (Data &other);
	friend bool operator< (string &str, Data &data);
	bool operator > (Data &other);
	friend bool operator > (string &str, Data &data);
	bool operator <= (string other);
	bool operator >= (string other);
	bool operator == (string other);
	friend bool operator == (Data &dataL, Data &dataR);
	friend bool operator == (string &other, Data& data);
	friend std::ostream& operator<<(std::ostream & out, Data &data);
	
};

struct Node
{
public:
	int size;  //размер вершины, т.е сколько ключей в нем находится
	Data key[3]; //ключи
	Node *first; // указатели на потомков
	Node *second;
	Node *third;
	Node *fourth;
	Node *parent; // указатель на родителя
	Node(string k);
	Node();
	void sort(); // сортирует вершины по возрастанию
	void insertToNode(string k); //добавление в вершину слова
	void insertToNode(string k, int timesAdded); //добавление в вершину слова с заданной частотой встречаемости
	void insertToNode(Data k); //добавление в вершину словаа
	void insertToNode(Data k, int timesAdded); //добавление в вершину слова с заданной частотой встречаемости
	bool isLeaf(); // возвращает true если вершина является листом, т.е не имеет потомков
	bool find(Data k); //  возвращает true если в вершине имеется ключ к
	void removeFromNode(Data k); // удаляет ключ из узла
	void removeFromNode(Data k, int timesAdded);  // удаляет ключ из узла заданное количество раз
};


class FrequencyDictionary
{

public:
	FrequencyDictionary();
	void insert(string k); //добавление слова
	void INSEART(string k, int timesAdded); //добавление слова
	void split(Node *node); //разделение вершины
	void printTree(Node *node, int space); //выводит словарь в форме 2-3 дерева
	void printTree();
	void printDict(Node *node); //выводит словарь в виде списка
	void printDict();
	void printThreeMostFrequentWords(); //выводит 3 самых часто встречающихся слова
	Node *SEARCH(string key); //поиск слова в словаре
	void DELETE(string key); // удаление заданного слова
	Node *findMin(Node *node);
	Node *fix(Node *node); // исправление дерева после удаления
	Node *redestribute(Node *node); // перераспределение
	Node *merge(Node *node); //склеивание
	void deleteTree(Node *node); // удаление дерева
	void deleteTree();
	bool isWord(string &k); // проверка является ли k словом
	void addToDicrionary(Node *node, string key); //добавление в словарь
	void removeFromDictionary(Node *node, string key);// удаление из словаря
	~FrequencyDictionary();

private:
	Node *root_; //корень дерева
	vector<Data> frequensyDict_; //частотный словарь
};
