#include <stdio.h>
#include <string.h>

int *(strch)(const char *s, int c)
{
	
	char h=c;
	int count=0;
	while(*s!= '\0' && *s!=h)
	{
		s++;
		count++;
	}
	return count;
}

int main () {
	const char str[] = "http://www.tutorialspoint.com";
	const char ch = 'i';
	int *ret;
	char *s=str;
	ret = strch(str, ch);
	while(

	printf("String after |%c| is - |%d|\n", ch, ret);
	
//	printf("String after |%c| is -%%c  %d\n", ch, ret);
	
	return(0);
}
