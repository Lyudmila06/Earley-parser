#include "semantic_analyzer.h"
void semantic_analyzer::analyze_vars(lexical_analyzer la)
{
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "type of data") {
            for (int j = 0; j < count_vars; j++) {
                if (la.table[i+1][1] == vars[j][1]) {
                    cout << "Redefined variable " << la.table[i+1][1] << endl;
                    break;
                }
            }
            vars[count_vars][0] = la.table[i][1];
            vars[count_vars][1] = la.table[i+1][1];
            count_vars++;
        }
        if (la.table[i][3] == "identifier") {
            bool defined = false;
            for (int j = 0; j < count_vars; j++) {
                if (vars[j][1] == la.table[i][0])  {
                    defined = true;
                    break;
                }
            }
            if (!defined)
                cout << "Undefined variable " << la.table[i][1] << endl;
        }

    }
    for (int j = 0; j < count_vars; j++) cout << vars[j][1] << ", ";
    cout << endl << "Success" << endl;
};