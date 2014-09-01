#ifndef BASICBLOCK_H
#define BASICBLOCK_H
#include <list>
#include "irclass.h"
#include "bitbool.h"
using namespace std;
class BasicBlock{
    list<instruction*> inst;
    list<BasicBlock*> pred;
    list<BasicBlock*> succ;
    bitvec in,out,gen,kill;
    string BBLabel;
    public:
    list <instruction*>::iterator get_begin_inst();
    list <instruction*>::iterator get_end_inst();
    list <instruction*>::reverse_iterator get_rbegin_inst(){
        return inst.rbegin();
    }
    list <instruction*>::reverse_iterator get_rend_inst(){
        return inst.rend();
    }

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
    bool isAlreadyKilled(int start,int end){
        for(int i = start; i <= end; ++i){
            if(kill[i] == 1)
                return false;
        }
        return true;
    }
    void setGen(int i,int start,int end){
        gen[i] = 1;
        for(int i = start; i <= end; ++i){
            kill[i] = 1;
        }   
    }
void setIn(bitvec& bv){
       in = bv;  
    }
void setOut(bitvec& bv){
       out = bv;  
    }


    bitvec getGen(){
       return gen;
    }
   bitvec getKill(){
      return kill;
   } 
   bitvec getIn(){
       return in;
    }
   bitvec getOut(){
      return out;
   } 

    void bitResize(int size){
        in.resize(size);
        out.resize(size);
        gen.resize(size);
        kill.resize(size);
   }
    void initBitToZero(int size){
        for(int i = 0; i < size; ++i){
            in[i] = 0;
            out[i] =0;
            gen[i] = 0;
            kill[i] =0;
        }
    }
};

#endif
