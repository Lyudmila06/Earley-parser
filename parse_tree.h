//
// Created by Lyudmila on 17.12.2020.
//

#ifndef EARLY_PARSE_TREE_H
#define EARLY_PARSE_TREE_H
#include "early.h"
#include "gramma.h"
#include "lexer.h"
#include "lexical.h"

class parse_tree {
public:

    vector<int> pi_;
    earley *erl;
    symbol xk;

    void parse_run(earley& erl);
    void R(items_t::iterator& a, int i);
    bool isR(symbol x, unsigned int r);
    void print_pi();
    void printSituation(items_t::iterator it_item);
    void printRules(vector<int> num);

};


#endif //EARLY_PARSE_TREE_H
