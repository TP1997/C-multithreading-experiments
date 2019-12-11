#include <iostream>
#include <thread>

using namespace std;

//Thread wrapper following RAII-idiom
class ThreadRAII{
    thread &m_thread;
public:
    ThreadRAII(thread &threadObj): m_thread(threadObj){

    }
    ~ThreadRAII(){
        if(m_thread.joinable()){
            m_thread.detach();
        }
    }
};

void threadCallback(){
    for(int n=0; n<10000; n++)
        cout<<"thread function executing..."<<endl;
}
int main()
{
    thread threadObj(threadCallback);

    //If this line is commented, the program will crash.
    //Hence threadObj's destructor will terminate the program & throw execption.
    ThreadRAII wrappedThreadObj(threadObj);
    return 0;
}
