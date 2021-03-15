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
        lexer lex_;
        string vars[1000][2];
        string undef_vars[1000];
        int count_vars = 0;

    semantic_analyzer(lexer& _lex)
    {
        //this->tree = pi_;
        //this->earl = earl;
        this->lex_ = _lex;
    }

    void semantic_run();
    void analyze_vars(lexical_analyzer la);
    void analyze_expr();
    void analyze_keywords();

};


#endif //EARLY_SEMANTIC_ANALYZER_H
