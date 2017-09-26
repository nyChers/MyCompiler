/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-25T23:27:24+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: base.cpp
 * @Last modified by:   ny
 * @Last modified time: 26-09-2017
 */
#include "base.h"

bool Base::isChar(char ch) {

    return false;
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
    if(str[0] == '_' || str[0] == '$' || isLetter(str[0])) {
        for(int i=1; str[i]!='\0'; i++) {
            if(spaces(str[i]))
                return false;
            return true;
        }
    }
    return false;
}

bool Base::isInt(char *ch) {

}

bool Base::isFloats(char *ch) {

}
