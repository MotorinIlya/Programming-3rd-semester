#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "word_reader.h"
#include "word_writer.h"

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;


size_t Size_map (map<string, size_t>);
int count_words (dict& gist);


int main ()
{
	ifstream fin;
	fin.open("/home/motorog/dev/lab0b/input.txt");

    ofstream fout;
    fout.open("/home/motorog/dev/lab0b/output.csv");

	dict gist;

	word_reader reader;

	while (!fin.eof())
	{
		reader.read_word(fin);
		reader.add_word_in_gist(gist);
		reader.del_word();
	}
    
    gist.erase("");
    int size_map = Size_map(gist);

	word_writer writer (gist);

	int words = count_words(gist);
	writer.cout_gist(fout, words);

	fin.close();
    fout.close();
    cout << "done!" << endl;
	return 0;
}


size_t Size_map (dict m)
{
	size_t size = 0;
	for (auto i : m)
	{
		size++;
	}
	return size;
}

int count_words (dict& gist)
{
    int count = 0;
    for (auto i : gist)
    {
        count += i.second;
    }
    return count;
}