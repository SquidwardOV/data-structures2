//Лабораторная номер 1 из списка
////////////////////////////////////////////////////////////////////////////////////////////

Solution.h
  
#pragma once
#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits);

private:
    void backtrack(const std::string& digits, const std::vector<std::string>& digit_to_letters, int index, std::string& current, std::vector<std::string>& result);
};

////////////////////////////////////////////////////////////////////////////////////////////////

Solution.cpp

  #include "Solution.h"

std::vector<std::string> Solution::letterCombinations(std::string digits) {
    std::vector<std::string> result;
    if (digits.empty()) return result;
    
    std::vector<std::string> digit_to_letters = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::string current;
    backtrack(digits, digit_to_letters, 0, current, result);
    
    return result;
}

void Solution::backtrack(const std::string& digits, const std::vector<std::string>& digit_to_letters, int index, std::string& current, std::vector<std::string>& result) {
    if (index == digits.length()) {
        result.push_back(current);  
        return;
    }
    
    std::string letters = digit_to_letters[digits[index] - '0'];
    for (char c : letters) {
        current.push_back(c);
        backtrack(digits, digit_to_letters, index + 1, current, result);
        current.pop_back();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include "Solution.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);
    Solution sol;


    std::vector<std::string> test_cases = { "23", "", "2" };
    for (const std::string& digits : test_cases) {
        std::cout << "Ввод: " << digits << std::endl;
        std::vector<std::string> result = sol.letterCombinations(digits);
        std::cout << "Вывод: [";
        for (int i = 0; i < result.size(); ++i) {
            std::cout << "\"" << result[i] << "\"";
            if (i < result.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
  
    std::string additional_digits;
    std::cout << "\nВведите номер: ";
    std::cin >> additional_digits;
    std::vector<std::string> additional_result = sol.letterCombinations(additional_digits);
    std::cout << "Вывод для введённого номера: [";
    for (int i = 0; i < additional_result.size(); ++i) {
        std::cout << "\"" << additional_result[i] << "\"";
        if (i < additional_result.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

