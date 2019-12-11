#include <iostream>
#include <vector>
#include <functional>
#include <thread>

using namespace std;

class WorkerThread{
public:
    void operator()(){
        cout << "Worker thread "<<this_thread::get_id()<<" is executing..."<<endl;
    }

};

int main()
{
    //Strat 10 worker threads
    vector<thread> threadList;
    for(int n=0; n<10; n++)
        threadList.push_back(thread(WorkerThread()));

    //Wait for all worker threads to finnish.
    cout<<"Waiting for all worker threads to finnish."<<endl;

    //for_each(threadList.begin(), threadList.end(), mem_fn(&thread::join));

    //Alternative solution. Using both will cause program to terminate.
    for_each(threadList.begin(), threadList.end(), [](thread &t){cout<<"Thread "<<t.get_id()<<" finished"<<endl;  t.join();});

    //Using this solution will give thread_id's as "a non-executing thread".
    for_each(threadList.begin(), threadList.end(), [](thread &t){t.join(); cout<<"Thread "<<t.get_id()<<" finished"<<endl;});

    //Safe solution: check if thread is joinable.
    for_each(threadList.begin(), threadList.end(), [](thread &t){ if(t.joinable()){cout<<"Detaching thread "<<t.get_id()<<" ..."<<endl; t.detach();} })

    cout<<"Exiting main thread..."<<endl;

    return 0;
}
