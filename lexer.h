//
// Created by 1 on 13/11/2020.
//

#ifndef EARLY_LEXER_H
#define EARLY_LEXER_H

#include <string>
#include <vector>

typedef std::vector< std::string > input_t;

class lexer{
    input_t input_;
    int pos_;

public:
    lexer():pos_(0){}

    void add_to_input( const std::string& _str ) { input_.push_back( _str ); }
    std::string get_next()
    {
        if( pos_ < input_.size() )
        {
            return input_[ pos_ ++ ];
        }

        return "EOF";
    }
};

#endif //EARLY_LEXER_H
