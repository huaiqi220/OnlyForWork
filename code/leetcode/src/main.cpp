#include <iostream>
#include <ListNode.h>
// #include <lc1047.h>
#include <lc150.h>




int main() {
    std::cout << "Hello, CMake!" << std::endl;
    ListNode* node = new ListNode();
    std::cout << "正确引入了node头文件" << std::endl;
    Solution150 solution;
    std::vector<std::string> str({"10","6","9","3","+","-11","*","/","*","17","+","5","+"});
    int res = solution.evalRPN(str);
    std::cout << res << std::endl;
    return 0;
}