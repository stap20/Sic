#include"hex_inc.h"
int _Hex_Char_To_INT(char conv);
char _Hex_Int_To_CHAR(int conv);
int _Hex_String_To_INT(string String);
string _Int_To_Hex_STR(int Hex_Number_In_INT,int Old_String_SIZE);
int _Str_To_INT(string String);

string _String_Hex_INC_X(string Location,string OFFSET,string Dec_OFFSET)// OFFSET is a number we must add on hex to get another location
{
   reverse(Location.begin(),Location.end()); //Reverse String Because We read Hex From Right To Left like 003c c when read array have weight 3 in hex have 0
   reverse(OFFSET.begin(),OFFSET.end()); //Reverse String Because We read Hex From Right To Left like 003c c when read array have weight 3 in hex have 0
   reverse(Dec_OFFSET.begin(),Dec_OFFSET.end());
   int Hex_After_Inc_X_INT_Value=_Hex_String_To_INT(Location)+(_Hex_String_To_INT(OFFSET)*_Str_To_INT(Dec_OFFSET)) ;
   string Hex_Num_After_CONV=_Int_To_Hex_STR(Hex_After_Inc_X_INT_Value,Location.size());

   return Hex_Num_After_CONV;
}

int _Str_To_INT(string String)
{
    double sum=0;
    for(int i=0;i<String.size();i++){
        sum+=((String[i]-'0')*pow(10,i));
    }
   return sum;
}

int _Hex_Char_To_INT(char conv)
{
       switch(conv)
       {
      case 'a' :
      case 'A' : return 10;
      case 'b' :
      case 'B' : return 11;
      case 'c' :
      case 'C' : return 12;
      case 'd' :
      case 'D' : return 13;
      case 'e' :
      case 'E' : return 14;
      case 'f' :
      case 'F' : return 15;
      default  : return conv-'0';
   }
}


char _Hex_Int_To_CHAR(int conv)
{
       switch(conv)
       {
      case 10 : return 'A';
      case 11 : return 'B';
      case 12 : return 'C';
      case 13 : return 'D';
      case 14 : return 'E';
      case 15 : return 'F';
      default : return conv+'0';
   }
}



int _Hex_String_To_INT(string String)
{
    int sum=0;
    for(int i=0;i<String.size();i++){
        sum+=_Hex_Char_To_INT(String[i])*pow(16,i);
    }

  return sum;
}


string _Int_To_Hex_STR(int Hex_Number_In_INT,int Old_String_SIZE)
{
   string String="";
   int Hex_Reminder_From_DIV;
   for(int i=Old_String_SIZE-1;i>=0;i--)
   {
    if(Hex_Number_In_INT<=15)    //To Handel If We Find Reminder Included In Hex
        String+=_Hex_Int_To_CHAR(Hex_Number_In_INT);
    else if(Hex_Number_In_INT>=pow(16,i))      //If Else We must Find Power<=Sum
        {
        Hex_Reminder_From_DIV = Hex_Number_In_INT/pow(16,i);
        String+=_Hex_Int_To_CHAR(Hex_Reminder_From_DIV);
       Hex_Number_In_INT-=Hex_Reminder_From_DIV * pow(16,i);
        }
    else   //If We Have 0 in On left not include in our number
        String+='0';
   }
    return String;
}
