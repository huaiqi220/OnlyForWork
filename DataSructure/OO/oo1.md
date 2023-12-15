## 什么是抽象类，C++的抽象类怎么实现

在C++中，抽象类是一种包含纯虚函数（Pure Virtual Function）的类。纯虚函数是在基类中声明但没有提供具体实现的虚函数。抽象类的主要目的是为了通过派生类（子类）提供一种接口，而不是为了实例化对象。抽象类提供了一种定义接口的方法，但它本身不能被实例化。

以下是如何在C++中定义和实现抽象类的一般方法：

```cpp
#include <iostream>

// 抽象类
class AbstractClass {
public:
    // 纯虚函数
    virtual void pureVirtualFunction() = 0;

    // 普通成员函数
    void concreteFunction() {
        std::cout << "Concrete function in abstract class." << std::endl;
    }

    // 虚析构函数
    virtual ~AbstractClass() {
        // 虚析构函数，确保派生类的析构函数被调用
    }
};

// 具体类继承抽象类
class ConcreteClass : public AbstractClass {
public:
    // 实现抽象类中的纯虚函数
    void pureVirtualFunction() override {
        std::cout << "Implementation of pure virtual function." << std::endl;
    }
};

int main() {
    // 抽象类不能被实例化
    // AbstractClass abstractObject;  // 错误，不能实例化抽象类

    // 通过指针或引用使用派生类
    ConcreteClass concreteObject;
    concreteObject.pureVirtualFunction();
    concreteObject.concreteFunction();

    // 使用抽象类指针
    AbstractClass* abstractPointer = &concreteObject;
    abstractPointer->pureVirtualFunction();
    abstractPointer->concreteFunction();

    return 0;
}
```

在上述示例中：

- `AbstractClass` 是一个抽象类，其中包含一个纯虚函数 `pureVirtualFunction()`，没有提供具体实现。
- `ConcreteClass` 是一个具体类，继承自 `AbstractClass`，并实现了 `pureVirtualFunction()`。
- 抽象类不能被实例化，但可以通过指针或引用使用派生类对象。
- 抽象类中可以包含普通成员函数和虚析构函数。

通过定义抽象类，可以确保派生类实现了抽象类中声明的接口，同时为派生类提供了一致的接口标准。