#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 505

typedef struct {
    char book_name[55];
    char author[25];
    char publisher[35];
    char publish_date[15];
} Book;

int cmp(const void *a,const void *b) {
    Book* book_a = (Book*)a;
    Book* book_b = (Book*)b;
    return strcmp(book_a->book_name,book_b->book_name);
}

//[l,r)
int lower_bound(Book *books,int n,Book add) {
    int l = 0,r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (strcmp(books[mid].book_name,add.book_name) < 0) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return l;
}

void insert_book(Book *books,int n,Book add) {
    int pos = lower_bound(books,n,add);
    for (int i = n;i > pos;i--) {
        books[i] = books[i-1];
    }
    books[pos] = add;
}

void search_book(Book *books,int n,char *name) {
    for (int i = 0;i < n;i++) {
        if (strstr(books[i].book_name,name) !=NULL) {
            printf("%-50s%-20s%-30s%-10s\n",books[i].book_name,books[i].author,books[i].publisher,books[i].publish_date);
        }
    }
}

void delete_book(Book *books,int *n,char *name) {
    int idx = 0;
    for (int i = 0; i < *n; i++) {
        if (strstr(books[i].book_name,name) == NULL) {
            books[idx++] = books[i];
        }
    } 
    *n = idx;
}


int main() {
    FILE *source,*target;
    source = fopen("books.txt","r");
    if (source == NULL) {
        printf("无法打开 books.txt\n");
        return 1;
    }
    target = fopen("ordered.txt","w");
    if (target == NULL) {
        printf("无法创建 ordered.txt\n");
        fclose(source);
        return 1;
    }

    Book books[MAXN];
    int n = 0;
    while (fscanf(source,"%s %s %s %s",books[n].book_name,books[n].author,books[n].publisher,books[n].publish_date) == 4) {
        n++;
    }
    qsort(books,n,sizeof(Book),cmp);

    while(1) {
        int cmd;
        scanf("%d",&cmd);
        if (cmd == 0) {
            break;
        }
        else if (cmd == 1) {
            Book add;
            scanf("%s %s %s %s",add.book_name,add.author,add.publisher,add.publish_date);
            insert_book(books,n,add);
            n++;
        }
        else if(cmd == 2) {
            char find_name[55];
            scanf("%s",find_name);
            search_book(books,n,find_name);
        }
        else if (cmd == 3) {
            char delete_name[55];
            scanf("%s",delete_name);
            delete_book(books,&n,delete_name);
        }
    }
    for (int i = 0;i < n;i++) {
        fprintf(target,"%-50s%-20s%-30s%-10s\n",books[i].book_name,books[i].author,books[i].publisher,books[i].publish_date);
    }
    fclose(source);
    fclose(target);
    return 0;
}