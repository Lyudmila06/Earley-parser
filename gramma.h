//
// Created by 1 on 13/11/2020.
//

#ifndef EARLY_GRAMMA_H
#define EARLY_GRAMMA_H

#include <vector>
#include <map>
#include <string>

struct symbol{
    std::string name_;
    bool is_terminal_;

    symbol(){}
    symbol( const std::string& _name, bool _is_terminal )
            :
            name_(_name),
            is_terminal_(_is_terminal)
    {}
};

typedef std::vector< symbol > symbols_t;
typedef std::map< std::string, unsigned int > name2index_t;
typedef std::map< unsigned int, std::string > index2name_t;

typedef std::vector< unsigned int > indexes_t;

struct rule{
    std::string rule_name_;
    unsigned int left_nonterminal_;
    indexes_t  right_part_;

    rule(){}
    rule( const std::string& _rule_name )
            :
            rule_name_(_rule_name)
    {}
};

typedef std::vector< rule > rules_t;

class grammar{
public:
    unsigned int start_nonterminal_index_;

    symbols_t symbols_;
    name2index_t name2index_;
    index2name_t index2name_;

    rules_t rules_;


    unsigned int add_symbol( const std::string& _name, bool _is_terminal, bool _is_start = false )
    {
        unsigned int _cur_index = symbols_.size();
        symbols_.push_back( symbol( _name, _is_terminal ) );

        if( _is_start ) start_nonterminal_index_ = _cur_index;

        name2index_[ _name ] = _cur_index;
        index2name_[ _cur_index ] = _name;

        return _cur_index;
    }

    unsigned int add_rule( const std::string& _name )
    {
        unsigned int _cur_index = rules_.size();
        rules_.push_back( rule( _name ) );

        return _cur_index;
    }

    void add_left_nonterminal_to_rule( unsigned int _rule_index, const std::string& _nonterminal_name )
    {
        rules_[ _rule_index ].left_nonterminal_ = name2index_[ _nonterminal_name ];
    }

    void add_symbol_to_right_part_of_rule( unsigned int _rule_index, const std::string& _symbol_name )
    {
        rules_[ _rule_index ].right_part_.push_back( name2index_[ _symbol_name ] );
    }

    friend class earley;

};


#endif //EARLY_GRAMMA_H
