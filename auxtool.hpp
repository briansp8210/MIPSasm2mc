#ifndef AUXTOOL_HPP_
#define AUXTOOL_HPP_
#include <string>

void lower_str(std::string &str);
std::string fetch_reg(std::string &reg);
bool formalize_imm(std::string &imm, int len);
void trim_str(std::string &str);
int radix_chk(std::string &str);
void error_msg(char *msg);

#endif
