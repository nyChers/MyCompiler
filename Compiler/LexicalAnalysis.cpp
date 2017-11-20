/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-24T22:10:19+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: LexicalAnalysis.cpp
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-11-20T20:34:35+08:00
 */

#include "LexicalAnalysis.h"

void LexicalAnalysis::scanwords() {
    char ch;
    cnt = 0;//行字符数
    row = 0;//行数

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
	output(fileout, "#", "#");
	Token tk("#", "#");
	tk.r = row;
	tk.c = 1;
	T.push(tk);
    //printf("The Lexical Analysis has been successfully done~\n");
}
Token LexicalAnalysis::getToken() {
	Token t = T.front();
	T.pop();
	return t;
}

void LexicalAnalysis::clearnotes() {

    //空格
	for (int i=0, flag=0; buffer_scan[i] != '\0'; i++) {
        //不删除字符串的空格
		if(buffer_scan[i] == '"') {
			flag = 1 - flag;
			continue;
		}
		if(buffer_scan[i] == ' ' && flag == 0) {
            int j;
			for(j=i+1; buffer_scan[j] != '\0' && buffer_scan[j] == ' '; j++);
			if (buffer_scan[j] == '\0') {
				buffer_scan[i] = '\0';
				break;
			}
			if (buffer_scan[j] != '\0' && ((spaces(buffer_scan[j])) || (i > 0 && spaces(buffer_scan[i - 1])))) {
                int k;
                for (k=i; buffer_scan[j] != '\0'; j++, k++) {
					buffer_scan[k] = buffer_scan[j];
				}
				buffer_scan[k] = '\0';
				i--;
			}
		}
	}

	//制表符
	for (int i=0, flag=0; buffer_scan[i] != '\0'; i++) {
		if (buffer_scan[i] == '\t') {
			for (int j=i; buffer_scan[j] != '\0'; j++) {
				buffer_scan[j] = buffer_scan[j + 1];
			}
			i = -1;
		}
	}
}


//自动机~
void LexicalAnalysis::getWord(int state) {
    char word[100];
    int chcnt = 0;
    int finish = 0;
	Token t;

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
            case 5://'='
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
            break;

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
            case 5://'='
                word[chcnt] = '\0';
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
            case 5:
                if(buffer_scan[i] == '.') {
                    word[chcnt++] = buffer_scan[i];
                    state = 20;
                    break;
                }
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
            switch(state) {
            case 40:
                switch(Kind_Char(buffer_scan[i])) {
                case 1:
                    word[chcnt] = '\0';
                    i--;
                    finish = 1;
                    state = 50;
                    break;
                case 2:
                    word[chcnt] = '\0';
                    i--;
                    finish = 1;
                    state = 50;
                    break;
                case 3:
                    word[chcnt] = '\0';
                    i--;
                    finish = 1;
                    state = 50;
                    break;
                case 0:
                    word[chcnt++] = buffer_scan[i];
                    state = 40;
                    break;
                default:
                    word[chcnt++] = buffer_scan[i];
                    break;
                }
                break;

            case 41:
                word[chcnt++] = buffer_scan[i];
                if(buffer_scan[i] == '"') {
                    if(Kind_Char(buffer_scan[i-1]) == 4){
                        //为转义 \"
                    }
                    else {
                        word[chcnt] = '\0';
                        finish = 1;
                        state = 50;
                    }
                }
                break;

            case 42:
                word[chcnt++] = buffer_scan[i];
                if(buffer_scan[i] == '\'') {
                    word[chcnt] = '\0';
                    finish = 1;
                    state = 50;
                }
                break;

            case 43:
                if(buffer_scan[i] == '=') {
                    word[chcnt++] = buffer_scan[i];
                    state = 43;
                }
                else {
                    word[chcnt] = '\0';
                    finish = 1;
                    i--;
                    state = 50;
                }
                break;

            default:
                word[chcnt++] = buffer_scan[i];
                break;
            }
            break;

        case 5:
            finish = 0;
            state = 0;
            chcnt = 0;
            i--;
            t = kindWord(word);
			t.r = row;
			t.c = i + 1;
			T.push(t);
            break;
        default:
            break;
        }
        if(buffer_scan[i+1] == '\0') {
            word[chcnt] = '\0';
			t = kindWord(word);
			t.r = row;
			t.c = i;
			T.push(t);
        }
    }
}

Token LexicalAnalysis::kindWord(char *str) {
	string s = str;
	Token to;
    if(iskeyword(str)) {
        output(fileout,"KEYWORD",str);
		to.set(s, s);
	}
    else if(isSignwords(str)) {
        output(fileout,"SIGNWORD",str);
		to.set("SIGNWORD", s);
	}
    else if(isInt(str)) {
        output(fileout,"INTEGER",str);
		to.set("INTEGER", s);
    }
    else if(isFloats(str)) {
        output(fileout,"FLOAT",str);
		to.set("FLOAT", s);
    }
    else if(str[0] == '\'' && str[strlen(str) - 1] == '\'') {
        output(fileout,"CHARACTER",str);
		to.set("CHAR", s);
    }
    else if(str[0] == '"' && str[strlen(str) - 1] == '"') {
        output(fileout,"STRING",str);
		to.set("STRING", s);
    }
    else if(spaces(str[0]) && str[0] != '"' && str[0] != '\'') {
        if(strcmp(str, "<") == 0 || strcmp(str, ">") == 0 || strcmp(str, "<=") == 0 || strcmp(str, ">=") == 0) {
            output(fileout,"RELATION TOKEN",str);
			to.set("RELATION", s);
        }
        else if(strcmp(str, "<<") == 0 || strcmp(str, ">>") == 0 || strcmp(str, ">>>") == 0 || strcmp(str, "<<<") == 0) {
            output(fileout,"STREAM TOKEN",str);
			to.set("STREAM TOKEN", s);
        }
        else if(strchr(str, '=') != NULL) {
            if (strcmp(str, "==") == 0 || strcmp(str, "!=") == 0) {
                output(fileout,"RELATION TOKEN",str);
				to.set("RELATION", s);
			}
			else {
                output(fileout,"EVALUATION",str);
				to.set("=", s);
			}
        }
        else if(strcmp(str, "||") == 0) {
            output(fileout,"LOGIC TOKEN",str);
			to.set("LOGIC", s);
        }
        else if(strcmp(str, "&&") == 0) {
            output(fileout,"LOGIC TOKEN",str);
			to.set("LOGIC", s);
        }
        else if(strcmp(str, "!") == 0) {
            output(fileout,"LOGIC TOKEN",str);
			to.set("LOGIC", s);
        }
        else if(strcmp(str, "++") == 0 || strcmp(str, "--") == 0 || strcmp(str, "~") == 0) {
            output(fileout,"++ -- ~",str);
			to.set("++ -- ~", s);
        }
        else if(strlen(str) == 1) {

            switch (str[0]) {
            case '?':
			case ':': output(fileout, "? :", str); break;
			case ' ': output(fileout, "SPACE", str); break;
			case '{': output(fileout, " { ", str); to.set("{", s); break;
			case '}': output(fileout, " } ", str); to.set("}", s); break;
            case '[':
            case ']':
			case '(': output(fileout, " ( ", str); to.set("(", s); break;
            case ')': output(fileout, " ) ", str); to.set("(", s); break;
			case '.': output(fileout, " . ", str); break;
			case ',': output(fileout, " , ", str); break;
			case ';': output(fileout, " ; ", str); to.set(";", s); break;
            case '+': output(fileout, "OPERATOR", str); to.set("+-", s); break;
            case '-': output(fileout, "OPERATOR", str); to.set("+-", s); break;
            case '*': output(fileout, "OPERATOR", str); to.set("*/", s); break;
            case '/': output(fileout, "OPERATOR", str); to.set("*/", s); break;
            case '%': output(fileout,"OPERATOR",str); break;
            case '|':
            case '^':
            case '&': output(fileout,"BIT OPERATOR",str); break;
            default: output(fileout,"OTHER",str); break;
            }
        }
    }
    else {
        output(fileout,"ERROR~!",str);
		to.set("error", s);
    }
	return to;
}
