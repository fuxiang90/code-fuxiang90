#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int main()
{
    int n;
    vector<int > data;
    cin>>n;
    for(int i = 0 ; i < n ; ++i){
        int num;
        cin>>num;
        data.push_back(num);
    }
    int result = n;
    for(int i = n -1 ; i >= 0 ; --i){
        if(data[i] > data[i-1]){
            result --;
        }else{
            break;
        }
    }
    cout << result <<endl;
    return 0;
}
