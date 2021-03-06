/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-25T23:27:24+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: base.cpp
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-28T15:49:38+08:00
 */
#include "Base.h"

int Base::Kind_Char(char ch) {
    if(isLetter(ch))
        return 1;
    if(isDigit(ch))
        return 2;
    if(ch == '$' || ch == '_')
        return 3;
    if(ch == '\\')
        return 4;
    if(ch == '=')
        return 5;
    return 0;
}

bool Base::isLetter(char ch) {
    if(('A'<=ch && ch<='Z') || ('a'<=ch && ch<='z'))
        return true;
    return false;
}

bool Base::isDigit(char ch) {
    if('0'<=ch && ch<='9')
        return true;
    return false;
}

int Base::iskeyword(char *str) {
    for(int i=0;i<keyword_num;i++) {
        if(!strcmp(str,keywords[i]))
            return i+1;
    }
    return 0;
}

bool Base::spaces(char ch) {
    if ((ch > 'z' || (ch < 'a' && ch > 'Z') || (ch < 'A' && ch > '9') || (ch < '0')) && ch != '_' && ch != '$')	{
		return true;
	}
	return false;
}

bool Base::isSignwords(char *str) {
    int len = strlen(str);
    if(str[0] == '_' || str[0] == '$' || isLetter(str[0])) {
        for(int i=1; i<len; i++) {
            if(spaces(str[i]))
                return false;
        }
        return true;
    }
    return false;
}

bool Base::isInt(char *str) {
    int len = strlen(str);
    if(str[0] == '-' || isDigit(str[0])) {
        if(str[0] == '-' && len <= 1)
            return false;
        for(int i=1; i<len; i++) {
            if(!isDigit(str[i]))
                return false;
        }
        return true;
    }
    return false;
}

bool Base::isFloats(char *str) {
    int flag = 0;
    int len = strlen(str);
    if(str[0] == '-' && len <= 1)
        return false;
    if(str[0] == '-' || isDigit(str[0])) {
        for(int i=1; i<len; i++) {
            if(str[i] == '.') {
                if(flag == 0) {
                    flag = 1;
                    continue;
                }
                else {
                    return false;
                }
            }
            if(!isDigit(str[i]))
                return false;
        }
        return true;
    }
    else if(str[0] == '.') {
        for(int i=1; i<len; i++) {
            if(!isDigit(str[i]))
                return false;
        }
        return true;
    }
    return false;
}

void Base::output(FILE * f,char* token, char* value) {
    fprintf(f,"< %-15s , %-10s >\n", token, value);
}
