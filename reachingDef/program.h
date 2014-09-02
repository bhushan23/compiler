#ifndef PROGRAM_H
#define PROGRAM_H
#include "basicblock.h"
#include "irclass.h"
class Program{
    list<BasicBlock*> basicBlock;
    map<string,BasicBlock*> mapBB;
    public:
    list <BasicBlock*>::iterator get_begin();
    list <BasicBlock*>::iterator get_end();
    void print_program();
    void create_dot_file();
    void addNewBb(BasicBlock* bb);
    Program(){

    }
    Program(BasicBlock* bb){
        basicBlock.push_back(bb);
    }
    BasicBlock* GetBasicBlockFromLabel(string&);    
    void add_instruction(instruction* ,instruction*);
    void add_instruction(instruction* , BasicBlock*);

};
#endif
