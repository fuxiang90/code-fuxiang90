#include <iostream>
#include <set>
#include <iterator>
using namespace std;

int main()
{
	typedef multiset<int, greater<int> > IntSet;

	IntSet coll1;

	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	IntSet::iterator pos;
	for(pos = coll1.begin(); pos != coll1.end(); ++pos)
	{
		cout << *pos << ' ';
	}
	cout << endl;

	IntSet::iterator ipos = coll1.insert(4);
	cout << "4 inserted as element "
		 << distance(coll1.begin(), ipos) + 1
		 << endl;

	multiset<int> coll2(coll1.begin(), coll1.end());
	copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	coll2.erase(coll2.begin(), coll2.find(3));

	int num;
	num = coll2.erase(5);
	cout << num << " elements removed" << endl;

	copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
