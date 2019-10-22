#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bt-5.0.0/inc/btree.h"


int main()
{
    int i, n, size;
    long sdt;
    char name[80];
    BTA * book;
    btinit();
    book = btopn("mybook", 0, 0);
    if (!book) {
        printf("Create my book\n");
	book = btcrt("mybook", 0, 0);
        printf("Inseet data\n");
        sdt = 983456789;
        if ( btins(book, "Dung", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Dung\n");
        sdt = 544545454;
        if ( btins(book, "Thang", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Thang\n");
        sdt = 466565656;
        if ( btins(book, "Huong", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Huong\n");
        sdt = 545454555;
        if ( btins(book, "Anh", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Anh\n");
    }
	
    do
    {
        printf("1.Add phone\n2.Search phone\n3.Print list\n4.Exit\nYour choice:");
        scanf("%d",&n);
        while (getchar()!='\n');
        switch(n){
              case 1:
                   printf("Name:");
                   gets(name);
                   printf("Number:");
                   scanf("%d",&sdt);
                   while (getchar()!='\n');
                   btins(book, name, (char*)&sdt, sizeof(long)); 
                   break;
              case 2:
                   printf("Name:");
                   gets(name);
                   if ( btsel(book, name, (char*)&sdt, sizeof(long), &size) ) 
			printf("Not found number for %s!\n", name);
                   else 
			printf("Phone number of %s is %d\n", name, sdt);
                   break;
              case 3:
                   btsel(book, "", (char*)&sdt, sizeof(long), &size);
		   while ( btseln(book, name, (char*)&sdt, sizeof(long), &size)==0 ) {
			printf("%s\t%10d\n", name, sdt);
                   }	
                   break;
              case 4:
                   btcls(book);
                   break;
          }
     }while(n!=4);
     return 0;
}
