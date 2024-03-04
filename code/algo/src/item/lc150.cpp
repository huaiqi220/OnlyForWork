#include "lc150.h"
#include <string>
#include <vector>
#include <stack>

using namespace std;

int Solution150::evalRPN(std::vector<std::string> &tokens)
{
    stack<int> temp;
    for(auto item : tokens){
        if(item != "+" && item != "-" && item != "*" && item != "/"){
            temp.push(stoi(item));
        }else if(item == "+"){
            int n2 = temp.top();
            temp.pop();
            int n1 = temp.top();
            temp.pop();
            temp.push(n1 + n2);
        }else if(item == "-"){
            int n2 = temp.top();
            temp.pop();
            int n1 = temp.top();
            temp.pop();
            temp.push(n1 - n2);
        }else if(item == "*"){
            int n2 = temp.top();
            temp.pop();
            int n1 = temp.top();
            temp.pop();
            temp.push(n1 * n2);
        }else if(item == "/"){
            int n2 = temp.top();
            temp.pop();
            int n1 = temp.top();
            temp.pop();
            temp.push(n1 / n2);
        }

    }
    return temp.top();
}