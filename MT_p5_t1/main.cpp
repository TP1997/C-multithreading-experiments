//Using mutex & lock guard to fix race conditions.

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

class Wallet{
    int mMoney;
    mutex mutex_;
public:
    Wallet(): mMoney(0){};
    int getMoney(){return mMoney;}
    void addMoney(int money){
        //mutex_.lock();
        lock_guard<mutex> lockGurad(mutex_);
        while((money--)>0){
            mMoney++;
       }
       //mutex_.unlock();
    }
};

int testMultithreadedWallet(){
    Wallet wallet;
    vector<thread> threads;
    for(int n=0; n<5; n++){
        threads.push_back(thread(&Wallet::addMoney, &wallet, 1000));
    }

    for(int n=0; n<threads.size(); n++){
        threads[n].join();
    }

    return wallet.getMoney();

}
int main()
{
    int val=0;
    for(int n=0; n<1000; n++){
        if((val=testMultithreadedWallet()) != 5000){
            cout << "Error at count " << n << ". Money in wallet = " << val << ". Should be 5000." << endl;
        }
    }
    return 0;
}
