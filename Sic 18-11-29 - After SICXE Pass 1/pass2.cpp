#include "pass2.h"
void PASS_TWO(vector<string> &Labels,vector<string> &Instruction,
              vector<string> &Prog_Loc_Counter_Array,vector <Symbol_Table> &Table,
              vector<string> &Ob_Code_For_Hte,vector <Literal_Table> &LITERAL_Table,
              vector<string> &Another_Labels,int &current_Ob_For_Hte)
{
    for(int i=0;i<Another_Labels.size()-1;i++) // 34an ma5od4 ma3aya al location bata3 end
    {
        string ob;
         if(Another_Labels[i]=="") //RSUB OBJ Code Handle
        {
          ob="4F0000";
        }
        else if(Another_Labels[i][0]=='X'||Another_Labels[i][0]=='C')
        {
            ob = String_To_Opcode(Another_Labels[i]);
        }

        else
        {
             ob=OBJECT_CODE_Create(Instruction[i] ,Another_Labels[i] ,Prog_Loc_Counter_Array[i+1],Table,LITERAL_Table);
        }
    cout<<ob<<"       "<<Prog_Loc_Counter_Array[i+1]<<"          "<<Instruction[i]<<"        "<<Another_Labels[i]<<endl;
    //cout<<ob<<endl;
    cout<<"------------------------------------------"<<endl;
       Ob_Code_For_Hte.push_back(ob);

    }
}
