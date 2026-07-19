#pragma once
//have.h v1.0
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<limits>
#include<algorithm>
#include<cctype>
#include<source_location>
//====================must know if you want use these function==================================================================================
// 
//ADDITIONAL
//all the function can return a mistake num,and it in a namespace have_tool
//we provide a function named "decode" to help you debug
//it form decode(we provide function)
// and then it will return mistake's true name
// the function if meet EOF ,it will clear the eofbit and failbit,don't forget this
// 
// MISTAKE TYPE MEANING
// "mistake::normal" means the function is end and normal
// "mistake::eof"  means the function meet EOF
// "mistake::agmt_fail"  means the function's arguments have problem,you should change your mistake
// "mistake::more_line" means the input line more than sup
// "mistake::line_too_long" means the input line is too long(more than 10000 char)
// "mistake::debug_exit" it only return it you add some debug argument in we provide interface
// TOOLS
// "have"----
// this function have one template and three overloads ,all the forms have strict input validation
// it can help you protect the user's bad input or get you except words from user
// ---->the template "have"
// its form----have(variable)
// the variable will repeat request until get true data
// ---->the int "have"
// it like the template "have" ,but it only accept int type
// and it require you input two int validation to boundary restriction
// its form----have(int variable,inf,sup,flag),the flag don't need you provide
// the flag can tell you the mistake's address if you use it like "have(user,3,2)"
// 2026.7.15
// {
// we add a string name "the_key" behind the sup ,its new form----have(int variable,inf,sup,the_key,flag)
// if you input line is simple with "the_key",it will return mistake::debug_exit and end ,but it don't change your int
// variable,so you had better give the int variable a initial value,it's not necessary ,it only provide to debug
// if you need debug but your variable will do something ,you can try to use it carefully(we don't invite a careful version about it)
// }
// ---->the char "have"
// its like the int "have" but it use ASCLL to  boundary restriction
// so you should allow the address in ASCLL to decide the inf and the sup
// ---->the string "have"
// it form----have(string variable,{except words},flog)
// if the "except words" is empty ,it will tell you the mistake's address 
// 2026.7.4
// {
// we add a string overloading have function , it will be use by itself , becuase we have found that if a line have empty among input words
// the templete have will stop read when it read the empty,so we add it ,it just change achievement ,and we write it only tell you to download 
// the new database to fix this problem ,thank your support!
// }
// 
// "read"----
// it can read multiline input and put them into a vector
// the vector can use to initialization your vector
// 2026.6.7
// {
// ----we change it ,now it need a num,tow mystring struct ,the num means how many lines can read into the vector
// ---->mystring
// it structure is  {std::string words;   the words is you want output string,if the enter is true,it will output a"\n" in the  
//                   bool enter = 1;};                            end of the string,you can use it like this
//                                                                std::vector<string>example=read({7},{"please input",false},{"over!",true}
//                                                                or don't output,you can write"read({3})" or"read({3},{},{"over!",true})"
//                                                                the"please input" will output in the begin,the "over!" will output if the
//                                                                user's input lines more than the sup
// you had better to tell user"input Ctrl+Z to leave",otherwise user maigt feel so bad
// }
// 2026.6.13
// {
// ----we change the struct ,we add a bool variable named "empty_" into its members,if "empty_" is false ,it will output your string,otherwise 
// it won't output,don't forget to set it,because its initial value is false,and the once form is can't use,the new form is
// -----read(your string vector,sup,mystring begin,mystring fail),it don't need you use a vector to accpet it ,it will directly change
// your vector ,but your vector's data will all clear,so please use it carefully,and if user input more than the sup ,the more than lines will
// clear by the function ,so you had better to tell user"please input not more than xxx".and the sup isn't the vector's elements' num, it's this 
// time can read lines.
// ----we add a bool variable "continue_",if it is true,it will read lines in the vector's end ,otherwise it will clear it before read lines
// and it initial value is false,remember set it.the new form is read(your string vector,sup,mystring begin,mystring fail,continue_)
// }
// 
// 
// "print"----
// it need a string vector and it can show its all messages
// 
// "trim"----
// it need a string and trim both sides of the string
// it will return the clearly string,don't forget use the former string to accept it
// 
// "lower"----
// like the "trim", but it only make the string become lower
//====================must know if you want use these function==================================================================================


namespace have_tool {
    //====================global variable===========================================================================================================
    static constexpr size_t MAX_LINE_LENGTH = 10000;
    //====================global variable===========================================================================================================
    
    
    
    
    //====================struct&class==============================================================================================================
    struct mystring
    {
        std::string words;
        bool enter = 1;
        bool empty_ = 0;
    };
    enum class mistake { eof, agmt_fail, more_line, normal,line_too_long,debug_exit };
    //====================struct&class==============================================================================================================



    //====================function's declaration===================================================================================================
    inline mistake have(int& user, int inf, int sup,std::string the_key,const std::source_location& loc = std::source_location::current());
    template<class h> mistake have(h& user);
    inline mistake have(std::string& user, std::initializer_list<std::string> except,
                       const std::source_location& loc = std::source_location::current());
    inline mistake read(std::vector<std::string>& user, int sup, mystring begin, mystring fail,
                       const bool continue_=false, const std::source_location& loc = std::source_location::current());
    inline void print(const std::vector<std::string>& user);
    inline std::string lower(std::string str);
    inline std::string trim(const std::string& str);
    inline mistake have(char& user, char inf, char sup, const std::source_location& loc = std::source_location::current());
    inline mistake readline(std::string& line);
    inline std::string decode(mistake mistake);
    inline mistake have(std::string& user, const std::source_location& loc = std::source_location::current());
    //====================function's declaration=====================================================================================================



    //====================function's complete========================================================================================================
    template<class h> mistake have(h& user)
    {
        std::string line;
        bool test = false;
        while (!test)
        {
            mistake error = readline(line);
            if (error == mistake::eof)
                return mistake::eof;
            if (error == mistake::line_too_long) {
                std::cout << "输入过长，请精简后重试\n";
                continue;
            }
            std::stringstream ss(line);
            if (ss >> user && ss.eof())
                test = true;
            else
                std::cout << "输入无效！\n";
        }
        return mistake::normal;
    }

    inline mistake have(int& user, int inf, int sup,std::string the_key={}, const std::source_location& loc)
                                                                                /*   we can't definition twice the const
                                                                                  ,so this place don't need write that
                                                                                  "= std::source_location::current()" */
    {
        std::string line;
        bool test = false;
        if (inf > sup)
        {
            std::cout << "代码参数设置有误！\n";
            std::cout << "调用在文件 " << loc.file_name()
                << "，第 " << loc.line() << " 行\n";
            return mistake::agmt_fail;
        }
        while (!test)
        {
            mistake error = readline(line);
            if (error == mistake::eof)
                return mistake::eof;
            if (error == mistake::line_too_long) {
                std::cout << "输入过长，请精简后重试\n";
                continue;
            }
            trim(line);
            if (!the_key.empty() && line == the_key)
                return mistake::debug_exit;
            std::stringstream ss(line);
            if (ss >> user && ss.eof() && user >= inf && user <= sup)
                test = true;
            else
                std::cout << "请输入 [" << inf << ", " << sup << "] 内的整数\n";
        }
        return mistake::normal;
    }

    inline mistake have(std::string& user, std::initializer_list<std::string> except, const std::source_location& loc)
    {
        if (except.size() == 0)
        {
            std::cout << "代码参数设置有误！\n";
            std::cout << "调用在文件 " << loc.file_name()
                << "，第 " << loc.line() << " 行\n";
            return mistake::agmt_fail;
        }
        bool test = false;
        std::string line;
        do
        {
            mistake error = readline(line);
            if (error == mistake::eof)
                return mistake::eof;
            if (error == mistake::line_too_long) {
                std::cout << "输入过长，请精简后重试\n";
                continue;
            }
            line = trim(line);
            for (const auto& exc : except)
            {
                if (exc == line)
                {
                    user = line;
                    test = true;
                    break;
                }
            }
            if (!test)
                std::cout << "输入无效！\n";
        } while (!test);
        return mistake::normal;
    }

    inline mistake read(std::vector<std::string>& user, int sup, mystring begin, mystring fail, bool continue_,const std::source_location& loc)
    {
        if(!continue_)
              user.clear();
        int num_line = 0;
        if (sup <= 0)
        {
            std::cout << "代码参数设置有误！\n";
            std::cout << "调用在文件 " << loc.file_name()
                << "，第 " << loc.line() << " 行\n";
            std::cout << "已调整为无限制模式\n";
            sup = std::numeric_limits<int>::max();
        }
        if (!begin.empty_)
        {
            if (begin.enter) { std::cout << begin.words << "\n"; }
            else { std::cout << begin.words; }
        }
        std::string user_str;
        mistake error;
        while (true)
        {
            error= readline(user_str);
            if (error == mistake::eof)
                break;
            if (error == mistake::line_too_long) {
                std::cout << "输入过长，请精简后重试\n";
                continue;
            }
            if ((user.size()+1)> sup)
            {
                if (!fail.empty_)
                {
                    if (fail.enter) { std::cout << fail.words << "\n"; }
                    else { std::cout << fail.words; }
                }
               while(getline(std::cin,user_str)){}
                std::cin.clear();
                return mistake::more_line;
            }
            user.push_back(user_str);
        }
        std::cin.clear();
        return mistake::normal;
    }

    inline void print(const std::vector<std::string>& user)
    {
        for (const std::string& str : user)
            std::cout << str << "\n";
    }

    inline std::string lower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
            [](char c) -> char {
                return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            });
        return str;
    }

    inline std::string trim(const std::string& str) {/*   make the string's empty blanks disappear
                                                       to make the machine can process it with true way     */
        const size_t start = str.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        const size_t end = str.find_last_not_of(" \t\r\n");
        return str.substr(start, end - start + 1);
    }

    inline mistake have(char& user, char inf, char sup, const std::source_location& loc)
    {
        if (inf > sup)
        {
            std::cout << "代码参数设置有误！\n";
            std::cout << "调用在文件 " << loc.file_name()
                << "，第 " << loc.line() << " 行\n";
            return mistake::agmt_fail;
        }
        std::string line;
        while (true)
        {
            mistake error = readline(line);
            if (error == mistake::eof)
                return mistake::eof;
            if (error == mistake::line_too_long) {
                std::cout << "输入过长，请精简后重试\n";
                continue; 
            }
            if (line.empty())
            {
                std::cout << "输入无效！\n";
                continue;
            }
            line = trim(line);
            if (line.size() != 1) {
                std::cout << "仅能输入一个字符！\n";
                continue;
            }
            user = line[0];
            if (user >= inf && user <= sup)
                return mistake::normal;
            std::cout << "请输入 [" << inf << ", " << sup << "] 内的一个字符\n";
        }
    }
    inline mistake readline(std::string& line)
    {
        line.clear();
        char user{};
        while (std::cin.get(user))
        {
            if (user == '\n')
                return mistake::normal;
            if (line.size() < MAX_LINE_LENGTH)
                line.push_back(user);
            else
            {
                std::string kill;
                while(getline(std::cin,kill)){}
                std::cin.clear();
                return mistake::line_too_long;
            }
        }
        std::cin.clear();
        if (line.size() == 0)
        {
            return mistake::eof;
        }
        return mistake::normal;
    }
    inline mistake have(std::string& user, const std::source_location& loc) 
    {
        while (true)
        {
            mistake err = readline(user);
            if (err == mistake::eof) 
            {
                return mistake::eof;
            }
            if (err == mistake::line_too_long)
            {
                std::cout << "输入过长，请精简后重试（限制 " << MAX_LINE_LENGTH << " 字符）\n";
                continue; 
            }
            return mistake::normal;
        }
    }
    inline std::string decode(mistake m)
    {
        switch (m){
        case mistake::eof: return "EOF";
        case mistake::agmt_fail: return "参数错误";
        case mistake::more_line: return "行数超限";
        case mistake::normal: return "正常";
        case mistake::line_too_long: return"单行字数超限";
        case mistake::debug_exit: return"调试跳过";
        default: return "错误码";
        }
    }
    //====================function's complete=========================================================================================================
}
