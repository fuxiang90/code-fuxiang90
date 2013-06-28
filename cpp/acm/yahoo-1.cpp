#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

int a,b,m,d;

int isOk(vector<int> & vec)
{
    int n = vec.size();
    int d = vec[n-1];
    int pos = n-1;
    int pos2 = -1;
    int pos3 = -1;
    pos --;
    if(pos >= 0){
        while(pos >= 0 && vec[pos] != d)
            pos --;
        if(pos >=0 && vec[pos] == d)
            pos2 = pos ;
        else
            return 0;
        pos --;
        while(pos >= 0 && vec[pos] != d)
            pos --;
        if(pos >=0 && vec[pos] == d)
            pos3 = pos ;
        else
            return 0;
    }
    for(int i = pos3  ; i < pos2 ; i ++){
        if(vec[i] != vec[pos2 +i]) return 0;
    }

    if(pos3 != -1 && pos2 != -1 && pos3 < pos2  &&  pos2 < n) return pos2;
    return 0;

}
int main()
{
    freopen("in","r",stdin);
    int t;
    scanf("%d",&t);

    for(int i = 1 ; i <= t ; i ++){
        scanf("%d%d%d%d",&a,&b,&m,&d);
        int pos = 0;
        int sum = 0;
        int c = 0;
        a = a%b;
        a *= 10;
        int j = 1;
        set<int> d_set;
        vector<int> vec;
        int old_sum = 0;
        int times = 0;

        int flag_num = -1;
        while(sum < m){
            c = a/b;

            vec.push_back(c);


            if(c == d ){
                pos  = j;
                sum ++;
            }
            if(c*b == a ){
                break;
            }
            if(d_set.find(c) ==  d_set.end()){
                d_set.insert(c);
            }else {
                int pos = isOk(vec);
                if(pos && vec[pos] != 0 ){
                    int flag = 0;
                    for(int i = pos+1 ; i < vec.size() ; i ++ ){
                        if(vec[i] == d){
                            flag = 1;
                            break ;
                        }
                    }
                    if(flag == 0 )
                        break;

                }
            }
            a = (a- c*b)*10;

            j++;
        }

        printf("%d\n",pos);

    }
	return 0;
}
