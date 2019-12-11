//Returning values from thread using std::promise and std::future.

#include <iostream>
#include <thread>
#include <future>

using namespace std;

void initalizer(promise<int> *promObj){
    cout << "Inside thread" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    promObj->set_value(666);
}
int main()
{
    promise<int> promiseObj;
    future<int> futureObj = promiseObj.get_future();
    thread t(initalizer, &promiseObj);
    cout << futureObj.get() << endl;
    t.join();
    return 0;
}
