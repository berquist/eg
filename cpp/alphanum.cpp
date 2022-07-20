#ifdef NDEBUG
#undef NDEBUG
#endif

#include "alphanum.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <cstring>

int main()
{
    // testcases for the algorithm
    assert(doj::alphanum_comp("","") == 0);
    assert(doj::alphanum_comp("","a") < 0);
    assert(doj::alphanum_comp("a","") > 0);
    assert(doj::alphanum_comp("a","a") == 0);
    assert(doj::alphanum_comp("","9") < 0);
    assert(doj::alphanum_comp("9","") > 0);
    assert(doj::alphanum_comp("1","1") == 0);
    assert(doj::alphanum_comp("1","2") < 0);
    assert(doj::alphanum_comp("3","2") > 0);
    assert(doj::alphanum_comp("a1","a1") == 0);
    assert(doj::alphanum_comp("a1","a2") < 0);
    assert(doj::alphanum_comp("a2","a1") > 0);
    assert(doj::alphanum_comp("a1a2","a1a3") < 0);
    assert(doj::alphanum_comp("a1a2","a1a0") > 0);
    assert(doj::alphanum_comp("134","122") > 0);
    assert(doj::alphanum_comp("12a3","12a3") == 0);
    assert(doj::alphanum_comp("12a1","12a0") > 0);
    assert(doj::alphanum_comp("12a1","12a2") < 0);
    assert(doj::alphanum_comp("a","aa") < 0);
    assert(doj::alphanum_comp("aaa","aa") > 0);
    assert(doj::alphanum_comp("Alpha 2","Alpha 2") == 0);
    assert(doj::alphanum_comp("Alpha 2","Alpha 2A") < 0);
    assert(doj::alphanum_comp("Alpha 2 B","Alpha 2") > 0);

    assert(doj::alphanum_comp(1,1) == 0);
    assert(doj::alphanum_comp(1,2) < 0);
    assert(doj::alphanum_comp(2,1) > 0);
    assert(doj::alphanum_comp(1.2,3.14) < 0);
    assert(doj::alphanum_comp(3.14,2.71) > 0);
    assert(doj::alphanum_comp(true,true) == 0);
    assert(doj::alphanum_comp(true,false) > 0);
    assert(doj::alphanum_comp(false,true) < 0);

    std::string str("Alpha 2");
    assert(doj::alphanum_comp(str,"Alpha 2") == 0);
    assert(doj::alphanum_comp(str,"Alpha 2A") < 0);
    assert(doj::alphanum_comp("Alpha 2 B",str) > 0);

    assert(doj::alphanum_comp(str,strdup("Alpha 2")) == 0);
    assert(doj::alphanum_comp(str,strdup("Alpha 2A")) < 0);
    assert(doj::alphanum_comp(strdup("Alpha 2 B"),str) > 0);

#if 1
    // show usage of the comparison functor with a set
    std::set<std::string, doj::alphanum_less<std::string> > s;
    s.insert("Xiph Xlater 58");
    s.insert("Xiph Xlater 5000");
    s.insert("Xiph Xlater 500");
    s.insert("Xiph Xlater 50");
    s.insert("Xiph Xlater 5");
    s.insert("Xiph Xlater 40");
    s.insert("Xiph Xlater 300");
    s.insert("Xiph Xlater 2000");
    s.insert("Xiph Xlater 10000");
    s.insert("QRS-62F Intrinsia Machine");
    s.insert("QRS-62 Intrinsia Machine");
    s.insert("QRS-60F Intrinsia Machine");
    s.insert("QRS-60 Intrinsia Machine");
    s.insert("Callisto Morphamax 7000 SE2");
    s.insert("Callisto Morphamax 7000 SE");
    s.insert("Callisto Morphamax 7000");
    s.insert("Callisto Morphamax 700");
    s.insert("Callisto Morphamax 600");
    s.insert("Callisto Morphamax 5000");
    s.insert("Callisto Morphamax 500");
    s.insert("Callisto Morphamax");
    s.insert("Alpha 2A-900");
    s.insert("Alpha 2A-8000");
    s.insert("Alpha 2A");
    s.insert("Alpha 200");
    s.insert("Alpha 2");
    s.insert("Alpha 100");
    s.insert("Allegia 60 Clasteron");
    s.insert("Allegia 52 Clasteron");
    s.insert("Allegia 51B Clasteron");
    s.insert("Allegia 51 Clasteron");
    s.insert("Allegia 500 Clasteron");
    s.insert("Allegia 50 Clasteron");
    s.insert("40X Radonius");
    s.insert("30X Radonius");
    s.insert("20X Radonius Prime");
    s.insert("20X Radonius");
    s.insert("200X Radonius");
    s.insert("10X Radonius");
    s.insert("1000X Radonius Maximus");
    // print sorted set to cout
    std::copy(s.begin(), s.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

    // show usage of comparision functor with a map
    typedef std::map<std::string, int, doj::alphanum_less<std::string> > m_t;
    m_t m;
    m["z1.doc"]=1;
    m["z10.doc"]=2;
    m["z100.doc"]=3;
    m["z101.doc"]=4;
    m["z102.doc"]=5;
    m["z11.doc"]=6;
    m["z12.doc"]=7;
    m["z13.doc"]=8;
    m["z14.doc"]=9;
    m["z15.doc"]=10;
    m["z16.doc"]=11;
    m["z17.doc"]=12;
    m["z18.doc"]=13;
    m["z19.doc"]=14;
    m["z2.doc"]=15;
    m["z20.doc"]=16;
    m["z3.doc"]=17;
    m["z4.doc"]=18;
    m["z5.doc"]=19;
    m["z6.doc"]=20;
    m["z7.doc"]=21;
    m["z8.doc"]=22;
    m["z9.doc"]=23;
    // print sorted map to cout
    for(m_t::iterator i=m.begin(); i!=m.end(); ++i)
        std::cout << i->first << '\t' << i->second << std::endl;

    // show usage of comparison functor with an STL algorithm on a vector
    std::vector<std::string> v;
    // vector contents are reversed sorted contents of the old set
    std::copy(s.rbegin(), s.rend(), std::back_inserter(v));
    // now sort the vector with the algorithm
    std::sort(v.begin(), v.end(), doj::alphanum_less<std::string>());
    // and print the vector to cout
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
#endif

    return 0;
}
