
/**
 * @file Criss_cross.h
 * @brief ������������ ���� ��� ������ Criss_Cross.
 *
 * ���� ����� ������������ ����� ��������� ������� ����������. �� ����� ��������� ������ ���� �� �����
 * ,� ����� ������������ ������� �����������.
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
   * @brief ������������ ����� ����� � ����������.
   */

struct Word {
    /**
 * \var std::wstring value
 * \brief ���� ��������
 */
    std::wstring value;
    /**
* \var std::vector<int> occupied_letters
* \brief ������ ��� �������� ������� ����
*/
    std::vector<int> occupied_letters;
    /**
* \var  int location
* \brief ������ ������������ ����� (0 - �����. 1 - ����.)
*/
    int location;
    /**
* \var int start_x
* \brief ���������� x ������ ����� � �������
*/
    int start_x;
    /**
* \var int start_y
* \brief ���������� y ������ ����� � �������
*/
    int start_y;
};

/**
 * @class Criss_Cross
 * @brief ������������ ����� ������� ����������.
 */

class Criss_Cross {
private:
    /**
* \var std::vector<std::vector<wchar_t>> grid
* \brief �������
*/
    std::vector<std::vector<wchar_t>> grid;
    /**
* \var size_t size_grid
* \brief ������ �������
*/
    size_t size_grid;
    /**
* \var size_big_word
* \brief ������ �������� �����
*/
    size_t size_big_word;
    /**
* \var size_t count_words
* \brief ���������� ����
*/
    size_t count_words;
    /**
* \var size_t count_insert_words
* \brief ���������� ����������� ����
*/
    size_t count_insert_words; 
    /**
* \var std::wfstream In
* \brief �������� �������� �����
*/
    std::wfstream In;
    /**
* \var  std::wofstream Out
* \brief �������� ��������� �����
*/
    std::wofstream Out;
    /**
* \var  std::vector<struct Word> words
* \brief ��������� ������ ����
*/
    std::vector<struct Word> words;
    /**
* \var std::vector<struct Word> words_2
* \brief ��������� ������ ����_2
*/
    std::vector<struct Word> words_2;
    /**
* \var std::vector<std::wstring> invalidWords
* \brief ������ ����, �� �������� � �������
*/
    std::vector<std::wstring> invalidWords;  

    /**
     * @brief ��������� ����� �� �������� �����.
     *
     * ��� ������� ������� ��������� ����, �����, ������� �� ������� �����,
     * ������������ ��� ��������� ����� � ��������.
     *
     *
     * @param buffer ������ ��� �������� ����.
     */

    void Check_Words(std::vector<std::wstring>& buffer);

    /**
     * @brief ������� ���������� ���� � ����.
     *
     * @return ���������� ���������� ���� � �����.
     */

    bool Count_number_words();

    /**
     * @brief ������ ����� �� �����.
     */

    void Input_file();

    /**
     * @brief ���������� ������� ���������� � ����.
     */

    void Output_file();

    /**
     * @brief ��������� ��� ����� �� ������������.
     *
     * @param filename ��� �����.
     * @return True, ���� ��� ����� ����� � False, ���� �� �����.
     */

    bool check(const std::string& filename);

    /**
     * @brief ������� ������ ����� ����� � ���� ����, ������� � ������ �����.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2.
     * @return True, ���� ���� ����������� � False, ���� ���.
     */

    bool Find_First_Intersection(const Word w1, const Word w2, int& a, int& b);

    /**
     * @brief ��������, ����� �� ����� ������������� � �������.
     *
     * @param word �����.
     * @param StartX ���������� ������ ����� � ������� �� x.
     * @param StartY ���������� ������ ����� � ������� �� y.
     * @param direction ������������ ����� � �������(0 �������������, 1 �����������).
     * @return True, ���� ����� ����� ������ � ������� � False, ���� ���.
     */

    bool Can_Place_Word(const std::wstring& word, int StartX, int StartY, int direction);

    /**
     * @brief �������� ������� ����� � ������.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2..
     */

    void Mark_Occupied_Letters(Word& w1, Word& w2, int a, int b);

    /**
     * @brief ���������� ����� � �������.
     *
     * @param w1 ������ �����.
     * @param w2 ������ �����.
     * @param � ������ ����������� � w1.
     * @param b ������ ����������� � w2..
     * @param d ������������ ����� � �������(0 �������������, 1 �����������).
     */

    void Insert_Word(Word& w1, Word& w2, int a, int b, int d);

    /**
     * @brief ��������� ������ ����� � �������.
     *
     * @param w ������ ����.
     */

    void Insert_First_Word(std::vector<struct Word>& w);

    /**
     * @brief �������� ������� ���������� � �������.
     *
     * @param left ����� ������� �����.
     * @param right ������ ������� �����.
     * @param top ������� ������� �����.
     * @param bottom ������ ������� �����.
     */

    void Print(int left, int right, int top, int bottom);

    /**
    * @brief ���������� ������� �������.
    *
    * @param left ����� ������� �����.
    * @param right ������ ������� �����.
    * @param top ������� ������� �����.
    * @param bottom ������ ������� �����.
    */

    void Defining_Boundaries(int& left, int& right, int& top, int& bottom);

    /**
     * @brief ������� ��� '#' � ������� � �������� �� ' '.
     */

    void Grill_Replacement();

    /**
    * @brief ������� � ������� �����, ������� �� ����� � �������.
    *
    * @param w ������ ����.
    */

    void Invalid_words(std::vector<struct Word> w); 

    //���

    /**
     * @brief ���������� ������������ ����������.
     */

    void Make_Visualization();

    /**
     * @brief ������� ������� ���� � �������.
     *
     * @param left ����� ������� �����.
     * @param right ������ ������� �����.
     * @param top ������� ������� �����.
     * @param bottom ������ ������� �����.
     */

    void Calculate_Percentage(int left, int right, int top, int bottom);

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

    bool Find_Centre_Intersection_left(const Word w1, const Word w2, int& a, int& b, int p);

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

    bool Find_Centre_Intersection_right(const Word w1, const Word w2, int& a, int& b, int p);

    /**
     * @brief ���������� ������� ���������� ������ �������.
     */

    void Make_Criss_Cross_2();

public:

    /**
     * @brief �����������.
     *
     * @param filename_in ��� ����� �����.
     * @param filename_out ��� ����� ������.
     */

    Criss_Cross(const std::string& filename_in, const std::string& filename_out) {
        if (check(filename_in) == true) {
            In.open(filename_in);
            if (!In) {
                std::wcerr << L"������ �������� �����";
            }
            else {
                Out.open(filename_out);
                if (Count_number_words() == false) {
                    std::wcerr << L"������: ���� ����! ��������� ����" << std::endl;
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
            std::wcerr << L"������: �������� ����� �����������" << std::endl;
        }
    }

    /**
    * @brief ����������.
    */

    ~Criss_Cross() {
        In.close();
        Out.close();
    }

    /**
    * @brief ���������� ������� ����������.
    */

    void Make_Criss_Cross();
};


