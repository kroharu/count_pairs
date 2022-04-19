#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
// #include <ncurses.h>
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
        cout << "Ошибка: Использование приложения: count_pairs.exe [путь к текстовому файлу] [первое искомое слово] [второе искомое слово] [максимальное допустимое расстояние между словами]" << endl;
    if (i == 2)
        cout << "Ошибка: Необходимо, чтобы файл был с расширением .txt" << endl;
    if (i == 3)
        cout << "Ошибка: Указанного файла или пути не существует" << endl;
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
        while (getline(fin, s))
        {
            replace_if(s.begin(), s.end(), ::ispunct, ' ');
            istringstream iss(s);
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
    cout << "Уникальных пар в файле: " << col << endl;
    getch();
    return 0;
}