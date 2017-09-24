#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

const int ReservedWord_NUM = 12;
const char* ReservedWord_SET[] = {
    "for",
    "while",
    "do",
    "continue",
    "break",
    "if",
    "else",
    "char",
    "int",
    "double",
    "float",
    "return",
};


bool isNum(char ch) {
    if('0'<=ch && ch<='9')
        return true;
    return false;
}

bool isLetter(char ch) {
    if(('A'<=ch && ch<='Z') || ('a'<=ch && ch<='z'))
        return true;
    return false;
}

int findReservedWord(char* ch) {
    for(int i=0;i<ReservedWord_NUM;i++) {
        if(!strcmp(ch,ReservedWord_SET[i]))
            return i+1;
    }
    return 0;
}
