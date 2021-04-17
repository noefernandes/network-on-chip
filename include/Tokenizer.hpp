#ifndef _TOKENIZER_
#define _TOKENIZER_
#include <vector>
#include <iostream>


class Tokenizer{
    public:
        Tokenizer(std::string &line): buffer(""){
            for(auto i(0u); i < line.length(); ++i){
                if(line[i] == ' '){
                    continue;
                }else{            
                    while(line[i] != ' ' && i < line.length()){
                        buffer += line[i];
                        i++;
                    }
                    token.push_back(buffer);
                    buffer = "";
                }
            }
        }

        std::vector<std::string> getToken(){
            return token;
        }

        void setToken(std::vector<std::string> tok){
            token = tok;
        }

    private:
        std::string buffer;
        std::vector<std::string> token;
};
#endif