/**
 * @Author: NingYu Zhang
 * @Date:   2017-11-16T20:25:08+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: main.cpp
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-12-17T16:30:58+08:00
 */


#include "LexicalAnalysis.h"
#include <cstring>
#include <string>
#include <iomanip>

//struct Token {
//	string type;
//	string val;
//	int r;
//	int c;
//};
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
void BDS();		//表达式
void BDS1();	//表达式1
void X();		//项
void X1();		//项1
void YZ();		//因子


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

void printQua() {

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
		matchToken("SIGNWORD");
		if (lookahead.type == "=") {
			matchToken("=");
			BDS();
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

			TJ();

			if (lookahead.type == ")") {
				matchToken(")");

				YJ1();

				if (lookahead.type == "else") {
					matchToken("else");
					YJ1();
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
	BDS();

	if (lookahead.type == "RELATION") {
		matchToken("RELATION");

	}
	else {
		outError(" 缺少 关系符号 ", lookahead.r, lookahead.c);
	}

	BDS();
}

void BDS() {
	X();
	BDS1();
}

void BDS1() {
	if (lookahead.type == "+-") {
		matchToken("+-");
		if (lookahead.type == ";") {
			outError(" 缺少 右符号 ", lookahead.r, lookahead.c);
		}
		else {
			X();
			BDS1();
		}

	}

	//空串
}

void X() {
	YZ();
	X1();
}

void X1() {
	if (lookahead.type == "*/") {
		matchToken("*/");
		YZ();
		X1();
	}

	//空串
}

void YZ() {
	if (lookahead.type == "(") {
		matchToken("(");
		BDS();
		if (lookahead.type == ")")
			matchToken(")");
		else {
			outError(" 缺少 ） ", lookahead.r, lookahead.c);
		}
	}
	else if (lookahead.type == "SIGNWORD") {
		matchToken("SIGNWORD");
	}
	else if (lookahead.type == "INTEGER") {
		matchToken("INTEGER");
	}
	else {
		outError(" 缺少 右符号 ", lookahead.r, lookahead.c);
	}
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
