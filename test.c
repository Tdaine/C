
#include"DoCommuntConvert.h"

const char *search = "C:\\Users\\dell\\Desktop\\bit";

void test(const char * search)
{
	char add[200];
	char add2[200];
	strcpy(add, search);
	strcpy(add2, search);
	strcat(add2, "c++");
	strcat(add, "\\*.c");
	mkdir(add2);
	long handle;
	struct _finddata_t fileinfo;
	handle = _findfirst(add, &fileinfo);
	if (-1 == handle)
		return 0;
	do
	{
			strcpy(add, search);
			strcpy(add2, search);
			strcat(add, "\\");
			strcat(add2, "c++\\");
			strcat(add, fileinfo.name);
			strcat(add2, fileinfo.name);
			test(add);
			FILE *PfIn = NULL;
			FILE *PfOut = NULL;
			PfIn = fopen(add, "r");
			PfOut = fopen(add2, "w");
			if (PfIn == NULL)
			{
				perror("read file:");
				fclose(PfIn);
				exit(EXIT_FAILURE);
			}
			if (PfOut == NULL)
			{
				perror("write file:");
				fclose(PfIn);
				exit(EXIT_FAILURE);
			}
			DoCommentConvert(PfIn, PfOut);
			fclose(PfIn);
			PfIn = NULL;
			fclose(PfOut);
			PfOut = NULL;
		
	}while (!_findnext(handle, &fileinfo));
	_findclose(handle);
	printf("转换成功\n");
}



int main()
{
	test(search);
	system("pause");
	return 0;
}

