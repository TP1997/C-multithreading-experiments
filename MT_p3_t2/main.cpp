//How to pass references to thread.
#include <iostream>
#include <thread>

using namespace std;

void threadCallback(int const &x){
    int &y=const_cast<int &>(x);
    y=100;
    cout << "Inside created thread, x = " << x << endl;
}
int main()
{
    int x=9;
    cout << "In main thread : Before new thread start, x = " << x << endl;
    thread threadObj(threadCallback, ref(x));
    threadObj.join();
    cout << "In main thread : After new thread joins, x = " << x << endl;
    return 0;
}
