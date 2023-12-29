#include <vector>
#include <string>
#include <cstdint>

using std::vector;
using std::string;


class bit_array {
public:
    bit_array ();
    ~bit_array ();

    //Constructs an array storing a specified number of bits.
    //The first sizeof(long) bits can be initialized using the value parameter.
    explicit bit_array (int num_bits, unsigned long value = 0); 
    bit_array (const bit_array& b);

    //Exchanges the values of two bit arrays.
    void swap (bit_array& b);

    bit_array& operator=(const bit_array& b);
    
    //Changes the size of the array. In case of expansion, new elements are initialized with the value value.
    void resize (int num_bits, bool value = false);
    
    //Clears the array.
    void clear ();

    //Adds a new bit to the end of the array. If necessary
    //memory is redistributed.
    void push_back (bool bit);

    //Bit operations on arrays.
    //They only work on arrays of the same size.
    bit_array& operator&=(const bit_array& b);
    bit_array& operator|=(const bit_array& b);
    bit_array& operator^=(const bit_array& b);

    //Bit shift with zero padding.
    bit_array& operator<<=(int n);
    bit_array& operator>>=(int n);
    bit_array operator<<(int n) const;
    bit_array operator>>(int n) const;

    //Sets the bit with index n to val.
    bit_array& set (int n, bool val = true);

    //Fills the array with the truth.
    bit_array& set ();

    //Sets the bit with index n to false.
    bit_array& reset (int n);

    //Fills the array with a lie.
    bit_array& reset ();

    //true if the array contains a true bit.
    bool any () const;

    //true if all bits of the array are false.
    bool none () const;
    
    //Bit inversion.
    bit_array operator~() const;

    //Counts the number of single bits.
    int count () const;

    //Returns the value of the bit at index i.
    bool operator[](int i) const;

    //returns the size of the array.
    int size () const;

    //true if the array is empty.
    bool empty() const;

    //Returns the string representation of the array.
    string to_string() const;
private:

    vector<unsigned long> array;

    int num_bits;   
    int num_elements;

    void sub_bits ();
};

bool operator==(const bit_array& a, const bit_array& b);
bool operator!=(const bit_array& a, const bit_array& b);

bit_array operator&(const bit_array& a, const bit_array& b);
bit_array operator|(const bit_array& a, const bit_array& b);
bit_array operator^(const bit_array& a, const bit_array &b);