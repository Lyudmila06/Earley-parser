#ifndef EARLY_GENERATOR_H
#define EARLY_GENERATOR_H
#include "early.h"
#include "gramma.h"
#include "lexer.h"
#include "lexical.h"
#include "parse_tree.h"
#include <vector>

class generator {
public:
    lexer lex_;
    lexical_analyzer la;
    map <string, string> gen_rule;
    vector<vector<string>> result_table;

    generator(lexical_analyzer la);

    void generator_run();

    void print_result();

    void print_java_script();

};


#endif //EARLY_GENERATOR_H
