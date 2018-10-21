#include"instruction_find.h"
using namespace std;
const string SIC_Instruction_Set_NAME [42]={"ADD","ADDF","AND","COMP","COMPF","DIV","DIVF","J" ,"JEQ","JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","OR","RD","RSUB","SSK","STA","STB","STCH","STF","STL","STI","STS","STSW","STT","STX","SUB","SUBF","TD","TIX","WD"};
const string SIC_Instruction_Set_Num  [42]={"18" ,"58"  ,"40" ,"28"  ,"88"   ,"24" ,"64"  ,"3C","30" ,"34" ,"38" ,"40"  ,"00" ,"68" ,"50"  ,"70" ,"08" ,"6C" ,"74" ,"04" ,"D0" ,"20" ,"60"  ,"44","D8","4C"  ,"EC" ,"0C" ,"78" ,"54"  ,"80" ,"D4" ,"14" ,"7C" ,"E8"  ,"84" ,"10" ,"1C" ,"5C"  ,"E0","2C" ,"DC"};

string _Instruction_Found_Get_INST(string current_string)
{
    for(int i=0;i<42;i++)
    if(current_string==SIC_Instruction_Set_NAME[i])
        return SIC_Instruction_Set_Num[i];
    return NOT_FOUND;
}
