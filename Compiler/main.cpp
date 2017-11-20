/**
 * @Author: NingYu Zhang
 * @Date:   2017-11-16T10:25:08+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: main.cpp
 * @Last modified by:   NingYu Zhang
 * @Last modified time: 2017-11-20T20:36:19+08:00
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

void matchToken(string s) {
	if (s != lookahead.type) {
		cout << "syntax error\n" << endl;
		exit(0);
	}
	else
		lookahead = lex.getToken();
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
						cout << "SUCCESSFULLY!" << endl;
					}
					else {
						cout <<setprecision(10)<< " 缺锟斤拷 } "<<setprecision(10)<<"row: "<<lookahead.r << endl;
						cout << setprecision(10) << "row: " << lookahead.r << "col: " << lookahead.c << endl;
					}
				}
			}
		}
	}
}

int main() {
	lex.scanwords();
	lookahead = lex.getToken();

	CX();
    return 0;
}
