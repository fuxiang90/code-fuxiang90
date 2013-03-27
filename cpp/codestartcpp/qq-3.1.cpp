#include<iostream>
using namespace std;
int main()
{
	int HH,MM,SS,hh,mm,ss;
	char c;
	int i=0;
	int t;
	cin>>t;
	while(i<t)
	{
		cin>>HH>>c>>MM>>c>>SS;
		cin>>hh>>c>>mm>>c>>ss;
		int sum1=HH*3600+MM*60+SS;
		int sum2=(hh%12)*3600+mm*60+ss;
		sum1+=(12*3600);
		int sum3=sum1-sum2;
		sum3%=(12*3600);
		HH=sum3/3600;
		sum3 -= HH*3600;
		MM=(sum3%3600)/60;
		sum3 -= MM*60;
		SS=sum3%60;
		if(HH<10)
			cout<<0;
		cout<<HH<<':';
	    if(MM<10)
		    cout<<0;
	    cout<<MM<<':';
	    if(SS<10)
		    cout<<0;
	    cout<<SS<<endl;
		i++;
	}
}
