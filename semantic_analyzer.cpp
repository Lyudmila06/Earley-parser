#include "semantic_analyzer.h"
void semantic_analyzer::analyze_vars(lexical_analyzer la)
{
    map <string, string>:: iterator it1, it2;
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "type of data" && la.table[i][1] != "void") {
            it1 = var_.find(la.table[i+1][1]);
            if (it1 != var_.end()) {
                cout << "Redefined variable '" << la.table[i + 1][1] << "' in line " << la.table[i][2] << endl;
            } else {
                if (la.table[i+1][1] != "main")
                    var_.insert(make_pair(la.table[i + 1][1], la.table[i][1]));
            }
        }
        if (la.table[i][3] == "identifier" && la.table[i][1] != "main") {
            bool defined = false;

            it2 = var_.find(la.table[i][1]);
            if (it2 == var_.end()) {
                cout << "Undefined variable '" << la.table[i][1] << "' in line " << la.table[i][2] << endl;
            }
        }

    }
    map <string, string> :: iterator it = var_.begin();
    cout << "Defined variables:" << endl;//вывод объявленных переменных для проверки
    for (int i = 0; it != var_.end(); it++, i++) {
        cout << it->second << " " << it->first << endl;
    }
    cout << "Variables analysis completed" << endl << endl;
};


void semantic_analyzer::analyze_expr(lexical_analyzer la) {
    map<string, string>::iterator it1, it2;
    for (int i = 0; i <= la.count; i++) {
        if (la.table[i][3] == "operator =") {
            it1 = var_.find(la.table[i-1][1]);
            string type_var = it1->second;
            if (it1 == var_.end()) { //если рассматривается необъявленная переменная
                cout << "VERY BAD: undefined variable '" << la.table[i-1][1] << "' :( I will try to do smth" << endl;
                while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {") i++;
                continue;
            }
            i++;
            while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {") {
                string str = la.table[i][1];
                if (la.table[i][3] == "digit") {
                    if (str.find('.') != string::npos) { //если присваивается вещественное число
                        if (type_var != "double") {
                            cout << "Conversion from " << type_var << " to double" << " in line " << la.table[i][2] << endl;
                        }
                    } else { //если присваивается целое число
                        if (type_var != "double" && type_var != "int")
                            cout << "Conversion from " << type_var << " to int" << " in line " << la.table[i][2] << endl;;
                        }
                    }
                //if (la.table[i][3] == "operator 1 poriadka" | la.table[i][3] == "operator 2 poriadka" || la.table[i][3] == "separator )" || la.table[i][3] == "separator (") i++;
                if (la.table[i][3] == "identifier") { //если присваивается переменная
                    string type_expr_var = var_[la.table[i][1]];
                    if ((type_var != type_expr_var) & (type_var != "double" | type_expr_var != "int"))
                        cout << "Conversion from " << type_var << " to " << type_expr_var << " in line " << la.table[i][2] << endl;;
                }
                if (la.table[i][3] == "logicheskia const") { //если присваивается true/false
                    if (type_var != "bool") {
                        cout << "Conversion from " << type_var << " to bool" << " in line " << la.table[i][2] << endl;
                    }
                }
                if (la.table[i][3] == "symbol") { //если присваивается символ
                    if (type_var != "char") {
                        cout << "Conversion from " << type_var << " to char" << " in line " << la.table[i][2] << endl;
                    }
                }
                i++;
            }
        }

        if (la.table[i][3] == "operator sravnenia") { //рассматриваем совместимость сравниваемых значений
            string type_left, type_right;
            int j = i;
            i++; j--;
            //while (la.table[j][3] != "separator ;" && la.table[j][3] != "separator {" && la.table[j][1] != "keyword") // для левой части сравнения
            {
//                if (la.table[i][3] == "operator 1 poriadka" | la.table[i][3] == "operator 2 poriadka" || la.table[i][3] == "separator )" || la.table[i][3] == "separator (") {
//                    i++;
//                    continue;
//                }
                if (type_left == "" && la.table[j][3] != "identifier") {
                    if (la.table[j][3] == "digit") type_left = "double";
                    if (la.table[j][3] == "logicheskia const") type_left = "bool";
                    if (la.table[j][3] == "symbol") type_left = "char";
                    //continue;
                    //break;
                }

                if (la.table[j][3] == "identifier") {
                    it1 = var_.find(la.table[j][1]);
                    if (it1 == var_.end()) {
                        cout << "STILL VERY BAD: undefined variable '" << la.table[j][1] << "' :( I will try to do smth" << endl;
                        while (la.table[j][3] != "separator ;" && la.table[j][3] != "separator {") j--;
                        continue;
                    }
                    string type_expr_var = var_[la.table[j][1]];
                    if (type_left != type_expr_var)
                        if (type_left == "")
                            type_left = type_expr_var;
                        else if ((type_expr_var != "int" && type_expr_var != "double") | type_left != "double")
                            cout << "Conversion from " << type_left << " to " << type_expr_var << " in line " << la.table[i][2] << endl;
                    //break;
                }
                if (type_left != "" && la.table[j][3] != "identifier"){
                    if (type_left == "double" && la.table[j][3] != "digit")
                        cout << "Conversion from " << type_left << " to " << la.table[j][3] << " in line " << la.table[i][2] << endl;
                    else if (type_left == "bool" && la.table[i][3] != "logicheskia const")
                        cout << "Conversion from " << type_left << " to " << la.table[j][3] << " in line " << la.table[i][2] << endl;
                    else if (type_left == "char" && la.table[i][3] != "symbol")
                        cout << "Conversion from " << type_left << " to " << la.table[j][3] << " in line " << la.table[i][2] << endl;
                    //break;

                }
                j--;
            }

            //while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {" && la.table[i][1] != "keyword") //для правой части сравнения
            {
                if (type_right == "" && la.table[i][3] != "identifier") {
                    if (la.table[i][3] == "digit") type_right = "double";
                    if (la.table[i][3] == "logicheskia const") type_right = "bool";
                    if (la.table[i][3] == "symbol") type_right = "char";
                    //continue;
                    //break;
                }

                if (la.table[i][3] == "identifier") {
                    it1 = var_.find(la.table[i][1]);
                    if (it1 == var_.end()) {
                        cout << "STILL VERY BAD: undefined variable '" << la.table[j][1] << "' :( I will try to do smth" << " in line " << la.table[i][2] << endl;
                        while (la.table[i][3] != "separator ;" && la.table[i][3] != "separator {") i--;
                        continue;
                    }
                    string type_expr_var = var_[la.table[i][1]];
                    if (type_right != type_expr_var)
                        if (type_right == "")
                            type_right = type_expr_var;
                        else if ((type_expr_var != "int" && type_expr_var != "double") | type_right != "double")
                            cout << "Conversion from " << type_right << " to " << type_expr_var << " in line " << la.table[i][2] << endl;
                        //break;
                }
                if (type_right != "" && la.table[i][3] != "identifier"){
                    if (type_right == "double" && la.table[i][3] != "digit")
                        cout << "Conversion from " << type_right << " to " << la.table[i][3] << " in line " << la.table[i][2] << endl;
                    else if (type_right == "bool" && la.table[i][3] != "logicheskia const")
                        cout << "Conversion from " << type_right << " to " << la.table[i][3] << " in line " << la.table[i][2] << endl;
                    else if (type_right == "char" && la.table[i][3] != "symbol")
                        cout << "Conversion from " << type_right << " to " << la.table[i][3] << endl;
                    //break;
                }
                i++;
            }

            if (type_left != type_right && !(type_left == "double" && type_right == "int") && !(type_left == "int" && type_right == "double")) //при сравнении неподходящих типов
                cout << "Invalid operands to binary expression " << type_left << " and " << type_right << " in line " << la.table[i-1][1] << endl;
            else
                cout << "Fine operands to binary expression " << type_left << " and " << type_right << endl; //при сравнении подходящих типов
        }
    }
    cout << "Expressions analysis completed" << endl;
}