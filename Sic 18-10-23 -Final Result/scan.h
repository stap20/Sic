#include<iostream>
#include <fstream>
#include <string>
#include<vector>
#include"hex_inc_dec.h"
#include"instruction_find.h"
#include "String _To_Opcode_Fit_8.h"
#include"currentline_divide_strings.h"
#include "hex_indirect_addressing_changer.h"
#include "Chek_if_Dec.H"
using namespace std;
#ifndef SCAN_H_DEF
#define SCAN_H_DEF
const string HEX_THREE ="0003";
const string HEX_ONE ="0001";
void Pass_ONE(string File_Path);
void Pass_TWO(string File_Path);
void test();
#endif // SCAN_H_DEF