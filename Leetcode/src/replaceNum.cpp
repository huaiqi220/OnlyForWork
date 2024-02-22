#include <iostream>
#include <string>

using namespace std;

string replace(string s){
    string n = "number";
    string res;
    for(auto item : s){
        if(item >= 'a' && item <= 'z'){
            res.push_back(item);
        }else{
            res += n;
        }
    }
    return res;
}

int main(){
    string s;
    cin >> s;
    string res = replace(s);
    cout << res;
}