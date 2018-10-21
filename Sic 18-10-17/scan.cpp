#include"scan.h"
#include"hex_inc.h"
#include"instruction_find.h"
#include"currentline_divide_strings.h"
using namespace std;
string Prog_Name,Prog_Loc_Counter;
string Current_Line_Without_Spac[4]; //this array store line without spacing like h1w1a start 1010 put it in pos 0 h1w1a pos 1 start (4 because we have label and inst and label and x if u have) mustn't have 4 string .....
vector<string> Labels;
vector<string> Instruction;
vector<string> Prog_Loc_Counter_Array;
int line_counter=0;

bool IsFile_Found(string file_path);
void _Store_DATA(string Current_Str );
void Pass_ONE(string File_Path);
void test();

struct Symbol_Table
{
    vector<string> Label;
    vector<string> Label_Location;
}Table;
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
        if(location==0)
            {
                Table.Label.push_back(Current_Str);
                Table.Label_Location.push_back(Prog_Loc_Counter);
            }
         else if((location==1||location==2)&&(Current_Str!="x"&&Current_Str!=","))
         {
                Labels.push_back(Current_Str);
                  cout<<Current_Str<<endl;
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
           else if(     2Start_Prog_Flag==true&&Current_Line_Without_Spac[1]!="START")
           {
              for(int i=0;i<4;i++)
                {
                _Store_DATA(Current_Line_Without_Spac[i],i);
                }
                  Prog_Loc_Counter_Array.push_back(Prog_Loc_Counter);
                  Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,HEX_THREE);
           }
           line_counter++;
        }
    }
}
void test()
{
   // cout<<Prog_Loc_Counter_Array.size()<<endl;
   //for(int i=0;i<Labels.size();i++)
    //cout<<Labels[i]<<" "<<Prog_Loc_Counter_Array[i]<<endl;
}
