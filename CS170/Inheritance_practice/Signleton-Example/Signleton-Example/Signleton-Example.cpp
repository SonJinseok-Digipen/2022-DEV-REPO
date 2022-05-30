/*
//Name :Jinseok Son
//Date :2022-5-29
////Description : Practice SingleTon

*/
#include<iostream>
class MoreModifierExamples
{
public:
    // until we reach another tag, all variables and functions
    // will be public
    int publicIntegar;
    int anotherExample;
private:
    // Now, they'll be private
    void PrivateFunction() {}
    double safeValue;
protected:
    // And now... protected
    float protectedNumber;
    int AlsoProtected() { return 0; }
};

class Fun
{
public:
    inline static int count=0;
    static void PrintCount()
    {
        std::cout << count << '\n';
    }
    static void AddCount(int number)
    {
        count += number;
    }
    void hello()
    {
        static int hello = 0;
        hello++;
        std::cout << hello << '\n';
    }


protected:

private:

};




int main()
{
    Fun::PrintCount();
    Fun::AddCount(1000);
    Fun::PrintCount();
    Fun fun;
    fun.hello();
    fun.hello();
    
}

