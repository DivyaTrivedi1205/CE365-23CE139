#include <bits/stdc++.h>
using namespace std;

vector<string> keywords = {
    "int","float","char","double","void","long","short",
    "if","else","for","while","do","return","struct","break","continue"
};

vector<string> operators = {
    "+","-","*","/","=","<",">","<=",">=","==","!=","++","--","&&","||","%"
};

vector<char> punctuations = {'(',')','{','}','[',']',';',',','.'};
vector<string> symbolTable;

bool isKeyword(string s){
    for(auto k:keywords) if(k==s) return true;
    return false;
}

bool isOperator(string s){
    for(auto o:operators) if(o==s) return true;
    return false;
}

bool isPunctuation(char c){
    for(auto p:punctuations) if(p==c) return true;
    return false;
}

bool existsInSymbolTable(string s){
    for(auto x:symbolTable) if(x==s) return true;
    return false;
}

int main(){
    ifstream fin("input.c");
    if(!fin){
        cout<<"File not found\n";
        return 0;
    }

    string line;
    int lineNo=0;
    vector<string> errors;
    bool blockComment=false;

    cout<<"TOKENS\n";

    while(getline(fin,line)){
        lineNo++;
        int n=line.length();

        for(int i=0;i<n;i++){
            if(blockComment){
                if(i+1<n && line[i]=='*' && line[i+1]=='/'){
                    blockComment=false;
                    i++;
                }
                continue;
            }

            if(i+1<n && line[i]=='/' && line[i+1]=='*'){
                blockComment=true;
                i++;
                continue;
            }

            if(i+1<n && line[i]=='/' && line[i+1]=='/'){
                break;
            }

            if(isspace(line[i])) continue;

            if(isalpha(line[i]) || line[i]=='_'){
                string word;
                while(i<n && (isalnum(line[i]) || line[i]=='_')){
                    word+=line[i++];
                }
                i--;
                if(isKeyword(word))
                    cout<<"Keyword: "<<word<<"\n";
                else{
                    cout<<"Identifier: "<<word<<"\n";
                    if(!existsInSymbolTable(word))
                        symbolTable.push_back(word);
                }
            }

            else if(isdigit(line[i])){
                string num;
                while(i<n && (isalnum(line[i]) || line[i]=='.')){
                    num+=line[i++];
                }
                i--;
                bool invalid=false;
                for(char c:num)
                    if(isalpha(c)) invalid=true;

                if(invalid)
                    errors.push_back("Line "+to_string(lineNo)+" : "+num+" invalid lexeme");
                else
                    cout<<"Constant: "<<num<<"\n";
            }

            else if(line[i]=='\'' || line[i]=='\"'){
                char q=line[i];
                string s;
                s+=line[i++];
                while(i<n && line[i]!=q){
                    s+=line[i++];
                }
                if(i<n) s+=q;
                cout<<"Constant: "<<s<<"\n";
            }

            else{
                string two;
                if(i+1<n){
                    two+=line[i];
                    two+=line[i+1];
                }
                if(isOperator(two)){
                    cout<<"Operator: "<<two<<"\n";
                    i++;
                }
                else if(isOperator(string(1,line[i]))){
                    cout<<"Operator: "<<line[i]<<"\n";
                }
                else if(isPunctuation(line[i])){
                    cout<<"Punctuation: "<<line[i]<<"\n";
                }
            }
        }
    }

    cout<<"\nLEXICAL ERRORS\n";
    for(auto e:errors) cout<<e<<"\n";

    cout<<"\nSYMBOL TABLE ENTRIES\n";
    for(int i=0;i<symbolTable.size();i++)
        cout<<i+1<<") "<<symbolTable[i]<<"\n";

    fin.close();
    return 0;
}
