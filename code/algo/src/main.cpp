#define FIBONACCI_HELPER(n, a, b) \
    ((n) == 0 ? (a) : \
     ((n) == 1 ? (b) : \
     FIBONACCI_HELPER((n) - 1, (b), (a) + (b))))
// 定义一个宏来计算斐波那契数列的第 n 个元素
#define FIBONACCI(n) \
    ((n) <= 1 ? (n) : FIBONACCI_HELPER((n), 0, 1))


#include <iostream>
// #include <ListNode.h>
// // #include <lc1047.h>
// #include <lc150.h>
// #include <queue>
// #include <string>
// #include <qs.h>
// #include <vector>
// #include <qs.cpp>

// class Solution {
// public:
//     int compareVersion(string version1, string version2) {
//         queue<int> qv1;
//         queue<int> qv2;
//         string temp = "";
//         for(char c : version1){
//             if(c == '.'){
                
//                 qv1.push(stoi(temp));
//                 temp= "";
//             }else{
//                 temp.push_back(c);
//             }
//         }
//         qv1.push(stoi(temp));
//         temp = "";

//         for(char c : version2){
//             if(c == '.'){
//                 qv2.push(stoi(temp));
//                 temp= "";
//             }else{
//                 temp.push_back(c);
//             }
//         }
//         qv2.push(stoi(temp));
//         return compare(qv1,qv2);

//     }


//     int compare(queue<int>& q1, queue<int>& q2){
//         while(!q1.empty() || !q2.empty()){
//             int qv1 = !q1.empty() ? q1.front() : 0;
//             int qv2 = !q2.empty() ? q2.front() : 0;
//             cout << qv1 << " " << qv2 << endl;
//             if(qv1 > qv2) return 1;
//             if(qv1 < qv2) return -1;
//             if(!q1.empty()) q1.pop();
//             if(!q2.empty()) q2.pop();
//             if(q1.empty() && q2.empty()) return 0;
//         }
//         return 0;
//     }
// };


// enum class Status { OK, ERROR };






int main() {
    int n = 10;
    std::cout << "Fibonacci number at position " << n << " is: " << FIBONACCI(n) << std::endl;
    return 0;

    // std::vector<int> test = {5,7,3,78,756,3,4,9,3,34,765,324,876,344,234,65,765,32};
    // quicks q;
    // q.quicksort(test,0,test.size() -1 );
    // for(auto item : test){
    //     std::cout << item << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "Hello, CMake!" << std::endl;
    // Solution solution;
    // solution.compareVersion("1.0","1.0.0");
    // Status status = Status::OK;
    //  std::cout << static_cast<int>(status) << std::endl;
    // ListNode* node = new ListNode();
    // std::cout << "正确引入了node头文件" << std::endl;
    // Solution150 solution;
    // std::vector<std::string> str({"10","6","9","3","+","-11","*","/","*","17","+","5","+"});
    // int res = solution.evalRPN(str);
    // std::cout << res << std::endl;
    return 0;
}