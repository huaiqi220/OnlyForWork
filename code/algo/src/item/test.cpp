#include <iostream>

// 基类
class Base {
public:
    // 虚函数
    virtual void display() {
        std::cout << "Base::display()" << std::endl;
    }
};

// 派生类
class Derived : public Base {
public:
    // 重写了基类的虚函数
    void display() override {
        std::cout << "Derived::display()" << std::endl;
    }

    // 派生类特有的函数
    void additionalFunction() {
        std::cout << "Derived::additionalFunction()" << std::endl;
    }
};

// int main() {
//     Base* basePtr;
//     Derived derivedObj;

//     // 将派生类对象的地址赋给基类指针
//     basePtr = &derivedObj;

//     // 调用虚函数，将会执行派生类的虚函数
//     basePtr->display(); // 输出：Derived::display()

//     // 由于基类指针的静态类型是 Base*，因此不能直接调用派生类特有的函数
//     // basePtr->additionalFunction(); // 这行代码会导致编译错误

//     // 但如果我们知道 basePtr 指向的对象是 Derived 类的实例，可以使用类型转换来调用派生类特有的函数
//     static_cast<Derived*>(basePtr)->additionalFunction(); // 输出：Derived::additionalFunction()

//     return 0;
// }
