//#include "irclass.h"
#include <iostream>
#include "program.h"
#include "basicblock.h"
using namespace std;


int main(){
    BasicBlock* entryBB = new BasicBlock();
    operand op[5],oplab[5];
    //instruction ir[6];
    Program program =  Program();
    
    op[0]=operand(reg,"r0");
    op[1]=operand(reg,"r1");
    op[2]=operand(reg,"r2");
    op[3]=operand(sym,"A");
    op[4]=operand(con,5);
    oplab[0] = operand(oplabel,"BB1");
    oplab[1] = operand(oplabel,"BB2");
    instruction* irs1 = new instruction(mov,op[0],op[4],"entry");
    instruction* irs1a = new instruction(ld,op[1],op[3]);
    instruction* irs2 = new instruction(mov,op[2],op[0]);
    instruction* irs3 = new instruction(jmpe,op[2],op[1],oplab[0]);
    instruction* irs4 = new instruction(add,op[0],op[1],"BB1");
    instruction* irs5 = new instruction(add,op[0],op[0],op[1]);
    instruction* irs6 = new instruction(st,op[3],op[0]);
    instruction* irj = new instruction(jmp,oplab[1]);
    instruction* irj1 = new instruction(add,op[0],op[1],"BB2");
     
    program.add_instruction(irs1,entryBB);  
    program.add_instruction(irs1a,irs1);
    program.add_instruction(irs2,irs1a);
    program.add_instruction(irs3,irs2); 
    program.add_instruction(irs4,irs3);
   // (irs5->getParent())->add_instruction(irj);
    program.add_instruction(irs5,irs4);
    program.add_instruction(irs6,irs5);
    program.add_instruction(irj,irs6);
    program.add_instruction(irj1,irj);
    irs4->set_opcodeno(sub);
    /*
       instruction& irs5 = program.add_instruction(instruction(ld,op[0],op[3]));
       instruction& irs1 = program.add_instruction(instruction(ld,op[1],op[4]));
       instruction& irs3 = program.add_instruction(instruction(add,op[2],op[1],op[0]));
       instruction& irs6 = program.add_instruction(instruction(st,op[3],op[2]));
       */
   // entryBB->print_instruction();
irs6->set_opcodeno(ld);
//entryBB->print_instruction();

program.print_program();

    return 0;
}
