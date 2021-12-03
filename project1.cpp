#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <cmath>

#define ull unsigned long long

using namespace std;





unordered_map<string, double> getQuadrigram(){
    
    unordered_map<string, double> ret;

    std::ifstream ifs("english_quadgrams.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        string str;
        while (!ifs.eof()) {
            getline(ifs,str); // each line is "word count"
            string word, count;
            int i = 0;
            while(str[i] != ' '){
                word.push_back(str[i]);
                ++i;                
            }
            ++i;
            while(str[i] != '\0'){
                count.push_back(str[i]);
                ++i;
            }
            // cout<<word<<","<<count<<"\n";
            double num = log10((double)stoi(count)/4224127913); // 4224127913 is the total count
            ret[word] = num;
        }
    }
    ifs.close();
    return ret;
}




int main() {
    // map<char,ull> count;
    // map<ull,char> rank;


    // std::ifstream ifs("test.txt", std::ios::in);
    // if (!ifs.is_open()) {
    //     cout << "Failed to open file.\n";
    // } 
    // else {
    //     char c;
    //     while (!ifs.eof()) {
    //         c = ifs.get();
    //         if(c <= 'Z' && c >= 'A'){
    //             count[(char)c]++;
    //         }
    //         else if(c <= 'z' && c >= 'a'){
    //             count[(char)(c-'a'+'A')]++;
    //         }
    //     }
    // }
    // ifs.close();
    // for(const auto &pair:count){
    //     rank[pair.second] = pair.first;
    //     cout<<pair.first<<": "<<pair.second<<"\n";
    // }
    // string frequencyOrder;
    // for(const auto &pair:rank){
    //     frequencyOrder.push_back(pair.second);
    // }
    // reverse(frequencyOrder.begin(), frequencyOrder.end());
    // cout<<frequencyOrder<<"\n";

    unordered_map<string, double> Quadrigram;
    Quadrigram = getQuadrigram();
    for(auto& pair: Quadrigram){
        cout<<pair.first<<","<<pair.second<<"\n";
    }

    

    return 0;
}




