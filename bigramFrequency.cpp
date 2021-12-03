#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

#define ull unsigned long long

using namespace std;

string getBigram(string &pre, char nextC){
    string ret = "";
    ret.push_back(pre[1]);
    ret.push_back(nextC);
    return ret;
}

int main() {
    map<string,ull> count;
    map<ull,string> rank;
    string bigram = "";
    int c;
    std::ifstream ifs("test.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        for(int i = 0; i < 2;){
            c = ifs.get();
            if(c <= 'Z' && c >= 'A'){
                bigram.push_back((char)c);
                i++;
            }
            else if(c <= 'z' && c >= 'a'){
                bigram.push_back((char)(c-'a'+'A'));
                i++;
            }
        }
        count[bigram]++;
        while (!ifs.eof()) {
            c = ifs.get();
            if(c <= 'Z' && c >= 'A'){
                bigram = getBigram(bigram, (char)c);
                count[bigram]++;
            }
            else if(c <= 'z' && c >= 'a'){
                bigram = getBigram(bigram, (char)(c-'a'+'A'));
                count[bigram]++;               
            }
        }
    }
    ifs.close();
    for(const auto &pair:count){
        rank[pair.second] = pair.first;
        // cout<<pair.first<<": "<<pair.second<<"\n";
    }
    vector<pair<string, int>> frequencyOrder;
    for(const auto &pair:rank){
        frequencyOrder.push_back(make_pair(pair.second,pair.first));
    }
    reverse(frequencyOrder.begin(), frequencyOrder.end());
    for(const auto &pair: frequencyOrder){
        cout<<pair.first<<":"<<pair.second<<"\n";
    }

    

    return 0;
}




