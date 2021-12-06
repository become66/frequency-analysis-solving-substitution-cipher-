#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <cmath>
#include <cstdlib> 
#include <ctime>   

#define ull unsigned long long
#define mutatedMaxWidth 15
#define repeatTime 3000
#define processingTime 20

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

double getScore(const string &plainText, const unordered_map<string, double> &Quadrigram){
    double score = 0;
    string quadrStr = "." + plainText.substr(0,3); //"." is dummy
    for(size_t i = 3; i < plainText.size(); ++i){
        getNewQuastr(quadrStr, plainText[i]);
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
    std::ifstream ifs("cypherText.txt", std::ios::in);
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
    // cout<<sortedLetterString.size()<<","<< mappedString.size()<<"(should both be 26)\n";
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

string getMutatedMappedString(const string &mappedString, int maxWidth){
    try {
        if (maxWidth < 1 || maxWidth > 26) {
            throw "maxWidth should > 0 && < 26!";
        }
    }
    catch (const char* message) {
        std::cout << message << std::endl;
        exit(-1);
    }
    
    string mutatedMappedString = mappedString;
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
    swap(mutatedMappedString[firstIdx], mutatedMappedString[secondIdx]);
    return mutatedMappedString;
}

pair<double,pair<string, string>> getNearOptimalDecrytionKey(const unordered_map<string, double> &Quadrigram, const string &sortedLetterString , const string &cypherText){
    double highestScore = 0, mutatedScore = 0;
    string  mappedString, mutatedMappedString; 
    unordered_map<char, char> decryptDictionary, mutatedDecryptDictionary;
    string plainText, mutatedplainText;
    //initialization first generation
    mappedString = "ZXQJKVBPYGFWMUCLDRHSNIOATE"; // use most common frequencyOrderedString as innitial mappedString
    decryptDictionary = getDecryptDictionary(sortedLetterString, mappedString);
    plainText = decrypt(cypherText, decryptDictionary);
    highestScore = getScore(plainText, Quadrigram);

    // cout<<"current highestScore: "<<highestScore<<"\n";
    for(int i = 0; i < repeatTime; i++){
        mutatedMappedString = getMutatedMappedString(mappedString, mutatedMaxWidth);
        mutatedDecryptDictionary = getDecryptDictionary(sortedLetterString, mutatedMappedString);
        mutatedplainText = decrypt(cypherText, mutatedDecryptDictionary);
        mutatedScore = getScore(mutatedplainText, Quadrigram);
        if(mutatedScore > highestScore){
            mappedString = mutatedMappedString;
            decryptDictionary = mutatedDecryptDictionary;
            plainText = mutatedplainText;
            highestScore = mutatedScore;
            // cout<<"current highestScore: "<<highestScore<<"\n";
            // cout<<"current plainText: "<<plainText<<"\n";
            // cout<<"current mappedString: "<<mappedString<<"\n";
        }
    }
    pair<double,pair<string, string>> best;
    best.first = highestScore;
    best.second.first = mappedString;
    best.second.second = plainText;
    return best;
}

int main() {
    srand( time(NULL) );

    map<char,ull> countMap;
    for(char c = 'A'; c <= 'Z'; c++){
        countMap[c] = 0;
    }
    string cypherText = readCypherText(countMap);
    string sortedLetterString = getsortedLetterString(countMap);
    unordered_map<string, double> Quadrigram = getQuadrigram();

    set<pair<double,pair<string, string>>> decrptionKeys;
    for(int i = 0; i < processingTime; ++i){
        decrptionKeys.insert(getNearOptimalDecrytionKey(Quadrigram, sortedLetterString, cypherText));
    }
    // cout<<decrptionKeys.size()<<"\n";

    pair<double,pair<string, string>> bestDecrptionKey;
    set<pair<double,pair<string, string>>>::reverse_iterator it = decrptionKeys.rbegin();
    for(int i = 0; i < 3; ++i, ++it){
        bestDecrptionKey = *it;
        cout<<"No. "<<(i+1)<<" posible:\n\n";
        cout<<"encryption mappingDictionary:"<<"\n";
        cout<<sortedLetterString<<"\n";
        cout<<"           ||\n           \\/\n"; //arrow
        cout<<bestDecrptionKey.second.first<<"\n\n"; // mappedString

        for(char &c: bestDecrptionKey.second.second){ // convert to lower case
            c = tolower(c);
        }
        cout<<"plainText: "<<bestDecrptionKey.second.second<<"\n"; // plainText
        cout<<"------------------------------------------------------------\n";
    }

    return 0;
}