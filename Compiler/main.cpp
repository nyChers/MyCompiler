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
void BDS();		//���ʽ
void BDS1();	//���ʽ1
void X();		//��
void X1();		//��1
void YZ();		//����


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
		matchToken("SIGNWORD");
		if (lookahead.type == "=") {
			matchToken("=");
			BDS();
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

				if (lookahead.type == "else") {
					matchToken("else");
					YJ1();
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
	BDS();

	if (lookahead.type == "RELATION") {
		matchToken("RELATION");

	}
	else {
		outError(" ȱ�� ��ϵ���� ", lookahead.r, lookahead.c);
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
			outError(" ȱ�� �ҷ��� ", lookahead.r, lookahead.c);
		}
		else {
			X();
			BDS1();
		}

	}

	//�մ�
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

	//�մ�
}

void YZ() {
	if (lookahead.type == "(") {
		matchToken("(");
		BDS();
		if (lookahead.type == ")")
			matchToken(")");
		else {
			outError(" ȱ�� �� ", lookahead.r, lookahead.c);
		}
	}
	else if (lookahead.type == "SIGNWORD") {
		matchToken("SIGNWORD");
	}
	else if (lookahead.type == "INTEGER") {
		matchToken("INTEGER");
	}
	else {
		outError(" ȱ�� �ҷ��� ", lookahead.r, lookahead.c);
	}
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
