//Passing arguments to threads.
#include <iostream>
#include <string>
#include <thread>

using namespace std;
chrono::milliseconds dur(1000);

void threadCallback(int x, string s){
    cout << "Passed number: " << x << ", passed string: " << s << endl;
}
void startThread1(){
    int x=10;
    string s="Sample string";
    thread threadObj(threadCallback, x, s);
    threadObj.join();
}

void newThreadCallback(int *p){
    cout << "Inside thread: *p = " << *p << endl;
    this_thread::sleep_for(dur);
    *p=20;
}
void startThread2(){
    int *p=new int();
    *p=10;
    cout << "Inside main thread: *p = " << *p << endl;
    thread t(newThreadCallback, p);
    t.detach();
    delete p;
    p=nullptr;
}
int main()
{
    startThread2();
    this_thread::sleep_for(dur);
    return 0;
}
