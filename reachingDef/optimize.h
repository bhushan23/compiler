#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include "irclass.h"

class roptimizer{
  program pm;

 public:
  roptimizer(){}
  roptimizer(program& pm){
    start_optimize(pm);
  }
  void start_optimize(program&);
  bool removable_opcode(opcodeenum);
 
};


#endif
