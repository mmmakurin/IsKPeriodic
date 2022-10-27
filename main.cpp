#include <iostream>
#include <string>
using namespace std;

void computeLPS(string pat, int* lps) // Префиксная функция и формирование массива lps для алгоритма КМП
{
    int j = 0;

    lps[0] = 0; // lps[0] всегда 0 

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void IsKPeriodic(int K, const string& txt) // функция проверки кратности на основе алгоритма КМП
{
    if (K < 1) // проверка условия K > 0
    {
        cout << "K должно быть больше 0" << endl;
    }
    else
    {
        string pat; // формируем подстроку, беря начальные символы строки по колличеству К
        for (int i = 0; i < K; ++i)
            pat.push_back(txt[i]);

        int* lps = new int[pat.size()];

        computeLPS(pat, lps);

        int i = 0;
        int j = 0;
        int value = 0;
        while (i < txt.size()) {
            if (pat[j] == txt[i])
            {
                j++;
                i++;
            }
            if (j == pat.size()) {
                value++; // считаем совпадения
                j = lps[j - 1];
            }

            else if (i < txt.size() && pat[j] != txt[i]) {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    i = i + 1;
                }
            }
        }
        if (K * value == txt.size()) // если количество найденных совпадений, умноженное на К, равно длине строки, то строка кратна К
            cout << "строка " << txt << " кратна " << K << endl;
        else cout << "строка " << txt << " не кратна " << K << endl; // иначе не кратна
        delete[] lps;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    string txt = "abcabcabcabcabcabc"; // проверяемая строка
    int K = 3; // проверка строки на кратность
    IsKPeriodic(K, txt);
    return 0;
}