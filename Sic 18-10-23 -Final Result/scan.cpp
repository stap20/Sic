#include"scan.h"
using namespace std;
string Prog_Name,Prog_Loc_Counter;
string Current_Line_Without_Spac[4]; //this array store line without spacing like h1w1a start 1010 put it in pos 0 h1w1a pos 1 start (4 because we have label and inst and label and x if u have) mustn't have 4 string .....
vector<string> Labels;
vector<string> Instruction;
vector<string> Prog_Loc_Counter_Array;
vector<string> Ob_Code_For_Hte;
int line_counter=0; //number of line in program
string startposition;
int current_location=0;
int LITERAL_Table_location=0;
bool End_Rive=false;
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

struct Literal_Table
{
    string Value;
    string op_code_value;
    string Address;
    string LENGTH;
    bool Takken;
};
vector <Literal_Table> LITERAL_Table;

bool IsFile_Found(string file_path)
{
        ifstream File(file_path.c_str());
        return (bool)File;
}
bool IS_Found_In_Literal_Table(string current_value)
{
   for(int i=0;i<LITERAL_Table.size();i++)
   {
     if(LITERAL_Table[i].Value==current_value)
        return true;
   }
   return false;
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
//function in file rem
string expression_calc_disp(string current_str)
{
    int sign_count=0;
    string current_label="";
    vector<string> labels_must_calc_disp;
    for(int i=0;i<current_str.size();i++)
    {
        if((current_str[i]=='-')||(current_str[i]=='+')||(current_str[i]=='*')||(current_str[i]=='/'))
        {
            labels_must_calc_disp.push_back(current_label);
            sign_count++;
            current_label="";
            labels_must_calc_disp.push_back(string(1, current_str[i]));
        }
        else
        current_label+=current_str[i];
    }
     if(current_label!="")
        labels_must_calc_disp.push_back(current_label);

    if((labels_must_calc_disp.size()-sign_count)==sign_count+1)
    {
        for(int i=1;i<labels_must_calc_disp.size();i+=2)
        {
            if(labels_must_calc_disp[i]=="-")
            {
                labels_must_calc_disp[i+1] = _String_Hex_DEC_X(_Get_Label_LOC(labels_must_calc_disp[i-1]),_Get_Label_LOC(labels_must_calc_disp[i+1]));
            }
        }
        return labels_must_calc_disp[labels_must_calc_disp.size()-1];
    }

    else if(labels_must_calc_disp.size()==1)
    {
        return _Get_Label_LOC(labels_must_calc_disp[0]);
    }
}
void _Store_DATA(string Current_Str,int location)
{
    string check=_Instruction_Found_Get_INST(Current_Str);
    if(check==NOT_FOUND) //Not Instruction
    {
        if(location==0) //we must store location if it at 0 like label for jump
            {
                if(Current_Str!="LTORG") //ltorg handler
                {
                    Table.push_back(Symbol_Table());
                    Table[current_location].Label=Current_Str;
                    Table[current_location].Label_Location=Prog_Loc_Counter;
                    current_location++;
                }
            }
         else if ((location==1||location==2)&&_Check_If_DECLERATION(Current_Str)!=RESB&&_Check_If_DECLERATION(Current_Str)!=RESW)
         {
                Labels.push_back(Current_Str);
         }
         else if((location==1||location==2)&&(_Check_If_DECLERATION(Current_Str)==RESB||_Check_If_DECLERATION(Current_Str)==RESW))
          {
              Labels.push_back(RESB);
              Instruction.push_back("-1");
          }
    }
    else
        {
        Instruction.push_back(Current_Str);
        }
}
void literal_add()
{
     //   cout<<"------------------------------------->"<<Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1]<<endl;

    string temp;
    for(int i=0;i<LITERAL_Table.size();i++)
    {
        if(LITERAL_Table[i].Takken==false)
        {
            temp=LITERAL_Table[i].Value;
            temp.insert(0,"=");
            Labels.push_back("*");
            Instruction.push_back(temp);
            if(End_Rive==true) //end prog
            {
                LITERAL_Table[i].Address=Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1];
                Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,LITERAL_Table[i].LENGTH,HEX_ONE);
                Prog_Loc_Counter_Array.push_back(Prog_Loc_Counter);
            }
            else
            {
                Prog_Loc_Counter_Array.push_back(Prog_Loc_Counter);
                Prog_Loc_Counter=_String_Hex_INC_X(Prog_Loc_Counter,LITERAL_Table[i].LENGTH,HEX_ONE);
                LITERAL_Table[i].Address=Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1];
            }
            LITERAL_Table[i].Takken=true;
       // cout<<"------------------------------------->"<<Prog_Loc_Counter<<endl;

        }
    }
}
///Pass One
void Pass_ONE(string File_Path)
{
    if(IsFile_Found(File_Path))
    {
        bool Start_Prog_Flag;
       ifstream File_Read;
       bool not_EQU=false;
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
                    if((Current_Line_Without_Spac[0]=="BASE")||(Current_Line_Without_Spac[1]=="BASE"))
                    break;
                    if(Current_Line_Without_Spac[1]=="EQU")
                        break; //we will store equ manually
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
                    if(Current_Line_Without_Spac[i][0]=='=')
                    {
                        Current_Line_Without_Spac[i].erase(0,1);
                        if(IS_Found_In_Literal_Table(Current_Line_Without_Spac[i])==false)
                        {
                            int str_size=Current_Line_Without_Spac[i].size()-3;
                            LITERAL_Table.push_back(Literal_Table());
                            LITERAL_Table[LITERAL_Table_location].Value=Current_Line_Without_Spac[i];

                            LITERAL_Table[LITERAL_Table_location].op_code_value=String_To_Opcode(Current_Line_Without_Spac[i]); // op code handeler value

                            if((Current_Line_Without_Spac[i][0]=='x')||(Current_Line_Without_Spac[i][0]=='X'))
                            {
                                int inc_size=ceil((str_size*1.0)/2.0);
                                LITERAL_Table[LITERAL_Table_location].LENGTH=String_To_Opcode_Change_Size_TO_X(to_string(inc_size),4,'0');
                            }
                            else
                            LITERAL_Table[LITERAL_Table_location].LENGTH=String_To_Opcode_Change_Size_TO_X(to_string(str_size),4,'0');
                            LITERAL_Table_location++;
                        }
                    }
                }
                if(Current_Line_Without_Spac[1]=="")
                    Labels.push_back("");
            if((Current_Line_Without_Spac[0]=="BASE")||(Current_Line_Without_Spac[1]=="BASE"))
            {

            }

           else if(Current_Line_Without_Spac[0]=="LTORG")
                  {
                    literal_add();
                  }
            else
            {
                  Prog_Loc_Counter_Array.push_back(Prog_Loc_Counter);
                  if(_Instruction_Found_Get_INST(Current_Line_Without_Spac[0])!=NOT_FOUND)
                 {
                      not_EQU=_Instruction_Found_Get_Location_Count_INC(Prog_Loc_Counter,Current_Line_Without_Spac,0);
                 }

                  else if(_Instruction_Found_Get_INST(Current_Line_Without_Spac[1])!=NOT_FOUND)
                 {
                  not_EQU=_Instruction_Found_Get_Location_Count_INC(Prog_Loc_Counter,Current_Line_Without_Spac,1);
                 }

                  else
                  {
                    not_EQU=_Instruction_Found_Get_Location_Count_INC(Prog_Loc_Counter,Current_Line_Without_Spac,1);
                      if((not_EQU==false)&&_Get_Label_LOC(Current_Line_Without_Spac[1])==NOT_FOUND) //this EQUATE inst
                      {
                        Labels.push_back(Current_Line_Without_Spac[0]);
                        Instruction.push_back(Current_Line_Without_Spac[1]);
                        if(Current_Line_Without_Spac[2]=="*")
                        Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1]=Prog_Loc_Counter;

                        else if(is_number(Current_Line_Without_Spac[2]))
                        {
                            reverse(Current_Line_Without_Spac[2].begin(),Current_Line_Without_Spac[2].end());
                            int int_value=_Str_To_INT(Current_Line_Without_Spac[2]);
                            string Hex_Num_After_CONV=_Int_To_Hex_STR(int_value,4);
                            Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1]=Hex_Num_After_CONV;
                        }
                        else
                           Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1]=expression_calc_disp(Current_Line_Without_Spac[2]);

                            Table.push_back(Symbol_Table());
                            Table[current_location].Label=Current_Line_Without_Spac[0];
                            Table[current_location].Label_Location=Prog_Loc_Counter_Array[Prog_Loc_Counter_Array.size()-1];
                            current_location++;
                      }

                  }
            }
           }
           line_counter++;
        }
        if(LITERAL_Table.size()>0)
        {
            End_Rive=true;
            literal_add();
        }
    }
}

///Pass Two
//void Pass_TWO(string File_Path)
//{
//    if(IsFile_Found(File_Path))
//    {
//        int current_Ob_For_Hte=0;// because we set -1 if it resb or resw
//       ofstream File_Write;
//       string Current_Opcode="";
//       File_Write.open(File_Path.c_str());
//       ///Symbol Table
//       File_Write<<"                                 SYMBOL TABLE"<<endl;
//       File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
//       File_Write<<"			   ------------------------"<<endl;
//
//       for(int i=0;i<Table.size()&&Table[i].Label!="END";i++)
//       {
//        File_Write<<"			  |"<<Table[i].Label<<"               "<<Table[i].Label_Location<<endl;
//        if(i<Table.size()-2)
//        File_Write<<"                          |------------------------"<<endl;
//       }
//
//       ///OP Code & Location Counter
//       File_Write<<"                           ------------------------"<<endl;
//       File_Write<<"==========================================================================================="<<endl;
//       File_Write<<"                          OP Code & Location Counter"<<endl;
//       File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
//       File_Write<<"			   ------------------------"<<endl;
//
//        for(int i=0;i<Labels.size()-1;i++) // 34an ma5od4 ma3aya al location bata3 end
//        {
//            File_Write<<"			  |"<<Prog_Loc_Counter_Array[i];
//           if(Labels[i]=="") //RSUB OBJ Code Handle
//            {
//                string current_obj_code;
//                string instruction_as_op=_Instruction_Found_Get_INST(Instruction[i]);
//                reverse(instruction_as_op.begin(),instruction_as_op.end());
//                current_obj_code=String_To_Opcode_Change_Size_TO_X(instruction_as_op,6,'0');
//                reverse(current_obj_code.begin(),current_obj_code.end());
//                Ob_Code_For_Hte.push_back(current_obj_code);
//                    File_Write<<"               "<<current_obj_code<<"|"<<endl;
//                    current_Ob_For_Hte++;
//            }
//
//          else if(_Check_If_DECLERATION(Labels[i])!=RESB&&_Check_If_DECLERATION(Labels[i])!=RESW)
//            {
//                 ///Indirect Addressing
//                  if(Labels[i][Labels[i].size()-1]=='x'||Labels[i][Labels[i].size()-1]=='X')
//                  {
//                      Ob_Code_For_Hte.push_back(_Instruction_Found_Get_INST(Instruction[i])+_Hex_Indirect_CHANGER(_Get_Label_LOC(Labels[i].substr(0, Labels[i].size()- 1))));
//                    File_Write<<"               "<<_Instruction_Found_Get_INST(Instruction[i])+_Hex_Indirect_CHANGER(_Get_Label_LOC(Labels[i].substr(0, Labels[i].size()- 1)/* here we remove last char x*/))<<"|"<<endl; // if it word we store value in hex now we fit it in 6 digit
//                    current_Ob_For_Hte++;
//                  }
//                  else if(_Check_If_DECLERATION(Labels[i])==WORD)
//                  {
//                      Ob_Code_For_Hte.push_back(String_To_Opcode_Change_Size_TO_X(Instruction[i],6,'0'));
//                    File_Write<<"               "<<String_To_Opcode_Change_Size_TO_X(Instruction[i],6,'0')<<"|"<<endl; // if it word we store value in hex now we fit it in 6 digit
//                    current_Ob_For_Hte++;
//                  }
//
//                  ///Byte
//                   else if(_Check_If_DECLERATION(Labels[i])==BYTE)
//                   {
//                       string current_ob_code=Instruction[i];
//                       if(current_ob_code.size()>6)
//                       {
//                       vector<string> current_ob_code_for_hte;
//                       Object_Code_Fix_Exced_6(current_ob_code_for_hte,current_ob_code);
//                       for(int j=0;j<current_ob_code_for_hte.size();j++)
//                       {
//                       Ob_Code_For_Hte.push_back(current_ob_code_for_hte[j]);
//                       current_Ob_For_Hte++;
//                        if(j>=1)
//                        {
//                            reverse(current_ob_code_for_hte[j].begin(),current_ob_code_for_hte[j].end());
//                            current_ob_code_for_hte[j]=String_To_Opcode_Change_Size_TO_X(current_ob_code_for_hte[j],6,' ');
//                            reverse(current_ob_code_for_hte[j].begin(),current_ob_code_for_hte[j].end());
//                            File_Write<<"                          |                   "<<current_ob_code_for_hte[j]<<"|"<<endl;
//                        }
//                         else
//                       File_Write<<"               "<<current_ob_code_for_hte[j]<<"|"<<endl;
//                        if(j<current_ob_code_for_hte.size()-1)
//                        File_Write<<"                          |-------------------------|"<<endl;
//                       }
//                       }
//                       else
//                       {
//                        Ob_Code_For_Hte.push_back(current_ob_code);
//                       File_Write<<"               "<<current_ob_code<<"|"<<endl; // if it byte we store value in hex now we only display it
//                       current_Ob_For_Hte++;
//                       }
//                   }
//
//                   ///Label
//                   else if(Instruction[i]!="-1")
//                   {
//                        Ob_Code_For_Hte.push_back(_Instruction_Found_Get_INST(Instruction[i])+_Get_Label_LOC(Labels[i]));
//                       File_Write<<"               "<<_Instruction_Found_Get_INST(Instruction[i])+_Get_Label_LOC(Labels[i])<<"|"<<endl; //normal op code
//                       current_Ob_For_Hte++;
//                   }
//            }
//            else if(_Check_If_DECLERATION(Labels[i])==RESB||_Check_If_DECLERATION(Labels[i])==RESW)
//                    {
//                      Ob_Code_For_Hte.push_back("-1"); // handle if( we have resb or resw in middle)
//            File_Write<<"                     |"<<endl;
//                    }
//            else
//                File_Write<<"                     |"<<endl;
//            if(i<Labels.size()-2)
//            File_Write<<"                          |-------------------------|"<<endl;
//        }
//
//        Ob_Code_For_Hte.push_back("0"); //for end
//        File_Write<<"                           -------------------------"<<endl;
//        File_Write<<"==========================================================================================="<<endl;
//        File_Write<<"                                      HTE"<<endl;
//        File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
//        File_Write<<"                                     Header"<<endl;
//        File_Write<<"			    ----------------------"<<endl;
//
//        ///Head
//        reverse(Prog_Name.begin(),Prog_Name.end());  //4akl
//        Prog_Name=String_To_Opcode_Change_Size_TO_X(Prog_Name,6,' '); //fit name 6 places 34an 4akl bas
//        reverse(Prog_Name.begin(),Prog_Name.end());  //4akl
//        File_Write<<"                           |H^"<<Prog_Name<<"^";
//        File_Write<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0')<<"^";
//        File_Write<<String_To_Opcode_Change_Size_TO_X(_String_Hex_DEC_X(Table[Table.size()-1].Label_Location,Prog_Loc_Counter_Array[0]),6,'0')<<"|"<<endl;
//        File_Write<<"			    ----------------------"<<endl;
//
//        ///Text
//        File_Write<<"                 ==============================================="<<endl;
//       int i=0,last=0,sum_bits=0,j=0;
//        vector <string> current_prog_length;  //store all program lengths in this vector
//         Prog_Length_Calc(Ob_Code_For_Hte,Prog_Loc_Counter_Array,current_prog_length);
//         for( i=0;i<current_prog_length.size();i++)
//         {
//             cout<<"A"<<current_prog_length[i]<<endl;
//                    ///Text
//                    File_Write<<"                                     Text : "<<i+1<<endl;
//                    File_Write<<"			    ----------------------"<<endl;
//                    File_Write<<" ---------------------------------------------------------------------------------------"<<endl;
//                    File_Write<<"|T^"<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0');
//                    File_Write<<"^"<<current_prog_length[i];
//
//                     for( j=last;(sum_bits+Ob_Code_For_Hte[j].size())<=60&&Ob_Code_For_Hte[j]!="-1"&&j<=Ob_Code_For_Hte.size();j++)
//                        {
//                            File_Write<<"^"<<Ob_Code_For_Hte[j];
//                            sum_bits+=Ob_Code_For_Hte[j].size();
//                        }
//                     if(Ob_Code_For_Hte[j]=="-1")
//                            j++;
//
//                    sum_bits=0;
//                    last=j;
//
//                    File_Write<<endl;
//                    File_Write<<" ---------------------------------------------------------------------------------------"<<endl;
//         }
//        ///End
//        File_Write<<"==========================================================================================="<<endl;
//        File_Write<<"                                      END"<<endl;
//        File_Write<<"-------------------------------------------------------------------------------------------"<<endl;
//        File_Write<<"                           	    --------"<<endl;
//        File_Write<<"                                   |E^"<<String_To_Opcode_Change_Size_TO_X(Prog_Loc_Counter_Array[0],6,'0')<<"|"<<endl;;
//        File_Write<<"                           	    --------"<<endl;
//      File_Write.close();
//
//   }
//}
void test()
{

    for(int i=0;i<Prog_Loc_Counter_Array.size();i++)
    {
        cout<<Prog_Loc_Counter_Array[i]<<"      "<<Instruction[i]<<endl;
    }
   cout<<"-----------------------------------"<<endl;
   for(int i=0;i<LITERAL_Table.size();i++)
        cout<<LITERAL_Table[i].Address<<"           "<<LITERAL_Table[i].LENGTH<<"          "<<LITERAL_Table[i].Value<<"      "<<LITERAL_Table[i].op_code_value<<endl;

  /* for(int i=0;i<Labels.size();i++)
   {
       string temp;
       temp = _Get_Label_LOC(Labels[i]);
       if(i<Instruction.size())
       {
           if(_Instruction_Found_Get_INST(Instruction[i])!=NOT_FOUND)
                       cout<<i<<"             "<<Prog_Loc_Counter_Array[i]<<"                    "<<"         "<<Instruction[i]<<"           "<<Labels[i]<<endl;
           else
                       cout<<i<<"             "<<Prog_Loc_Counter_Array[i]<<"                    "<<"         "<<Instruction[i]<<"           "<<Labels[i]<<endl;

       }
        else
          cout<<i<<"             "<<Prog_Loc_Counter_Array[i]<<"                    "<<"                     "<<Labels[i]<<endl;
   }*/
   cout<<"-----------------------------------"<<endl;
   for(int i=0;i<Table.size()-1;i++)
        cout<<Table[i].Label_Location<<"           "<<Table[i].Label<<endl;
}
