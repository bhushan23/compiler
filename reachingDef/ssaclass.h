#ifndef SSACLASS_H
#define SSACLASS_H
#include <map>
class ssa_form{
  program pm;
  map <int,int> refering;
  int logical_reg_val;
public:
  ssa_form(){
  }
  ssa_form(program&);
  void print_instruction();
  int get_reg_operandindex(operand&);
  program get_program(){
    return pm;
  }
};
#endif
