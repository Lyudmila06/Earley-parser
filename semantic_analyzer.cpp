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
    cout << "Defined variables:" << endl;//вывод объявленных переменных для проверки
    for (int i = 0; it != var_.end(); it++, i++) {
        cout << it->second << " " << it->first << endl;
    }
    cout << endl << "Variables analysis completed" << endl;
};


void semantic_analyzer::analyze_expr(lexical_analyzer la) {
    map<string, string>::iterator it1, it2;
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "operator =") {
            it1 = var_.find(la.table[i-1][1]);
            string type_var = it1->second;
            if (it1 == var_.end()) {
                cout << "VERY BAD: undefined variable:( I'm trying to do smth" << endl;
                while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {") i++;
                continue;
            }
            i++;
            while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {") {
                string str = la.table[i][1];
                if (la.table[i][3] == "digit") {
                    if (str.find('.') != string::npos) { //если присваивается вещественное число
                        if (type_var != "double") {
                            cout << "Conversion from " << type_var << " to double" << endl;
                        }
                    } else { //если присваивается целое число
                        if (type_var != "double" && type_var != "int")
                            cout << "Conversion from " << type_var << " to int" << endl;
                        }
                    }
                //if (la.table[i][3] == "operator 1 poriadka" | la.table[i][3] == "operator 2 poriadka" || la.table[i][3] == "separator )" || la.table[i][3] == "separator (") i++;
                if (la.table[i][3] == "identifier") { //если присваивается переменная
                    string type_expr_var = var_[la.table[i][1]];
                    if ((type_var != type_expr_var) & (type_var != "double" | type_expr_var != "int"))
                        cout << "Conversion from " << type_var << " to " << type_expr_var << endl;
                }
                if (la.table[i][3] == "logicheskia const") { //если присваивается true/false
                    if (type_var != "bool") {
                        cout << "Conversion from " << type_var << " to bool" << endl;
                    }
                }
                if (la.table[i][3] == "symbol") { //если присваивается символ
                    if (type_var != "char") {
                        cout << "Conversion from " << type_var << " to char" << endl;
                    }
                }
                i++;
            }
        }
    }
    cout << "Expressions analysis completed" << endl;
}