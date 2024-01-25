#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "professional.c"
static info customer_details;


void display_customer(info *head)
{
    printf("%s\n", head->phone);
    printf("%s\n", head->area);
}

void cumstomer_side(link *head)
{
    char file_name[81];
    strcpy(file_name, head->phone);
    strcat(file_name, ".txt");
    FILE *ptr = fopen(file_name, "a");
    fprintf(ptr,"%s\n%s\n%d",customer_details.phone,customer_details.area,head->expect);
    fclose(ptr);
}


void export(char file_name[81], link *head)
{
    printf("export");
    link member;
    FILE *fptr;
    FILE *new;
    new = fopen("temp.bin", "a+b");
    fptr = fopen(file_name, "r+b");
    while (fread(&member, sizeof(member), 1, fptr))
    {
        if (strcmp(member.phone, head->phone))
        {
            fwrite(&member, sizeof(member), 1, new);
        }
    }

    fclose(fptr);
    fclose(new);
    remove(file_name);
    rename("temp.bin", file_name);
    printf("\n\nyour proffesinal worker will at your site\n");
    cumstomer_side(head);
}

// reading the file by arranging them into ascending order
void find_worker(char file_name[81])
{
    FILE *ptr;
    int i = 0, no_of_workers;
    link list[no_of_workers], temp, worker_details;

    // reading the file given as parameter and presenting them in list
    ptr = fopen(file_name, "r+b");
    if (ptr==NULL)
    {
        printf("\ncurrently there are no workers please visit again\n");
    }
    
    while (!feof(ptr))
    {
        fread(&worker_details, sizeof(worker_details), 1, ptr);
        list[i] = worker_details;
        i++;
    }
    fclose(ptr);
    no_of_workers = i;
    // reading the worker and sorting on basis of their wage
    for (int i = 0; i < no_of_workers; i++)
    {
        for (int j = i; j < no_of_workers; j++)
        {
            if (list[i].expect > list[j].expect)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    for (int i = 0; i < no_of_workers - 1; i++)
    {
        printf(" ....%d....\n", i + 1);
        display(&list[i]);
        printf("\n");
    }

    int sl_no;
    printf("enter your worker sl.no:\n");
    printf("enter 0 if you haven't found good expert");
    scanf("%d",&sl_no);
    if (sl_no == 0)
    {
        printf("please visit again you may find a better worker\n");
        exit(0);
    }
    printf("\nyour wroker is one the way\n");
    display(&list[sl_no - 1]);
    export(file_name, &list[sl_no - 1]);
}

void apending_sectors()
{
    char sector_name[81];
    printf("enter the sector name :\n");
    scanf("%s", sector_name);
    FILE *ptr = fopen("sectors.txt", "a");
    fprintf(ptr, "%s\n", sector_name);
    fclose(ptr);
}
void sector_determining(int choice)
{
    char sector_reads[81];
    int i = 0, x;
    FILE *ptr = fopen("sectors.txt", "r");
    while (fscanf(ptr, "%s", sector_reads) != EOF)
    {
        i++;
        printf("%d", i);
        printf("%s\n", sector_reads);
    }
    fclose(ptr);
    printf("\n\n");
    printf("enter 0 in case if your sector is not listed in the above one\n");
    printf("enter the slot number\n");
    scanf("%d",&x);

    if (x == 0)
    {
        apending_sectors();
        fclose(ptr);
        x = i + 1;
    }
    ptr = fopen("sectors.txt", "r");
    for (int j = 0; j < x; j++)
    {
        fscanf(ptr,"%s",sector_reads);
    }
    fclose(ptr);
    strcat(sector_reads, "_worker.bin");
    if (choice == 1)
    {
        new_user(sector_reads);
    }

    if (choice == 0)
    {
        find_worker(sector_reads);
    }
}

void new_customer()
{

    printf("enter your phone number\n");
    scanf("%s", customer_details.phone);
    
   while (strlen(customer_details.phone)!=10)
   {
    printf("enter your 10 digit phone number\n");
    scanf("%s", customer_details.phone);
   }
   
    printf("enter your area name");
    scanf("%s",customer_details.area);
}

void customer_main(void)
{
    int ch, x = 1;
    while (x)
    {
        printf("enter the choice\n");
        printf("1.new customer\n 2.to exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("your service our pleasure\n");
            new_customer();
            sector_determining(0);
            break;
        case 2:
            printf("thank you visit again\n");
            exit(0);
        default:
            break;
        }
    }
}

int main(void)
{

    char sector_reads[81];
    int ch, res, x;
    printf("WELCOME TO WAGET\n");

    x = prinicial();
    if (x == 1)
    {
        customer_main();
    }
    if (x == 2)
    {
            printf("thank you for choosing waget\n");
            printf("\n\n");
            sector_determining(1);
        
    }
    return 0;
}