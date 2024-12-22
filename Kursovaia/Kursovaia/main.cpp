#include "Criss_cross.h"

int main(int argc, char* argv[]) {
    std::locale::global(std::locale("ru_RU.UTF-8")); 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (argc < 3) {
        std::wcerr << L"Ошибка: не указано имя файла" << std::endl; 
        return 1; 
    }

    Criss_Cross a(argv[1], argv[2]);
    a.make_criss_cross();

    system("pause");
    return 0;
}
// \Users\user\source\repos\Kursovaia\x64\Debug
//Kursovaia.exe имя_файла