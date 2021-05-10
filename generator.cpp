#include "generator.h"
void generator::generator_run()
{
    string s1, s2;
    bool b = false;
    for (int i = 0; i < la.count + 1; i++) {
        s2 = la.table[i][2];
        map <string, string>::iterator it = gen_rule.find(la.table[i][1]);
        if (it != gen_rule.end()) {
            s1 = gen_rule[la.table[i][1]];
        }
        else {
            s1 = la.table[i][1];
        }
        vector<string> pair;
        pair.push_back(s1);
        pair.push_back(s2);
        result_table.push_back(pair);
        if (s1 == "") {
            b = true;
            result_table.pop_back();
            result_table.pop_back();
        }
    }
    if (b == true){
        result_table.pop_back();
        result_table.erase(result_table.begin());
        result_table.erase(result_table.begin());
        result_table.erase(result_table.begin());
    }
    //print_result();
    print_java_script();
}

generator::generator(lexical_analyzer la)
{
    this->la = la;

    //result_table= new vector<>(la.count, 2);

    gen_rule.insert(make_pair("main", ""));
    gen_rule.insert(make_pair("int", "let"));
    gen_rule.insert(make_pair("bool", "let"));
    gen_rule.insert(make_pair("double", "let"));
    gen_rule.insert(make_pair("char", "let"));
    gen_rule.insert(make_pair("mod", "%"));
    gen_rule.insert(make_pair("==", "==="));
}

void generator::print_result()
{
    for (int i = 0; i < la.count; i++) {
        cout << result_table[i][0] << " " << result_table[i][1] << endl;
    }
}

void generator::print_java_script() {
    for (int i = 0; i < result_table.size(); i++) {
        if ((i != result_table.size() - 1) && (result_table[i + 1][0] == ";"))
            cout << result_table[i][0];
        else
            cout << result_table[i][0] << " ";
        if ((i != result_table.size() - 1) && (result_table[i][1] != result_table[i+1][1]))
            cout << endl;
    }
}