#include <iostream>
using namespace std;

struct point
{
    int poi[8];
} temp;

char map[9][7];
int len[9];
int Min;
char DNA[] = {'A', 'C', 'G', 'T'};
int n;

int dfs(point tp, int sum, int depth)
{
    int i, j;
    point temp;

    if(sum > depth)
        return 0;

    for(i = 0; i < n; i++)
    {
        if( len[i] - tp.poi[i] + sum > depth)
            return 0;
    }

    for(i = 0; i < n; i++)
    {
        if(map[i][ tp.poi[i] ])
            break;
    }

    if(i == n)
    {
        return 1;
    }

    int flag;
    for(i = 0; i < 4; i++)
    {
        flag = 0;
        for(j = 0; j < n; j++)
        {

            if(map[j][ tp.poi[j] ] == DNA[i])
            {
                flag = 1;
                temp.poi[j] = tp.poi[j] + 1;
            }
            else
                temp.poi[j] = tp.poi[j];
        }
        if(flag)
            if ( dfs(temp, sum + 1, depth) )
                return 1;
    }

    return 0;
}

int main()
{
    int t, i;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
        {
            scanf("%s", map[i]);
            len[i] = strlen(map[i]);
        }
        for(i = 0; i < n; i++)
        {
            temp.poi[i] = 0;
        }

        for(i = 1; ; i++)
        {
            if( dfs(temp, 0, i) )
                break;
        }

        printf("%d\n", i);
    }
    return 0;
}

