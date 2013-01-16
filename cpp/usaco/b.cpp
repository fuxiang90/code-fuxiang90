#include<iostream>
#include<string>
using namespace std;
typedef struct stack
{
    char path[1003];
    int len;
} stack;
int insert(string s,stack* st)
{
    st->len++;
    st->path[1]='/';
    int k=1;
    for(int i=1; i<s.length();)
    {
        if(s[k]=='/' && s[i+1]=='.' && s[i+2]=='/')
        {
//st->len++;
//st->path[st->len]=s[i];
            i+=2;
        }
        else if(s[k]=='/' && s[i+1]=='.' && s[i+2]=='.' && s[i+3]=='/')
        {
            for(int j=st->len; st->path[j]!='/' && st->len>=1; j--)
            {
                st->len--;
            }
            i+=3;
        }
        else
        {
            st->len++;
//cout<<st->len<<endl;
            st->path[st->len]=s[i];
            i++;
            k=i;
        }
    }
    return 0;
}
int main()
{
    int n;
    int i,j;


    cin>>n;
    for(i=1; i<=n; i++)
    {
        string s;
        cin>>s;
        stack* st=NULL;
        st=(stack *)malloc(sizeof(stack));
        st->len=0;
        insert(s,st);
        for(j=1; j<=st->len; j++)
        {
            cout<<st->path[j];
        }
        cout<<endl;
    }
    return 0;
}
