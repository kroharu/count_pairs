#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
//#include <ncurses.h>
#include <conio.h>
#include <stdio.h>
#include <sstream>
#include <locale.h>
#include <ctype.h>
#include <algorithm>

using namespace std;

int error(int i)
{
    if (i == 1)
        cout << "Error: Usage: count_pairs.exe [path to the txt file] [first word] [second word] [max length between words]" << endl;
        // cout << "Ошибка: Использование приложения: count_pairs.exe [путь к текстовому файлу] [первое искомое слово] [второе искомое слово] [максимальное допустимое расстояние между словами]" << endl;
    if (i == 2)
        cout << "Error: file format must be .txt" << endl;
        // cout << "Ошибка: Необходимо, чтобы файл был с расширением .txt" << endl;
    if (i == 3)
        cout << "Error: no such file or path" << endl;
        // cout << "Ошибка: Указанного файла или пути не существует" << endl;
    return 0;
}

int main(int argc, char **argv)
{ 
    setlocale(LC_ALL, "rus");
 
    int         n = 0, k = 0, col = 0, rasst, num;
    string      c1, c2, s, s2;
    ifstream    fin;
    std::string::size_type i;

    if (argc != 5)
        return (error(1));
    if (strcmp(argv[1] + strlen(argv[1]) - 4, ".txt"))
        return (error(2));
    c1 = argv[2];
    c2 = argv[3];
    rasst = atoi(argv[4]);
    fin.open(argv[1]);
    if (fin.good())
    {
        while (std::getline(fin, s))
        {
            std::replace_if(s.begin(), s.end(), ::ispunct, ' ');
            std::istringstream iss(s);
            while (iss >> s2)
            {
                if (s2 == c1)
                {
                    num = 0;
                    while (iss >> s2)
                    {
                        num++;
                        if (s2 == c2 && num <= rasst + 1)
                        {
                            col++;
                            break ;
                        }
                    }
                }
            }
        }
        fin.close();
    }
    else
        return (error(3));
    cout << "Unique pairs in this file: " << col << endl;
    // cout << "Уникальных пар в файле: " << col << endl;
    return 0;
}