#ifndef EARLY_SEMANTIC_ANALYZER_H
#define EARLY_SEMANTIC_ANALYZER_H
#include "early.h"
#include "gramma.h"
#include "lexer.h"
#include "lexical.h"
#include "parse_tree.h"

class semantic_analyzer {
    public:
        vector<int> tree;
        earley *earl;


    semantic_analyzer(vector<int> pi_, earley *earl)
    {
        this->tree = pi_;
        this->earl = earl;
    }

    void semantic_run();
    void analyze_vars();
    void analyze_expr();
    void analyze_keywords();

};


#endif //EARLY_SEMANTIC_ANALYZER_H
