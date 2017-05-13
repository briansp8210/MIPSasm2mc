#include <map>
#include <bitset>
#include <cctype>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "parser.hpp"
#include "auxtool.hpp"
using namespace std;

map<string, int> sym_tab;
map<streampos, resolve_info> resolve_tab;

void encode_instr(ifstream &assembly, ofstream &machine_code)
{
    string instruction;
    string result;
    string op;
    int pc = 0;
    streampos pos;

    while(!assembly.eof())
    {
        // reading a line of instruction/label and trimming it
        getline(assembly, instruction);
        trim_str(instruction);

        // when coming across a label
        if(instruction.back() == ':')
        {
            string symbol(instruction.substr(0, instruction.length()-1));
            if(sym_tab.find(symbol) != sym_tab.end())
            {
                error_msg("Multiple definition of symbol!");
            }

            sym_tab[symbol] = pc;
            continue;
        }

        // otherwise, an instruction is read, begin to parse each field of it
        // also, record current output position
        stringstream instr_ss(instruction);
        pos = machine_code.tellp();

        getline(instr_ss, op, ' ');
        lower_str(op);

        // R-type instruction
        if(op=="jr"  || op=="sllv" || op=="sll" || op=="sllv" || op=="mul" ||
           op=="add" || op=="sub"  || op=="and" || op=="or"   || op=="slt" || op=="sltu")
        {
            encode_r(instr_ss, op, result);
        }
        // I-type instruction
        else if(op=="addi" || op=="beq" || op=="li"  || op=="ori" || op=="bnez" ||
                op=="lw"   || op=="sw"  || op=="blt" || op=="ble")
        {
            encode_i(instr_ss, op, result, pos, pc);
        }
        // J-type instruction
        else if(op=="j" || op=="jal")
        {
            encode_j(instr_ss, op, result, pos);
        }
        // blank line
        else if(op=="")
        {
            continue;
        }

        pc++;
        machine_code<<result<<'\n';
    }

    // starting to resolve the symbols
    resolve_symbol(machine_code);
}

// Encode R-type instruction
void encode_r(stringstream &instr, string &op, string &result)
{
    string rs("00000");
    string rt("00000");
    string rd("00000");
    string shamt("00000");

    // op $rs
    if(op=="jr")
    {
        getline(instr, rs);
    }
    // op $rd, $rt, shamt
    else if(op=="sll")
    {
        getline(instr, rd, ',');
        getline(instr, rt, ',');
        getline(instr, shamt);
    }
    // op $rd, $rt, $rs
    else if(op=="sllv")
    {
        getline(instr, rd, ',');
        getline(instr, rt, ',');
        getline(instr, rs);
    }
    // op $rd, $rs, $rt
    else if(op=="mul" || op=="add" || op=="sub" || op=="and" ||op=="or" ||
            op=="slt" || op=="sltu")
    {
        getline(instr, rd, ',');
        getline(instr, rs, ',');
        getline(instr, rt);
    }
    else
    {
        error_msg("Wrong control flow!!");
    }

    formalize_imm(shamt, 5);
    result = "000000" + fetch_reg(rs) + fetch_reg(rt) + fetch_reg(rd) + shamt + funct_field.at(op);
}

// Encode I-type instruction
void encode_i(stringstream &instr, string &op, string &result, streampos pos, int pc)
{
    string rs("00000");
    string rt("00000");
    string immediate("0000000000000000");

    // op $rt, immediate($rs)
    if(op=="lw" || op=="sw")
    {
        getline(instr, rt, ',');
        getline(instr, immediate, '(');
        getline(instr, rs, ')');
        instr.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // op $rs, immediate
    else if(op=="bnez")
    {
        getline(instr, rs, ',');
        getline(instr, immediate);
    }
    // op $rt, immediate
    else if(op=="li")
    {
        getline(instr, rt, ',');
        getline(instr, immediate);
    }
    // op $rt, $rs, immediate
    else if(op=="addi" || op=="ori")
    {
        getline(instr, rt, ',');
        getline(instr, rs, ',');
        getline(instr, immediate);
    }
    // op $rs, $rt, immediate
    else if(op=="beq" || op=="blt"  || op=="ble")
    {
        getline(instr, rs, ',');
        getline(instr, rt, ',');
        getline(instr, immediate);
    }
    else
    {
        error_msg("Wrong control flow!!");
    }

    if(!formalize_imm(immediate, 16))
    {
        // here, immediate is actually a label, which has been trimmed
        resolve_info tmp(immediate, I_TYPE, pc);
        streamoff off = 16;
        resolve_tab[pos+off] = tmp;
        immediate = "0000000000000000";
    }
    result = op_field.at(op) + fetch_reg(rs) + fetch_reg(rt) + immediate;
}

//Encode J-type instruction
void encode_j(stringstream &instr, string &op, string &result, streampos pos)
{
    string target_address("00000000000000000000000000");

    getline(instr, target_address);

    if(!formalize_imm(target_address, 26))
    {
        // in J-type case, pc isn't needed
        resolve_info tmp(target_address, J_TYPE, -1);
        streamoff off = 6;
        resolve_tab[pos+off] = tmp;
        target_address = "00000000000000000000000000";
    }
        
    result = op_field.at(op) + target_address;
}

// translate the symbol in branch and jump instruction to correct value
void resolve_symbol(ofstream &machine_code)
{
    map<streampos, resolve_info>::iterator iter;

    for(iter=resolve_tab.begin(); iter!=resolve_tab.end(); ++iter)
    {
        // set the output position to immediate field of branch instruction
        // or target address field of jump instruction
        machine_code.seekp(iter->first);

        string label = (iter->second).label;
        int label_pc = sym_tab[label];

        if((iter->second).instr_type == I_TYPE)
        {
            int pc = (iter->second).program_counter;
            bitset<16> tmp(label_pc - (pc+1));
            machine_code<<tmp<<'\n';
        }
        else
        {
            bitset<26> tmp(label_pc);
            machine_code<<tmp<<'\n';
        }
    }
}

