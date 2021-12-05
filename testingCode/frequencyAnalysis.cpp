#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

#define ull unsigned long long

using namespace std;


int main() {
    map<char,ull> count;
    map<ull,char> rank;


    std::ifstream ifs("test.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        char c;
        while (!ifs.eof()) {
            c = ifs.get();
            if(c <= 'Z' && c >= 'A'){
                count[(char)c]++;
            }
            else if(c <= 'z' && c >= 'a'){
                count[(char)(c-'a'+'A')]++;
            }
        }
    }
    ifs.close();
    for(const auto &pair:count){
        rank[pair.second] = pair.first;
        cout<<pair.first<<": "<<pair.second<<"\n";
    }
    string frequencyOrder;
    for(const auto &pair:rank){
        frequencyOrder.push_back(pair.second);
    }
    reverse(frequencyOrder.begin(), frequencyOrder.end());
    cout<<frequencyOrder<<"\n";

    

    return 0;
}




