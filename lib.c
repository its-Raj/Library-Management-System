#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "data.bin"

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

typedef struct books
{
    int books_id;
    char name[25];
    char author[30];
    char studentName[30];
    Date issue_date;
} book;

// Function Decleration 
void header();
void start();
void addbook();
void display();
void searchBooks();
void deleteBooks();

int main()
{
    system("cls");
    start();
    return 0;
}

void header()
{
    printf("\n\n\n");
    printf("\t\t\t\t***************************************************************************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t************           Library management System               ************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t***************************************************************************");
}

void start()
{

    int ch;
    header();

    printf("\n\n\t\t\t\tEnter 1 to Add Book");
    printf("\n\t\t\t\tEnter 2 to View Book Details");
    printf("\n\t\t\t\tEnter 3 to Search Book");
    printf("\n\t\t\t\tEnter 4 to Delete Book");

    printf("\n\n\t\t\t\tEnter Choice : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        addbook();
        break;
    case 2:
        display();
        break;
    case 3:
        searchBooks();
        break;
    case 4:
        deleteBooks();
        break;

    default:
        printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        break;
    }
}

void addbook()
{

    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Add Book                                    ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    book data = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "ab+");

    printf("\n\n\t\t\t\tENTER YOUR DETAILS BELOW :");
    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");

    printf("\n\t\t\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u", &data.books_id);

    printf("\n\t\t\t\tBook Name  = ");
    fflush(stdin);
    fgets(data.name, 50, stdin);

    printf("\n\t\t\t\tAuthor Name  = ");
    fflush(stdin);
    fgets(data.author, 30, stdin);

    printf("\n\t\t\t\tStudent Name  = ");
    fflush(stdin);
    fgets(data.studentName, 30, stdin);

    printf("\n\t\t\tEnter date in format (day/month/year): ");
    scanf("%d/%d/%d", &data.issue_date.dd, &data.issue_date.mm, &data.issue_date.yyyy);

    fwrite(&data, sizeof(data), 1, fp);

    fclose(fp);

    printf("\n\t\t\t\tBook added Successfully.................");

    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
    getchar();

    system("cls");
    start();
}

void display()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              book Details                                ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;
    book data = {0};

    FILE *fp = NULL;
    unsigned int countBook = 1;
    fp = fopen(FILE_NAME, "rb");

    while (fread(&data, sizeof(data), 1, fp))
    {
        printf("\n\t\t\t\tBook Count = %d\n\n", countBook);
        printf("\t\t\t\tBook id : %u", data.books_id);
        printf("\n\t\t\t\tBook name : %s", data.name);
        printf("\t\t\t\tBook authorName : %s", data.author);
        printf("\t\t\t\tBook issue date(day/month/year) : (%d/%d/%d)\n\n", data.issue_date.dd, data.issue_date.mm, data.issue_date.yyyy);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if (!found)
    {
        printf("\n\n\t\t\t\tNo Record Found... ");
    }

    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
    getchar();

    system("cls");
    start();
}

void searchBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Search Book                                 ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;
    char bookName[30] = {0};
    book data = {0};

    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    printf("\n\n\t\t\t\tEnter Book Name to search : ");
    fflush(stdin);
    fgets(bookName, 30, stdin);
    while (fread(&data, sizeof(data), 1, fp))
    {
        if (!strcmp(data.name, bookName))
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("\t\t\t\tBook id : %u", data.books_id);
        printf("\n\t\t\t\tBook name : %s", data.name);
        printf("\t\t\t\tBook authorName : %s", data.author);
        printf("\t\t\t\tBook issue date(day/month/year) : (%d/%d/%d)\n\n", data.issue_date.dd, data.issue_date.mm, data.issue_date.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record Found....");
    }

    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
    getchar();

    system("cls");
    start();
}

void deleteBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                         Delete Books Details                             ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;
    int bookDelete = 0;
    char bookName[30] = {0};
    book data = {0};

    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin", "wb");
    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    printf("\n\t\t\t\tEnter Book ID NO. for delete:");
    scanf("%d", &bookDelete);

    while (fread(&data, sizeof(data), 1, fp))
    {
        if (data.books_id != bookDelete)
        {
            fwrite(&data, sizeof(data), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found) ? printf("\n\t\t\t\tRecord deleted successfully.....") : printf("\n\t\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin", FILE_NAME);

    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
    getchar();

    system("cls");
    start();
}
