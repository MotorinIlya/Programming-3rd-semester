#include "word_reader.h"

void word_reader::read_word (ifstream& fin)
{
    char ch;
    fin.get(ch);
    while (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
    {
        str += ch;
        if (fin.eof())
        {
            break;
        }
        ch = fin.get();            
    }    
}

void word_reader::add_word_in_gist (dict& gist)
{
    if (gist.find(str) != gist.end())
    {
        gist[str]++;
    }
    else
    {
        gist[str] = 1;
    }
}

void word_reader::del_word ()
{
    str = "";
}
