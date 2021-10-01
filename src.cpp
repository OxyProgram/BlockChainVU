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
void test5();
void collisionTest();
string gen_random(const int lenght);

int main(int argc, char *argv[]) {

    Hash hash;
    string input = *argv;

    cout << "Pasirinkite ivesties buda:  " << endl;
    cout << "1. Is isorinio failo\n 2. Ivesti ranka\n 3. Vykdyti analize" << endl;
    char c;
    cin >> c;
    if (c == '1') {
        string hashString = hash.generateHash(input);
        cout << hashString + "\n" << endl;
    }
    if (c == '2') {
        string s;
        cin >> s;
        cout << hash.generateHash(s) + "\n" << endl;
    }
    if(c == '3') {
        runAnalysis();
    }

}

void runAnalysis() {

    generateFile1("a", "file1.txt");  //Generates a file the same symbol "a"
    generateFile1("b", "file2.txt");  //Generates a file the same symbol "b"
    generateFile2("file3.txt");       //Generates a file with unique strings of 1000 symbols
    generateFile2("file4.txt");       //Generates a file with unique strings of 1000 symbols
    generateFile3("file5.txt");       //Generates a file with a strings with one unique character appended
    generateFile3("file6.txt");       //Generates a file with a strings with one unique character appended

    test1();  //Input can be of any size
    test2();  //Output will always be 64 character hex
    test3();  //Function is deterministic
    test4();  //Hash'ing konstitucija.txt
    collisionTest();  //Collision test
    test5();  //Changing input slightly generates vastly different result

}

void test1() {

    string s, o;
    Hash hash;

    cout << "1. Input can be of any size:" << endl;
    s = gen_random(0);
    o = hash.generateHash(s);
    s = gen_random(1);
    o = hash.generateHash(s);
    s = gen_random(1000);
    o = hash.generateHash(s);
    s = gen_random(10000);
    o = hash.generateHash(s);
    cout << "Hash function can take a randon string input with character count from 0 to 10000\n" << endl;
    
}

void test2() {

    cout << "2. Output will always be 64 character hex:\n" << endl;
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
    cout << "Hash function returnd 64 character hex from input size (0, 1000)\n" << endl;
}

void test3() {
    cout << "3. Function is deterministic:\n" << endl;
    bool a = functionIsDeterministic("file1.txt");
    bool b = functionIsDeterministic("file2.txt");

    if(a || b) {
        cout << "3 test UNsuccessfull!" << endl;
        return;
    }
    cout << "3 test successfull!" << endl;
    cout << "Functions always returns the same output for input 'a'/'b'\n" << endl;
}

void test5() {

    cout << "6. Slightly modifying the input vastly changes the output\n" << endl;

    Hash hash;

    string s1 = "aaaaaaaaaaaaaaaaaaaa";
    string s2 = "Aaaaaaaaaaaaaaaaaaaa";
    string s3 = "a!aaaaaaaaaaaaaaaaaaa";
    string h1 = hash.generateHash(s1);
    string h2 = hash.generateHash(s2);
    string h3 = hash.generateHash(s3);

    cout << "---------------------------------------------------" << endl;
    cout << "Input                   |      Output" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << s1 + "    | " + h1 << endl;
    cout << s2 + "    | " + h2 << endl;
    cout << s3 + "    | " + h3 << endl;
    cout << "---------------------------------------------------" << endl;

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


    cout << "4. Function is fairly efficient:\n" << endl;
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
    cout << "test 4 took " + to_string(diff) + " ms\n" << endl;
    in.close();

}

void collisionTest() {

    cout << "5. Collision test\n" << endl;
    Hash hash;
    string s1, s2;
    int i = 0;
    for(int i = 0; i < 100000; i++) {
        s1 = gen_random(6);
        s2 = gen_random(6);
        if(hash.generateHash(s1).compare(hash.generateHash(s2))) {
            i++;
        }
    }
    cout << to_string(i) + " collisions detected out of 100 000 pairs" << endl;

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




























