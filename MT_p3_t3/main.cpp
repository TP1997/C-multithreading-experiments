//Assigning pointer to member function of a class as thread function:

#include <iostream>
#include <thread>

using namespace std;

class Foo{
public:
    Foo()=default;
    void sampleMemFunc(int x){
        cout << "Inside member function " << x << endl;
    }

};

int main()
{
    Foo fooObj;
    int x=10;
    thread tObj(&Foo::sampleMemFunc, &fooObj, x);
    tObj.join();
    return 0;
}
