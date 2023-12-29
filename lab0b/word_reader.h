#pragma once
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#define dict map<string, size_t>


using std::string;
using std::ifstream;
using std::map;


class word_reader {
private:
    string str = "";
public:
    void read_word (ifstream& fin);

    void add_word_in_gist (dict& gist);

    void del_word ();
};
