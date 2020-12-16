#include <iostream>
#include <string>
#include <math.h>

using namespace std;


void printPascalTriangel(const int n);
constexpr uint number(const uint i);

int main(){
    int i;
    cout << "Liczna poziomów (max 10): ";
    cin >> i;
    if(i > 10)
        cout << "wartość za duża" << endl;
    else if(i < 2)
        cout << "wartość za mała" << endl;
    else
        printPascalTriangel(i);
}



void printPascalTriangel(const int n){
    for(int i = 0 ; n > i ; i++){
        auto x = 1;
        cout << string((n - i - 1) * (n / 2), ' ');
        for (int j = 0; j <= i; j++){
            auto y = x;
            x = x * (i - j) / (j + 1);
            auto space = number(x) - 1; 
            cout << y << string(n - 1 - space - n%2, ' '); 
        }
        cout << endl;
    }
}


constexpr uint number(const uint i){
    return i > 0 ? (int)log10((double)i) + 1 : 1;
}
