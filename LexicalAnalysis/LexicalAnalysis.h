/**
 * @Author: NingYu Zhang <ny>
 * @Date:   27-09-2017
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.h
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-27T23:58:06+08:00
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
    void clearnotes();
    void getWord(int);
    void kindWord(char*);
private:
    FILE* filein;
    FILE* fileout;
    char buffer_in[2][256];
    char buffer_scan[256];
};
#endif
