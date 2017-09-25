/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-24T22:10:19+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.cpp
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-26T00:07:55+08:00
 */



#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

char* FILE_NAME;


bool isDigit(char ch) {
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

void output(char* key, char* value)
{
    printf("< %s , %s >\n", key, value);
}
