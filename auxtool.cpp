#include <bitset>
#include <cctype>
#include <string>
#include <iostream>
#include "parser.hpp"
#include "auxtool.hpp"
using namespace std;

// convert a string to lower case
void lower_str(string &str)
{
    for(size_t i=0; i<str.length(); i++)
        str[i] = tolower(str[i]);
}

// fetch the register number
string fetch_reg(string &reg)
{
    trim_str(reg);
    if(reg!="00000" && reg[0]!='$')
        error_msg("Register encoding error!");

    return (reg == "00000") ? "00000" : reg_num.at(reg.substr(1));
}

// formalize number into binary having len-bits
bool formalize_imm(string &imm, int len)
{
    int num;
    int radix = radix_chk(imm);

    if(radix == -1)
        return false;
    else if(radix == 16)
        num = stoi(imm, nullptr, 16);
    else if(radix == 10)
        num = stoi(imm, nullptr, 10);
    else if(radix == 8)
        num = stoi(imm, nullptr, 8);
    else
        error_msg("Invalid radix of number!");

    if(num>(1<<(len-1)-1) || num<-(1<<(len-1)))
        error_msg("Immediate out of range!");

    // for R-type shamt field
    if(len == 5)
    {
        bitset<5> tmp(num);
        imm = tmp.to_string();
    }
    // for I-type immediate field
    else if(len == 16)
    {
        bitset<16> tmp(num);
        imm = tmp.to_string();
    }
    // for J-type target address field
    else if(len == 26)
    {
        bitset<26> tmp(num);
        imm = tmp.to_string();
    }
    else
        error_msg("Invalid length of binary!");

    return true;
}

// remove leading and trailing spaces and tabs
void trim_str(string &str)
{
    size_t head, tail;

    for(head=0; head<str.length() && (str[head]==' '||str[head]=='\t'); head++);
    for(tail=str.length()-1; tail>=0 && (str[tail]==' '||str[tail]=='\t'); tail--);

    str = str.substr(head, tail-head+1);
    return;
}

// check the radix of number
int radix_chk(string &str)
{
    trim_str(str);

    // if the target is not a number
    if(str[0]!='-' && !isdigit(str[0]))
        return -1;

    if(str.length()>=2 && str[0]=='0' && tolower(str[1])=='x')
        return 16;
    else if(str.length()>=2 && str[0]=='0')
        return 8;
    else
        return 10;
}

// print an assigned error message and exit
inline void error_msg(char *msg)
{
    cerr<<"ERROR: "<<msg<<'\n';
    exit(1);
}
