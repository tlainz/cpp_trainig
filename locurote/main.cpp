#define CATCH_CONFIG_MAIN
//#include "catch.hpp"


#include <map>
#include <limits>
#include <iostream>

using namespace std;

template<typename K, typename V>
class interval_map {
public:
    std::map<K, V> m_map;

    V m_valBegin;
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val) {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd))
            return;

        typename std::map<K, V>::iterator iterBegin; /*The new begin with val, can be begin()*/
        typename std::map<K, V>::iterator iterEnd;   /*the new end of val, can be end()*/

        auto lowerKeyBegin = m_map.lower_bound(keyBegin); //either end() or some iter whose key is not less than keyBegin. [1st O(logN)]
        auto upperKeyEnd = m_map.upper_bound(keyEnd); //some iter where keyEnd < key, or end()  [2nd O(logN)]
        auto prevKeyEnd = std::prev(upperKeyEnd);

        /*
        The next interval of the new interval starts at keyEnd if the previous value at keyEnd differed from val
        */
        if (!(prevKeyEnd->second == val))
        {
            // prevKeyEnd is either less than the new end we are inserting, or the same (no update to avoid copying from erased node)
            if (!(prevKeyEnd->first < keyEnd) && !(keyEnd < prevKeyEnd->first))
                iterEnd = prevKeyEnd;
            else
                iterEnd = m_map.insert_or_assign(upperKeyEnd, keyEnd, prevKeyEnd->second);
        }
        else
        {
            iterEnd = upperKeyEnd;
        }

        /*
        The new interval starts at keyBegin if the would-be previous interval has a different value.
        Previous interval is either a key in the map less than keyBegin, or non-existent when lower_bound is m_map.begin()
        The new interval's start is merged with previous interval, if the previous interval has the same value.
        */
        if (lowerKeyBegin != m_map.begin())
        {
            auto prevIter = std::prev(lowerKeyBegin); //safe when end(), because we always have at least one value
            if (!(prevIter->second == val))
            {
                iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
            }
            else iterBegin = prevIter;
        }
        else
        {
            iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
        }

        /*
        Erase all keys between the new begin and end (excluding) so that there is only one value after iterBegin
        This is fine when iterEnd is end()
        */
        {
            auto nextIterOfBegin = std::next(iterBegin);//somehow msvc doesn't support if-initialization
            if (nextIterOfBegin != m_map.end())
            {
                //I would be very interested in a smarter way to get rid of this part without additional storage ...
                m_map.erase(nextIterOfBegin, iterEnd);
            }
        }

        ////debug - check canonical
        //for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
        //{
        //  auto next = std::next(iter);
        //  if (next != m_map.end() && iter->second == next->second)
        //  {
        //      throw;
        //  }
        //}
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        return (--m_map.upper_bound(key))->second;
    }

    void print() {
        cout << "\n" << m_valBegin << "\n";
        for (auto it = m_map.begin(); it != m_map.end(); ++it) {
            std::cout << it->first << ", " << it->second << "\n";
        }
    }

};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.

struct TestKeyType
{
    unsigned int val;
    constexpr TestKeyType(unsigned int val) : val(val) {}
    constexpr bool operator<(const TestKeyType& other) const { return val < other.val; }
};

namespace std {
    template<> class numeric_limits<TestKeyType> {
    public:
        static constexpr TestKeyType lowest() { return TestKeyType(numeric_limits<unsigned int>::lowest()); }
        //static constexpr TestKeyType lowest() { return TestKeyType(-250); }
    };
}

using TestValueType = char;

struct TestFloatKeyType
{
    float val;

    TestFloatKeyType() = default;

    TestFloatKeyType(float val) : val(val) {}
    bool operator< (TestFloatKeyType other) const
    {
        return other.val - val > 1.e-4f;
    }
};

namespace std {
    template<> class numeric_limits<TestFloatKeyType> {
    public:
        static TestFloatKeyType lowest() { return TestFloatKeyType(numeric_limits<float>::lowest()); }
    };
}
/*
TEST_CASE("EmptyRange")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 3, 'B');
    REQUIRE(m.m_map.count(3) == 0);

    m.assign(3, 2, 'B');
    REQUIRE(m.m_map.count(2) == 0);
    REQUIRE(m.m_map.count(3) == 0);
}


TEST_CASE("TrivialRange")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 10, 'B');
    REQUIRE(m[0] == 'A');
    for (int i = 1; i < 10; i++)
    {
        REQUIRE(m[i] == 'B');
    }
    REQUIRE(m[10] == 'A');
}

TEST_CASE("TrivialTwoRange")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 3, 'B');
    m.assign(6, 8, 'C');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
    REQUIRE(m[6] == 'C');
    REQUIRE(m[7] == 'C');
    REQUIRE(m[8] == 'A');
}

TEST_CASE("OverwriteLowest")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(std::numeric_limits<TestKeyType>::lowest(), 10000, 'B');
    REQUIRE(m[0] == 'B');
    REQUIRE(m[9999] == 'B');
    REQUIRE(m[10000] == 'A');
}

TEST_CASE("Merge")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(std::numeric_limits<TestKeyType>::lowest(), 10, 'B');
    m.assign(10, 20, 'B');
    REQUIRE(m[0] == 'B');
    REQUIRE(m[10] == 'B');
    REQUIRE(m[19] == 'B');
    REQUIRE(m[20] == 'A');
}

TEST_CASE("FloatKey")
{
    interval_map<TestFloatKeyType, TestValueType> m('A');
    m.assign(1.f, 5.f, 'B');
    REQUIRE(m[0.f] == 'A');
    REQUIRE(m[.999999999f] == 'B');
    REQUIRE(m[1.f] == 'B');
    REQUIRE(m[4.999f] == 'B');
    REQUIRE(m[5.f] == 'A');

}

TEST_CASE("OverlappingRangeComplete")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 5, 'B');
    m.assign(1, 6, 'C');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'C');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'C');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeInner")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 6, 'C');
    m.assign(3, 5, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'C');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeSmallToLarge")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'C');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'C');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeLargeToSmall")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 6, 'C');
    m.assign(1, 5, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("ExtendingRangeBegin")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 5, 'B');
    m.assign(1, 4, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("ExtendingRangeEnd")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'B');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("ExtendingRangeBothBeginEnd")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(2, 3, 'B');
    m.assign(1, 5, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("OverwriteEndValueSafety")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(2, 5, 'B');
    m.assign(5, 8, 'C');
    m.assign(4, 5, 'A');
}

TEST_CASE("ReusingExistingRangeBothBeginEnd")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(2, 3, 'B');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("ReusingEnd")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(4, 6, 'A');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("RestoringInitial")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(1, 5, 'A');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'A');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("RestoringInitial2")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(0, 7, 'A');
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'A');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("VeryComplex")
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 6, 'B');
    m.assign(2, 5, 'C');
    m.assign(4, 7, 'A');

    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
    REQUIRE(m[6] == 'A');
    REQUIRE(m[7] == 'A');
}
*/
int main() {
    interval_map<int, char> mymap{ 'a' };

    //mymap.assign({ {10,'c'},{20,'a'},{30,'c'},{40,'i'},{50,'c'},{60,'i'} });
    //mymap.assign(65, 68, 'z');    mymap.print();

    while (1)
    {
        mymap.print();

        int start, endK;
        char ch;

        std::cout << "\n\n Enter start, end, char: ";
        std::cin >> start >> endK >> ch;

        mymap.assign(start, endK, ch);
    }

}
