
/**
 * @file Criss_cross.h
 * @brief Заголовочный файл для класса Criss_Cross.
 *
 * Этот класс представляет собой генерацию решетки кроссворда. Он может считывать список слов из файла
 * ,а затем генерировать таблицу кроссвордов.
 */

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>   
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <unordered_set>
#include <fstream> 
#include <regex> 
#include <Windows.h>

 /**
   * @struct Word
   * @brief Представляет собой слово в кроссворде.
   */

struct Word {
    /**
 * \var std::wstring value
 * \brief Поле значение
 */
    std::wstring value;
    /**
* \var std::vector<int> occupied_letters
* \brief Вектор для хранения занятых букв
*/
    std::vector<int> occupied_letters;
    /**
* \var  int location
* \brief Хранит расположение слова (0 - гориз. 1 - верт.)
*/
    int location;
    /**
* \var int start_x
* \brief Координата x начала слова в решетке
*/
    int start_x;
    /**
* \var int start_y
* \brief Координата y начала слова в решетке
*/
    int start_y;
};

/**
 * @class Criss_Cross
 * @brief Представляет собой решетку кроссворда.
 */

class Criss_Cross {
private:
    /**
* \var std::vector<std::vector<wchar_t>> grid
* \brief Решетка
*/
    std::vector<std::vector<wchar_t>> grid;
    /**
* \var size_t size_grid
* \brief Размер решетки
*/
    size_t size_grid;
    /**
* \var size_big_word
* \brief Длинна длинного слова
*/
    size_t size_big_word;
    /**
* \var size_t count_words
* \brief Количество слов
*/
    size_t count_words;
    /**
* \var size_t count_insert_words
* \brief Количество добавленных слов
*/
    size_t count_insert_words; 
    /**
* \var std::wfstream In
* \brief Название входного файла
*/
    std::wfstream In;
    /**
* \var  std::wofstream Out
* \brief Название выходного файла
*/
    std::wofstream Out;
    /**
* \var  std::vector<struct Word> words
* \brief Двумерный вектор слов
*/
    std::vector<struct Word> words;
    /**
* \var std::vector<struct Word> words_2
* \brief Двумерный вектор слов_2
*/
    std::vector<struct Word> words_2;
    /**
* \var std::vector<std::wstring> invalidWords
* \brief Вектор слов, не вошедших в решетку
*/
    std::vector<std::wstring> invalidWords;  

    /**
     * @brief Проверяет слова из входного файла.
     *
     * Эта функция убирает дубликаты слов, слова, имеющие не русские буквы,
     * конвертирует все заглавные буквы в строчные.
     *
     *
     * @param buffer Вектор для проверки слов.
     */

    void Check_Words(std::vector<std::wstring>& buffer);

    /**
     * @brief Считает количество слов в файл.
     *
     * @return Возвращает количество слов в файле.
     */

    bool Count_number_words();

    /**
     * @brief Читает слова из файла.
     */

    void Input_file();

    /**
     * @brief Записывает решетку кроссворда в файл.
     */

    void Output_file();

    /**
     * @brief Проверяет имя файла на правильность.
     *
     * @param filename Имя файла.
     * @return True, если имя файла верно и False, если не верно.
     */

    bool check(const std::string& filename);

    /**
     * @brief Находит первую общую букву у двух слов, начиная с начала слова.
     *
     * @param w1 Первое слово.
     * @param w2 Второе слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2.
     * @return True, если есть пересечение и False, если нет.
     */

    bool Find_First_Intersection(const Word w1, const Word w2, int& a, int& b);

    /**
     * @brief Прверяет, может ли слово распологаться в решетке.
     *
     * @param word Слово.
     * @param StartX Координата начала слова в решетке по x.
     * @param StartY Координата начала слова в решетке по y.
     * @param direction Расположение слова в решетке(0 горизонтально, 1 вертикально).
     * @return True, если слово может встать в решетку и False, если нет.
     */

    bool Can_Place_Word(const std::wstring& word, int StartX, int StartY, int direction);

    /**
     * @brief Помечает занятые буквы в вслове.
     *
     * @param w1 Первое слово.
     * @param w2 Второе слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2..
     */

    void Mark_Occupied_Letters(Word& w1, Word& w2, int a, int b);

    /**
     * @brief Добавление слова в решетку.
     *
     * @param w1 Первое слово.
     * @param w2 Пторое слово.
     * @param а Индекс пересечения в w1.
     * @param b Индекс пересечения в w2..
     * @param d Расположение слова в решетке(0 горизонтально, 1 вертикально).
     */

    void Insert_Word(Word& w1, Word& w2, int a, int b, int d);

    /**
     * @brief Вставляет первое слово в решетку.
     *
     * @param w Вектор слов.
     */

    void Insert_First_Word(std::vector<struct Word>& w);

    /**
     * @brief Печатает решетку кроссворда в консоль.
     *
     * @param left Левая крайняя точка.
     * @param right Правая крайняя точка.
     * @param top Верхняя крайняя точка.
     * @param bottom Нижняя крайняя точка.
     */

    void Print(int left, int right, int top, int bottom);

    /**
    * @brief Определяет границы решетки.
    *
    * @param left Левая крайняя точка.
    * @param right Правая крайняя точка.
    * @param top Верхняя крайняя точка.
    * @param bottom Нижняя крайняя точка.
    */

    void Defining_Boundaries(int& left, int& right, int& top, int& bottom);

    /**
     * @brief Удаляет все '#' в решетке и заменяет на ' '.
     */

    void Grill_Replacement();

    /**
    * @brief Выводит в консоль слова, которые не вошли в решетку.
    *
    * @param w Вектор слов.
    */

    void Invalid_words(std::vector<struct Word> w); 

    //Доп

    /**
     * @brief Генерирует визуализацию кроссворда.
     */

    void Make_Visualization();

    /**
     * @brief Считает процент букв в решетке.
     *
     * @param left Левая крайняя точка.
     * @param right Правая крайняя точка.
     * @param top Верхняя крайняя точка.
     * @param bottom Нижняя крайняя точка.
     */

    void Calculate_Percentage(int left, int right, int top, int bottom);

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

    bool Find_Centre_Intersection_left(const Word w1, const Word w2, int& a, int& b, int p);

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

    bool Find_Centre_Intersection_right(const Word w1, const Word w2, int& a, int& b, int p);

    /**
     * @brief Генерирует решетку кроссворда вторым методом.
     */

    void Make_Criss_Cross_2();

public:

    /**
     * @brief Конструктор.
     *
     * @param filename_in Имя файла входа.
     * @param filename_out Имя файоа выхода.
     */

    Criss_Cross(const std::string& filename_in, const std::string& filename_out) {
        if (check(filename_in) == true) {
            In.open(filename_in);
            if (!In) {
                std::wcerr << L"Ошибка открытия файла";
            }
            else {
                Out.open(filename_out);
                if (Count_number_words() == false) {
                    std::wcerr << L"Ошибка: Файл пуст! Заполните файл" << std::endl;
                }
                else {
                    Input_file();
                    std::sort(words.begin(), words.end(), [](const Word& a, const Word& b) {
                        return a.value.size() > b.value.size();
                        });

                    std::sort(words_2.begin(), words_2.end(), [](const Word& a, const Word& b) {
                        return a.value.size() > b.value.size();
                        });

                    size_big_word = words[0].value.size();
                    size_grid = size_big_word * size_big_word;
                    grid.resize(size_grid, std::vector<wchar_t>(size_grid, L' '));
                }
            }
        }
        else {
            std::wcerr << L"Ошибка: название файла некорректно" << std::endl;
        }
    }

    /**
    * @brief Деструктор.
    */

    ~Criss_Cross() {
        In.close();
        Out.close();
    }

    /**
    * @brief Генирирует решетку кроссворда.
    */

    void Make_Criss_Cross();
};


