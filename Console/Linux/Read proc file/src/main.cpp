#include <thread>
#include <iostream>
#include <boost/filesystem.hpp>
#include <condition_variable>
#include <cstdlib>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>

namespace fs = boost::filesystem;

using namespace std;

namespace Local{
    void search(bool flag);
}

enum class Platform{
    x86,
    x64
};

struct ProcesInfo{
    string      name;
    pid_t       pid;
    string      state;
    string      user;
    uint        memSize;
    Platform    platform;
};


vector<fs::path> pids;
condition_variable rescanProcCv;
mutex m;

bool rescanProc = false;
bool rescanProcDone = false;

void exampleFunction();
void getProcPids();
void findTop(const fs::path &pidPath);
int readProcesStat(pid_t pid, ProcesInfo *info);

using namespace Local;

//=== main loop ==================================================

int main() {
    getProcPids();
    auto pid {getpid()};
    ProcesInfo info;
    readProcesStat(pid, &info);
}

//================================================================


int readProcesStat(pid_t pid, [[maybe_unused]]ProcesInfo *info){
    char pfile[256];
    constexpr uint bufferSize {4096};
    unsigned char buffer[bufferSize];
    //int stat {-1};
    
    sprintf(pfile, "/proc/%d/status", pid);
    int fd = open(pfile, 00);
    [[maybe_unused]]int bytesRead = read(fd, buffer, bufferSize);

    string result;
    stringstream ss;
    ss << buffer;
    ss >> result;

    cout << result;
    //showProcStatus(buffer, bytesRead);
    return 1;
}


void charTableToString(unsigned char *source, int lenght, string &dest){
    
}


void showProcStatus(unsigned char *data, int lenght){
    unsigned char *end {data + lenght};
    for(unsigned char *d = data; data < end; ){
        cout << d <<endl;
        while(*d++);
    }
}


void showProcess(){
    auto i  = 0;
    for (auto &&s : pids){
        cout << setw(10) << s.filename().string();
        if(!((++i)%10)) cout << endl;
    }
}

void exampleFunction(){
    thread t1(Local::search, true);
    thread t2(Local::search, false);
    
    t1.detach();
    t2.detach();

    while(true){
        getProcPids();

        {
            lock_guard<mutex> lg(m);
            cout << "Issuing rescan common... \n";
            rescanProc = true;
        }

        rescanProcCv.notify_one();

        {
            unique_lock<mutex> ul(m);
            cout << "Main thread [tid=" << this_thread::get_id() << "] is waiting to finish rescan...\n";
            rescanProcCv.wait(ul, []{return rescanProcDone;});
        }

        {
            lock_guard<mutex> lg(m);
            cout << "Main thread [tid=" << this_thread::get_id() << "] all workers finished rescan \n";
            rescanProc = false;
            rescanProcDone = false;
        }

        this_thread::sleep_for(chrono::milliseconds(10000));
    }
}


void getProcPids(){
    pids.clear();
    fs::directory_iterator end;
    fs::path proc {"/proc/"};

    auto lambda {[](const string &s){return all_of(s.begin(), s.end(), ::isdigit);}};
    fs::directory_iterator iter{proc};
    for ( ; iter != end; ++iter){
        if(lambda(iter->path().stem().string())){
            pids.push_back(iter->path());
        }
    }
    
}


void findTop(const fs::path &pidPath){
    string s(pidPath.string().rbegin(), pidPath.string().rend());
}


void Local::search(bool flag){
    auto tid = this_thread::get_id();

    while(true){
        {
            unique_lock<mutex> ul(m);
            cout << "Search thread [tid=" << tid << "] is waiting\n";
            rescanProcCv.wait(ul, []{return rescanProc;});
        }
        
        cout << "Search thread [tid=" << tid << "] is scaning...\n";
        this_thread::sleep_for(chrono::milliseconds(1000));
        auto start {chrono::steady_clock::now()};

        if(flag)
            for_each(pids.begin(), pids.begin() + pids.size() / 2, findTop);
        else
            for_each(pids.rbegin(), pids.rbegin() + pids.size() / 2, findTop);
        
        auto end {chrono::steady_clock::now()};

        {
            lock_guard<mutex> ul(m);
            cout << tid << ": Scaning ok. Size: " << pids.size() << endl;
            cout << tid << ": " << chrono::duration<double, milli>(end - start).count() << "ms" << endl;
            rescanProcDone |= true;
        }

        rescanProcCv.notify_one(); 
    }
}