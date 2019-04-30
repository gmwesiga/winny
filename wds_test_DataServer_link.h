#ifndef WINNY_oracleDATA_LINK_H
#define WINNY_oracleDATA_LINK_H
#include datalink.h

namespace winny_DataServer_link
{
    class test_DataServer_link: public DataServer_link
    {
        private:
            string server_name_
            string user_name_
            string pass_word_
            bool is_good_    
    };
};
#endif