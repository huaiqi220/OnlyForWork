#include <lc1047.h>
#include <iostream>
#include <stack>
#include <algorithm>
#include <string>


// void Solution1047::isValid()
// {
//     cout << "成功调用1047 中isValid函数" << endl;
// }

std::string Solution1047::removeDuplicates(std::string s)
{
    std::stack<char> stk;
    for(auto item : s){
        if(stk.empty()){
            stk.push(item);
            continue;
        }else{
            if(stk.top() == item){
                stk.pop();
                continue;
            }else{
                stk.push(item);
            }
        }
    }
    std::string str;
    while(!stk.empty()){
        str += stk.top();
        stk.pop();
    }
    reverse(str.begin(),str.end());
    return str;
}

std::string Solution1047::removeDuplicates2(std::string s)
{
    std::string str;
    for(char c : s){
        if(!str.empty() && str.back() == c){
            str.pop_back();
        }else{
            str.push_back(c);
        }
    }
    return str;

}
