#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken(){};
        Chicken(int _age) : age(_age) {};
        Chicken(int _age, const char *_name) : age(_age) 
        {
            if(_name != nullptr){
                int len = strlen(_name) + 1;
                name = new char[len];
                for (int i = 0; i < len; i++)
                    name[i] = _name[i];
            } else {
                _name = nullptr;
            }
        };
        Chicken(const Chicken &_c) :age(_c.age)
        {
            if(_c.name != nullptr){
                int len = strlen(_c.name) + 1;
                name = new char[len];
                for (int i = 0; i < len; i++)
                    name[i] = _c.name[i];
            } else {
                name = nullptr;
            }
        };

        Chicken operator=(const Chicken &_c) 
        {
            if (this == &_c)
                return *this;
            
            if (name != nullptr)
            {
                delete [] name;
                name = nullptr; 
            }

            age = _c.age;
            if(_c.name != nullptr){
                int len = strlen(_c.name) + 1;
                name = new char[len];
                for (int i = 0; i < len; i++)
                    name[i] = _c.name[i];
            }
            
            return *this;
        };

        ~Chicken()
        {
            if (name != nullptr)
                delete[] name;
        };

        void setAge(int _age)
        {
            age = _age;
        };

        void setName(const char *_name)
        {
            if(_name != nullptr){
                int len = strlen(_name) + 1;
                char *temp = new char[len];
                for (int i = 0; i < len; i++)
                    temp[i] = _name[i];
                
                if(name != nullptr)
                    delete[] name;
                name = temp;
            } else {
                if(name != nullptr)
                    delete [] name;
                name = nullptr;
            }
        };

        const char *getName() const
        {
            return name;
        };

        const int &getAge() const
        {
            return age;
        };
};

int main(){ 
    auto print = [](const Chicken &c){ 
        std::cout << "Hi, everyone! My name is " << c.getName()  
                  << ", I am " << c.getAge() << " years old." << std::endl; 
    }; 
    Chicken c(24, "Kunkun"); 
    print(c); 

    Chicken d; 
    d = c; 
    print(d); // 测试【赋值运算符】是否正确，能正确输出给 20 分 

    Chicken a = c; 
    print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分 

    c.setName("Xukun Cai"); 
    print(c); 
    print(a); 
    print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分 

    Chicken b; 
    b = d = c; 
    print(b); 
    print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分 

    c.setName(c.getName());
    std::cout << "c.name = " << c.getName() << std::endl;
    return 0;
}