//Poor example of event handling between threads.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class Application{
    mutex m_mutex;
    bool m_bDataLoaded;
public:
    Application(): m_bDataLoaded(false){}
    void loadData(){
        //Make this thread sleep for while for clarification.
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Loading data from XML" << endl;
        //Acquire lock for the rest of the program block
        lock_guard<mutex> guard(m_mutex);
        //Set flag tell that data is loaded.
        m_bDataLoaded=true;

    }
    void mainTask(){
        cout << "Do some handshaking." << endl;

        //Acquire the lock.
        m_mutex.lock();
        //Check if flag is set to true or not.
        while(m_bDataLoaded==false){
            //Release the lock.
            m_mutex.unlock();
            //Make this thread sleep for while, aka idle, till XML-data is loaded.
            this_thread::sleep_for(chrono::milliseconds(100));
            //Acquire the lock for checking the loop condition.
            m_mutex.lock();
        }
        //Release the lock.
        m_mutex.unlock();
        //Do processing on loaded data.
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
