#ifndef BASICBLOCK_H
#define BASICBLOCK_H
#include <list>
#include "irclass.h"
using namespace std;
class BasicBlock{
    list<instruction*> inst;
    list<BasicBlock*> pred;
    list<BasicBlock*> succ;
    string BBLabel;
    public:
    list <instruction*>::iterator get_begin_inst();
    list <instruction*>::iterator get_end_inst();
    list <BasicBlock*>::iterator get_begin_pred(){
        return pred.begin();
    }
    list <BasicBlock*>::iterator get_end_pred(){
        return pred.end();
    }
    list <BasicBlock*>::iterator get_begin_succ(){
        return succ.begin();
    }
    list <BasicBlock*>::iterator get_end_succ(){
        return succ.end();
    }
    void setBBLabel(string& st){
        BBLabel = st;
    }
   string getBBLabel(){
        return BBLabel;
    }
    void print_pred();
    void print_succ();
    void print_instruction();
    void add_instruction(instruction* in) {
        inst.push_back(in);
        in->setParent(this);
    }
    void pushSucc(BasicBlock*);
    void pushPred(BasicBlock*);
    int get_len(){
        return inst.size();
    }
    int find_lhs(operand&);
    //    list <instruction*>::iterator remove_instruction(  list<instruction*>::iterator );
    //
};

#endif
