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
#include <cstdlib> 
#include <ctime>   

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

double getScore(const string &str, unordered_map<string, double> &Quadrigram){
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

string getsortedLetterString(map<char,ull> &countMap){
    string sortedLetterString;
    sortedLetterString.reserve(26);
    set<pair<ull,char>> sortedOrder;
    for(const auto &pair:countMap){
        sortedOrder.insert(make_pair(pair.second, pair.first));
    }
    for(auto &pair:sortedOrder){
        sortedLetterString.push_back(pair.second);
    }
    return sortedLetterString;
}

unordered_map<char, char> getDecryptDictionary(const string &sortedLetterString,const string &mappedString){
    cout<<sortedLetterString.size()<<","<< mappedString.size()<<"(should both be 26)\n";
    unordered_map<char, char> decryptDictionary;
    for(size_t i = 0; i < sortedLetterString.size(); ++i){
        decryptDictionary[sortedLetterString[i]] = mappedString[i];
    }
    return decryptDictionary;
}

string decrypt(const string &cypherText, const unordered_map<char, char> &decryptDictionary){
    string plainText = cypherText;
    for(size_t i = 0; i < plainText.size(); i++){
        plainText[i] = decryptDictionary.at(cypherText[i]); // same effect with decryptDictionary[cypherText[i]] and can pass compile
    }
    return plainText;
}

void getNewMappedString(string &mappedString, int maxWidth){
    try {
        if (maxWidth < 1 || maxWidth > 26) {
            throw "maxWidth should > 0 && < 26!";
        }
    }
    catch (const char* message) {
        std::cout << message << std::endl;
    }
    //take maxWidth = 6 for example
    int width, pos; 
    if(maxWidth == 1){
        width = 1; 
    }
    else{
        width = rand()%(maxWidth-1) + 1; // width = 1~6
    }

    pos = rand()%(26 - width); // if width = 6 =>  pos = 0~19; if width = 1 => pos = 0~24
    int firstIdx = pos, secondIdx = pos + width;
    swap(mappedString[firstIdx], mappedString[secondIdx]);
}

int main() {
    srand( time(NULL) );

    map<char,ull> countMap;
    for(char c = 'A'; c <= 'Z'; c++){
        countMap[c] = 0;
    }
    string sortedLetterString;
    string cypherText;
    unordered_map<char, char> decryptDictionary;
    unordered_map<string, double> Quadrigram;
    string mappedString = "ZXQJKVBPYGFWMUCLDRHSNIOATE"; // use most common frequencyOrderedString as innitial mappedString
    int preScore = 0, newScore = 0;
    
    cypherText = readCypherText(countMap);
    sortedLetterString = getsortedLetterString(countMap);
    decryptDictionary = getDecryptDictionary(sortedLetterString, mappedString);
    Quadrigram = getQuadrigram();

    








    // for(auto& pair: Quadrigram){
    //     cout<<pair.first<<","<<pair.second<<"\n";
    // }
    // cout<<getScore("Theinstallationsaresiteresponsivetheprocessisacollaborationwiththeimmediatecommunitiesinlocalspacestheinstallationsconsistedoftwolayersofsoundaseriesofcompositionscreatedfromlullabiescontributedbyfathersfromtheimmediatecommunityandasetofmotionactivatedsoundstationsaudiencespresencepromptsmultitudesofstoriestounfoldaudiodocumentariescreatedinconversationwithfathersonfederalprobationinstallationsareanopencalltothecommunitythroughaparticipatorylocationbasedcontributoryaudioaugmentedrealityplatformthatcanbeexperiencedonlinethroughamapandinphysicalspaceorbywalkingtheneighborhoodsasanaugmentedaudioappthemapcreatesasonicrepresentationofmemorieslullabiesvisionsanddesirescocreatingnewcollectivesocialmemories", Quadrigram)<<"\n";

    // for(int i = 0; i < 1000; i++){
    //     char A,B;
    //     getExchangeCh(A,B,8);
    //     cout<<A<<","<<B<<"\n";
    // }

    return 0;
}




