#include <iostream>
#include <thread>

using namespace std;

void threadCallback(int i){
    cout<<"Inside thread"<<i<<" :: ID ="<<this_thread::get_id()<<endl;
}
int main()
{
    thread threadObj1(threadCallback, 1);
    thread threadObj2(threadCallback, 2);

    if(threadObj1.get_id() != threadObj2.get_id())
        cout<<"Both threads have different id:s"<<endl;

    cout<<"From main thread :: ID of thread1 ="<<threadObj1.get_id()<<endl;
    cout<<"From main thread :: ID of thread2 ="<<threadObj2.get_id()<<endl;

    threadObj1.join();
    threadObj2.join();
    return 0;
}
