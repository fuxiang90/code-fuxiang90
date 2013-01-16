#include<string>
#include<iostream>
#include<map>
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;

int main()
{
      short test = 31767;
      FILE* fp = fopen("1.bin", "wb");

      printf("%d   %d   %d\n", test, (test >> 8) ,sizeof(int));
      fprintf(fp, "%c%c", test, (test >> 8));
// = fwrite(&test, sizeof(short), 1, fp);

// 用这种方法来存储可以通过fread读出来无误
      fflush(fp);
      //重新打开
      fclose(fp);
      fp = fopen("1.bin", "rb");

      fread(&test, sizeof(short), 1, fp);
      printf("%d", test);
      fclose(fp);

      return 0;
}
