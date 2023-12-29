#include "bit_array.h"
#include <assert.h>

bit_array::bit_array ()
{
    bit_array::num_bits = 0;
    bit_array::num_elements = 0;
}

bit_array::~bit_array (){}


bit_array::bit_array (int num_bits, unsigned long value)
{
    assert(num_bits >= 0);
    this -> num_bits = num_bits;
    this -> num_elements = num_bits / 64 + bool(num_bits % 64);
    this -> array.push_back(value);
    int i = 1;
    while (i < this -> num_elements)
    {
        this -> array.push_back(0);
        i++;
    }
    this -> sub_bits();
}

bit_array::bit_array (const bit_array& b)
{
    this -> num_bits = b.num_bits;
    this -> num_elements = b.num_elements;
    for (int i = 0; i < b.num_elements; i++)
    {
        this -> array.push_back(b.array[i]);
    }
}

bit_array& bit_array::operator = (const bit_array& b)
{
    this -> resize(b.num_bits);
    for (int i = 0; i < b.num_elements; i++)
    {
        this -> array[i] = b.array[i];
    }
    return *this;
}

void bit_array::resize (int num_bits, bool value)
{
    assert(num_bits >= 0);
    int old_num_bits = this -> num_bits;
    int old_num_el = this -> num_elements;
    int num_elements = num_bits / 64 + bool(num_bits % 64);
    if (num_elements > old_num_el)
    {
        int add_bits = num_bits - old_num_bits;
        for (int i = 0; i < add_bits; i++)
        {
            this -> push_back(value);
        }
    }
    else
    { 
        int sub_elements = old_num_el - num_elements;
        for (int i = 0; i < sub_elements; i++)
        {
            this -> array.erase(this -> array.end() - 1); 
        }
        this -> num_bits = num_bits;
        this -> num_elements = num_elements;
        this -> sub_bits();
    }
}

void bit_array::clear ()
{
        for (int i = 0; i < this -> num_elements; i++)
        {
            this -> array.erase(this -> array.end() - 1);
        }
        this -> num_elements = 0;
        this -> num_bits = 0;
}

void bit_array::push_back (bool bit)
{
    int skip = (this -> num_elements * 64 - this -> num_bits);
    unsigned long pos = 1;
    if (!(skip))
    {
        this -> array.push_back(0);
        this -> array.back() |= bit * (pos << 63);
        this -> num_bits++;
        this -> num_elements++;
    }
    else
    {
        this -> array.back() |= bit * (pos << (skip - 1));
        this -> num_bits++;
    }
}

bit_array& bit_array::set (int n, bool val)
{
    assert(n >= 0 && n < this -> num_bits);
    int pos = 63 - (n % 64);
    unsigned long bit = 1;
    bit <<= pos;
    int el = n / 64;
    if (val)
    {
        this -> array[el] |= bit;
    }
    else
    {
        unsigned long mask = UINT64_MAX;
        mask ^= bit;
        this -> array[el] &= mask;
    }
    return (bit_array &) *this;
}

bit_array& bit_array::set ()
{
    for (int i = 0; i < this -> num_elements; i++)
    {
        this -> array[i] |= UINT64_MAX;
    }
    this -> sub_bits();
    return (bit_array &) *this;
}

bit_array& bit_array::reset (int n)
{
    assert(n >= 0 && n < this -> num_bits);
    int pos = 63 - (n % 64);
    unsigned long bit = 1;
    bit <<= pos;
    unsigned long mask = UINT64_MAX;
    mask ^= bit;
    int el = n / 64;
    this -> array[el] &= mask;
    return (bit_array &) *this;
}

bit_array& bit_array::reset ()
{
    for (int i = 0; i < this -> num_elements; i++)
    {
        this -> array[i] &= 0;
    }
    return (bit_array &) *this;
}

bool bit_array::any () const
{
    for (auto i : this -> array)
    {
        if (i)
        {
            return true;
        }
    }
    return false;
}

bool bit_array::none () const
{
    for (auto i : this -> array)
    {
        if (i)
        {
            return false;
        }
    }
    return true;
}

int bit_array::count () const
{   
    int count = 0;
    for (auto el : this -> array)
    {
        while (el)
        {
            if (el % 2)
            {
                count++;
            }
            el /= 2;
        }

    }
    return count;
}

int bit_array::size () const
{
    return this -> num_bits;
}

bool bit_array::empty () const
{
    return !(this -> num_bits);
}

string bit_array::to_string () const
{
    string bit_array = "";
    for (int i = 0; i < this -> num_bits; i++)
    {
        unsigned long el = this -> array[i / 64];
        unsigned long mask = 1;
        mask <<= 63 - (i % 64);
        el &= mask;
        if (el)
        {
            bit_array += '1';
        }
        else
        {
            bit_array += '0';
        }
    }
    return bit_array;
}

void bit_array::swap (bit_array& b)
{
    int one_num_bits = this -> num_bits;
    int one_num_elements = this -> num_elements;
    vector one_array = this -> array;
    this -> num_bits = b.num_bits;
    this -> num_elements = b.num_elements;
    this -> array = b.array;
    b.num_bits = one_num_bits;
    b.num_elements = one_num_elements;
    b.array = one_array;
}

bit_array& bit_array::operator &= (const bit_array& b)
{
    assert(this -> num_bits == b.size());
    for (int i = 0; i < this -> num_elements; i++)
    {
        this -> array[i] &= b.array[i];
    }
    return (bit_array&) (*this);
}

bit_array& bit_array::operator |= (const bit_array& b)
{
    assert(this -> num_bits == b.size());
    for (int i = 0; i < this -> num_elements; i++)
    {
        this -> array[i] |= b.array[i];
    }
    return (bit_array&) (*this);
}

bit_array& bit_array::operator ^= (const bit_array& b)
{
    assert(this -> num_bits == b.size());
    for (int i = 0; i < this -> num_elements; i++)
    {
        this -> array[i] ^= b.array[i];
    }
    return (bit_array&) (*this);
}

bit_array bit_array::operator ~ () const
{
    bit_array new_array (this -> num_bits);
    unsigned long mask = UINT64_MAX;
    for (int i = 0; i < this -> num_elements; i++)
    {
        new_array.array[i] = this -> array[i] ^ mask;
    }
    new_array.sub_bits();
    return new_array;
}

bit_array& bit_array::operator <<= (int n)
{
    this -> array[0] <<= n;
    for (int i = 1; i < this -> num_elements; i++)
    {
        unsigned long mask = UINT64_MAX;
        mask <<= 64 - n;
        mask &= this -> array[i];
        mask >>= 64 - n;
        this -> array[i - 1] += mask;
        this -> array[i] <<= n;
    }
    return (bit_array&) (*this);
}

bit_array& bit_array::operator >>= (int n)
{
    this -> array[this -> num_elements - 1] >>= n;
    for (int i = this -> num_elements - 2; i >= 0; i--)
    {
        unsigned long mask = UINT64_MAX;
        mask >>= 64 - n;
        mask &= this -> array[i];
        mask <<= 64 - n;
        this -> array[i + 1] += mask;
        this -> array[i] >>= n;
    }
    this -> sub_bits();
    return (bit_array&) (*this);
}

bool bit_array::operator [] (int i) const
{
    assert(i >= 0 && i < this -> num_bits);
    unsigned long el = this -> array[i / 64];
    int pos = i % 64;
    unsigned long mask = 1;
    mask <<= 63 - pos;
    mask &= el;
    if (mask)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bit_array bit_array::operator << (int n) const
{
    bit_array new_array;
    new_array = *this;
    new_array.array[0] <<= n;
    for (int i = 1; i < this -> num_elements; i++)
    {
        unsigned long mask = UINT64_MAX;
        mask <<= 64 - n;
        mask &= this -> array[i];
        mask >>= 64 - n;
        new_array.array[i - 1] += mask;
        new_array.array[i] <<= n;
    }
    return new_array;
}

bit_array bit_array::operator >> (int n) const
{
    bit_array new_array;
    new_array = *this;
    new_array.array[new_array.num_elements - 1] >>= n;
    for (int i = this -> num_elements - 2; i >= 0; i--)
    {
        unsigned long mask = UINT64_MAX;
        mask >>= 64 - n;
        mask &= this -> array[i];
        mask <<= 64 - n;
        new_array.array[i + 1] += mask;
        new_array.array[i] >>= n;
    }
    new_array.sub_bits();
    return new_array;
}

bool operator == (const bit_array& a, const bit_array& b)
{
    string stra = a.to_string();
    string strb = b.to_string();
    return (stra == strb);
}

bool operator != (const bit_array& a, const bit_array& b)
{
    string stra = a.to_string();
    string strb = b.to_string();
    return (stra != strb);
}

bit_array operator & (const bit_array& a, const bit_array& b)
{
    assert(a.size() == b.size());
    int size = a.size();
    bit_array new_array;
    for (int i = 0; i < size; i++)
    {
        new_array.push_back(a[i] && b[i]);
    }
    return new_array;
}

bit_array operator | (const bit_array& a, const bit_array& b)
{
    assert(a.size() == b.size());
    int size = a.size();
    bit_array new_array;
    for (int i = 0; i < size; i++)
    {
        new_array.push_back(a[i] || b[i]);
    }
    return new_array;
}

bit_array operator ^ (const bit_array& a, const bit_array& b)
{
    assert(a.size() == b.size());
    int size = a.size();
    bit_array new_array;
    for (int i = 0; i < size; i++)
    {
        new_array.push_back(a[i] ^ b[i]);
    }
    return new_array;
}

void bit_array::sub_bits ()
{
    int sub_bits = 64 - (num_bits % 64);
    if (sub_bits != 64)
    {
        unsigned long mask = UINT64_MAX;
        mask <<= sub_bits;
        this -> array.back() &= mask;
    }
}
