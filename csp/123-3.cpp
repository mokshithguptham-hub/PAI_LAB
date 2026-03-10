#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

long long getNumber(string s, unordered_map<char,int>& mp)
{
    long long num = 0;
    for(char c : s)
        num = num * 10 + mp[c];
    return num;
}

bool isValid(vector<string>& words, string result, unordered_map<char,int>& mp)
{
    for(string w : words)
        if(mp[w[0]] == 0 && w.length() > 1)
            return false;

    if(mp[result[0]] == 0 && result.length() > 1)
        return false;

    long long sum = 0;
    for(string w : words)
        sum += getNumber(w, mp);

    long long res = getNumber(result, mp);

    return sum == res;
}

bool solve(vector<char>& letters, int index, unordered_map<char,int>& mp,
           vector<bool>& used, vector<string>& words, string result)
{
    if(index == letters.size())
    {
        if(isValid(words, result, mp))
        {
            cout << "\nSolution Found:\n";
            for(auto &p : mp)
                cout << p.first << " = " << p.second << endl;

            cout << "\nNumbers:\n";
            long long sum = 0;
            for(string w : words)
            {
                long long val = getNumber(w, mp);
                cout << val << " ";
                sum += val;
            }

            cout << "= " << getNumber(result, mp) << endl;

            return true;
        }
        return false;
    }

    for(int d = 0; d <= 9; d++)
    {
        if(!used[d])
        {
            used[d] = true;
            mp[letters[index]] = d;

            if(solve(letters, index + 1, mp, used, words, result))
                return true;

            used[d] = false;
            mp.erase(letters[index]);
        }
    }

    return false;
}

int main()
{
    int n;
    cout << "Enter number of words to add: ";
    cin >> n;

    vector<string> words(n);
    cout << "Enter the words:\n";
    for(int i = 0; i < n; i++)
        cin >> words[i];

    string result;
    cout << "Enter result word: ";
    cin >> result;

    set<char> uniqueLetters;

    for(string w : words)
        for(char c : w)
            uniqueLetters.insert(c);

    for(char c : result)
        uniqueLetters.insert(c);

    if(uniqueLetters.size() > 10)
    {
        cout << "Too many unique letters (max 10 allowed)." << endl;
        return 0;
    }

    vector<char> letters(uniqueLetters.begin(), uniqueLetters.end());
    unordered_map<char,int> mp;
    vector<bool> used(10,false);

    if(!solve(letters, 0, mp, used, words, result))
        cout << "No solution exists." << endl;

    return 0;
}
