#include <iostream>
#include <fstream>
#include <algorithm>
#include "FrequencyDictionary.h"
using std::cout;

int main()
{
	FrequencyDictionary dict;

	std::ifstream file;
	file.open("text.txt");

	string word;
	while (file >> word)
	{	
		dict.insert(word);	//чтение из файла всех слов и занесение их в словарь
	}
	file.close();

	dict.printTree();
	cout << "\n";
	dict.printThreeMostFrequentWords(); // вывод 3x самых часто встречающихся слов

	cout << "\nWhole dictionary: \n";
	dict.printDict(); // вывод всего частотного словаря отсортированного по частоте встречаемости слов

	cout << "\nInserting words with set frequency\n";
	dict.INSEART("Wa4gg", 20); // добавляем неправильное слово
	cout << "Inserting Watson\n";
	dict.INSEART("Watson", 20); // длбавляем слово с частотой встречаемости
	dict.printThreeMostFrequentWords(); // вывозим 3 самых часто встречающихся слова

	cout << "\ndeleteng xoxo\n";
	dict.DELETE("xoxo"); // слово не удалится так как такого слова в словаре нет
	dict.printDict();

	cout << "\ndeleteng was\n";
	dict.DELETE("was");
	dict.printThreeMostFrequentWords();
	cout << "whole dictionary after deleting was\n";
	dict.printDict();

	return 0;
}

