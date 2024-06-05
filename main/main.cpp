#include <iostream>
#include <windows.h>
#include <string>

typedef bool (*ContainsAllCharactersFunc)(const char*, const char*);

int main() {
    std::string inputString;
    std::string charactersToFind;
    SetConsoleCP(1251); // Устанавливаем кодировку консоли для поддержки кириллицы
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);
    std::cout << "Введите символы для поиска: ";
    std::getline(std::cin, charactersToFind);

    HMODULE hLib = LoadLibrary("CharChecker.dll");
    if (hLib == NULL) {
        std::cerr << "Не удалось загрузить библиотеку CharChecker.dll" << std::endl;
        return 1;
    }

    ContainsAllCharactersFunc containsAllCharacters = (ContainsAllCharactersFunc)GetProcAddress(hLib, "containsAllCharacters");
    if (containsAllCharacters == NULL) {
        std::cerr << "Не удалось получить адрес функции containsAllCharacters" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = containsAllCharacters(inputString.c_str(), charactersToFind.c_str());

    if (result) {
        std::cout << "Все символы найдены в строке." << std::endl;
    }
    else {
        std::cout << "Не все символы найдены в строке." << std::endl;
    }

    FreeLibrary(hLib);

    return 0;
}
