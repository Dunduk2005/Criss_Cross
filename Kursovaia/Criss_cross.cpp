/**
 * @file Criss_cross.cpp
 * @brief ����, �������� ���������� �������.
 *
 * ���� ���� �������� ���������� ������� ��� ����������� �������.
 * ��� ���������� �������� ��������� � ���� Criss_Cross.cpp
 */

#include"Criss_cross.h"

/**
    * @brief ������� ���������� ���� � ����.
    *
    * @return ���������� ���������� ���� � �����.
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
 * @brief ��������� ����� �� �������� �����.
 *
 * ��� ������� ������� ��������� ����, �����, ������� �� ������� �����,
 * ������������ ��� ��������� ����� � ��������.
 *
 *
 * @param buffer ������ ��� �������� ����.
 */

void Criss_Cross::Check_Words(std::vector<std::wstring>& buffer) {
    std::unordered_set<std::wstring> uniqueWords;
    std::wregex russianWordRegex(L"^[�-��-���]+$"); // ���������� ��������� ��� �������� ������� ����

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
        std::wcerr << std::endl << L"��������� ���� �������!" << std::endl;
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
        std::wcerr << std::endl << L"��������� ����� � ����� � ���������� ������� ���� �������!" << std::endl;
    }

    count_words = buffer.size();

    for (auto& word : buffer) {
        for (auto& ch : word) {
            if (ch >= L'�' && ch <= L'�') {
                ch = ch + (L'�' - L'�');
            }
        }
    }

    if (buffer.size() == 0) abort();
}

/**
    * @brief ������ ����� �� �����.
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
    * @brief ������� ��� '#' � ������� � �������� �� ' '.
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
 * @brief ���������� ������� ���������� � ����.
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

    std::wcerr << std::endl << L"������� ���� � �������. �������: "; 
    Calculate_Percentage(right, left, top, bottom + top + 1);
}

/**
     * @brief ��������� ��� ����� �� ������������.
     *
     * @param filename ��� �����.
     * @return True, ���� ��� ����� ����� � False, ���� �� �����.
     */

bool Criss_Cross::check(const std::string& filename) { // �������� �������� �����
    std::regex filePattern(R"([a-zA-Z0-9_]+\.txt$)");
    return std::regex_match(filename, filePattern);
}

/**
     * @brief ������� ������ ����� ����� � ���� ����, ������� � ������ �����.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2.
     * @return True, ���� ���� ����������� � False, ���� ���.
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
    * @brief ��������, ����� �� ����� ������������� � �������.
    *
    * @param word �����.
    * @param StartX ���������� ������ ����� � ������� �� x.
    * @param StartY ���������� ������ ����� � ������� �� y.
    * @param direction ������������ ����� � �������(0 �������������, 1 �����������).
    * @return True, ���� ����� ����� ������ � ������� � False, ���� ���.
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
    * @brief �������� ������� ����� � ������.
    *
    * @param w1 ������ �����.
    * @param w2 ������ �����.
    * @param � ������ ����������� � w1.
    * @param b ������ ����������� � w2..
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
     * @brief ���������� ����� � �������.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2..
     * @param d ������������ ����� � �������(0 �������������, 1 �����������).
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
    * @brief ��������� ������ ����� � �������.
    *
    * @param w ������ ����.
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
* @brief ������� � ������� �����, ������� �� ����� � �������.
*
* @param w ������ ����.
*/

void Criss_Cross::Invalid_words(std::vector<struct Word> w) { 
    std::wcerr << std::endl << L"�����, �� �������� � ������� ����������:" << std::endl;

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
     * @brief ������� ������� ���� � �������.
     *
     * @param left ����� ������� �����.
     * @param right ������ ������� �����.
     * @param top ������� ������� �����.
     * @param bottom ������ ������� �����.
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
    std::wcerr << L"������/�����: " << count_letters << '/' << count_cell << std::endl;  
}


/**
* @brief ���������� ������� �������.
*
* @param left ����� ������� �����.
* @param right ������ ������� �����.
* @param top ������� ������� �����.
* @param bottom ������ ������� �����.
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
 * @brief �������� ������� ���������� � �������.
 *
 * @param left ����� ������� �����.
 * @param right ������ ������� �����.
 * @param top ������� ������� �����.
 * @param bottom ������ ������� �����.
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
 * @brief ���������� ������������ ����������.
 */

void Criss_Cross::Make_Visualization() {
    grid.clear();
    grid.resize(size_grid, std::vector<wchar_t>(size_grid, L' ')); 
    count_insert_words = 0; 
    Make_Criss_Cross_2();
}


/**
 * @brief ������� ������ ����� ����� � ���� ����, ������� � �������� ����� � ������� �����.
 *
 * @param w1 ������ �����.
 * @param w2 ������ �����.
 * @param � ������ ����������� � w1.
 * @param b ������ ����������� � w2.
 * @param p ����� �� ������� ������ ����������� ��� ����������� �����.
 * @return True, ���� ���� ����������� � False, ���� ���.
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
     * @brief ������� ������ ����� ����� � ���� ����, ������� � �������� ����� � ������� ������.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2.
     * @param p ����� �� ������� ������ ����������� ��� ����������� ������.
     * @return True, ���� ���� ����������� � False, ���� ���.
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
 * @brief ���������� ������� ���������� ������ �������.
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

    std::wcerr << std::endl << L"������� ���� � �������. ������� c ���������������: ";
    Calculate_Percentage(right, left, top, bottom + top + 1);
}


