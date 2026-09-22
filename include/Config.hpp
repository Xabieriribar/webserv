#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

class LocationConfig
{
    std::string path;
    std::string root;

    std::string index;
    std::string cgiExtension;
    std::string cgiInterpreter;

    bool autoindex;
    std::map<int, std::string> returnCode;
};

class ServerConfig
{
    std::string ip, port, root;
    size_t maxBodyBytes;
    std::map<int, std::string> errorCode;
};

class ConfigTokens
{
    private:
        std::vector<std::string> words;
        size_t pos;
    public:
        ConfigTokens(std::string& path) : pos(0)
        {
            std::ifstream file(path.c_str());
            if (!file)
                throw std::runtime_error("Failed to open config file");
            std::string line;
            size_t bytes;
            std::string word;
            size_t i = 0;
            //server {
            while (std::getline(file, line))
            {
                //check if bytes are larger than number allowed
                i = 0;
                while (line[i])
                {
                    char ch;
                    if (i == line.size())
                        ch = '\n';
                    else
                        ch = line[i];
                    if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '{' || ch == '}' || ch == ';' || ch == '#')
                    {
                        if (!word.empty())
                            words.push_back(word);
                        else if (ch == '{' || ch == '}' || ch == ';')
                        {
                            word += ch;
                            words.push_back(word);
                        }
                        else if (ch == '#')
                            break ;
                        word.clear();
                    }
                    else
                        word += ch;
                    i++;
                }
                //check how this worked?
                //if we were on the last char of the line, on the null terminator, then change that by the /n, if not, just keep ch as line[i]
                //check if it was a whitespace character, a { } or a ;
                //if yes, then check if the word has something. If yes, then push it right? I mean, push it, augment pos
                //if no, then the word has something, then put character into word, augment i. For exmaple, for server, it sees that is not bizarre char
                //therefore is a normal character, so put it into word, jump i++
            }

        }

};