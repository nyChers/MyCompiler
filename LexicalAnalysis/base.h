/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-25T23:00:43+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: base.h
 * @Last modified by:   ny
 * @Last modified time: 26-09-2017
 */



#ifndef _Base_H_
#define _Base_H_

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>

static const int keyword_num = 31;
static const char* keywords[] = { "short", "int", "long", "float", "double", "char"
, "struct", "union", "enum", "typedef", "const", "unsigned", "signed", "extern"
, "static", "void", "if", "else", "switch", "case", "for", "do", "while", "continue"
, "break", "default", "sizeof", "return", "true", "false","include"};

class Base
{
public:
	int charnum;
public:
	Base() {
        charnum = 0;
    }
	virtual ~Base();

	bool isChar(char);//判断字符类型
	bool spaces(char); //当前空格是否可以消除
	bool isLetter(char);//是否是字母
	int iskeyword(char*);//是否是关键字
	bool isSignwords(char*);//是否是标识符,不能以字母开头
	bool isDigit(char);//是否是数字
	bool isInt(char*);//是否是整数
	bool isFloats(char*);//是否是浮点型
	void output(char*,char*);//输出token-value对``
};

#endif
