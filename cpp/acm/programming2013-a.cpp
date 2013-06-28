#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
int n,m;
int main()
{
    freopen("in","r",stdin);
    int t;
    scanf("%d",&t);
    char str[110];
    char str_2[110];
    for(int i = 1 ; i <= t ; i ++){
        map<string ,string > str_map;
        vector<string > str_vec;
        scanf("%d%d",&n,&m);
        //do{scanf("%s",str);}while(getchar()!='\n');

        for(int j = 1 ; j <= m ; j ++){
            scanf("%s%s",str,str_2);
            str_map.insert(map<string,string >::value_type(str,str_2));
        }
        //do{scanf("%s",str);}while(getchar()!='\n');
        do{
            scanf("%s",str);
            str_vec.push_back(str);
        }while(getchar()!='\n');
        int len = str_vec.size();
        for(int j = 1 ; j < n ; j ++){
            for(int k = 0 ; k < len ; k ++){
                string  &str_temp = str_vec[k];
                map<string ,string>::iterator iter = str_map.find(str_temp);
                if(iter != str_map.end()){
                    str_vec[k] = iter->second;
                }
            }
        }
        printf("Case #%d:",i);
        for(int j = 0 ; j < str_vec.size() ; j ++){
            printf(" %s",str_vec[j].c_str());
        }
        printf("\n");

    }
	return 0;
}
