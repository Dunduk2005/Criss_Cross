// срвнение двух алгоритмов визуально 
// посичтать процент с двух решеток +
// regular на входные данные
// вывести слова при помощи регулярки, которые не вошли в решетку
// 
// 

#include "Criss_cross.h"

/**
 * @brief Главная функция программы.
 *
 * Эта функция инициализирует локаль, устанавливает кодировку консоли,
 * проверяет количество аргументов командной строки и создает объект
 * Criss_Cross для выполнения операции Make_Criss_Cross.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 в случае успешного завершения, 1 в случае ошибки.
 */

int main(int argc, char* argv[]) {
    std::locale::global(std::locale("ru_RU.UTF-8")); 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (argc < 3) {
        std::wcerr << L"Ошибка: не указано имя файла" << std::endl; 
        return 1; 
    }

    Criss_Cross a(argv[1], argv[2]);
    a.Make_Criss_Cross();

    system("pause");
    return 0;
}
// \Users\user\source\repos\Kursovaia\x64\Debug
//Kursovaia.exe имя_файла