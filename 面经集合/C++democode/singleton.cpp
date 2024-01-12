// TODO: 单例模式示例代码
class Singleton{
private:
    static Singleton* instance;
    Singleton() {}

public:
    // 禁止拷贝构造函数和赋值操作
    Singleton(const Singleton& ) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance(){
        if(instance == nullptr){
            instance = new Singleton();
        }
        return instance;
    }
};

// Singleton* instance = Singleton::getInstance();
// Singleton singleton = Singleton();
// Singleton* singleton = new Singleton();