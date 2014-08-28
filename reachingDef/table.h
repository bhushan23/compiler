#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>
using namespace std;
void opcode_table_init();
string opcode_table_getinst(int);
int opcode_table_getindex(string&);
int add_symbol(string&);
int get_symbol_index(string&);
string get_symbol(int );
#endif
