#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <chrono>
#include <chrono>
#include <ratio>
#include <thread>
#include "header.h"

using namespace std;
using namespace std::chrono;

void runAnalysis();
void generateFile1(string input, string fileName);
void generateFile2(string fileName);
void generateFile3(string fileName);
void generateFile4();;
bool validateInputCanBeOfAnyLength(string fileName);
bool validateOutputLenght(string fileName);
bool functionIsDeterministic(string fileName);
void test1();
void test2();
void test3();
void test4();
void collisionTest();
string gen_random(const int lenght);

int main(int argc, char *argv[]) {

    Hash hash;
    string input = *argv;
    string hashString = hash.generateHash(input);
    cout << hashString << endl;
    runAnalysis();

}

void runAnalysis() {

    generateFile1("a", "file1.txt");  //Generates a file the same symbol "a"
    generateFile1("b", "file2.txt");  //Generates a file the same symbol "b"
    generateFile2("file3.txt");       //Generates a file with unique strings of 1000 symbols
    generateFile2("file4.txt");       //Generates a file with unique strings of 1000 symbols
    generateFile3("file5.txt");       //Generates a file with a strings with one unique character appended
    generateFile3("file6.txt");       //Generates a file with a strings with one unique character appended

    test1();
    test2();
    test3();
    test4();
    collisionTest();

}

void test1() {
    bool a = validateInputCanBeOfAnyLength("file1.txt");
    bool b = validateInputCanBeOfAnyLength("file2.txt");
    if(a || b) {
        cout << "1 test UNsuccessfull!" << endl;
        return;
    }
    cout << "1 test successfull!" << endl;
}

void test2() {
    bool a = validateOutputLenght("file1.txt");
    bool b = validateOutputLenght("file2.txt");
    bool c = validateOutputLenght("file3.txt");
    bool d = validateOutputLenght("file4.txt");
    bool e = validateOutputLenght("file5.txt");

    if(!(a && b && c && d && e)) {
        cout << "2 test UNsuccessfull!" << endl;
        return;
    }
    cout << "2 test successfull!" << endl;
}

void test3() {
    bool a = functionIsDeterministic("file1.txt");
    bool b = functionIsDeterministic("file2.txt");

    if(a || b) {
        cout << "3 test UNsuccessfull!" << endl;
        return;
    }
    cout << "3 test successfull!" << endl;
}

bool validateInputCanBeOfAnyLength(string fileName) {
    Hash hash;

    ifstream in(fileName);
    string test1, test2;
    in >> test1;
    test1 = hash.generateHash(test1);
    for(int i = 0; i < 9; i++) {
        in >> test2;
        if(!test1.compare(hash.generateHash(test2))) {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
}

bool validateOutputLenght(string fileName) {
    Hash hash;

    ifstream in(fileName);
    string test1;
    for(int i = 0; i < 9; i++) {
        in >> test1;
        test1 = hash.generateHash(test1);
        if(test1.length() != 64) {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
}

bool functionIsDeterministic(string fileName) {
    Hash hash;

    ifstream in(fileName);
    string test1, test2;
    in >> test1;
    test1 = hash.generateHash(test1);
    for(int i = 0; i < 9; i++) {
        in >> test2;
        if(!test1.compare(hash.generateHash(test2))) {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
}

void test4() {

    Hash hash;
    ifstream in("konstitucija.txt");
    string s, t;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 788; i++) {
        in >> t;
        s = hash.generateHash(t);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "test 4 took " + to_string(diff) + " ms" << endl;
    in.close();

}

void collisionTest() {

    Hash hash;
    string s1, s2;
    int i = 0;
    for(int i = 0; i < 10000; i++) {
        s1 = gen_random(6);
        s2 = gen_random(6);
        if(hash.generateHash(s1).compare(hash.generateHash(s2))) {
            i++;
        }
    }
    cout << to_string(i) + " collisions detected out of 10000 pairs" << endl;

}


void generateFile1(string input, string fileName) {

    ofstream of(fileName);
    for(int i = 0; i < 10; i++)
        of << input << endl;
    of.close();
}

void generateFile2(string fileName) {

    ofstream of(fileName);
    for(int i = 0; i < 10; i++)
        of << gen_random(1000) << endl;
    of.close();
}

void generateFile3(string fileName) {

    ofstream of(fileName);
    string s = gen_random(1000);
    string t;
    for(int i = 0; i < 10; i++) {
        t = s;
        t += gen_random(1);
        of << t << endl;
    }
    of.close();
}

string gen_random(const int lenght) {
    
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, sizeof(alphanum) - 1);

    tmp_s.reserve(lenght);

    for (int i = 0; i < lenght; ++i) 
        tmp_s += alphanum[dis(gen)];
    
    
    return tmp_s;
}




























