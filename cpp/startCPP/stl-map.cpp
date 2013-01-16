#include<string>
#include<iostream>
#include<map>
#include<fstream>
using namespace std;

struct person
{
	string name;
	int age;

	person(string name, int age)
	{
		this->name =  name;
		this->age = age;
	}

	bool operator== (const person& p) const
	{
		return name==p.name && age==p.age;
	}
    bool operator <  (const person& p) const
	{
        if (name == p.name) return age < p.age;
		return name < p.name ;
	}
};


int main()
{

	typedef map<person,int> umap;
	umap m;
	person p1("Tom1",20);
	person p2("zsdasd",22);
	person p3("ojisdjkashd",22);
	person p4("Thhjjhjhh",23);
	person p5("linux",24);
	m.insert(umap::value_type(p3, 100));
	m.insert(umap::value_type(p4, 100));
	m.insert(umap::value_type(p5, 100));
	m.insert(umap::value_type(p1, 100));
	m.insert(umap::value_type(p2, 100));

    fstream fin("fterms.dic");
    string s;
    int ans = 1;
    while(fin>>s)
    {
        person p(s,20);
        m.insert(umap::value_type(p, ans ++ ));

    }

    person p6("Tom2",20);
    double start = clock();
    for(int i = 1 ; i <= 100000 ; i ++){
        if(m.find(p2) != m.end()){
            //cout << m.find(p2)->second<<endl;
        }
        if(m.find(p6) != m.end()){
            //cout << m.find(p2)->second<<endl;
        }

    }
    double end = clock();
    printf(" query time is %lf\n ", (double)(end-start)/CLOCKS_PER_SEC );
	//mm.insert(boost::unordered_map< <pair<int ,int>,int>::value_type(make_pair(12,24) ,1) );


	return 0;
}
