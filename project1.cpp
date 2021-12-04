#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <set>
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
            double num = log10((double)stoi(count)/4224127913); // 4224127913 is the total count of Quadrigram
            ret[word] = num;
        }
    }
    ifs.close();
    return ret;
}


void getNewQuastr(string &pre, char nextC){
    pre = pre.substr(1,3);
    pre.push_back(nextC);
}

double getScore(string str, unordered_map<string, double> &Quadrigram){
    double score = 0;
    string quadrStr = "." + str.substr(0,3); //"." is dummy
    for(size_t i = 3; i < str.size(); ++i){
        getNewQuastr(quadrStr, str[i]);
        unordered_map<string,double>::const_iterator it = Quadrigram.find (quadrStr);
        if ( it == Quadrigram.end() ){ // not find
            score += log10(0.01/4224127913); // 4224127913 is the total count of Quadrigram
        } 
        else{
            score += it->second;
        }
    }
    return score;
}

string readCypherText(map<char,ull> &countMap){
    string cypherText;
    std::ifstream ifs("test.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        char c;
        while (!ifs.eof()) {
            c = ifs.get();
            if(c <= 'Z' && c >= 'A'){
                cypherText.push_back((char)c);
                countMap[(char)c]++;
            }
            else if(c <= 'z' && c >= 'a'){
                cypherText.push_back((char)c-'a'+'A');
                countMap[(char)(c-'a'+'A')]++;
            }
        }
    }
    ifs.close();
    return cypherText;
}

set<pair<ull,char>> getSortedOrder(map<char,ull> &countMap){
    set<pair<ull,char>> sortedOrder;
    for(const auto &pair:countMap){
        sortedOrder.insert(make_pair(pair.second, pair.first));
    }
    return sortedOrder;
}

unordered_map<char, char> getDecryptDictionary(set<pair<ull,char>> &sortedOrder){
    unordered_map<char, char> decryptDictionary;
    string frequencyOrderedString = "ZXQJKVBPYGFWMUCLDRHSNIOATE";
    int i = 0;
    for(auto &pair:sortedOrder){
        // cout<<pair.first<<","<<pair.second<<"\n";
        decryptDictionary[pair.second] = frequencyOrderedString[i];
        ++i;
    }
    return decryptDictionary;
}


int main() {
    map<char,ull> countMap;
    for(char c = 'A'; c <= 'Z'; c++){
        countMap[c] = 0;
    }
    set<pair<ull,char>> sortedOrder;
    string cypherText;
    unordered_map<char, char> decryptDictionary;
    unordered_map<string, double> Quadrigram;
    
    cypherText = readCypherText(countMap);
    sortedOrder = getSortedOrder(countMap);
    decryptDictionary = getDecryptDictionary(sortedOrder);
    Quadrigram = getQuadrigram();


    // for(auto &pair: decryptDictionary){
    //     cout<<pair.first<<","<<pair.second<<"\n";
    // }




    // for(auto& pair: Quadrigram){
    //     cout<<pair.first<<","<<pair.second<<"\n";
    // }
    // cout<<getScore("Theinstallationsaresiteresponsivetheprocessisacollaborationwiththeimmediatecommunitiesinlocalspacestheinstallationsconsistedoftwolayersofsoundaseriesofcompositionscreatedfromlullabiescontributedbyfathersfromtheimmediatecommunityandasetofmotionactivatedsoundstationsaudiencespresencepromptsmultitudesofstoriestounfoldaudiodocumentariescreatedinconversationwithfathersonfederalprobationinstallationsareanopencalltothecommunitythroughaparticipatorylocationbasedcontributoryaudioaugmentedrealityplatformthatcanbeexperiencedonlinethroughamapandinphysicalspaceorbywalkingtheneighborhoodsasanaugmentedaudioappthemapcreatesasonicrepresentationofmemorieslullabiesvisionsanddesirescocreatingnewcollectivesocialmemories", Quadrigram)<<"\n";


    

    return 0;
}




