#include<iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    string t = "";
    int chk = 0;
    for (int i = 0 ; i < s.size() ; i++) 
    {
        if(s[i] != ' ')
        {
            t += s[i];
            chk = 1;
        } 
        else if (chk)
        {
            t += ' ';
            chk = 0;
        }
    }
    if(t.back() == ' ')
    {
        t.pop_back();
    }
    cout << t << endl;
}