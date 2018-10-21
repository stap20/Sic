#include"scan.h"
using namespace std;

string Prog_Name,Prog_Loc_Counter;
string Current_Line_Without_Spac[4]; //this array store line without spacing like h1w1a start 1010 put it in pos 0 h1w1a pos 1 start (4 because we have label and inst and label and x if u have) mustn't have 4 string .....
vector<string> Labels;
vector<string> Instruction;
vector<string> Prog_Loc_Counter_Array;
int line_counter=0; //number of line in program
int current_location=0;

bool IsFile_Found(string file_path);
void _Store_DATA(string Current_Str );
void Pass_ONE(string File_Path);
void test();

struct Symbol_Table
{
    string Label;
    string Label_Location;
};
vector <Symbol_Table> Table;
bool IsFile_Found(string file_path)
{
        ifstream File(file_path.c_str());
        return (bool)File;
}

void _Store_DATA(string Current_Str,int location)
{
    string check=_Instruction_Found_Get_INST(Current_Str);
    if(check==NOT_FOUND) //Not Instruction
    {
        if(location==0) //we must store location if it at 0 like label for jump
            {
                Table.push_back(Symbol_Table());
                Table[current_location].Label=Current_Str;
                Table[current_location].Label_Location=Prog_Loc_Counter;
                current_location++;
            }
         else if ((location==1||location==2)&&_Check_If_DECLERATION(Current_Str)==NOT_FOUND)
         {
                Labels.push_back(Current_Str);
         }
    }
    else
        {
        Instruction.push_back(Current_Str);
        }
}
void Pass_ONE(string File_Path)
{
    if(IsFile_Found(File_Path))
    {
        bool Start_Prog_Flag;
       ifstream File_Read;
       string Current_Line;
       File_Read.open(File_Path.c_str());
        while (getline(File_Read, Current_Line)) // Here We Take Line In File and put it in Current_Line
        {
            _Current_Line_Divide_Strings_BYREF(Current_Line,Current_Line_Without_Spac);
            if(Current_Line_Without_Spac[1]=="START")
           {
            Start_Prog_Flag=true;
            Prog_Name= Current_Line_Without_Spac[0];
            Prog_Loc_Counter=Current_Line_Without_Spac[2];
           }
           else if(Start_Prog_Flag==true&&Current_Line_Without_Spac[1]!="START")
           {
              for(int i=0;i<4;i++)
                {
                    if(Current_Line_Without_Spac[i]!="")
                _Store_DATA(Current_Line_Without_Spac[i],i);
                if(_Check_If_DECLERATION(Current_Line_Without_Spac[i])!=NOT_FOUND)
                    i++;
                }
                  Prog_Loc_Counter_Array.push_back(Prog_Loc_Counter);
                  if(_Check_If_DECLERATION(Current_Line_Without_Spac[1])==RESB)
                        Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,HEX_ONE,Current_Line_Without_Spac[2]/*This Offset After resb*/);
                  else if(_Check_If_DECLERATION(Current_Line_Without_Spac[1])==RESW)
                        Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,HEX_THREE,Current_Line_Without_Spac[2]/*This Offset After resw*/);
                  else if(_Check_If_DECLERATION(Current_Line_Without_Spac[1])==BYTE)
                        Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,HEX_ONE,HEX_ONE/*This For Normal Byte Inc By 1*/);
                  else // if it Word we inc by 3 because that i put it in default
                        Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,HEX_THREE,HEX_ONE/*Default inc by 3*/);
           }
           line_counter++;
        }
    }
}
/*word->inc 3
byte->inc 1
resw->inc (3*rakam aly ba3daha)
resb->inc (1*)*/
void test()
{
   for(int i=0;i<Instruction.size();i++)
    cout<<i<<"                 "<<Instruction[i]<<"           "<<Prog_Loc_Counter_Array[i]<<endl;
}

