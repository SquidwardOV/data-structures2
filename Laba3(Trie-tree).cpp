// Лаба номер 2 из списка. В trie–дереве определить, сколько слов имеют длину <, >, =, чем заданное значение K.

//--------------------------------------------------------------------------------------------------------------------

trie.h
  
//--------------------------------------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* CreateNode();

void insert(TrieNode* root, string key); // Вставка ключа 
void printTrie(TrieNode* root, string prefix); // Вывод дерева
void deleteNode(TrieNode* root, string key);
int countLessThanK(TrieNode* root, int K); // Подсчет слов с длиной меньше K
int countEqualToK(TrieNode* root, int K); // Подсчет слов с длиной равной K
int countGreaterThanK(TrieNode* root, int K); // Подсчет слов с длиной больше K
//--------------------------------------------------------------------------------------------------------------------

trie.cpp

//--------------------------------------------------------------------------------------------------------------------
#include "trie.h"

TrieNode* CreateNode() {
    TrieNode* node = new TrieNode;
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode* root, string key) {
    TrieNode* currentNode = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!currentNode->children[index]) {
            currentNode->children[index] = CreateNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

void deleteNode(TrieNode* root, string key) {
    TrieNode* currentNode = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!currentNode->children[index]) {
            cout << "Узел не найден" << endl;
            return;
        }
        currentNode = currentNode->children[index];
    }
    if (!currentNode->isEndOfWord) {
        cout << "Узел не найден" << endl;
        return;
    }
    else {
        currentNode->isEndOfWord = false;
    }
    cout << "Узел успешно удален" << endl;
}

void printTrie(TrieNode* root, string prefix) {
    if (root->isEndOfWord) {
        cout << prefix << endl;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char c = i + 'a';
            printTrie(root->children[i], prefix + c);
        }
    }
}

// Функция для подсчета слов с длиной меньше K
int countLessThanK(TrieNode* root, int K) {
    int count = 0;
    if (root == nullptr)
        return count;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i]) {
            count += countLessThanK(root->children[i], K - 1);
        }
    }

    if (root->isEndOfWord && K > 0)
        count++;

    return count;
}



// Функция для подсчета слов с длиной равной K
int countEqualToK(TrieNode* root, int K) {
    int count = 0;
    if (root == nullptr)
        return count;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        count += countEqualToK(root->children[i], K - 1);
    }

    if (root->isEndOfWord && K == 0)
        count++;

    return count;
}

// Функция для подсчета слов с длиной больше K
int countGreaterThanK(TrieNode* root, int K) {
    int count = 0;
    if (root == nullptr)
        return count;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        count += countGreaterThanK(root->children[i], K - 1);
    }

    if (root->isEndOfWord && K < 0)
        count++;

    return count;
}
//--------------------------------------------------------------------------------------------------------------------

main.cpp

//--------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "trie.h"

int main() {
    SetConsoleOutputCP(1251);
    TrieNode* root = CreateNode();

    // Вставляем слова в trie-дерево
    insert(root, "apple");
    insert(root, "banana");
    insert(root, "orange");
    insert(root, "pear");
    insert(root, "peach");
    insert(root, "grape");

    // Выводим trie-дерево
    cout << "Слова из Trie-дерева:" << endl;
    printTrie(root, "");

    // Задаем значение K
    int K;
    cout << "\nВведите значение K: ";
    cin >> K;

    // Подсчитываем количество слов с длиной меньше, равной и больше K
    int lessThanK = countLessThanK(root, K);
    int equalToK = countEqualToK(root, K);
    int greaterThanK = countGreaterThanK(root, K);

    // Выводим результаты
    cout << "\nКоличество слов с длиной меньше " << K << ": " << lessThanK << endl;
    cout << "Количество слов с длиной равной " << K << ": " << equalToK << endl;
    cout << "Количество слов с длиной больше " << K << ": " << greaterThanK << endl;

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------
