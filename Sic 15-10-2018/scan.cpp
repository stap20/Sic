#include<bits/stdc++.h>
#include <fstream>
#include"scan.h"
using namespace std;
string Prog_Name;

struct Symbol_Table
{
  string Label;
  string Location;
}Table;
bool file_valid(string File_Path)
{
    ifstream file_test;
    file_test.open(File_Path.c_str());
    if(file_test.is_open())
    return true;
    return false;
}
bool find_text(string current_line,string target)
{
  if(current_line.find(target)!=std::string::npos)
  return true;
  return false;

}
void Store_Data(string current_line)
{

}
void Scan(string File_Path)
{
    if(file_valid(File_Path))
    {
    ifstream file_used;
    string current_line;
    file_used.open(File_Path.c_str());
    while (getline(file_used, current_line))
        {
          if(find_text(current_line,"START"))
          cout<<current_line<<endl;
        }
       // hex_my++;
       // cout<<hex_my<<endl;
        }

    else
        cout<<"no";
}
