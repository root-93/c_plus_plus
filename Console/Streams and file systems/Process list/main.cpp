#include <sys/sysinfo.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    constexpr long MB = 1024 * 1024;
    constexpr int min = 60;
    constexpr int hours = min * 60;

    struct sysinfo si;
    sysinfo(&si);
    cout << setw(15) << "uptime : " << (int)si.uptime/hours << ":" << (int)(si.uptime % hours) / min << endl;
    cout << setw(15) << "freeram : " << si.freeram / MB << "MB" << endl;
    cout << setw(15) << "totoalram : " << si.totalram /MB << "MB" << endl;
    cout << setw(15) << "proc count : " << si.procs << endl;
}