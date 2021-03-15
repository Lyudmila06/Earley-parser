//
// Created by Lyudmila on 17.12.2020.
//

#include "parse_tree.h"

void parse_tree::printRules(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "\n" << vec[i] << ") " << erl->gr_.symbols_[ erl->gr_.rules_[vec[i]].left_nonterminal_ ].name_ << " -> ";
        for(unsigned int _rp_index = 0; _rp_index < erl->gr_.rules_[vec[i]].right_part_.size(); ++ _rp_index ) {
            std::cout << erl->gr_.symbols_[ erl->gr_.rules_[vec[i]].right_part_[ _rp_index ] ].name_;
        }
    }
}



void parse_tree::printSituation(items_t::iterator it_item) { //просто печатает выбранную ситуацию
        std::cout << "[" << erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].left_nonterminal_ ].name_ << "-->";
        unsigned int _rp_index = 0;
        for( ; _rp_index < erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_.size(); ++ _rp_index )
        {
            if( _rp_index == (*it_item).dot_pos_ ) {std::cout << "*";
                std::cout << erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].name_;
            }
            std::cout << erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_[ _rp_index ] ].name_;
        }

        if( _rp_index == (*it_item).dot_pos_ ) std::cout << "*";
        std::cout << ", " << (*it_item).origin_ << "]" << (*it_item).rule_index_;
        if ((*it_item).dot_pos_ == erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_.size()) std::cout << ") last";
        std::cout <<"\n";
}


void parse_tree::parse_run(earley& erl) {
    this->erl = &erl;
    states_t::iterator it = erl.states_.begin(), end = erl.states_.end();

    //поиск в In ситуации [S->a*, 0]
    unsigned int _rp_index = 0;
    int n = erl.states_.size() - 1;
    it += n ;
    cout << n << "\n";
    items_t::iterator it_item = (*it).items_.begin(), end_item = (*it).items_.end();
    for (; it_item != end_item; ++it_item) {
        unsigned int _rp_index = 0;
//        cout << erl.gr_.rules_[ (*it_item).rule_index_ ].right_part_.size() - 1;
//         cout << erl.gr_.symbols_[ erl.gr_.rules_[ (*it_item).rule_index_ ].right_part_[ it_item->dot_pos_ ] ].name_ << "\n";
//        cout << (*it_item).dot_pos_ << " " << erl.gr_.rules_[ (*it_item).rule_index_ ].right_part_.size() << "\n";
        if ((*it_item).dot_pos_ == erl.gr_.rules_[ (*it_item).rule_index_ ].right_part_.size() && (*it_item).origin_ == 0){ // если ситуация вида [S -> a*, 0]
            cout << "\n Get situation";
            printSituation(it_item);
            R(it_item, n);
            break;
        }
    }
    print_pi();

}


bool parse_tree::isR(symbol x, unsigned int r){
    states_t::iterator it = erl->states_.begin();
    //cout << " r: " << r << " \n";
    it += r;
    items_t::iterator it_item = (*it).items_.begin(), end_item = (*it).items_.end();
    for(int i = 0 ; it_item != end_item; ++ it_item, i++ ) {
        if (erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_[ it_item->dot_pos_ ] ].name_ == x.name_)
            //вывод для проверки какой символ записан перед * и после *
            //cout << " before dot:" << erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_[ it_item->dot_pos_ - 1 ] ].name_
            //<< "   after dot:" << erl->gr_.symbols_[ erl->gr_.rules_[ (*it_item).rule_index_ ].right_part_[ it_item->dot_pos_ ] ].name_ << "\n";
            //cout << i;
            return true;
    }
    return false;
}

void parse_tree::R(items_t::iterator& a, int j){
    pi_.push_back((*a).rule_index_); //1)
    //print_pi();
    //cout << "pi_: " << (*a).rule_index_ << "\n";
    //2)
    int k = erl->gr_.rules_[ (*a).rule_index_ ].right_part_.size();
    int c = j;
    //cout << "k:" << k << "; c:" << c << ";\n" ;
    while (k != 0) {
        xk = erl->gr_.symbols_[erl->gr_.rules_[(*a).rule_index_].right_part_[k-1]];
        //cout << "xk: " << xk.name_ << " (term:" << xk.is_terminal_ << ")\n";
        if (xk.is_terminal_) { //3а)
            k--;
            c--;
            //cout << "k-- , c-- \n";
        }
        if (!xk.is_terminal_) { //3б)
            states_t::iterator it = erl->states_.begin();
            it += c;
            symbol x;
            unsigned int r;
            items_t::iterator it_item = (*it).items_.begin(), end_item = (*it).items_.end();
            for (; it_item != end_item; ++it_item) {
                x = erl->gr_.symbols_[erl->gr_.rules_[(*it_item).rule_index_].left_nonterminal_];
                //cout <<  " Start 3b)  Xk:" << xk.name_ << "   A:" << x.name_
                //<< "   dot:" << it_item->dot_pos_ << "   end:" << erl->gr_.rules_[ it_item->rule_index_ ].right_part_.size() << "\n";
                if (x.name_ == xk.name_ && it_item->dot_pos_ == erl->gr_.rules_[ it_item->rule_index_ ].right_part_.size()) {
                    r = (*it_item).origin_;
                    //3б) "...где некоторый r таков..."
                    if (isR(x, r)) {
                        //cout << "R(" << erl->gr_.symbols_[erl->gr_.rules_[(*it_item).rule_index_].left_nonterminal_].name_ << "->" << erl->gr_.symbols_[erl->gr_.rules_[(*it_item).rule_index_].right_part_[0]].name_ << "...," << c << ")\n";
                        R(it_item, c);
                        k--;
                        c = r;
                        //cout << "k:" << k << "; c:" << c << ";\n" ;
                        break;
                    }
                }

            }


        }
    }
}

void parse_tree::print_pi() {
    //for (int i : pi_) cout << i;
    cout << "\n Pi = ";
    for (int i = 0; i < pi_.size(); i++) cout << pi_[i] << "_";
}



