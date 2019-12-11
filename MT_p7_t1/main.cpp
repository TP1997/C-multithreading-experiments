//Event handling between threads using condition variable.

#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Application{
    mutex m_mutex;
    condition_variable m_condVar;
    bool m_bDataLoaded;
public:
    Application(): m_bDataLoaded(false){};
    void loadData(){
        //Make this thread sleep for while for clarification.
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Loading data from XML" << endl;
        //Acquire lock for the rest of the program block
        lock_guard<mutex> guard(m_mutex);
        //Set flag tell that data is loaded.
        m_bDataLoaded=true;
        //Notify the condition variable.
        m_condVar.notify_one();
    }
    bool isDataLoaded(){
        return m_bDataLoaded;
    }
    void mainTask(){
        cout << "Do some handshaking." << endl;
        //Acquire the lock.
        unique_lock<mutex> mlock(m_mutex);
        // Start waiting for the Condition Variable to get signaled
        // Wait() will internally release the lock and make the thread to block
        // As soon as condition variable get signaled, resume the thread and
        // again acquire the lock. Then check if condition is met or not
        // If condition is met then continue else again go in wait.
        m_condVar.wait(mlock, bind(&Application::isDataLoaded, this));
        cout << "Do processing on loaded data." << endl;
    }
};
int main()
{
    Application app;
    thread thread1(&Application::mainTask, &app);
    thread thread2(&Application::loadData, &app);

    thread2.join();
    thread1.join();

    return 0;
}
