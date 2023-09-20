#ifndef __MYHASHTABLE_H__
#define __MYHASHTABLE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>

#include "MyVector_k221j976.h"
#include "MyLinkedList_k221j976.h"

static const long long uh_param_a = 53;       // universal hash function parameter a
static const long long uh_param_b = 97;       // universal hash function parameter b
static const long long prime_digits = 19;     // parameter used for finding a Mersenne prime
static const long long mersenne_prime = (1 << prime_digits) - 1;  // the Mersenne prime for universal hashing

// fast calculation of (n modulo mersenne_prime)
long long fastMersenneModulo(const long long n)
{
    // code begins
    return (n & mersenne_prime) + (n >> prime_digits);
    // code ends
}

// definition of the template hash function class
template <typename KeyType>
class HashFunc
{
  public:
    long long univHash(const KeyType key, const long long table_size) const;
};

// the hash function class that supports the hashing of the "long long" data type
template <>
class HashFunc<long long>
{
  public:
    long long univHash(const long long key, const long long table_size) const
    {
        long long hv = fastMersenneModulo(static_cast<long long>(uh_param_a * key + uh_param_b));
        hv = hv % table_size;
        return hv;
    }
};

// the has function class that supports the hashing of the "std::string" data type
template <>
class HashFunc<std::string>
{
  private:
    const int param_base = 37;      // the base used for inflating each character
  public:    
    long long univHash(const std::string& key, const long long table_size) const
    {
        long long hv = 0;
        for(size_t i = 0; i < key.length(); ++ i)
        {
            hv = param_base * hv + static_cast<long long>(key[i]);
        }
        hv = fastMersenneModulo(static_cast<long long>(uh_param_a * hv + uh_param_b));
        hv = hv % table_size;
        return hv;
    }
};

// definition of the template hashed object class
template <typename KeyType, typename ValueType>
class HashedObj
{
  public:

    KeyType key;
    ValueType value;

    HashedObj()
    {
        return;
    }

    HashedObj(const KeyType& k, const ValueType& v) :
        key(k),
        value(v)
    {
        return;
    }
  
    HashedObj(KeyType && k, ValueType && v) :
        key(std::move(k)),
        value(std::move(v))
    {
        return;
    }

    bool operator==(const HashedObj<KeyType, ValueType>& rhs)
    {
        return (key == rhs.key);
    }    

    bool operator!=(const HashedObj<KeyType, ValueType>& rhs)
    {
        return !(*this == rhs);
    }   

};

template <typename KeyType, typename ValueType>
class MyHashTable
{ 
  private:
    size_t theSize; // the number of data elements stored in the hash table
    MyVector<MyLinkedList<HashedObj<KeyType, ValueType> >* > hash_table;    // the hash table implementing the separate chaining approach
    MyVector<size_t> primes;    // a set of precomputed and sorted prime numbers

    // pre-calculate a set of primes using the sieve of Eratosthenes algorithm
    // will be called if table doubling requires a larger prime number for table size
    // expected to update the private member "primes"
    void preCalPrimes(const size_t n)
    {
        // code begins
          //      std::cout<<"precalprimes\n";
        MyVector<bool> prbool(n+1);
        for(int i=0; i<=n; i++){
            prbool[i] = true;}
        prbool[0] = prbool[1] = false;
        for(int i = 2; i*i <= n; i++){
            if (prbool[i] and (long long)i *i <=n){
                for (int j = i*i; j <= n; j+= i){
                    prbool[j] = false;
                }
            }
        }
        for(int i=2; i <= n; i++){
            if (prbool[i] == true){
                primes.push_back(i);
            }
        }
 
        // code ends
    }

    // finding the smallest prime that is larger than or equal to n
    // should perform binary search against the private member "primes"
    size_t nextPrime(const size_t n)
    {
        // code begins;
        preCalPrimes(n+100);

        int baseprime=0, high= primes.size()-1;
        while (baseprime <= high){
            int midprimes = (baseprime+high)/2;
            if (primes[midprimes] < n){
                baseprime = midprimes +1;
            }
            else if (primes[midprimes] > n){
                high = midprimes-1;
            }
            else if (primes[midprimes] == n){
                return primes[midprimes];
            }
        }
        return primes[baseprime];

        // code ends
    }

    // finds the MyLinkedList itertor that corresponds to the hashed object that has the specified key
    // returns the end() iterator if not found
    typename MyLinkedList<HashedObj<KeyType, ValueType> >::iterator find(const KeyType& key)
    {
        // code begins
        HashFunc<KeyType> function;
        long long num = function.univHash(key, capacity());        
        MyLinkedList<HashedObj<KeyType, ValueType> > * whichList = hash_table[num];      
        typename MyLinkedList<HashedObj<KeyType, ValueType>>::iterator itr; 
        if (whichList->empty() == true){
            return whichList->end();}
        for(itr= whichList->begin(); itr != whichList->end(); itr++){
            if ((*itr).key == key){
                return itr;
            }
        }
        return whichList->end();        
        
        
    }

    // rehashes all data elements in the hash table into a new hash table with new_size
    // note that the new_size can be either smaller or larger than the existing size
    void rehash(const size_t new_size)
    {
        // code begins
        MyVector<MyLinkedList<HashedObj<KeyType, ValueType> >* > newtable = hash_table;
        for(int i=0; i<newtable.capacity(); i++){
            newtable[i] = hash_table[i];}
        if (new_size >= 16){
            hash_table.reserve(new_size);}
        else{
            hash_table.reserve(17);}
        for (int i=0; i<hash_table.capacity(); i++){
            hash_table[i] = new MyLinkedList<HashedObj<KeyType, ValueType>>;}
        while(hash_table.empty() == false){
            hash_table.remove(0);
        }
                theSize = 0;
        typename MyLinkedList<HashedObj<KeyType, ValueType>>::iterator itr;        
        for(int i=0; i<newtable.capacity();i++)   {  
            MyLinkedList<HashedObj<KeyType, ValueType> > * lists = newtable[i];
            if( lists->empty() == true){
                continue;}            
            for (itr = lists->begin(); itr != lists->end();itr++){
            insert(std::move(*itr));}}    
    }

    // doubles the size of the table and perform rehashing
    // the new table size should be the smallest prime that is larger than the expected new table size (double of the old size)
    void doubleTable()
    {
        size_t new_size = nextPrime(2 * hash_table.capacity());
        //size_t new_size = nextPrime(2 * hash_table.size());
        this->rehash(new_size);
        return;
    }

    // halves the size of the table and perform rehahsing
    // the new table size should be the smallest prime that is larger than the expected new table size (half of the old size)
    void halveTable()
    {
        size_t new_size = nextPrime(ceil(hash_table.capacity() / 2));
        this->rehash(new_size);
        return;
    }

  public:

    // the default constructor; allocate memory if necessary
    explicit MyHashTable(const size_t init_size = 3)
    {
        // code begins

        hash_table.reserve(init_size);
        for (int i=0; i<init_size; i++){
            hash_table[i] = new MyLinkedList<HashedObj<KeyType, ValueType>>;
        }        
        // code ends
    }

    // the default destructor; collect memory if necessary
    ~MyHashTable()
    {
        // code begins

        // code ends
    }

    // checks if the hash tabel contains the given key
    bool contains(const KeyType& key)
    {
        // code begins
        HashFunc<KeyType> getlist;
        auto & whichList = hash_table[ getlist.univHash(key, hash_table.capacity()) ];
        return find(key) != whichList->end();
        // code ends
    }

    bool retrieve(const KeyType& key, HashedObj<KeyType, ValueType>& data)
    {
        HashFunc<KeyType> getlist;
        auto& whichList = hash_table[getlist.univHash(key, hash_table.capacity())];

        for (auto itr = whichList->begin(); itr != whichList->end(); ++itr) {
            if ((*itr).key == key) {
                data = *itr;
                return true;
            }
        }

        return false;
    }


    bool insert(const HashedObj<KeyType, ValueType>& x)
    {
        // code begins
        
        HashFunc<KeyType> getlists;
        auto & whichList = hash_table[ getlists.univHash(x.key, hash_table.capacity()) ];
        if(contains(x.key) != false){
            return false;
        }
        whichList->push_back(x);
        theSize++;
        if( theSize > hash_table.capacity()/2){
            doubleTable();
        }
            
        
        return true;
        // code ends
    }

    // inserts the given data element into the hash table (move)
    // returns true if the key is not contained in the hash table
    // return false otherwise
    bool insert(HashedObj<KeyType, ValueType> && x)
    {
        HashFunc<KeyType> getlists;
        auto & whichList = hash_table[ getlists.univHash(x.key, hash_table.capacity()) ];
        if(contains(x.key) != false){
            return false;
        }
        whichList->push_back(x);
        theSize++;
        if( theSize > hash_table.capacity()/2){
            doubleTable();
        }

        return true;
        // code ends
    }

    // removes the data element that has the key from the hash table
    // returns true if the key is contained in the hash table
    // returns false otherwise
    bool remove(const KeyType& key)
    {
        // code begins;
        HashFunc<KeyType> index;
        auto & whichList = hash_table[index.univHash(key, hash_table.capacity())]; 
        typename MyLinkedList<HashedObj<KeyType, ValueType>>::iterator itr = find(key);
        if(itr == whichList->end()){
            return false;}
        whichList->erase(itr);
        if(--theSize <= (hash_table.capacity()/8)){
            halveTable();
        }
        return true;
        
        
    }

    // returns the number of data elements stored in the hash table
    size_t size()
    {
        // code begins
        return theSize;
        // code ends
    }

    // returns the capacity of the hash table
    size_t capacity()
    {
        // code begins;
        return hash_table.capacity();
        // code ends
    }

};


#endif // __MYHASHTABLE_H__