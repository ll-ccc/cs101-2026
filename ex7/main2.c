#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define BOOK_COUNT 6

typedef struct
{
    int id;
    int price;
    char title[100];
} Book;

int total_price(const Book books[], int count);
void list_book(const Book books[], int count);

int main(void)
{
    Book books[BOOK_COUNT] =
    {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550, "Killers of the Flower Moon"},
        {5, 870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    FILE *fp;

    fp = fopen("Book.bin", "wb");

    if (fp == NULL)
    {
        perror("Book.bin");
        return 1;
    }

    if (fwrite(books, sizeof(Book), BOOK_COUNT, fp)
        != BOOK_COUNT)
    {
        fprintf(stderr, "Failed to write Book.bin.\n");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0)
    {
        perror("Book.bin");
        return 1;
    }

    list_book(books, BOOK_COUNT);

    printf("\nTotal price: %d\n",
           total_price(books, BOOK_COUNT));

    return 0;
}

int total_price(const Book books[], int count)
{
    int i;
    int total = 0;

    for (i = 0; i < count; i++)
    {
        total += books[i].price;
    }

    return total;
}

void list_book(const Book books[], int count)
{
    int i;

    printf("%-4s%-8s%s\n", "Id", "Price", "Title");

    for (i = 0; i < count; i++)
    {
        printf("%-4d%-8d%s\n",
               books[i].id,
               books[i].price,
               books[i].title);
    }
}
