/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-24T22:10:19+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.cpp
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-27T22:00:25+08:00
 */

#include "LexicalAnalysis.h"

void LexicalAnalysis::scanwords() {
    char ch;
    int cnt = 0;//行字符数
    int row = 0;//行数

    while(1) {
        //读入字符
        ch = fgetc(filein);
        //判断读完文件
        if(ch == EOF)
            break;
        //判断行末
        if(ch == '\n') {
            buffer_scan[cnt] = '\0';
            row++;

            clearnotes();

            if(strlen(buffer_scan) > 0) {
                getWord(0);
            }

            cnt = 0;
        }
        else {
            buffer_scan[cnt++] = ch;
        }
    }
    printf("The result has been successfully saved~\n");
}

void LexicalAnalysis::clearnotes() {

}

void LexicalAnalysis::getWord(int state) {
    char word[100];
    int chcnt = 0;
    int num;
    int finish = 0;

    for(int i=0; i<strlen(buffer_scan); i++) {
        switch(state/10) {

        //起始状态
        case 0:
            switch(Kind_Char(buffer_scan[i])) {
            case 1://是字母
                word[chcnt++] = buffer_scan[i];
                state = 10;
                break;
            case 2://是数字
                word[chcnt++] = buffer_scan[i];
                state = 20;
                break;
            case 3://为变量合法符号 $ _
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 0:
            case 5:
                word[chcnt++] = buffer_scan[i];
                switch(buffer_scan[i]) {
                case '"':
                    state = 41;
                    break;
                case '\'':
                    state = 42;
                    break;
                case '=':
                    state = 43;
                    break;
                case '(':
                case ')':
                case '{':
                case '}':
                case '[':
                case ']':
                case ';':
                case ',':
                case '.':
                    state = 50;
                    word[chcnt] = '\0';
                    finish = 1;
                    break;
                default:
                    state = 40;
                    break;
                }
                break;
            default:
                word[chcnt++] = buffer_scan[i];
                break;
            }

        //通过字母进入的状态
        case 1:
            switch(Kind_Char(buffer_scan[i])) {
            case 1://是字母
                word[chcnt++] = buffer_scan[i];
                state = 10;
                break;
            case 2://是数字
                word[chcnt++] = buffer_scan[i];
                state = 20;
                break;
            case 3://为变量合法符号 $ _
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 0:
            case 5:
                word[chcnt] = '\0';
                num = 0;
                while(word[num] != '\0')
                    num++;

                i--;//吐出该字符
                finish = 1;
                state = 50;
                break;
            default:
                word[chcnt++] = buffer_scan[i];
                break;
            }
            break;

        //通过数字进入的状态
        case 2:
            switch(Kind_Char(buffer_scan[i])) {
            case 1://是字母
                word[chcnt++] = buffer_scan[i];
                state = 20;
                break;
            case 2://是数字
                word[chcnt++] = buffer_scan[i];
                state = 20;
                break;
            case 3://为变量合法符号 $ _
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 0:
                if(buffer_scan[i] == '.') {
                    word[chcnt++] = buffer_scan[i];
                    state = 20;
                    break;
                }
                word[chcnt] = '\0';
                finish = 1;
                state = 50;
                break;
            default:
                word[chcnt++] = buffer_scan[i];
                break;
            }
            break;


        case 3:
            switch(Kind_Char(buffer_scan[i])) {
            case 1://是字母
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 2://是数字
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 3://为变量合法符号 $ _
                word[chcnt++] = buffer_scan[i];
                state = 30;
                break;
            case 0:
                word[chcnt] = '\0';
                i--;
                finish = 1;
                state = 50;
                break;
            default:
                word[chcnt++] = buffer_scan[i];
                break;
            }
            break;


        case 4:


        }
    }
}
