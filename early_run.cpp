//
// Created by 1 on 14/11/2020.
//

#include "early_run.h"


void early_run(lexical_analyzer la) {

    grammar gr;

    gr.add_symbol( "Func", false, true );
    gr.add_symbol( "Pr", false, false );
    gr.add_symbol( "ReturnSt", false, false );
    gr.add_symbol( "ExprAssign", false, false );
    gr.add_symbol( "Loop", false, false );
    gr.add_symbol( "CondOp", false, false );
    gr.add_symbol( "Integer", false, false );
    gr.add_symbol( "Real", false, false );
    gr.add_symbol( "Id", false, false );
    gr.add_symbol( "IdSymb", false, false );
    gr.add_symbol( "LogConst", false, false );
    gr.add_symbol( "TypeId", false, false );
    gr.add_symbol( "LogOp", false, false );
    gr.add_symbol( "ComplxOp", false, false );
    gr.add_symbol( "VarVal", false, false );
    gr.add_symbol( "ArOprnd", false, false );
    gr.add_symbol( "Num", false, false );
    gr.add_symbol( "Arg", false, false );
    gr.add_symbol( "Expr", false, false );
    gr.add_symbol( "ReturnSt", false, false );
    gr.add_symbol( "Compar", false, false );
    gr.add_symbol( "Cond", false, false );
    gr.add_symbol( "ComplxOpConstr", false, false );
    gr.add_symbol( "VarDec", false, false );
    gr.add_symbol( "E1", false, false );
    gr.add_symbol( "T1", false, false );
    gr.add_symbol( "F1", false, false );
    gr.add_symbol( "CompOp", false, false );
    gr.add_symbol( "LoopOpPost", false, false );
    gr.add_symbol( "LoopOpPrec", false, false );
    gr.add_symbol( "LoopOpStep", false, false );

    //терминалы
    gr.add_symbol( "operator 1 poriadka", true );
    gr.add_symbol( "operator 2 poriadka", true );
    gr.add_symbol( "operator sravnenia", true );
    gr.add_symbol( "logicheskiy operator", true );
    gr.add_symbol( "operator =", true );
    gr.add_symbol( "separator ;", true );
    gr.add_symbol( "separator {", true );
    gr.add_symbol( "separator }", true );
    gr.add_symbol( "separator (", true );
    gr.add_symbol( "separator )", true );
    gr.add_symbol( "separator ,", true );
    gr.add_symbol( "if", true );
    gr.add_symbol( "while", true );
    gr.add_symbol( "for", true );
    gr.add_symbol( "else", true );
    gr.add_symbol( "type of data", true );
    gr.add_symbol( "logicheskia const", true );
    gr.add_symbol( "digit", true );
    gr.add_symbol( "symbol", true );
    gr.add_symbol( "identifier", true );
    gr.add_symbol( "!", true );
    gr.add_symbol( "return", true );



    //нетерминалы


    //терминалы

    //gr.add_symbol( "!", true );



    //правила

    unsigned int Func_1 = gr.add_rule( "Func --> TypeId main ( Arg ) { Pr }" );
    gr.add_left_nonterminal_to_rule( Func_1, "Func" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "type of data" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "identifier" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "separator (" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "Arg" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "separator )" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "separator {" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Func_1, "separator }" );

    unsigned int Func_2 = gr.add_rule( "Func --> TypeId main ( ) { Pr }" );
    gr.add_left_nonterminal_to_rule(Func_2, "Func" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "type of data" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "identifier" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "separator (" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "separator )" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "separator {" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Func_2, "separator }" );

    unsigned int Arg_1 = gr.add_rule( "Arg --> TypeId Id" );
    gr.add_left_nonterminal_to_rule(Arg_1, "Arg" );
    gr.add_symbol_to_right_part_of_rule( Arg_1, "type of data" );
    gr.add_symbol_to_right_part_of_rule( Arg_1, "identifier" );

    unsigned int Arg_2 = gr.add_rule( "Arg --> TypeId Id , Arg" );
    gr.add_left_nonterminal_to_rule( Arg_2, "Arg" );
    gr.add_symbol_to_right_part_of_rule( Arg_2, "type of data" );
    gr.add_symbol_to_right_part_of_rule( Arg_2, "identifier" );
    gr.add_symbol_to_right_part_of_rule( Arg_2, "separator ," );
    gr.add_symbol_to_right_part_of_rule( Arg_2, "Arg" );

    unsigned int Pr_1 = gr.add_rule( "Pr --> ExprAssign ; Pr" );
    gr.add_left_nonterminal_to_rule(Pr_1, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_1, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( Pr_1, "separator ;" );
    gr.add_symbol_to_right_part_of_rule( Pr_1, "Pr" );

    unsigned int Pr_2 = gr.add_rule( "Pr --> Loop Pr" );
    gr.add_left_nonterminal_to_rule(Pr_2, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_2, "Loop" );
    gr.add_symbol_to_right_part_of_rule( Pr_2, "Pr" );


    unsigned int Pr_3 = gr.add_rule( "Pr --> CondOp Pr" );
    gr.add_left_nonterminal_to_rule(Pr_3, "Pr" );
    gr.add_symbol_to_right_part_of_rule(Pr_3, "CondOp" );
    gr.add_symbol_to_right_part_of_rule(Pr_3, "Pr" );

    unsigned int Pr_4 = gr.add_rule( "Pr --> VarDec Pr" );
    gr.add_left_nonterminal_to_rule( Pr_4, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_4, "VarDec" );
    gr.add_symbol_to_right_part_of_rule( Pr_4, "Pr" );

    unsigned int Pr_5 = gr.add_rule( "Pr --> ReturnSt ;" );
    gr.add_left_nonterminal_to_rule(Pr_5, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_5, "ReturnSt" );
    gr.add_symbol_to_right_part_of_rule( Pr_5, "separator ;" );

    unsigned int Pr_6 = gr.add_rule( "Pr --> ExprAssign" );
    gr.add_left_nonterminal_to_rule( Pr_6, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_6, "ExprAssign" );


    unsigned int Pr_7 = gr.add_rule( "Pr --> Loop" );
    gr.add_left_nonterminal_to_rule(Pr_7, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_7, "Loop" );            //10

    unsigned int Pr_8 = gr.add_rule( "Pr --> CondOp" );
    gr.add_left_nonterminal_to_rule(Pr_8, "Pr" );
    gr.add_symbol_to_right_part_of_rule( Pr_8, "CondOp" );

    //part2

    unsigned int VarDec_1 = gr.add_rule( "VarDec --> TypeId  Id ;" );
    gr.add_left_nonterminal_to_rule( VarDec_1, "VarDec" );
    gr.add_symbol_to_right_part_of_rule( VarDec_1, "type of data" );
    gr.add_symbol_to_right_part_of_rule( VarDec_1, "identifier" );
    gr.add_symbol_to_right_part_of_rule(VarDec_1, "separator ;" );

    unsigned int VarDec_2 = gr.add_rule( "VarDec --> TypeId  ExprAssign ;" );
    gr.add_left_nonterminal_to_rule(VarDec_2, "VarDec" );
    gr.add_symbol_to_right_part_of_rule( VarDec_2, "type of data" );
    gr.add_symbol_to_right_part_of_rule( VarDec_2, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( VarDec_2, "separator ;" );

    //

    unsigned int VarVal_1 = gr.add_rule( "VarVal --> Integer" );
    gr.add_left_nonterminal_to_rule(VarVal_1, "VarVal" );
    gr.add_symbol_to_right_part_of_rule(VarVal_1, "digit" );


    unsigned int VarVal_3 = gr.add_rule( "VarVal --> LogConst" );
    gr.add_left_nonterminal_to_rule(VarVal_3, "VarVal" );
    gr.add_symbol_to_right_part_of_rule( VarVal_3, "logicheskia const" );

    unsigned int VarVal_4 = gr.add_rule( "VarVal --> Symbol" );
    gr.add_left_nonterminal_to_rule( VarVal_4, "VarVal" );
    gr.add_symbol_to_right_part_of_rule( VarVal_4, "symbol" );




    unsigned int ExprAssign_1 = gr.add_rule( "ExprAssign --> Id = Expr" );
    gr.add_left_nonterminal_to_rule(ExprAssign_1, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_1, "identifier" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_1, "operator =" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_1, "Expr" );


    unsigned int ExprAssign_2 = gr.add_rule( "ExprAssign --> Id = E1" );
    gr.add_left_nonterminal_to_rule(ExprAssign_2, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_2, "identifier" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_2, "operator =" );
    gr.add_symbol_to_right_part_of_rule( ExprAssign_2, "E1" );

    unsigned int E_1 = gr.add_rule( "E1 --> T1 Op2Prior E1" );
    gr.add_left_nonterminal_to_rule(E_1, "E1" );
    gr.add_symbol_to_right_part_of_rule( E_1, "T1" );
    gr.add_symbol_to_right_part_of_rule( E_1, "operator 2 poriadka" );
    gr.add_symbol_to_right_part_of_rule( E_1, "E1" );

    unsigned int E_2 = gr.add_rule( "E1 --> T1" );
    gr.add_left_nonterminal_to_rule( E_2, "E1" );
    gr.add_symbol_to_right_part_of_rule( E_2, "T1" );           //20

    unsigned int T_1 = gr.add_rule( "T1 --> T1 Op1Prior F1" );
    gr.add_left_nonterminal_to_rule(T_1, "T1" );
    gr.add_symbol_to_right_part_of_rule( T_1, "T1" );
    gr.add_symbol_to_right_part_of_rule( T_1, "operator 1 poriadka" );
    gr.add_symbol_to_right_part_of_rule( T_1, "F1" );

    unsigned int T_2 = gr.add_rule( "T1 --> F1" );
    gr.add_left_nonterminal_to_rule( T_2, "T1" );
    gr.add_symbol_to_right_part_of_rule( T_2, "F1" );

    unsigned int F_1 = gr.add_rule( "F1 --> ( E1 )" );
    gr.add_left_nonterminal_to_rule(F_1, "F1" );
    gr.add_symbol_to_right_part_of_rule(F_1, "separator (" );
    gr.add_symbol_to_right_part_of_rule(F_1, "E1" );
    gr.add_symbol_to_right_part_of_rule(F_1, "separator (" );

    unsigned int F_2 = gr.add_rule( "F1 --> ArOprnd" );
    gr.add_left_nonterminal_to_rule(F_2, "F1" );
    gr.add_symbol_to_right_part_of_rule( F_2, "ArOprnd" );


    unsigned int ArOprnd_1 = gr.add_rule( "ArOprnd --> Num" );
    gr.add_left_nonterminal_to_rule(ArOprnd_1, "ArOprnd" );
    gr.add_symbol_to_right_part_of_rule( ArOprnd_1, "digit" );

    unsigned int ArOprnd_2 = gr.add_rule( "ArOprnd --> Id" );
    gr.add_left_nonterminal_to_rule(ArOprnd_2, "ArOprnd" );
    gr.add_symbol_to_right_part_of_rule( ArOprnd_2, "identifier" );


    unsigned int Expr_1 = gr.add_rule( "Expr --> Num" );
    gr.add_left_nonterminal_to_rule( Expr_1, "Expr" );
    gr.add_symbol_to_right_part_of_rule( Expr_1, "digit" );


    unsigned int Expr_2 = gr.add_rule( "Expr --> Id" );
    gr.add_left_nonterminal_to_rule(Expr_2, "Expr" );
    gr.add_symbol_to_right_part_of_rule( Expr_2, "identifier" );

    unsigned int Expr_3 = gr.add_rule( "Expr --> LogConst" );
    gr.add_left_nonterminal_to_rule(Expr_3, "Expr" );
    gr.add_symbol_to_right_part_of_rule(Expr_3, "logicheskia const" );


    unsigned int Loop_1 = gr.add_rule( "Loop --> LoopOpPrec" );
    gr.add_left_nonterminal_to_rule(Loop_1, "Loop" );
    gr.add_symbol_to_right_part_of_rule( Loop_1, "LoopOpPrec" );        //30

    //Part3

    unsigned int Loop_2 = gr.add_rule( "Loop --> LoopOpPost" );
    gr.add_left_nonterminal_to_rule(Loop_2, "Loop" );
    gr.add_symbol_to_right_part_of_rule( Loop_2, "LoopOpPost" );

    unsigned int Loop_3 = gr.add_rule( "Loop --> LoopOpStep");
    gr.add_left_nonterminal_to_rule( Loop_3, "Loop" );
    gr.add_symbol_to_right_part_of_rule( Loop_3, "LoopOpStep" );

    unsigned int LoopOpPrec_1 = gr.add_rule( "LoopOpPrec --> while ( Cond ) ComplxOp" );
    gr.add_left_nonterminal_to_rule( LoopOpPrec_1, "LoopOpPrec" );
    gr.add_symbol_to_right_part_of_rule(  LoopOpPrec_1, "while" );
    gr.add_symbol_to_right_part_of_rule(  LoopOpPrec_1, "separator (" );
    gr.add_symbol_to_right_part_of_rule(  LoopOpPrec_1, "Cond" );
    gr.add_symbol_to_right_part_of_rule(  LoopOpPrec_1, "separator )" );
    gr.add_symbol_to_right_part_of_rule(  LoopOpPrec_1, "ComplxOp" );

    unsigned int  LoopOpPost_1 = gr.add_rule( "LoopOpPost --> do ComplxOp while ( Cond )" );
    gr.add_left_nonterminal_to_rule( LoopOpPost_1, "LoopOpPost" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "do" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "ComplxOp" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "while" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "separator (" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "Cond" );
    gr.add_symbol_to_right_part_of_rule( LoopOpPost_1, "separator )" );

    unsigned int LoopOpStep_1 = gr.add_rule( "LoopOpStep --> for ( ExprAssign; Cond; ExprAssign) ComplxOp" );
    gr.add_left_nonterminal_to_rule(LoopOpStep_1, "LoopOpStep" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "for" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "separator (" );
    //gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "data of type" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "separator ;" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "Cond" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "separator ;" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "separator )" );
    gr.add_symbol_to_right_part_of_rule( LoopOpStep_1, "ComplxOp" );

    ///?????
    unsigned int Cond_1 = gr.add_rule( "Cond --> ! LogConst" );
    gr.add_left_nonterminal_to_rule(Cond_1, "Cond" );
    gr.add_symbol_to_right_part_of_rule( Cond_1, "!" );
    gr.add_symbol_to_right_part_of_rule( Cond_1, "logicheskia const" );


    unsigned int Cond_2 = gr.add_rule( "Cond --> LogConst" );
    gr.add_left_nonterminal_to_rule(Cond_2, "Cond" );
    gr.add_symbol_to_right_part_of_rule( Cond_2, "logicheskia const" );

    unsigned int Cond_3 = gr.add_rule( "Cond --> Compar" );
    gr.add_left_nonterminal_to_rule( Cond_3, "Cond" );
    gr.add_symbol_to_right_part_of_rule( Cond_3, "Compar" );

    unsigned int Compar_1 = gr.add_rule( "Compar --> Expr CompOp Expr" );
    gr.add_left_nonterminal_to_rule(Compar_1, "Compar" );
    gr.add_symbol_to_right_part_of_rule( Compar_1, "Expr" );
    gr.add_symbol_to_right_part_of_rule( Compar_1, "CompOp" );
    gr.add_symbol_to_right_part_of_rule( Compar_1, "Expr" );


    unsigned int CompOp_1 = gr.add_rule( "CompOp --> ==" );
    gr.add_left_nonterminal_to_rule( CompOp_1, "CompOp" );
    gr.add_symbol_to_right_part_of_rule( CompOp_1, "operator sravnenia" );      //40

    unsigned int ComplxOp_1 = gr.add_rule( "ComplxOp --> { ComplxOpConstr }" );
    gr.add_left_nonterminal_to_rule( ComplxOp_1, "ComplxOp" );
    gr.add_symbol_to_right_part_of_rule( ComplxOp_1, "separator {" );
    gr.add_symbol_to_right_part_of_rule( ComplxOp_1, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOp_1, "separator }" );


    unsigned int ComplxOpConstr_21 = gr.add_rule( "ComplxOpConstr --> VarDec" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_21, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_21, "VarDec" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_21, "ComplxOpConstr" );

    unsigned int ComplxOpConstr_31 = gr.add_rule( "ComplxOpConstr --> ExprAssign;" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_31, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_31, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_31, "separator ;" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_31, "ComplxOpConstr" );


    unsigned int ComplxOpConstr_41 = gr.add_rule( "ComplxOpConstr --> LoopOpPrec" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_41, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_41, "LoopOpPrec" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_41, "ComplxOpConstr" );

    unsigned int ComplxOpConstr_51 = gr.add_rule( "ComplxOpConstr --> CondOp" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_51, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_51, "CondOp" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_51, "ComplxOpConstr" );

    unsigned int ComplxOpConstr_61 = gr.add_rule( "ComplxOpConstr --> LoopOpStep" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_61, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_61, "LoopOpStep" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_61, "ComplxOpConstr" );

    unsigned int ComplxOpConstr_71 = gr.add_rule( "ComplxOpConstr --> LoopOpPost" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_71, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_71, "LoopOpPost" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_71, "ComplxOpConstr" );

    unsigned int ComplxOpConstr_1 = gr.add_rule( "ComplxOpConstr --> ReturnSt ;" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_1, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule(ComplxOpConstr_1, "ReturnSt" );
    gr.add_symbol_to_right_part_of_rule(ComplxOpConstr_1, "separator ;" );

    unsigned int ComplxOpConstr_2 = gr.add_rule( "ComplxOpConstr --> VarDec" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_2, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_2, "VarDec" );

    unsigned int ComplxOpConstr_3 = gr.add_rule( "ComplxOpConstr --> ExprAssign;" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_3, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_3, "ExprAssign" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_3, "separator ;" );


    unsigned int ComplxOpConstr_4 = gr.add_rule( "ComplxOpConstr --> LoopOpPrec" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_4, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_4, "LoopOpPrec" );

    unsigned int ComplxOpConstr_5 = gr.add_rule( "ComplxOpConstr --> CondOp" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_5, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_5, "CondOp" );

    unsigned int ComplxOpConstr_6 = gr.add_rule( "ComplxOpConstr --> LoopOpStep" );
    gr.add_left_nonterminal_to_rule(ComplxOpConstr_6, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_6, "LoopOpStep" );

    unsigned int ComplxOpConstr_7 = gr.add_rule( "ComplxOpConstr --> LoopOpPost" );
    gr.add_left_nonterminal_to_rule( ComplxOpConstr_7, "ComplxOpConstr" );
    gr.add_symbol_to_right_part_of_rule( ComplxOpConstr_7, "LoopOpPost" );





    /////??????
    unsigned int ReturnSt_1 = gr.add_rule( "ReturnSt --> return Expr" );
    gr.add_left_nonterminal_to_rule(ReturnSt_1, "ReturnSt" );
    gr.add_symbol_to_right_part_of_rule( ReturnSt_1, "return" );
    gr.add_symbol_to_right_part_of_rule( ReturnSt_1, "Expr" );

    unsigned int CondOp_1 = gr.add_rule( "CondOp --> if ( Cond )  ComplxOp else ComplxOp" );
    gr.add_left_nonterminal_to_rule(CondOp_1, "CondOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "if");
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "separator (" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "separator )" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "ComplxOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "else" );
    gr.add_symbol_to_right_part_of_rule( CondOp_1, "ComplxOp" );

    unsigned int CondOp_2 = gr.add_rule( "CondOp --> if ( Cond )  ComplxOp" );
    gr.add_left_nonterminal_to_rule(CondOp_2, "CondOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_2, "if" );
    gr.add_symbol_to_right_part_of_rule( CondOp_2, "separator (" );
    gr.add_symbol_to_right_part_of_rule( CondOp_2, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_2, "separator )" );
    gr.add_symbol_to_right_part_of_rule( CondOp_2, "ComplxOp" );

    unsigned int CondOp_3 = gr.add_rule( "CondOp --> if ( Cond LogOp Cond )  ComplxOp else ComplxOp" );
    gr.add_left_nonterminal_to_rule(CondOp_3, "CinOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "if" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "separator (" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "logicheskiy operator" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "separator )" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "ComplxOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "else" );
    gr.add_symbol_to_right_part_of_rule( CondOp_3, "ComplxOp" );

    unsigned int CondOp_4 = gr.add_rule( "CondOp --> if ( Cond LogOp Cond )  ComplxOp " );
    gr.add_left_nonterminal_to_rule( CondOp_4, "CondOp" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "If" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "separator (" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "logicheskiy operator" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "Cond" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "separator )" );
    gr.add_symbol_to_right_part_of_rule( CondOp_4, "ComplxOp" );


    lexer lex;

    for (int i = 0; i <= la.count; i++){
        lex.add_to_input(la.table[i][3]);
    }

    earley parser( gr, lex );


    if( parser.parse(la) ){
        std::cout << "success\n";
        parser.print();
        parse_tree tree;
        //tree.parse_run(parser);
        //tree.printRules(tree.pi_);
        semantic_analyzer sem(lex);
        sem.analyze_vars(la);


    }
    else {
        //parser.print();
        parser.error_print();

    }
}
