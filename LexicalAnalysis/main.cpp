/**
 * @Author: NingYu Zhang <nyChers>
 * @Date:   2017-09-28T12:30:21+08:00
 * @Email:  zny_chers@hotmail.com
 * @Filename: main.cpp
 * @Last modified by:   nyChers
 * @Last modified time: 2017-09-28T16:30:36+08:00
 */



#include "LexicalAnalysis.h"

int main() {
	LexicalAnalysis lex("in.txt");
	lex.scanwords();

	return 0;
}
