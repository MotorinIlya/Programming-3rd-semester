#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#define dict map<string, size_t>
#define dict_pair pair<string, size_t>

using std::endl;
using std::map;
using std::multimap;
using std::pair;
using std::ofstream;
using std::string;
using std::cout;
using std::greater;

class word_writer {
private:
    multimap<size_t, string, greater<int> > gist;
public:
    word_writer (dict& gist);

    void cout_gist (ofstream& fout, int count_gist);
};