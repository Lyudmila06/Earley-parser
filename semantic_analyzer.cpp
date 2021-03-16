#include "semantic_analyzer.h"
void semantic_analyzer::analyze_vars(lexical_analyzer la)
{
    map <string, string>:: iterator it1, it2;
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "type of data" && la.table[i][1] != "void") {
            it1 = var_.find(la.table[i+1][1]);
            if (it1 != var_.end()) {
                cout << "Redefined variable " << la.table[i + 1][1] << endl;
            } else {
                var_.insert(make_pair(la.table[i + 1][1], la.table[i][1]));
            }
        }
        if (la.table[i][3] == "identifier" && la.table[i][1] != "main") {
            bool defined = false;

            it2 = var_.find(la.table[i][1]);
            if (it2 == var_.end()) {
                cout << "Undefined variable " << la.table[i][1] << endl;
            }
        }

    }
    map <string, string> :: iterator it = var_.begin();
    for (int i = 0; it != var_.end(); it++, i++) {  // выводим их
        cout << it->second << " " << it->first << endl;
    }
    cout << endl << "Success" << endl;
};


void semantic_analyzer::analyze_expr(lexical_analyzer la) {
    map<string, string>::iterator it1, it2;
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "operator =") {
            it1 = var_.find(la.table[i-1][1]);
            string type_var = it1->second;
            i++;
            while (la.table[i][3] != "separator ;") {
                string str = la.table[i][3];
                if (la.table[i][3] == "digit") {
                    //cout << "there" << endl;
                    if (str.find('.') != string::npos) {
                        if (type_var == "double")
                            i++;
                        else cout << "Conversion from " << type_var << " to double" << endl;
                    } else {
                        if (type_var == "double" | type_var == "int")
                            i++;
                        else {
                            cout << "Conversion from " << type_var << " to int" << endl;
                        }
                    }
                }
                if (la.table[i][3] == "operator 1 poriadka" | la.table[i][3] == "operator 2 poriadka") i++;
                if (la.table[i][3] == "identifier") {
                    string type_expr_var = var_[la.table[i][1]];
                    if ((type_var == type_expr_var) | (type_var == "double" && type_expr_var == "int")) {
                        i++;
                    } else {
                        cout << "Conversion from " << type_var << " to " << type_expr_var << endl;
                    }
                }
                if (la.table[i][3] == "logicheskia const") {
                    if (type_var == "bool") {
                        i++;
                    } else {
                        cout << "Conversion from " << type_var << " to bool" << endl;
                    }
                }
                if (la.table[i][3] == "symbol") {
                    if (type_var == "char") {
                        i++;
                    } else {
                        cout << "Conversion from " << type_var << " to char" << endl;
                    }
                }
            }
        }
    }
    cout << "Success express";
}