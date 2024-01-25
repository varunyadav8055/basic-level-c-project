#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct professional
{
    char phone[11];
    int expect;
} link;

typedef struct customer
{
    char phone[11];
    char area[81];
} info;
void complain(char block_number[11])
{
    char check[11];
    strcpy(check, block_number);
    FILE *ptr = fopen("blocked.bin", "a+b");
    fwrite(check, sizeof(check), 1, ptr);
    fclose(ptr);
}
bool blocked(char checks[])
{
    int i = 0;
    char file_output[11];
    FILE *ptr = fopen("blocked.bin", "r+b");
    fseek(ptr, 0, SEEK_SET);
    while (!feof(ptr))
    {
        fread(&file_output, sizeof(file_output), 1, ptr);
        if (strcmp(checks, file_output) == 0)
        {
            i++;
        }
    }
    fclose(ptr);
    if (i >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void worker_side(int choice, char phone_no[11])
{
    info read_customer;
    char file_name[81], check[11];
    strcpy(file_name, phone_no);
    strcat(file_name, ".txt");
    int result;
    int wage;
    int hr, min;
    time_t head_time;
    struct tm *x;
    time(&head_time);
    x = localtime(&head_time);

    FILE *ptr = fopen(file_name, "r");
    if (ptr == NULL)
    {
        printf("you have not got any deals");
        exit(0);
    }

    if (choice == 1)
    {
        fscanf(ptr, "%s", &read_customer.phone);
        fscanf(ptr, "%s", &read_customer.area);
        fscanf(ptr, "%d", &wage);
        fclose(ptr);
        fflush(ptr);

        printf("you got a deal at %s\n", read_customer.area);
        printf("contact %s\n", read_customer.phone);
        ptr = fopen(file_name, "w");
        fprintf(ptr, "%s\n%d\n%d\n%d\n", read_customer.phone, wage, x->tm_hour, x->tm_min);
        fclose(ptr);
    }

    if (choice == 2)
    {
        fscanf(ptr, "%s", &read_customer.phone);
        fscanf(ptr, "%d", &wage);
        fscanf(ptr, "%d", &hr);
        fscanf(ptr, "%d", &min);
        fclose(ptr);
        remove(file_name);
        printf("\nask the customers to enter phone number\n");
        scanf("%s", check);
        while (strlen(read_customer.phone) != 10 && strcmp(check, read_customer.phone) != 0)
        {
            printf("enter your 10 digit phone number\n");
            scanf("%s", check);
        }

        if (x->tm_min > min)
        {
            x->tm_min = x->tm_min + 60;
            x->tm_hour=x->tm_hour-1;
        }
        result = ((x->tm_hour - hr) + (x->tm_min - min) / 60) * wage;
        printf("collect ₹%d\n", result);
        printf("\nenter 1 if you want rise complain or 2 if u want exit\n");
        scanf("%d", &result);
        if (result == 1)
        {
            complain(phone_no);
        }
        remove(file_name);

        printf("THANK YOU VISIT AGAIN");
        exit(0);
    }
}

void display(link *head)
{
    printf("phone no :%s\n", head->phone);
    printf("wage per hour :%d\n", head->expect);
}

void new_user(char sector_name[81]) // came with filename as sectorNAME_worker.bin
{

    int x = 1, ch;
    link temp;
    printf("enter your phone number ");
    scanf("%s", temp.phone);
    while (strlen(temp.phone)!=10)
    {
       printf("enter your  10 digit phone number\n");
       scanf("%s",temp.phone);
    }
    
    if (blocked(temp.phone) == true) // if true exit if false continue
    {
        printf("YOU GOT BLOCKED\n");
        exit(0);
    }

    printf("\n1.NEW USER\n2.EXISTING USER \n ");
    scanf("%d", &ch);
    if (ch == 1)
    {
        printf("enter your excepected wage per hour \n");
        scanf("%d", &temp.expect);

        FILE *ptr;
        ptr = fopen(sector_name, "a+b");
        fwrite(&temp, sizeof(temp), 1, ptr);
        fclose(ptr);
    }

    if (ch == 2)
    {
        printf("\n1.see my deals\n2.collect your wage\n");
        scanf("%d", &ch);
        if (ch == 1)
        {
            worker_side(1, temp.phone);
        }
        if (ch == 2)
        {
            worker_side(2, temp.phone);
        }
    }
}

int prinicial()
{
    int x;
    printf("enter your choice\n");
    printf("1.get professional worker to our home\n");
    printf("2.become a professional worker\n");
    scanf("%d", &x);
    return x;
}
