//
// Created by 1 on 14/11/2020.
//

#include "lexical.h"

bool lexical_analyzer::isID(const string &str) {
    if (isdigit(str[0]))
        return false;
    int counter = 0;
    if (str[0] == '_')
        counter++;
    for(counter; counter < str.size(); counter++)
        if(!(isalnum(str[counter])) && str[counter] != '_')
            return false;
    return true;
}

bool lexical_analyzer::isDigit(const string &str) {
    bool digit = true;
    for (int i = 0; i < str.length(); i++){
        if (!isdigit(str[i]) && str[i] != '.')
            digit = false;
    }
    return digit;
}

bool lexical_analyzer::isSymbol(const string &str) {
    return str[0] == '\'' && str[2] == '\'';
}

bool lexical_analyzer::isKeyword(const string &str) {
    const vector <string> keywords{"break", "do", "do", "else", "return", "for", "if", "while"};
    for(const auto& keyword : keywords)
        if (keyword == str)
            return true;

    return false;
}

bool lexical_analyzer::isReservedName(const string &str) {
    const vector <string> reserve{"bool", "char", "const", "double", "false", "true", "float", "int", "null", "void"};
    for(const auto& reserve : reserve)
        if (reserve == str)
            return true;
    return false;
}

bool lexical_analyzer::isOperator(const string &str) {
    const vector <string> operators{"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "!=", "&&", "||", "==", "!", "mod"};
    for(const auto& op : operators)
        if (op == str)
            return true;
    return false;
}

bool lexical_analyzer::isSeparator(const string &str) {
    const vector <string> Separators{"{", "}", ",", "(", ")", ";"};
    for(const auto& separate : Separators)
        if (separate == str)
            return true;
    return false;
}

bool lexical_analyzer::isNotLegal(const string &str) {
    if (str == "\n")
        pos++;
    return str == " " || str == "\n" || str == "\r";
}


void lexical_analyzer::printRoleOfToken(const string& token) {
    count++;
    if (isOperator(token)){
        table[count][0] = "operator";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        if (token == "*" || token == "/" || token == "mod") {
            table[count][3] = "operator 1 poriadka";
        }
        else if (token == "+" || token == "-") {
            table[count][3] = "operator 2 poriadka";
        }
        else if (token == "<" || token == ">" || token == "==" || token == ">=" || token == "<=" || token == "!=") {
            table[count][3] = "operator sravnenia";
        }
        else if (token == "||" || token == "&&") {
            table[count][3] = "logicheskiy operator";
        }
        else if (token == "=") {
            table[count][3] = "operator =";
        }else if (token == "!") {
            table[count][3] = "!";
        }
        else {
            table[count][3] = "operator";
        }
    }
    else if(isSeparator(token)) {
        table[count][0] = "separator";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        if (token == ";") {
            table[count][3] = "separator ;";
        }
        else if (token == "{") {
            table[count][3] = "separator {";
        }
        else if (token == "}") {
            table[count][3] = "separator }";
        }
        else if (token == "(") {
            table[count][3] = "separator (";
        }
        else if (token == ")") {
            table[count][3] = "separator )";
        }        else if (token == ",") {
            table[count][3] = "separator ,";
        }
        else {
            table[count][3] = "separator";
        }
    }
    else if(isKeyword(token)) {
        table[count][0] = "keyword";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        if (token == "if") {
            table[count][3] = "if";
        }
        else if (token == "while") {
            table[count][3] = "while";
        }
        else if (token == "return") {
            table[count][3] = "return";
        }
        else if (token == "for") {
            table[count][3] = "for";
        }
        else if (token == "else") {
            table[count][3] = "else";
        }
        else {
            table[count][3] = "keyword";
        }
    }
    else if(isReservedName(token)) {
        table[count][0] = "reserved name";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        if (token == "int" || token == "bool" || token == "float" || token == "void" || token == "char" || token == "double") {
            table[count][3] = "type of data";
        }
        else if (token == "false" || token == "true") {
            table[count][3] = "logicheskia const";
        }
        else if (token == "null") {
            table[count][3] = "null";
        }
        else {
            table[count][3] = "reserved name";
        }
    }
    else if(isDigit(token)) {
        table[count][0] = "digit";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        table[count][3] = "digit";
    }
    else if(isSymbol(token)) {
        table[count][0] = "symbol";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        table[count][3] = "symbol";
    }
    else if(isID(token)) {
        table[count][0] = "identifier";
        table[count][1] = token;
        table[count][2] = to_string(pos);
        table[count][3] = "identifier";
    }
    else {
        count--;
        cout << "Identifier  " << token << " not found\n";
    }
}

void lexical_analyzer::lexicalAnalyze(const string &nameOfFile) {
    char ch;
    string buffer;
    fstream file(nameOfFile, fstream::in);

    if (!file.is_open()){
        cout << "error while opening the file\n";
        exit(0);
    }

    bool miltiCm = false, singleCm = false;
    while (file >> noskipws >> ch){
        /*if (singleCm || miltiCm){
            if (singleCm && ch == '\n')
                singleCm = false;
            if (miltiCm && ch == '*'){
                file >> ch;
                if (ch == EOF)
                    break;
                if (ch == '/')
                    miltiCm = false;
            }
            continue;
        }
        if (ch == '/'){
            string comm(1, ch);
            file >> ch;
            if(ch == EOF){
                printRoleOfToken(comm);
                break;
            }
            if(ch == '*'){
                miltiCm = true;
                comm += ch;
            }
            else if(ch == '/'){
                singleCm = true;
                comm += ch;
            }
            if(miltiCm || singleCm){
                printRoleOfToken(comm);
                continue;
            }
        }*/

        if (isNotLegal(string(1, ch))){
            if (!buffer.empty()){
                printRoleOfToken(buffer);
                buffer = "";
            }
            continue;
        }

        /*if(isOperator(string(1, ch))){
            if (!buffer.empty() && !isOperator(buffer)){
                printRoleOfToken(buffer);
                buffer = "";
            }
            /*if (isOperator(string(1, ch))){
                printRoleOfToken(std::string(1, ch));
                continue;
            }
        }*/

        if (isSeparator(string(1, ch))){
            if (!buffer.empty()){
                printRoleOfToken(buffer);
                buffer = "";
            }
            if (isSeparator(string(1, ch))){
                printRoleOfToken(std::string(1, ch));
                continue;
            }
        }
        buffer += ch;
    }
    file.close();
}