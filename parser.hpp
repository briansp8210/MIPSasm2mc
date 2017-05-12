#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <map>
#include <string>
#include <fstream>
#define I_TYPE 0
#define J_TYPE 1

void encode_instr(std::ifstream &assembly, std::ofstream &machine_code);
void encode_r(std::stringstream &instr, std::string &op, std::string &result);
void encode_i(std::stringstream &instr, std::string &op, std::string &result, std::streampos pos, int pc);
void encode_j(std::stringstream &instr, std::string &op, std::string &result, std::streampos pos);
void resolve_symbol(std::ofstream &machine_code);

struct resolve_info
{
    std::string label;
    bool instr_type;
    int program_counter;
    resolve_info(std::string l, bool t, int p): label(l), instr_type(t), program_counter(p){};
    resolve_info(): label(""), instr_type(I_TYPE), program_counter(-1){};
};

extern std::map<std::string, int> sym_tab;
extern std::map<std::streampos, resolve_info> resolve_tab;

const std::map<std::string, std::string> op_field
{
    {   "j", "000010"},
    { "jal", "000011"},
    { "beq", "000100"},
    {"bnez", "000101"},
    { "blt", "000110"},
    { "ble", "000111"},
    {"addi", "001000"},
    { "ori", "001101"},
    {  "li", "001111"},
    {  "lw", "100011"},
    {  "sw", "101011"},
};

const std::map<std::string, std::string> funct_field
{
    {  "jr", "001000"},
    { "sll", "000000"},
    {"sllv", "000100"},
    { "mul", "011000"},
    { "add", "100000"},
    { "sub", "100010"},
    { "and", "100100"},
    {  "or", "100101"},
    { "slt", "101010"},
    {"sltu", "101011"}
};

const std::map<std::string, std::string> reg_num
{
    {"zero", "00000"},
    {  "at", "00001"},
    {  "v0", "00010"},
    {  "v1", "00011"},
    {  "a0", "00100"},
    {  "a1", "00101"},
    {  "a2", "00110"},
    {  "a3", "00111"},
    {  "t0", "01000"},
    {  "t1", "01001"},
    {  "t2", "01010"},
    {  "t3", "01011"},
    {  "t4", "01100"},
    {  "t5", "01101"},
    {  "t6", "01110"},
    {  "t7", "01111"},
    {  "s0", "10000"},
    {  "s1", "10001"},
    {  "s2", "10010"},
    {  "s3", "10011"},
    {  "s4", "10100"},
    {  "s5", "10101"},
    {  "s6", "10110"},
    {  "s7", "10111"},
    {  "t8", "11000"},
    {  "t9", "11001"},
    {  "k0", "11010"},
    {  "k1", "11011"},
    {  "gp", "11100"},
    {  "sp", "11101"},
    {  "fp", "11110"},
    {  "ra", "11111"},
    {  "r0", "00000"},
    {  "r1", "00001"},
    {  "r2", "00010"},
    {  "r3", "00011"},
    {  "r4", "00100"},
    {  "r5", "00101"},
    {  "r6", "00110"},
    {  "r7", "00111"},
    {  "r8", "01000"},
    {  "r9", "01001"},
    { "r10", "01010"},
    { "r11", "01011"},
    { "r12", "01100"},
    { "r13", "01101"},
    { "r14", "01110"},
    { "r15", "01111"},
    { "r16", "10000"},
    { "r17", "10001"},
    { "r18", "10010"},
    { "r19", "10011"},
    { "r20", "10100"},
    { "r21", "10101"},
    { "r22", "10110"},
    { "r23", "10111"},
    { "r24", "11000"},
    { "r25", "11001"},
    { "r26", "11010"},
    { "r27", "11011"},
    { "r28", "11100"},
    { "r29", "11101"},
    { "r30", "11110"},
    { "r31", "11111"}
};

#endif
