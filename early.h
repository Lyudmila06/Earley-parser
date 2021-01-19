//
// Created by 1 on 13/11/2020.
//

#ifndef EARLY_EARLY_H
#define EARLY_EARLY_H

#include "gramma.h"
#include "lexer.h"
#include "lexical.h"

struct item{
    unsigned int    rule_index_;
    unsigned int    dot_pos_;
    unsigned int    origin_;

    item(){}
    item( unsigned int _rule_index, unsigned int _dot_pos, unsigned int _origin )
            :
            rule_index_(_rule_index),
            dot_pos_(_dot_pos),
            origin_(_origin)
    {}
};

typedef std::vector< item > items_t;

struct state{
    items_t        items_;
};

typedef std::vector< state > states_t;

class earley{
public:
    grammar&    gr_;
    lexer&        lex_;

    states_t    states_;

    earley( grammar& _gr, lexer& _lex )
            :
            gr_(_gr),
            lex_(_lex)
    {}

    bool parse(lexical_analyzer la);

    void print();
    void error_print();
    int position = 0;

private:
    bool scanner( unsigned int _state_num, lexical_analyzer la);
    void predictor( unsigned int _state_num, unsigned int _symbol );
    void completer( unsigned int _state_num, unsigned int _item_index );
};

#endif //EARLY_EARLY_H
