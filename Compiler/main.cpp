/**
 * @Author: NingYu Zhang
 * @Date:   2017-11-16T20:25:08+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: main.cpp
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-12-17T20:15:54+08:00
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

void matchToken(string);//���ƥ��
void outError(string,int,int);
void CX();		//�������
void FCX();		//�ֳ���
void BLSMBF();	//����˵������
void YJBF();	//��䲿��
void YJBF1();	//��䲿��1
void BLSM();	//����˵��
void BSFB();	//��ʶ����
void BSFB1();	//��ʶ����1
void BS();		//��ʶ��
void FHYJ();	//�������
void YJ();		//���
void YJ1();		//���1
void FZYJ();	//��ֵ���
void TJYJ();	//�������
void TJ();		//����
void XHYJ();	//ѭ�����
string BDS();		//���ʽ
string BDS1(string);	//���ʽ1
string X();		//��
string X1(string);		//��1
string YZ();		//����


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

//����
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
						outError(" ȱ�� } ", lookahead.r, lookahead.c);
					}
				}
				else {
					outError(" ȱ�� { ", lookahead.r, lookahead.c);
				}
			}
			else {
				outError(" ȱ�� ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" ȱ�� ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" ȱ�� main ", lookahead.r, lookahead.c);
	}

}

void FCX() {
	BLSMBF();

	if (lookahead.type == ";") {
		matchToken(";");
	}
	else {
		outError(" ȱ�� ; ", lookahead.r, lookahead.c);
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

	//�մ�
}

void BLSM() {
	if (lookahead.type == "int") {
		matchToken("int");
	}
	else {
		outError(" ȱ�� ����˵�� ", lookahead.r, lookahead.c);
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

	//�մ�

}

void BS() {
	if (lookahead.type == "SIGNWORD") {
		matchToken("SIGNWORD");
	}
	else {
		outError(" ȱ�� ��ʶ�� ", lookahead.r, lookahead.c);
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
		outError(" ���� ", lookahead.r, lookahead.c);
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
			outError(" ȱ�� = ", lookahead.r, lookahead.c);
			YJ();
		}
	}
	else {
		outError(" ȱ�� ����� ", lookahead.r, lookahead.c);
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

				QuaList.push_back(Qua(currline++, "GO",to_string(currline), "/", "/"));
				QuaList[backline - 1].res = to_string(currline);
				backline = currline - 1;
				if (lookahead.type == "else") {
					matchToken("else");
					YJ1();
					QuaList[backline - 1].d1 = to_string(currline);
				}
				else {
					outError(" ȱ�� else ", lookahead.r, lookahead.c);
				}
			}
			else {
				outError(" ȱ�� ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" ȱ�� ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" ȱ�� if ", lookahead.r, lookahead.c);
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
					outError(" ȱ�� do ", lookahead.r, lookahead.c);
				}

				YJ1();
				QuaList.push_back(Qua(currline++, "GO", to_string(backline), "/", "/"));
				QuaList[backline - 1].res = to_string(currline);
			}
			else {
				outError(" ȱ�� ) ", lookahead.r, lookahead.c);
			}
		}
		else {
			outError(" ȱ�� ( ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" ȱ�� while ", lookahead.r, lookahead.c);
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
			outError(" ȱ�� } ", lookahead.r, lookahead.c);
		}
	}
	else {
		outError(" ȱ�� { ", lookahead.r, lookahead.c);
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
	//if(d1=="")
	//	outError(" ȱ�� ����� ", lookahead.r, lookahead.c);
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
		outError(" ȱ�� ��ϵ���� ", lookahead.r, lookahead.c);
	}

	string d2 = BDS();
	//if (d2 == "")
	//	outError(" ȱ�� �ҷ��� ", lookahead.r, lookahead.c);
	backline = currline;
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
	//�մ�
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
	//�մ�
}

string YZ() {
	string d;
	if (lookahead.type == "(") {
		matchToken("(");
		d = BDS();
		if (lookahead.type == ")")
			matchToken(")");
		else {
			outError(" ȱ�� �� ", lookahead.r, lookahead.c);
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
		outError(" ȱ�� ���� ", lookahead.r, lookahead.c);
	}
	return d;
}


int main() {
	lex.scanwords();
	lookahead = lex.getToken();

	CX();

	if (errorflag) {
		cout << "���������ڴ��󣬲�������Ԫʽ��" << endl;
	}
	else {
		printQua();
	}
	system("pause");
    return 0;
}
