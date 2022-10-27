#include <iostream>
#include <string>
using namespace std;

void computeLPS(string pat, int* lps)// Prefix function and lps array formation for the KMP algorithm
{
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

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

void IsKPeriodic(int K, const string& txt) // multiplicity check function based on the KMP algorithm
{
    if (K < 1) // checking the condition K > 0
    {
        cout << "K must be greater than 0" << endl;
    }
    else
    {
        string pat; // form a substring by taking the initial characters of the string by the number К
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
                value++; // counting coincidences
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
        if (K * value == txt.size()) // if the number of matches found multiplied by K is equal to the length of the string, then the string is a multiple of K
            cout << "The string " << txt << " is a multiple of " << K << endl;
        else 
            cout << "Cтрока " << txt << " is not a multiple of " << K << endl; // otherwise it is not a multiple
        delete[] lps;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    string txt = "abcabcabcabcabcabc"; // the string being checked
    int K = 3; // checking the string for multiplicity
    IsKPeriodic(K, txt);
    return 0;
}