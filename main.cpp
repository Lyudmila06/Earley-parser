#include <iostream>
#include <string>
#include <iomanip>
#include "lexical.h"
#include "early_run.h"




int main()
{
    lexical_analyzer la;
    la.lexicalAnalyze("../example");
    for (int i = 0; i <= la.count; i++){
        for (int j = 0; j < la.len; j++){
            cout << setw(12) << la.table[i][j];
       }
        cout << endl;
    }

    cout << endl;
    early_run(la);

    return 0;
}