#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>

#include <stdint.h>
using namespace std;

bool IsUTF8(const void* pBuffer, long size)
{
    bool IsUTF8 = true;
    unsigned char* start = (unsigned char*)pBuffer;
    unsigned char* end = (unsigned char*)pBuffer + size;
    while (start < end)
    {
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
        {
            start++;
            IsUTF8 = false;
            break;
        }
        else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
        {
            IsUTF8 = false;
            break;
        }
        else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
        {
            if (start >= end - 1)
                break;
            if ((start[1] & (0xC0)) != 0x80)
            {
                IsUTF8 = false;
                break;
            }
            start += 2;
        }
        else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符
        {
            if (start >= end - 2)
                break;
            if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
            {
                IsUTF8 = false;
                break;
            }
            start += 3;
        }
        else
        {
            IsUTF8 = false;
            break;
        }
    }
    return IsUTF8;
}

void getChiString(const char *Chi, string &Pointer2Str)
{
    register int i, j;
    int len;
    stringstream ss;

    len = strlen(Chi);

    for (j = 0, i = 0; i < len; i ++)
    {
        if (IsUTF8(Chi + i ,3) == true)
        {
            printf("ok");
            ss << j++ << ".";
            ss << string(Chi + i, 3) << " ";
            i +=2;
        }
        else {
            ss << j++ << ".";
            ss << string(Chi + i,1) << " ";
        }

    }

    Pointer2Str = ss.str();
}

int main()
{
    string str;

    unsigned char test[] = "你好,中国";

    unsigned char *pstr = (unsigned char *)test;

    printf("%02x", *pstr);

    int8_t test2[20];

    memcpy(test2,test,sizeof(test));

    cout << sizeof(char) << " " << sizeof(int) << endl ;


    for(int i = 0 ; i < sizeof(test) ; i ++){
        //test2 =
        printf("%x\n",test[i]);
    }

    cout << sizeof(int) <<endl;
    cout << sizeof (test[0]) <<endl;
    cout << sizeof (test) <<endl;
    cout <<test <<endl;
    getChiString(test, str);
    cout << str << endl;


    return 0;

}

