#include <map>
#include <limits>
#include <cassert>
#include <vector>
#include <stdlib.h>
#include <iostream>


using namespace std;

template<typename K, typename V>

class interval_map {

	friend void IntervalMapTest();

	V m_valBegin;

    protected:
	std::map<K,V> m_map;

public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	{
	    m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {

	    if(!(keyBegin < keyEnd)) return;

 	    auto iterationUp = --m_map.upper_bound(keyEnd);
        auto mapBegin= m_map.end();
        auto mapEnd = m_map.end();

        if(iterationUp->second == val) {
           // cout<<"Contained Value";
            return;
        }
        else if(iterationUp->first < keyEnd)
        {
            V const& value = iterationUp->second;
            ++iterationUp;
            mapEnd = iterationUp = m_map.emplace_hint(iterationUp,keyEnd,value);
        }
        try
        {
            auto iterationDown = iterationUp;
            --iterationDown;
            if(keyBegin < iterationDown->first) iterationDown = --m_map.upper_bound(keyBegin);
            if(!(iterationDown->second == val))
            {
                if(iterationDown->first < keyBegin)
                {
                    ++iterationDown;
                    mapBegin= iterationDown = m_map.emplace_hint(iterationDown,keyBegin,val);
                }
                else
                {
                    iterationDown->second=val;

                    if(iterationDown!= m_map.begin() && !((--iterationDown)->second == val)) ++iterationDown;

                    else
                    {
                        auto hint = m_map.erase(iterationDown);
                        mapBegin=iterationDown = m_map.emplace_hint(hint,keyBegin,val);
                    }
                }
            }
            assert(iterationDown != m_map.end());
            m_map.erase(++iterationDown, iterationUp);
        }
       catch(...)
       {
            if(mapEnd != m_map.end()) m_map.erase(mapEnd);
            if(mapBegin != m_map.end()) m_map.erase(mapBegin);
            throw;
       }
    }

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
	int begin(){
        return m_map.begin();
	}
	int end(){
        return m_map.end();
	}
///*
	void print() {
       // cout << "\n" << m_valBegin << "\n";
        for (auto it = m_map.begin(); it != m_map.end(); ++it) {
            std::cout << it->first << ", " << it->second << "\n";
        }
    }
  //  */
};

int main()
{
    interval_map<int, char> mymap{ 'a' };
    int r;
    char val;
    for (int i = 0; i < 10; ++i)
        {
            r= rand()%26;
            val = 'a'+ r;

            mymap.assign(rand() % 256, rand() % 256, val);
            mymap.print();
            system("Pause");
        }
/*
    map<int, char>::iterator iter;

    for(iter = mymap.begin(); iter!=mymap.end();iter++)
    {
        cout<<"Key= "<<iter->first<<"; Value: "<<iter->second<<endl;
    }
*/
    system("Pause");
    return 0;
}


/*
int main() {
    interval_map<int, char> mymap{ 'a' };

    //mymap.assign({ {10,'c'},{20,'a'},{30,'c'},{40,'i'},{50,'c'},{60,'i'} });
    mymap.assign(65, 68, 'z');    //mymap.print();

    while (1)
    {
        /*
        mymap.print();

        int start, endK;
        char ch;

        std::cout << "\n\n Enter start, end, char: ";
        std::cin >> start >> endK >> ch;
        mymap.assign(start, endK, ch);
    }

}*/
