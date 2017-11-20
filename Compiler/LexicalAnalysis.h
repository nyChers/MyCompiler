/**
 * @Author: NingYu Zhang <ny>
 * @Date:   27-09-2017
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.h
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-11-20T20:34:36+08:00
 */


#ifndef _LEX_H
#define _LEX_H
#include "Base.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Token {
	Token() {};
	Token(string s1, string s2) {
		type = s1;
		val = s2;
	}
	void set(string s1, string s2) {
		type = s1;
		val = s2;
	}
	string type;
	string val;
	int r = 0;
	int c = 0;
};

class LexicalAnalysis:public Base
{
public:
    LexicalAnalysis(char* fi,char* fo) {
		row = 1;
		cnt = 1;
        filein = fopen(fi, "r");
        fileout = fopen(fo, "w");
    }
    LexicalAnalysis(char* fi) {
        filein = fopen(fi,"r");
        fileout = fopen("token.txt","w");
    }
    virtual ~LexicalAnalysis() {
        fclose(filein);
        fclose(fileout);
    };
    void scanwords();//扫描每一行
	Token getToken();
private:
    void clearnotes();//清楚注释空格
    void getWord(int);//状态自动机
    Token kindWord(char*);//分类打Token
private:
    FILE* filein;
    FILE* fileout;
    int cnt;
    int row;
	queue<Token> T;
    // char buffer_in[2][256];
    char buffer_scan[256];
};
#endif
