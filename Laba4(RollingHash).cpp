/// Лаба 4. Реализовать собственную полиномиальную хеш-функцию. С помощью алгоритма скользящего хеша решить поставленную задачу: 
//на вход подаётся строка (string или массив char по вашему усмотрению).
//Допускается только дописывание букв в начало строки. За минимальное количество действий преобразовать строку в новую строку так, 
//чтобы она читалась одинаково как справа на лево так и слева направо
//Указанные алгоритмы необходимо реализовать собственноручно, не прибегая к встроенным структурам данных с хэшами.

//------------------------------------------------------------------------------------------------------------------------------------------
HashTable.h
//------------------------------------------------------------------------------------------------------------------------------------------
  #pragma once

#include <iostream>
#include <string>
#include <vector>

class HashTable
{
public:
	enum State
	{
		FREE,
		RESERVED,
		DELETED
	};

	struct HashElementString
	{
		std::string data;
		State state;

		HashElementString(std::string d = std::string(), State st = State::FREE)
		{
			data = d;
			state = st;
		}
	};

	const unsigned int prime = 31;

private:
	HashElementString* table;
	int capacity;

public:
	HashTable(int cap = 0);
	~HashTable();
	HashElementString* getTable();
	int getCapacity();
	int h(int key);
	int g(int key);
	int h1(int key, int i);
	void resize();
	bool insert(HashElementString element);
	void deleteElement(int index);
	void clear();
	int find(const std::string& element);
	void print();
	std::string reverseString(const std::string& str);
	unsigned int rollingHash(unsigned int prevHash, char oldChar, char newChar, int length);
	std::string findPalindrome(const std::string& str);
	unsigned int computeHash(const std::string& s);
};
//------------------------------------------------------------------------------------------------------------------------------------------
HashTable.cpp
//------------------------------------------------------------------------------------------------------------------------------------------
#include "HashTable.h"
#include <cmath>

HashTable::HashTable(int cap)
{
    capacity = cap;
    table = new HashElementString[capacity];
    for (int i = 0; i < capacity; i++)
    {
        table[i] = HashElementString();
    }
}

HashTable::~HashTable()
{
    delete[] table;
}

HashTable::HashElementString* HashTable::getTable()
{
    return table;
}

int HashTable::getCapacity()
{
    return capacity;
}

int HashTable::h(int key)
{
    int h = 0;

    while (key > 0)
    {
        h += key % 10;
        key /= 10;
    }

    return h;
}

int HashTable::g(int key)
{
    return key + 1;
}

int HashTable::h1(int key, int i)
{
    return (h(key) + i * g(key));
}

void HashTable::resize()
{
    int newCapacity = capacity * 2;
    HashElementString* newTable = new HashElementString[newCapacity];
    for (int i = 0; i < newCapacity; i++)
    {
        if (i < capacity)
        {
            newTable[i] = table[i];
        }
        else
        {
            newTable[i] = HashElementString();
        }
    }
    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

bool HashTable::insert(HashElementString element)
{
    std::cout << "[ TRYING TO INSERT ELEMENT(" << element.data << ") ]\n";
    int index = h(element.data.size()) % capacity;

    if (table[index].state == State::FREE) // No collision
    {
        table[index].data = element.data;
        table[index].state = State::RESERVED;
        std::cout << "[ ELEMENT(" << element.data << ") INSERTED ]\n\n";
        return true;
    }
    else // Collision
    {
        std::cout << "[ COLLISION DETECTED, SOLVING ]\n";
        for (int i = 0; i < capacity; i++)
        {
            index = h1(element.data.size(), i) % capacity;
            if (table[index].state == State::FREE)
            {
                table[index].data = element.data;
                table[index].state = State::RESERVED;
                std::cout << "[ COLLISION SOLVED(FREE SPACE FOUND) ]\n";
                std::cout << "[ ELEMENT(" << element.data << ") INSERTED ]\n\n";
                return true;
            }
        }

        // No FREE space => need to resize the array
        resize();
        index = capacity / 2;
        table[index].data = element.data;
        table[index].state = State::RESERVED;
        std::cout << "[ COLLISION SOLVED(ARRAY RESIZED) ]\n";
        std::cout << "[ ELEMENT(" << element.data << ") INSERTED ]\n\n";
        return true;
    }

    std::cout << "[ COLLISION SOLVING FAILED ]\n";
    return false;
}

void HashTable::deleteElement(int index)
{
    if (table[index].state == State::RESERVED && index < capacity)
    {
        table[index].state = State::DELETED;
    }
}

void HashTable::clear()
{
    for (int i = 0; i < capacity; i++)
    {
        deleteElement(i);
    }
}

int HashTable::find(const std::string& element)
{
    for (int i = 0; i < capacity; i++)
    {
        if (table[i].data == element)
        {
            return i;
        }
    }

    return -1;
}

void HashTable::print()
{
    for (int i = 0; i < capacity; i++)
    {
        if (table[i].state == State::RESERVED)
        {
            std::cout << table[i].data << ' ';
        }
        else
        {
            std::cout << "[] ";
        }
    }

    std::cout << '\n';
}

std::string HashTable::reverseString(const std::string& str)
{
    std::string reversedStr;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        reversedStr.push_back(str[i]);
    }
    return reversedStr;
}

unsigned int HashTable::rollingHash(unsigned int prevHash, char oldChar, char newChar, int length)
{
    const unsigned int prime = 31;
    return (prevHash - oldChar * static_cast<unsigned int>(pow(prime, length - 1))) * prime + newChar;
}

std::string HashTable::findPalindrome(const std::string& str)
{
    if (str.empty())
        return "";

    int maxLength = 0;
    int startIdx = 0;

    int n = str.size();

    std::vector<unsigned int> prefixHash(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        prefixHash[i + 1] = prefixHash[i] * prime + str[i];
    }

    for (int len = 1; len <= n; ++len)
    {
        for (int i = 0; i + len <= n; ++i)
        {
            unsigned int hash1;
            if (i == 0)
            {
                hash1 = prefixHash[i + len];
            }
            else
            {
                hash1 = rollingHash(prefixHash[i], str[i - 1], str[i + len - 1], len);
            }
            std::string reversedSubstring = str.substr(i, len);
            std::reverse(reversedSubstring.begin(), reversedSubstring.end());
            unsigned int hash2 = computeHash(reversedSubstring);

            if (hash1 == hash2 && std::equal(str.begin() + i, str.begin() + i + len, str.rbegin() + str.size() - i - len))
            {
                if (len > maxLength)
                {
                    maxLength = len;
                    startIdx = i;
                }
            }
        }
    }

    return str.substr(startIdx, maxLength);
}

unsigned int HashTable::computeHash(const std::string& s)
{
    unsigned int hashValue = 0;
    for (char c : s)
    {
        hashValue = hashValue * prime + c;
    }
    return hashValue;
}
//------------------------------------------------------------------------------------------------------------------------------------------
main.cpp
//------------------------------------------------------------------------------------------------------------------------------------------
#include "HashTable.h"

int main()
{
    std::string inputString = "maamsdad";
    HashTable table = HashTable(5);

    table.insert(inputString);

    std::string palindrome = table.findPalindrome(inputString);

    std::cout << "Original String: " << inputString << std::endl;
    std::cout << "Palindrome: " << palindrome << std::endl;

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
