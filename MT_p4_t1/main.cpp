//A practical example of race condition.

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class Wallet{
    int mMoney;
public:
    Wallet(): mMoney(0){};
    int getMoney(){return mMoney;}
    void addMoney(int money){
        while((money--)>0){
            mMoney++;
       }
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
