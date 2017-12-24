/**
 * @Author: NingYu Zhang
 * @Date:   2017-11-16T20:25:08+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: main.cpp
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-11-16T20:44:06+08:00
 */


#include "LexicalAnalysis.h"
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;
//struct Token {
//	string type;
//	string val;
//	int r;
//	int c;
//};

struct Qua{
	Qua(int l, string o, string dd1, string dd2, string r) {
		line = l;
		op = o;
		d1 = dd1;
		d2 = dd2;
		res = r;
	}
	int line;
	string op;
	string d1;
	string d2;
	string res;
};

vector<Qua> QuaList;
int currline = 1;
int backline;
int jumpline;

Token lookahead;
LexicalAnalysis lex("in.txt");
bool errorflag = 0;

void matchToken(string);//标记匹配
void outError(string,int,int);
void CX();		//程序入口
void FCX();		//分程序
void BLSMBF();	//变量说明部分
void YJBF();	//语句部分
void YJBF1();	//语句部分1
void BLSM();	//变量说明
void BSFB();	//标识符表
void BSFB1();	//标识符表1
void BS();		//标识符
void FHYJ();	//复合语句
void YJ();		//语句
void YJ1();		//语句1
void FZYJ();	//赋值语句
void TJYJ();	//条件语句
void TJ();		//条件
void XHYJ();	//循环语句
string BDS();		//表达式
string BDS1(string);	//表达式1
string X();		//项
string X1(string);		//项1
string YZ();		//因子


void matchToken(string s) {
	if (s != lookahead.type) {
		cout << "syntax error\n" << endl;
	}
	else
		lookahead = lex.getToken();
}

void outError(string s, int r, int c) {
	errorflag = 1;
	cout << s;
	cout << "\t\trow: " << r << "\t\tcol: " << c << endl;
}

ofstream outQua("outQua.txt");
void printQua() {
	for (int i = 0; i < QuaList.size(); i++) {
		outQua << QuaList[i].line << "\t\t(" << QuaList[i].op << ",\t\t" << QuaList[i].d1 << ",\t\t" << QuaList[i].d2 << ",\t\t" << QuaList[i].res << ")" << endl;
	}
}

int tnum = 0;
string newSys() {
	string r = "t";
	r = r + to_string(tnum++);
	return r;
}

//程序
void CX() {
	if (lookahead.type == "main") {
		matchToken("main");
		if (lookahead.type == "(") {
			matchToken("(");
			if (lookahead.type == ")") {
				matchToken(")");
				if (lookahead.type == "{") {
					matchToken("{");

					FCX();

					if (lookahead.type == "}") {
						matchToken("}");
						cout << "Finished!" << endl;
					}
					else {
						outError(" 缺少 } ", lookahead.r, lookahead.c);
					}
				}
				else {
					outError(" 缺少 { ", lookahead.r, lookahead.c);
				}
			}
			else {
				outError(" 缺少 ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" 缺少 ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" 缺少 main ", lookahead.r, lookahead.c);
	}

}

void FCX() {
	BLSMBF();

	if (lookahead.type == ";") {
		matchToken(";");
	}
	else {
		outError(" 缺少 ; ", lookahead.r, lookahead.c);
	}

	YJBF();
}

void BLSMBF() {
	BLSM();
	BSFB();
}

void YJBF() {
	YJ();
	YJBF1();
}

void YJBF1() {
	if (lookahead.type == ";") {
		matchToken(";");
		YJ();
		YJBF1();
	}
	else if (lookahead.type == "}") {

	}
	else if (lookahead.type == "SIGNWORD") {
		outError(" 缺少 ; ", lookahead.r, lookahead.c);
		YJ();
		YJBF1();
	}
	//空串
}

void BLSM() {
	if (lookahead.type == "int") {
		matchToken("int");
	}
	else {
		outError(" 缺少 变量说明 ", lookahead.r, lookahead.c);
	}
}

void BSFB() {
	BS();
	BSFB1();
}

void BSFB1() {
	if (lookahead.type == ",") {
		matchToken(",");
		BS();
		BSFB1();
	}

	//空串

}

void BS() {
	if (lookahead.type == "SIGNWORD") {
		matchToken("SIGNWORD");
	}
	else {
		outError(" 缺少 标识符 ", lookahead.r, lookahead.c);
	}
}

void YJ() {
	if (lookahead.type == "SIGNWORD") {
		FZYJ();
	}
	else if (lookahead.type == "if") {
		TJYJ();
	}
	else if (lookahead.type == "while") {
		XHYJ();
	}
	else {
		outError(" 语句空 ", lookahead.r, lookahead.c);
	}
}

void FZYJ() {
	if (lookahead.type == "SIGNWORD") {
		string res = lookahead.val;
		matchToken("SIGNWORD");
		if (lookahead.type == "=") {
			matchToken("=");
			string op = "=";
			string d1 = BDS();
			string d2 = "/";
			QuaList.push_back(Qua(currline++, op, d1, d2, res));
		}
		else {
			outError(" 缺少 = ", lookahead.r, lookahead.c);
			YJ();
		}
	}
	else {
		outError(" 缺少 左符号 ", lookahead.r, lookahead.c);
	}
}

void TJYJ() {
	if (lookahead.type == "if") {
		matchToken("if");
		if (lookahead.type == "(") {
			matchToken("(");
			backline = currline;
			TJ();

			if (lookahead.type == ")") {
				matchToken(")");

				YJ1();

				QuaList.push_back(Qua(currline++, "GO",to_string(currline), "/", "/"));
				QuaList[backline - 1].res = to_string(currline);
				backline = currline - 1;
				if (lookahead.type == "else") {
					matchToken("else");
					YJ1();
					QuaList[backline - 1].d1 = to_string(currline);
				}
				else {
					outError(" 缺少 else ", lookahead.r, lookahead.c);
				}
			}
			else {
				outError(" 缺少 ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" 缺少 ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" 缺少 if ", lookahead.r, lookahead.c);
	}
}

void XHYJ() {
	if (lookahead.type == "while") {
		matchToken("while");
		if (lookahead.type == "(") {
			matchToken("(");
			jumpline = currline;
			TJ();

			if (lookahead.type == ")") {
				matchToken(")");
				if (lookahead.type == "do") {
					matchToken("do");
				}
				else {
					outError(" 缺少 do ", lookahead.r, lookahead.c);
				}

				YJ1();
				QuaList.push_back(Qua(currline++, "GO", to_string(jumpline), "/", "/"));
				QuaList[backline - 1].res = to_string(currline);
			}
			else {
				outError(" 缺少 ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" 缺少 ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" 缺少 while ", lookahead.r, lookahead.c);
	}
}

void FHYJ() {
	if (lookahead.type == "{") {
		matchToken("{");

		YJBF();

		if (lookahead.type == "}") {
			matchToken("}");
		}
		else {
			outError(" 缺少 } ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" 缺少 { ", lookahead.r, lookahead.c);
	}
}

void YJ1() {
	if (lookahead.type == "{") {
		FHYJ();
	}
	else
		YJ();
}

void TJ() {
	string d1 = BDS();
	string op;
	if(d1=="")
		outError(" 缺少 左符号 ", lookahead.r, lookahead.c);
	if (lookahead.type == "RELATION") {
		op = lookahead.val;
		if (op == ">")
			op = "<=";
		else if (op == "<")
			op = ">=";
		else if (op == ">=")
			op = "<";
		else if (op == "<=")
			op = ">";
		else if (op == "==")
			op = "!=";
		else
			op = "==";
		matchToken("RELATION");

	}
	else {
		outError(" 缺少 关系符号 ", lookahead.r, lookahead.c);
	}

	string d2 = BDS();
	backline = currline;
	if (d2 == "")
		outError(" 缺少 右符号 ", lookahead.r, lookahead.c);
	string res = to_string(currline);
	QuaList.push_back(Qua(currline++, op, d1, d2, res));
}

string BDS() {
	string res;
	string in = X();
	res = BDS1(in);
	return res;
}

string BDS1(string in) {
	string d1 = in;
	string op;
	string res = in;
	if (lookahead.type == "+-") {
		op = lookahead.val;
		matchToken("+-");
		string d2 = X();
		res = newSys();
		QuaList.push_back(Qua(currline++, op, d1, d2, res));
		BDS1(res);

	}

	return res;
	//空串
}

string X() {
	string in = YZ();
	string res = X1(in);
	return res;
}

string X1(string in) {
	string op;
	string res = in;
	if (lookahead.type == "*/") {
		op = lookahead.val;
		string d1 = in;
		matchToken("*/");
		string d2 = YZ();
		res = newSys();
		QuaList.push_back(Qua(currline++, op, d1, d2, res));
		X1(res);
	}

	return res;
	//空串
}

string YZ() {
	string d;
	if (lookahead.type == "(") {
		matchToken("(");
		d = BDS();
		if (lookahead.type == ")")
			matchToken(")");
		else {
			outError(" 缺少 ） ", lookahead.r, lookahead.c);
		}
	}
	else if (lookahead.type == "SIGNWORD") {
		d = lookahead.val;
		matchToken("SIGNWORD");
	}
	else if (lookahead.type == "INTEGER") {
		d = lookahead.val;
		matchToken("INTEGER");
	}
	else {
		outError(" 缺少 符号 ", lookahead.r, lookahead.c);
	}
	return d;
}


int main() {
	lex.scanwords();
	lookahead = lex.getToken();

	CX();

	if (errorflag) {
		cout << "输入代码存在错误，不生成四元式。" << endl;
	}
	else {
		printQua();
	}
	system("pause");
    return 0;
}
