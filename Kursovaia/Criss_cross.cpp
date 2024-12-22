/**
 * @file Criss_cross.cpp
 * @brief Файл, хранящий реализации функций.
 *
 * Этот файл содержит реализацию методов для составления решетки.
 * Для подробного описания перейдите в файл Criss_Cross.cpp
 */

#include"Criss_cross.h"

/**
    * @brief Считает количество слов в файл.
    *
    * @return Возвращает количество слов в файле.
    */


bool Criss_Cross::Count_number_words() {
    std::wstring buff;
    while (std::getline(In, buff))
    {
        count_words++;
    }
    if (count_words != 0) true;
    else return false;
}


/**
 * @brief Проверяет слова из входного файла.
 *
 * Эта функция убирает дубликаты слов, слова, имеющие не русские буквы,
 * конвертирует все заглавные буквы в строчные.
 *
 *
 * @param buffer Вектор для проверки слов.
 */

void Criss_Cross::Check_Words(std::vector<std::wstring>& buffer) {
    std::unordered_set<std::wstring> uniqueWords;
    std::wregex russianWordRegex(L"^[А-Яа-яёЁ]+$"); // Регулярное выражение для проверки русских слов

    auto it = buffer.begin();
    while (it != buffer.end()) {
        if (uniqueWords.find(*it) != uniqueWords.end()) {
            it = buffer.erase(it);
        }
        else {
            uniqueWords.insert(*it);
            ++it;
        }
    }
    if (count_words > buffer.size()) {
        std::wcerr << std::endl << L"Дубликаты были удалены!" << std::endl;
    }

    it = buffer.begin();
    while (it != buffer.end()) {
        if (!std::regex_match(*it, russianWordRegex)) {
            invalidWords.push_back(*it); 
            it = buffer.erase(it);
        }
        else {
            ++it;
        }
    }
    if (count_words > buffer.size()) {
        std::wcerr << std::endl << L"Нерусские слова и слова с нерусскими буквами были удалены!" << std::endl;
    }

    count_words = buffer.size();

    for (auto& word : buffer) {
        for (auto& ch : word) {
            if (ch >= L'А' && ch <= L'Я') {
                ch = ch + (L'а' - L'А');
            }
        }
    }

    if (buffer.size() == 0) abort();
}

/**
    * @brief Читает слова из файла.
    */

void Criss_Cross::Input_file() {
    In.clear();
    In.seekg(0, std::ios::beg);

    std::vector <std::wstring> buffer;
    buffer.resize(count_words);
    std::wstring buff;

    while (std::getline(In, buff))
    {
        buffer.push_back(buff);
    }

    Check_Words(buffer);

    words.resize(count_words);
    for (int i = 0; i < count_words; i++) {
        words[i].value = buffer[i];
        words[i].occupied_letters.resize(buffer[i].size(), 0);
        words[i].location = -1;
        words[i].start_x = -1;
        words[i].start_y = -1;
    }

    words_2.resize(count_words);
    for (int i = 0; i < count_words; i++) {
        words_2[i].value = buffer[i];
        words_2[i].occupied_letters.resize(buffer[i].size(), 0);
        words_2[i].location = -1;
        words_2[i].start_x = -1;
        words_2[i].start_y = -1;
    }
}

/**
    * @brief Удаляет все '#' в решетке и заменяет на ' '.
    */


void Criss_Cross::Grill_Replacement() {
    for (size_t i = 0; i < size_grid; i++) {
        for (size_t j = 0; j < size_grid; j++) {
            if (grid[i][j] == L'#') {
                grid[i][j] = L' ';
            }
        }
    }
}


/**
 * @brief Записывает решетку кроссворда в файл.
 */

void Criss_Cross::Output_file() {
    Grill_Replacement();

    int bottom = 0;
    int top = 0;
    int left = size_grid;
    int right = 0;

    Defining_Boundaries(left, right, top, bottom);

    std::cout << std::endl;
    for (size_t i = top; i < bottom + top + 1; i++) {
        Out << std::endl << "\t";
        for (size_t j = left; j < right; j++) {
            if (grid[i][j] != L' ')
                Out << "[]";
            else
                Out << grid[i][j] << " ";
        }
    }

    Print(left, right, top, bottom); 

    std::wcerr << std::endl << L"Процент букв в решетке. Перебор: "; 
    Calculate_Percentage(right, left, top, bottom + top + 1);
}

/**
     * @brief Проверяет имя файла на правильность.
     *
     * @param filename Имя файла.
     * @return True, если имя файла верно и False, если не верно.
     */

bool Criss_Cross::check(const std::string& filename) { // проверка названия файла
    std::regex filePattern(R"([a-zA-Z0-9_]+\.txt$)");
    return std::regex_match(filename, filePattern);
}

/**
     * @brief Находит первую общую букву у двух слов, начиная с начала слова.
     *
     * @param w1 Первое слово.
     * @param w2 Второе слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2.
     * @return True, если есть пересечение и False, если нет.
     */

bool Criss_Cross::Find_First_Intersection(const Word w1, const Word w2, int& a, int& b) {
    a = -1;
    b = -1;

    if (w1.value.empty() || w2.value.empty()) return false;
    if (w1.value.length() + w2.value.length() <= 1) return false;
    for (size_t i = 0; i < w2.value.length(); ++i) {
        for (size_t j = 0; j < w1.value.length(); ++j) {
            if (w2.value[i] == w1.value[j]) {
                if (w2.occupied_letters[i] == 0 and w1.occupied_letters[j] == 0) {
                    a = i;
                    b = j;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
    * @brief Прверяет, может ли слово распологаться в решетке.
    *
    * @param word Слово.
    * @param StartX Координата начала слова в решетке по x.
    * @param StartY Координата начала слова в решетке по y.
    * @param direction Расположение слова в решетке(0 горизонтально, 1 вертикально).
    * @return True, если слово может встать в решетку и False, если нет.
    */

bool Criss_Cross::Can_Place_Word(const std::wstring& word, const int startX, const int startY, int direction) {

    for (int i = 0; i < word.size(); i++) {
        if (direction == 0 && startX - 1 >= 0) {
            if (grid[startY][startX + i] != L' ' && grid[startY][startX + i] != word[i]) {
                return false;
            }
            if (i == word.size() - 1) {
                if (startX + i + 1 < grid[0].size() && grid[startY][startX + i + 1] != L' ') {
                    return false;
                }
            }

            if (grid[startY][startX - 1] != L' ') {
                return false;
            }

            if (i == 0) {
                if (grid[startY][startX - 1] != L' ') {
                    return false;
                }
            }
        }
        else if (direction == 1 && startY - 1 >= 0) {

            if (grid[startY + i][startX] != L' ' && grid[startY + i][startX] != word[i]) {
                return false;
            }
            if (i == word.size() - 1) {
                if (startY + i + 1 < grid.size() && grid[startY + i + 1][startX] != L' ') {
                    return false;
                }
            }

            if (grid[startY - 1][startX] != L' ') {
                return false;
            }

            if (i == 0) {
                if (grid[startY - 1][startX] != L' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
    * @brief Помечает занятые буквы в вслове.
    *
    * @param w1 Первое слово.
    * @param w2 Второе слово.
    * @param а Индекс пересечения в w1.
    * @param b Индекс пересечения в w2..
    */

void Criss_Cross::Mark_Occupied_Letters(Word& w1, Word& w2, int a, int b) {
    w1.occupied_letters[a] = 1;
    if (a > 0) {
        w1.occupied_letters[a - 1] = 1;
    }
    if (a < w1.value.size() - 1) {
        w1.occupied_letters[a + 1] = 1;
    }

    w2.occupied_letters[b] = 1;
    if (b > 0) {
        w2.occupied_letters[b - 1] = 1;
    }
    if (b < w2.value.size() - 1) {
        w2.occupied_letters[b + 1] = 1;
    }
}

/**
     * @brief Добавление слова в решетку.
     *
     * @param w1 Первое слово.
     * @param w2 Пторое слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2..
     * @param d Расположение слова в решетке(0 горизонтально, 1 вертикально).
     */

void Criss_Cross::Insert_Word(Word& w1, Word& w2, int a, int b, int d) {
    int i = 0, j = 0;
    d == 0 ? i = w1.start_x + b : i = w1.start_x - a;
    d == 0 ? j = w1.start_y - a : j = w1.start_y + b;
    if (d == 0 ? Can_Place_Word(w2.value, i, j, 1) == true : Can_Place_Word(w2.value, i, j, 0) == true) {
        for (wchar_t c : w2.value) {
            d == 0 ? grid[j++][i] = c : grid[j][i++] = c;
        }
        count_insert_words++; 
        d == 0 ? grid[j - w2.value.size() - 1 + a][i - 1] = '#' : grid[j - 1][i - w2.value.size() - 1 + a] = '#';
        d == 0 ? grid[j - w2.value.size() - 1 + a][i + 1] = '#' : grid[j + 1][i - w2.value.size() - 1 + a] = '#';
        d == 0 ? grid[j - w2.value.size() + 1 + a][i - 1] = '#' : grid[j - 1][i - w2.value.size() + 1 + a] = '#';
        d == 0 ? grid[j - w2.value.size() + 1 + a][i + 1] = '#' : grid[j + 1][i - w2.value.size() + 1 + a] = '#';

        d == 0 ? grid[j][i] = '#' : grid[j][i] = '#';
        d == 0 ? grid[j - w2.value.size() - 1][i] = '#' : grid[j][i - w2.value.size() - 1] = '#';
        d == 0 ? w2.location = 1 : w2.location = 0;
        d == 0 ? w2.start_x = i : w2.start_x = i - w2.value.size();
        d == 0 ? w2.start_y = j - w2.value.size() : w2.start_y = j;

        Mark_Occupied_Letters(w2, w1, a, b);
    }
}

/**
    * @brief Вставляет первое слово в решетку.
    *
    * @param w Вектор слов.
    */

void Criss_Cross::Insert_First_Word(std::vector<struct Word>& w) {
    int i = size_grid / 2;
    int j = size_grid / 2;
    w[0].start_x = i;
    w[0].start_y = j;
    for (wchar_t c : w[0].value) {
        grid[j][i++] = c;
    }
    grid[j][i] = '#';
    grid[j][i - w[0].value.size() - 1] = '#';
    w[0].location = 0;
    count_insert_words++;
}


/**
* @brief Выводит в консоль слова, которые не вошли в решетку.
*
* @param w Вектор слов.
*/

void Criss_Cross::Invalid_words(std::vector<struct Word> w) { 
    std::wcerr << std::endl << L"Слова, не вошедшие в решетку кроссворда:" << std::endl;

    for (int i = 0; i < count_words; i++) {
        if (w[i].location == -1) {
            std::wcout << w[i].value << std::endl; 
        }
    }

    for (int i = 0; i < invalidWords.size(); i++) {
        std::wcout << invalidWords[i] << std::endl; 
    }
}

void Criss_Cross::Make_Criss_Cross() {
    int a, b;
    for (int i = 0; i < count_words; i++) {
        if (i == 0) {
            Insert_First_Word(words);
        }
        else {
            for (int y = 1; y < count_words; y++) {
                for (int z = 0; z < count_words; z++) {
                    if (words[z].location != -1 && words[y].location == -1) {
                        if (Find_First_Intersection(words[y], words[z], b, a)) {
                            words[z].location == 0 ? Insert_Word(words[z], words[y], a, b, 0) : Insert_Word(words[z], words[y], a, b, 1);
                        }
                    }
                }
            }
        }
    }
    if (count_words - count_insert_words != 0) Invalid_words(words);
    Output_file(); 

    Make_Visualization(); 

}

/**
     * @brief Считает процент букв в решетке.
     *
     * @param left Левая крайняя точка.
     * @param right Правая крайняя точка.
     * @param top Верхняя крайняя точка.
     * @param bottom Нижняя крайняя точка.
     */

void Criss_Cross::Calculate_Percentage(int right, int left, int top, int bottom) {
    int count_cell = (right - left) * (bottom - top);
    int count_letters = 0;
    int percent = 0;

    for (size_t i = top; i < bottom; i++) {
        for (size_t j = left; j < right; j++) {
            if (grid[i][j] != L' ') {
                count_letters++;
            }
        }
    }

    percent = (count_letters * 100) / count_cell;
    std::wcerr << percent << " %" << std::endl;
    std::wcerr << L"Занято/Всего: " << count_letters << '/' << count_cell << std::endl;  
}


/**
* @brief Определяет границы решетки.
*
* @param left Левая крайняя точка.
* @param right Правая крайняя точка.
* @param top Верхняя крайняя точка.
* @param bottom Нижняя крайняя точка.
*/

void Criss_Cross :: Defining_Boundaries(int& left, int& right, int& top, int& bottom) {
    int count = 0;

    for (size_t i = 0; i < size_grid; i++) {
        for (size_t j = 0; j < size_grid; j++) {
            if (grid[i][j] != L' ') {
                if (j < left) left = j;
                count++;
            }
        }
        if (top == 0 && count != 0) top = i;
        if (i > right) right = i;
        if (count != 0) bottom++;
        count = 0;
    }
}


/**
 * @brief Печатает решетку кроссворда в консоль.
 *
 * @param left Левая крайняя точка.
 * @param right Правая крайняя точка.
 * @param top Верхняя крайняя точка.
 * @param bottom Нижняя крайняя точка.
 */

void Criss_Cross :: Print(int left, int right, int top, int bottom) {
    for (size_t i = top; i < bottom + top + 1; i++) {
        std::cout << std::endl << "\t";
        for (size_t j = left; j < right; j++) {
            std::wcout << grid[i][j] << " ";
        }
    }
}


/**
 * @brief Генерирует визуализацию кроссворда.
 */

void Criss_Cross::Make_Visualization() {
    grid.clear();
    grid.resize(size_grid, std::vector<wchar_t>(size_grid, L' ')); 
    count_insert_words = 0; 
    Make_Criss_Cross_2();
}


/**
 * @brief Находит первую общую букву у двух слов, начиная с серидины слова и двигась влево.
 *
 * @param w1 Первое слово.
 * @param w2 Второе слово.
 * @param а Индекс пересечения в w1.
 * @param b Индекс пересечения в w2.
 * @param p Число на единицу больше предыдущего для продвижения влево.
 * @return True, если есть пересечение и False, если нет.
 */

bool Criss_Cross::Find_Centre_Intersection_left(const Word w1, const Word w2, int& a, int& b, int p) {
    a = -1;
    b = -1;
    if (w1.value.empty() || w2.value.empty()) return false;
    if (w1.value.length() + w2.value.length() <= 1) return false;
    for (size_t i = 0; i < w2.value.length(); ++i) {
        for (size_t j = w1.value.length()/2; j > 0; --j) {
            if (w2.value[i] == w1.value[j]) {
                if (w2.occupied_letters[i] == 0 and w1.occupied_letters[j] == 0) {
                    a = i;
                    b = j;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
     * @brief Находит первую общую букву у двух слов, начиная с серидины слова и двигась вправо.
     *
     * @param w1 Первое слово.
     * @param w2 Второе слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2.
     * @param p Число на единицу больше предыдущего для продвижения вправо.
     * @return True, если есть пересечение и False, если нет.
     */


bool Criss_Cross::Find_Centre_Intersection_right(const Word w1, const Word w2, int& a, int& b, int p) {
    a = -1;
    b = -1;
    if (w1.value.empty() || w2.value.empty()) return false;
    if (w1.value.length() + w2.value.length() <= 1) return false;
    for (size_t i = 0; i < w2.value.length(); ++i) {
        for (size_t j = w1.value.length() / 2; j < w1.value.length(); ++j) {
            if (w2.value[i] == w1.value[j]) {
                if (w2.occupied_letters[i] == 0 && w1.occupied_letters[j] == 0) {
                    a = i;
                    b = j;
                    return true;
                }
            }
        }
    }
    return false;
}


/**
 * @brief Генерирует решетку кроссворда вторым методом.
 */

void Criss_Cross::Make_Criss_Cross_2() { 
    int a, b; 
    int p = 0; 
    for (int i = 0; i < count_words; i++) { 
        if (i == 0) { 
            Insert_First_Word(words_2); 
        }
        else {
            for (int y = 1; y < count_words; y++) { 
                for (int z = 0; z < count_words; z++) {
                    if (words_2[z].location != -1 && words_2[y].location == -1) {
                        for (int j = 0; j < words_2[z].value.size() / 2; j++) {
                            if (Find_Centre_Intersection_left(words_2[z], words_2[y], a, b, p) == true) {
                                words_2[z].location == 0 ? Insert_Word(words_2[z], words_2[y], a, b, 0) : Insert_Word(words_2[z], words_2[y], a, b, 1);
                                break;
                            }
                            if (Find_Centre_Intersection_right(words_2[z], words_2[y], a, b, p) == true) {
                                words_2[z].location == 0 ? Insert_Word(words_2[z], words_2[y], a, b, 0) : Insert_Word(words_2[z], words_2[y], a, b, 1);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if (count_words - count_insert_words != 0) Invalid_words(words_2);
    Grill_Replacement();
    int bottom = 0;
    int top = 0;
    int left = size_grid;
    int right = 0;

    Defining_Boundaries(left, right, top, bottom);
    Print(left, right, top, bottom);

    std::wcerr << std::endl << L"Процент букв в решетке. Перебор c уцентрированием: ";
    Calculate_Percentage(right, left, top, bottom + top + 1);
}


