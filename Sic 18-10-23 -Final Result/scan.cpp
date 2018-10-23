#include"scan.h"
using namespace std;
string Prog_Name,Prog_Loc_Counter;
string Current_Line_Without_Spac[4]; //this array store line without spacing like h1w1a start 1010 put it in pos 0 h1w1a pos 1 start (4 because we have label and inst and label and x if u have) mustn't have 4 string .....
vector<string> Labels;
vector<string> Instruction;
vector<string> Prog_Loc_Counter_Array;
vector<string> Op_Code_For_Hte;
int line_counter=0; //number of line in program
string startposition;
int current_location=0;

bool IsFile_Found(string file_path);
void _Store_DATA(string Current_Str );
void Pass_ONE(string File_Path);
void test();
void test2();
void Pass_TWO(string File_Path);

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
         else if ((location==1||location==2))
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
            startposition=Current_Line_Without_Spac[2];
           }
           else if(Start_Prog_Flag==true&&Current_Line_Without_Spac[1]!="START")
           {
              for(int i=0;i<4;i++)
                {
                    if(Current_Line_Without_Spac[i]!="")
                _Store_DATA(Current_Line_Without_Spac[i],i);
                if(_Check_If_DECLERATION(Current_Line_Without_Spac[i])!=NOT_FOUND)
                    {
                        string check=_Check_If_DECLERATION(Current_Line_Without_Spac[i]);
                        if(check!=RESB&&check!=RESW)
                        {
                           Instruction.push_back(String_To_Opcode(Current_Line_Without_Spac[2]));
                        }
                        i++;
                    }
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

string _Get_Label_LOC(string Label)
{
    for(int i=0;i<Table.size();i++)
    {
        if(Label==Table[i].Label)
            return Table[i].Label_Location;
    }
    return NOT_FOUND;
}


void Pass_TWO(string File_Path)
{
    if(IsFile_Found(File_Path))
    {
       ofstream File_Write;
       string Current_Opcode="";
       File_Write.open(File_Path.c_str());
       ///Symbol Table
       File_Write<<"                                 SYMBOL TABLE"<<endl;
       File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
       File_Write<<"			   ------------------------"<<endl;

       for(int i=0;i<Table.size()&&Table[i].Label!="END";i++)
       {
        File_Write<<"			  |"<<Table[i].Label<<"               "<<Table[i].Label_Location<<endl;
        if(i<Table.size()-2)
        File_Write<<"                          |------------------------"<<endl;
       }

       ///OP Code & Location Counter
       File_Write<<"                           ------------------------"<<endl;
       File_Write<<"==========================================================================================="<<endl;
       File_Write<<"                          OP Code & Location Counter"<<endl;
       File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
       File_Write<<"			   ------------------------"<<endl;

        for(int i=0;i<Labels.size();i++)
        {
            File_Write<<"			  |"<<Prog_Loc_Counter_Array[i];
            if(_Check_If_DECLERATION(Labels[i])!=RESB&&_Check_If_DECLERATION(Labels[i])!=RESW)
            {
                  if(Labels[i][Labels[i].size()-1]=='x'||Labels[i][Labels[i].size()-1]=='X')
                  {
                      Op_Code_For_Hte.push_back(_Instruction_Found_Get_INST(Instruction[i])+_Hex_Indirect_CHANGER(_Get_Label_LOC(Labels[i].substr(0, Labels[i].size()- 1))));
                    File_Write<<"               "<<_Instruction_Found_Get_INST(Instruction[i])+_Hex_Indirect_CHANGER(_Get_Label_LOC(Labels[i].substr(0, Labels[i].size()- 1)/* here we remove last char x*/))<<"|"<<endl; // if it word we store value in hex now we fit it in 6 digit
                  }
                  else if(_Check_If_DECLERATION(Labels[i])==WORD)
                  {
                      Op_Code_For_Hte.push_back(String_To_Opcode_Change_Size_TO_X(Instruction[i],6,'0'));
                    File_Write<<"               "<<String_To_Opcode_Change_Size_TO_X(Instruction[i],6,'0')<<"|"<<endl; // if it word we store value in hex now we fit it in 6 digit
                  }
                   else if(_Check_If_DECLERATION(Labels[i])==BYTE)
                   {
                       Op_Code_For_Hte.push_back(Instruction[i]);
                       File_Write<<"               "<<Instruction[i]<<endl; // if it byte we store value in hex now we only display it
                   }
                   else
                   {
                       Op_Code_For_Hte.push_back(_Instruction_Found_Get_INST(Instruction[i])+_Get_Label_LOC(Labels[i]));
                       File_Write<<"               "<<_Instruction_Found_Get_INST(Instruction[i])+_Get_Label_LOC(Labels[i])<<"|"<<endl; //normal op code
                   }
            }

            else
                File_Write<<"                     |"<<endl;
            if(i<Labels.size()-1)
            File_Write<<"                          |-------------------------|"<<endl;
        }

        File_Write<<"                           -------------------------"<<endl;
        File_Write<<"==========================================================================================="<<endl;
        File_Write<<"                                      HTE"<<endl;
        File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
        File_Write<<"                                     Head"<<endl;
        File_Write<<"			    ----------------------"<<endl;

        ///Head
        reverse(Prog_Name.begin(),Prog_Name.end());  //4akl
        Prog_Name=String_To_Opcode_Change_Size_TO_X(Prog_Name,6,' '); //fit name 6 places 34an 4akl bas
        reverse(Prog_Name.begin(),Prog_Name.end());  //4akl
        File_Write<<"                           |H^"<<Prog_Name<<"^";
        File_Write<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0')<<"^";
        File_Write<<String_To_Opcode_Change_Size_TO_X(_String_Hex_DEC_X(Table[Table.size()-1].Label_Location,Prog_Loc_Counter_Array[0]),6,'0')<<"|"<<endl;
        File_Write<<"			    ----------------------"<<endl;

        ///Text
        File_Write<<"                 ==============================================="<<endl;
        File_Write<<"                                     Text"<<endl;
        File_Write<<"			    ----------------------"<<endl;
        File_Write<<" ---------------------------------------------------------------------------------------"<<endl;

        File_Write<<"|T^"<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0')<<"^"<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0');
        File_Write<<"^"<<String_Decrease_SIZE(_String_Hex_DEC_X(Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-2],Prog_Loc_Counter_Array[0]),'0');
        for(int i=0;i<Op_Code_For_Hte.size();i++)
          File_Write<<"^"<<Op_Code_For_Hte[i];
          File_Write<<endl;
        File_Write<<" ---------------------------------------------------------------------------------------"<<endl;

        ///End
        File_Write<<"==========================================================================================="<<endl;
        File_Write<<"                                      END"<<endl;
        File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
        File_Write<<"                           	    --------"<<endl;
        File_Write<<"                                   |E^"<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0')<<"|"<<endl;;
        File_Write<<"                           	    --------"<<endl;
      File_Write.close();

   }
}
   /*
   for(int i=0;i<Labels.size();i++)
   {
                string temp = _Get_Label_LOC(Labels[itest]);
                if(Current_Line_Without_Spac[1]=="RESW" || Current_Line_Without_Spac[1]=="RESB")
                opcode="";
                if(Current_Line_Without_Spac[0]=="RSUB")
                opcode="4C0000";
                else if(_Instruction_Found_Get_INST(Current_Line_Without_Spac[0]) != NOT_FOUND)     //If instruction is in 1st
                opcode= _Instruction_Found_Get_INST(Current_Line_Without_Spac[0]) + temp;           //place of array, NO LABEL.
                else if (_Instruction_Found_Get_INST(Current_Line_Without_Spac[1]) != NOT_FOUND)    //If instruction is after
                opcode= _Instruction_Found_Get_INST(Current_Line_Without_Spac[1]) + temp;           //after a label.
   }


       cout<<"H" <<"^"<<Prog_Name <<"^0"<<startposition<<"^"<<Prog_Loc_Counter;
       cout<<"\n"<<"T"<<"^";
       cout<<"\n"<<"E"<<"^"<<startposition;

   }

}
*/



/*
void test2()
{

    for(int i=0;i<Labels.size();i++)
   {
       string temp;
       temp = _Get_Label_LOC(Labels[i]);
       if(i<Instruction.size())
            cout<<i<<"\t\t"<<current_location <<"\t"<<Labels[i][Labels[i].size()-1]<<"\t"
            <<_Instruction_Found_Get_INST(Instruction[i])<<"\t"<<Labels[i]<<"\t"<<temp<<endl;
        else
          cout<<i<<"                              "<<Labels[i]<<endl;
   }
   cout<<"\n---------------Symbol Table----------------"<<endl;
   for(int i=0;i<Table.size();i++)
        cout<<i<<"                 "<<Table[i].Label<<"           "<<Table[i].Label_Location<<endl;


}*/
void test()
{
   for(int i=0;i<Labels.size();i++)
   {
       string temp;
       temp = _Get_Label_LOC(Labels[i]);
       if(i<Instruction.size())
       {
           if(_Instruction_Found_Get_INST(Instruction[i])!=NOT_FOUND)
                       cout<<Prog_Loc_Counter_Array[i]<<"                 "<<_Instruction_Found_Get_INST(Instruction[i])<<"           "<<Labels[i]<<endl;
           else
                                   cout<<Prog_Loc_Counter_Array[i]<<"                 "<<Instruction[i]<<"           "<<Labels[i]<<endl;

       }
        else
          cout<<Prog_Loc_Counter_Array[i]<<"                              "<<Labels[i]<<endl;
   }
   cout<<"-----------------------------------"<<endl;
   for(int i=0;i<Table.size();i++)
        cout<<i<<"                 "<<Table[i].Label<<"           "<<Table[i].Label_Location<<endl;
}
