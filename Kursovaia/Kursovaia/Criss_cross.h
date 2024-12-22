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

struct Word {
   
    std::wstring value;
    std::vector<int> occupied_letters;
    int location;
    int start_x;
    int start_y;
};

class Criss_Cross {
private:
    std::vector<std::vector<wchar_t>> grid;
    size_t size_grid;
    size_t size_big_word;
    size_t count_words;
    size_t count_insert_words; 
    std::wfstream in;
    std::wofstream out;
    std::vector<struct Word> words;
    std::vector<struct Word> words_2;
    std::vector<std::wstring> invalidWords;  

    void check_words(std::vector<std::wstring>& buffer);
    bool count_number_words();
    void input_file();
    void output_file();
    bool check(const std::string& filename);
    bool find_first_intersection(const Word w1, const Word w2, int& a, int& b);
    bool can_place_word(const std::wstring& word, int StartX, int StartY, int direction);
    void mark_occupied_letters(Word& w1, Word& w2, int a, int b);
    void insert_word(Word& w1, Word& w2, int a, int b, int d);
    void insert_first_word(std::vector<struct Word>& w);
    void print(int left, int right, int top, int bottom);
    void defining_boundaries(int& left, int& right, int& top, int& bottom);
    void grill_replacement();
    void invalid_words(std::vector<struct Word> w); 

    void make_visualization();
    void calculate_percentage(int left, int right, int top, int bottom);
    bool find_centre_intersection_left(const Word w1, const Word w2, int& a, int& b, int p);
    bool find_centre_intersection_right(const Word w1, const Word w2, int& a, int& b, int p);
    void make_criss_cross_2();

public:

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
    ~Criss_Cross() {
        In.close();
        Out.close();
    }

    void make_criss_cross();
};


