
#include<string>
#include<iostream>
class Human
{
private:

public:
    int age=18;
    std::string name = "Human";
public:
    Human() 
    {
         age = 18;
         name = "Human";
    }
protected:
    bool name2 = false;
};

class NotHuman :public Human
{
public:
    int number = 518;
};




#include <iostream>
int main()
{
    std::cout << "Hello World!\n";
    NotHuman a;
    a.age = 100;
    a.number = 300;

}

