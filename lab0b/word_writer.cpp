#include "word_writer.h"

pair<size_t, string> flip_pair (pair<const string, size_t>& x)
{
    return pair<size_t, string> (x.second, x.first);
}

word_writer::word_writer (dict& gist)
{
    for (auto i : gist)
    {
        word_writer::gist.insert(flip_pair(i));
    }
}

void word_writer::cout_gist (ofstream& fout, int count_words)
{
    for (auto i : gist)
    {
        fout << i.second << ", " << i.first << " " << float(i.first) / float(count_words) * 100 << "%" << endl;
    }
}
