/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-25T23:00:43+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: base.h
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-26T00:07:43+08:00
 */



#ifndef _Base_H_
#define _Base_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>

static int keyword_num = 31;
static char* keywords[] = { "short", "int", "long", "float", "double", "char"
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

	int isChar(char c);//判断字符类型
	int spaces(char c); //当前空格是否可以消除
	int isLetter(char c);//是否是字母
	int iskeyword(char str[]);//是否是关键字
	int isSignwords(char str[]);//是否是标识符
	int isDigit(char c);//是否是数字
	int isInt(char str[]);//是否是整数
	int isFloats(char str[]);//是否是浮点型
};

#endif
