#ifndef BITVEC_H
#define BITVEC_H
    #include <iostream>
    #define BITS 8

    using namespace std;
    class bitvec{

            int blocks;
            int index;
            bool *bb;
            int cindex; //for iterator
        public:
            bitvec();
            bitvec(int);
            bitvec(const bitvec &);
            ~bitvec();
            void push_bit(bool);
            void resize(int);
            void show_bit();
            void set_bit(int);
            void clear_bit(int);
            bool query_bit(int);
            bitvec operator&(const bitvec&);
            bitvec operator|(const bitvec&);
            bitvec operator^(const bitvec&);
            bitvec& operator=(const bitvec&);
            bool& operator[](int);
            //for iterator
            bool getbegin();
            bool getend();
            int itbegin();
            int itend();
            bool next();
            bool previous();
            void setit(int);
            int getSize(){
                return blocks;
            }
    };
#endif
