/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-24T22:10:19+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.cpp
 * @Last modified by:   ny
 * @Last modified time: 26-09-2017
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

void output(char* key, char* value)
{
    printf("< %s , %s >\n", key, value);
}
