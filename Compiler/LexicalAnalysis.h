/**
 * @Author: NingYu Zhang <ny>
 * @Date:   27-09-2017
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.h
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-28T17:28:38+08:00
 */


#ifndef _LEX_H
#define _LEX_H
#include "Base.h"
class LexicalAnalysis:public Base
{
public:
    LexicalAnalysis(char* fi,char* fo) {
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
    void clearnotes();//清楚注释空格
    void getWord(int);//状态自动机
    void kindWord(char*);//分类打Token
private:
    FILE* filein;
    FILE* fileout;
    // char buffer_in[2][256];
    char buffer_scan[256];
};
#endif
