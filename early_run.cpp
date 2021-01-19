//
// Created by 1 on 14/11/2020.
//

#include "early_run.h"


void early_run(lexical_analyzer la) {

    grammar gr;

//нетерминалы
    gr.add_symbol( "S", false, true );
    gr.add_symbol( "B", false, false );
    gr.add_symbol( "A", false, false );

//терминалы

    gr.add_symbol( "a", true );
    gr.add_symbol( "b", true );
    gr.add_symbol( "s", true );

//правила
    unsigned int TypeId_4 = gr.add_rule( "TypeId —> bool" );
    gr.add_left_nonterminal_to_rule(TypeId_4, "S" );
    gr.add_symbol_to_right_part_of_rule(TypeId_4, "B" );
    gr.add_symbol_to_right_part_of_rule(TypeId_4, "a" );
    gr.add_symbol_to_right_part_of_rule(TypeId_4, "A" );

    unsigned int TypeId_5 = gr.add_rule( "TypeId —> double" );
    gr.add_left_nonterminal_to_rule( TypeId_5, "S" );
    gr.add_symbol_to_right_part_of_rule( TypeId_5, "B" );
    gr.add_symbol_to_right_part_of_rule( TypeId_5, "a" );

    unsigned int Arg_1 = gr.add_rule( "Arg —> TypeId Id" );
    gr.add_left_nonterminal_to_rule(Arg_1, "S" );
    gr.add_symbol_to_right_part_of_rule( Arg_1, "a" );
    gr.add_symbol_to_right_part_of_rule( Arg_1, "A" );

    unsigned int Arg_2 = gr.add_rule( "Arg —> TypeId Id , Arg" );
    gr.add_left_nonterminal_to_rule( Arg_2, "S" );
    gr.add_symbol_to_right_part_of_rule( Arg_2, "a" );

    unsigned int TypeId_3 = gr.add_rule( "TypeId —> void" );
    gr.add_left_nonterminal_to_rule(TypeId_3, "A" );
    gr.add_symbol_to_right_part_of_rule( TypeId_3, "b" );
    gr.add_symbol_to_right_part_of_rule( TypeId_3, "s" );
    gr.add_symbol_to_right_part_of_rule( TypeId_3, "s" );


    unsigned int Func_1 = gr.add_rule( "Func —> TypeId main ( Arg ) { Pr }" );
    gr.add_left_nonterminal_to_rule( Func_1, "B" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "B" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "a" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "A" );

    unsigned int Func_2 = gr.add_rule( "Func —> TypeId main ( ) { Pr }" );
    gr.add_left_nonterminal_to_rule(Func_2, "B" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "B" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "a" );


    unsigned int TypeId_1 = gr.add_rule( "TypeId —> int" );
    gr.add_left_nonterminal_to_rule( TypeId_1, "B" );
    gr.add_symbol_to_right_part_of_rule( TypeId_1, "a" );
    gr.add_symbol_to_right_part_of_rule( TypeId_1, "A" );


    unsigned int TypeId_2 = gr.add_rule( "TypeId —> char" );
    gr.add_left_nonterminal_to_rule(TypeId_2, "B" );
    gr.add_symbol_to_right_part_of_rule(TypeId_2, "a" );


    lexer lex;

/*for (int i = 0; i <= la.count; i++){
lex.add_to_input(la.table[i][1]);
}*/

    lex.add_to_input("a");
    lex.add_to_input("a");
    lex.add_to_input("b");
    lex.add_to_input("s");
    lex.add_to_input("s");

    earley parser( gr, lex );


    if( parser.parse(la) ){
        std::cout << "success\n";
        parser.print();
        parse_tree tree;
        tree.parse_run(parser);
    }
    else {
        //parser.print();
        parser.error_print();

    }
}
