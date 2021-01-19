//
// Created by 1 on 13/11/2020.
//

#include "early.h"

#include <iostream>

using namespace std;
bool earley::parse(lexical_analyzer( la))
{

    // сначала добавляем в нулевое состояние все ситуации, где в правиле тоит начальный
    // нетерминал грамматики
    states_.push_back( state() );

    // проходим по правилам грамматики
    for( unsigned int _rule_index = 0; _rule_index < gr_.rules_.size(); ++ _rule_index )
    {
        // и добавляем в нулевое состояние ситуации с правилами,
        // в которых нетерминал слева - это начальный нетерминал грамматики
        if( gr_.start_nonterminal_index_ == gr_.rules_[ _rule_index ].left_nonterminal_ )
        {
            states_[ 0 ].items_.push_back( item( _rule_index, 0, 0 ) );
        }
    }

    // запускаем последовательно Predictor и Completer на нулевом состоянии
    for( unsigned int _item_index = 0; _item_index < states_[ 0 ].items_.size(); ++ _item_index )
    {
        // если в текущей ситуации точка в конце правой части, то вызываем Completer
        if( states_[ 0 ].items_[ _item_index ].dot_pos_ == gr_.rules_[ states_[ 0 ].items_[ _item_index ].rule_index_ ].right_part_.size() )
        {
            completer( 0, _item_index );
        }
            // если символ после точки - это нетерминал, то вызываем Predictor
        else if( ! gr_.symbols_[ gr_.rules_[ states_[ 0 ].items_[ _item_index ].rule_index_ ].right_part_[ states_[ 0 ].items_[ _item_index ].dot_pos_ ] ].is_terminal_ )
        {
            predictor( 0, gr_.rules_[ states_[ 0 ].items_[ _item_index ].rule_index_ ].right_part_[ states_[ 0 ].items_[ _item_index ].dot_pos_ ] );
        }
    }

    // теперь для каждого состояния сначала инициализируем его вызовом scanner
    // а затем дополняем вызовами predictor и completer
    unsigned int _state_index = 1;
    do
    {
        if( scanner( _state_index - 1, la) )
        {
            // запускаем последовательно Predictor и Completer на нулевом состоянии
            unsigned int _item_index = 0;
            for( ; _item_index < states_[ _state_index ].items_.size(); ++ _item_index )
            {
                // если в текущей ситуации точка в конце правой части, то вызываем Completer
                if( states_[ _state_index ].items_[ _item_index ].dot_pos_ == gr_.rules_[ states_[ _state_index ].items_[ _item_index ].rule_index_ ].right_part_.size() )
                {
                    completer( _state_index, _item_index );
                }
                    // если символ после точки - это нетерминал, то вызываем Predictor
                else if( ! gr_.symbols_[ gr_.rules_[ states_[ _state_index ].items_[ _item_index ].rule_index_ ].right_part_[ states_[ _state_index ].items_[ _item_index ].dot_pos_ ] ].is_terminal_ )
                {
                    predictor( _state_index, gr_.rules_[ states_[ _state_index ].items_[ _item_index ].rule_index_ ].right_part_[ states_[ _state_index ].items_[ _item_index ].dot_pos_ ] );
                }
            }

            // если scanner не добавил ни одной ситуации в текущее состояние
            if( _item_index == 0 ) return false;
        }
        else break;

    } while( _state_index ++ < states_.size() );

    // проверяем вывелась ли текущая строка в данной грамматике или нет
    for( unsigned int _item_index = 0; _item_index < states_[ _state_index - 1 ].items_.size(); ++ _item_index )
    {
        item& _cur_item = states_[ _state_index - 1 ].items_[ _item_index ];

        // если в текущей ситуации точка в конце правой части и origin равен нулю
        if( _cur_item.dot_pos_ == gr_.rules_[ _cur_item.rule_index_ ].right_part_.size() && _cur_item.origin_ == 0 )
        {
            // если символ в левой части правила - это начальные нетерминал грамматики
            if( gr_.rules_[ _cur_item.rule_index_ ].left_nonterminal_ == gr_.start_nonterminal_index_ )
            {
                return true;
            }
        }
    }

    return false;
}

// параметр _state_num - номер состояния, которое необходимо обработать, чтобы добавить
// ситуации в следующее состояние _state_num + 1
bool earley::scanner( unsigned int _state_num, lexical_analyzer la )
{
    // читаем следующий символ во входной строке
    // если это конец строки, то не добавляем ни одной ситуации в следующее состояние
    std::string _next_symbol = lex_.get_next();
    position++;
    //cout<<_next_symbol<<endl;
    if( "EOF" == _next_symbol ) return false;

    // индекс следующего символа
    unsigned int _next_symbol_index = gr_.name2index_[ _next_symbol ];

    // новое состояние
    states_.push_back( state() );

    // проходим по ситуациям в состоянии под номером _state_num
    items_t::iterator it = states_[ _state_num ].items_.begin(), end = states_[ _state_num ].items_.end();
    int r = 0;
    for( ; it != end; ++ it )
    {
        // если точка не последняя в правой части правила

        if( gr_.rules_[ (*it).rule_index_ ].right_part_.size() > (*it).dot_pos_ )
        {
            // если символ после точки совпадает с текущим символом входной строки

            if( gr_.rules_[ (*it).rule_index_ ].right_part_[ (*it).dot_pos_ ] == _next_symbol_index )
            {  r++;
                // добавляем эту ситуацию в следующее состояние, предварительно передвинув
                // точку в правой части правила на символ правее
                states_[ _state_num + 1 ].items_.push_back( item( (*it).rule_index_, (*it).dot_pos_ + 1, (*it).origin_ ) );
            }

        }

    }
//    if (r == 0) {
//        cout<<"ожидалась другая лексема на месте "<<la.table[position-1][1]<<" в строке "<<la.table[position-1][2]<<endl;
//    }

    return true;
}

// параметр _state_num - номер теущего состояния
// параметр _symbol - нетерминал, для которого мы будем добавлять ситуации в текущее состояние.
// если _symbol - индекс нетерминала A, то добавим в текущее состояние все ситуации вида [A --> * alpha, _state_num]
// для каждого правила A --> alpha грамматики
void earley::predictor( unsigned int _state_num, unsigned int _symbol )
{
    // проходим по правилам грамматики
    for( unsigned int _rule_index = 0; _rule_index < gr_.rules_.size(); ++ _rule_index )
    {
        // если символ в левой части правила равен переданному как параметр, то добавляем ситуацию в текущее состояние
        if( gr_.rules_[ _rule_index ].left_nonterminal_ == _symbol )
        {
            // сначала проверим, что такой ситуации еще нет в данном состоянии
            bool _rule_is_in_state = false;
            items_t::iterator it = states_[ _state_num ].items_.begin(), end = states_[ _state_num ].items_.end();
            for( ; it != end; ++ it )
            {
                if( (*it).rule_index_ == _rule_index && (*it).dot_pos_ == 0 && (*it).origin_ == _state_num )
                {
                    _rule_is_in_state = true;
                    break;
                }
            }

            // если такой ситуации нет в данном состоянии, то добавляем ее
            if( ! _rule_is_in_state ) states_[ _state_num ].items_.push_back( item( _rule_index, 0, _state_num ) );
        }
    }
}

// параметр _state_num - номер текущего состояния
// параметр _item_index - номер ситуации вида [A --> alpha *, i]. Мы должны пойти в состояние номер i
// и нацти там все ситуации, где символ после точки равен символу A и добавить их в текущее состояние
// предварительно сдвинув точку в правой части правила на символ правее
void earley::completer( unsigned int _state_num, unsigned int _item_index )
{
    // мы имеем ситуацию вида [A --> alpha *, i]
    // проходим по все ситуациям в состоянии под номером i
    items_t::iterator it = states_[ states_[ _state_num ].items_[ _item_index ].origin_ ].items_.begin(),
            end = states_[ states_[ _state_num ].items_[ _item_index ].origin_ ].items_.end();
    for( ; it != end; ++ it )
    {
        // если точка не последняя в правой части правила
        if( gr_.rules_[ (*it).rule_index_ ].right_part_.size() > (*it).dot_pos_ )
        {
            // если символ после точки равен символу в евой части правила нашей ситуации
            // то добавляем эту ситуацию в текущее состоянии, сдвинув точку на символ правее
            if( gr_.rules_[ (*it).rule_index_ ].right_part_[ (*it).dot_pos_ ] == gr_.rules_[ states_[ _state_num ].items_[ _item_index ].rule_index_ ].left_nonterminal_ )
            {
                // сначала проверим, что такой ситуации еще нет в текущем состоянии
                bool _rule_is_in_state = false;
                items_t::iterator it_cur = states_[ _state_num ].items_.begin(), end_cur = states_[ _state_num ].items_.end();
                for( ; it_cur != end_cur; ++ it_cur )
                {
                    if( (*it_cur).rule_index_ == (*it).rule_index_
                        && (*it_cur).dot_pos_ == (*it).dot_pos_
                        && (*it_cur).origin_ == (*it).origin_ )
                    {
                        _rule_is_in_state = true;
                        break;
                    }
                }

                // если такой ситуации нет в данном состоянии, то добавляем ее
                if( ! _rule_is_in_state ) states_[ _state_num ].items_.push_back( item( (*it).rule_index_, (*it).dot_pos_ + 1, (*it).origin_ ) );
            }
        }
    }
}

void earley::error_print() {
    states_t::iterator it = states_.begin(), end = states_.end();

    int count = 0;

    for( ; it != end; ++ it )
    {
        count++;
    }

    it = states_.begin();
    end = states_.end();

    int n = 1;
    for( ; it != end; ++ it, n++ )
    {
        if (n == count - 1 ) {
            items_t::iterator it_item = (*it).items_.begin(), end_item = (*it).items_.end();
            for( ; it_item != end_item; ++ it_item )
            {
                unsigned int _rp_index = 0;
                for( ; _rp_index < gr_.rules_[ (*it_item).rule_index_ ].right_part_.size(); ++ _rp_index )
                {
                    if( _rp_index == (*it_item).dot_pos_ ) {
                        if (gr_.symbols_[ gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].is_terminal_ == true) {
                            std::cout<<"ожидался "<< gr_.symbols_[ gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].name_<<"в правиле"<<gr_.rules_[ (*it_item).rule_index_ ].rule_name_<<endl;
                        }

                    }
                }

            }
        }

    }
}


void earley::print()
{
    /*auto it1 = gr_.rules_.begin(), end1 = gr_.rules_.end();
    for(int i = 0 ; it1 != end1; ++ it1, i++ )
    {
        std::cout << "\n" << i << gr_.symbols_[it1->left_nonterminal_].name_ << " -> ";
        unsigned int _rp_ind = 0;
        for( ; _rp_ind < (*it1).right_part_.size(); ++ _rp_ind ) std::cout << gr_.symbols_[it1->right_part_[_rp_ind]].name_;
        }
*/

    states_t::iterator it = states_.begin(), end = states_.end();

    for(int i = 0 ; it != end; ++ it, i++ )
    {
        std::cout << i << " ------------------------------------------------\n";
        items_t::iterator it_item = (*it).items_.begin(), end_item = (*it).items_.end();
        for( ; it_item != end_item; ++ it_item )
        {

            std::cout << "[" << gr_.symbols_[ gr_.rules_[ (*it_item).rule_index_ ].left_nonterminal_ ].name_ << "-->";
            unsigned int _rp_index = 0;
            for( ; _rp_index < gr_.rules_[ (*it_item).rule_index_ ].right_part_.size(); ++ _rp_index )
            {
                if( _rp_index == (*it_item).dot_pos_ ) {std::cout << "*";
                   std::cout << gr_.symbols_[ gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].name_;
                }
                std::cout << gr_.symbols_[ gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].name_;
            }

            if( _rp_index == (*it_item).dot_pos_ ) std::cout << "*";
            std::cout << ", " << (*it_item).origin_ << "]" << (*it_item).rule_index_;
            if ((*it_item).dot_pos_ == gr_.rules_[ (*it_item).rule_index_ ].right_part_.size()) std::cout << ") last";
            std::cout <<"\n";
        }
        //std::cout << "--------------------------------------------------------\n";
    }
}


