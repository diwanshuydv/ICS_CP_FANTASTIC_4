#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct customer
{
    char name[50];
    int age;
    long long phone_number;
    int id;
    int password;
};

struct order
{
    int total_order;
    char cloth_type[50];
    char status[50];
    int pant_count;
    int shirt_count;
    int tshirt_count;
    int kurta_count;
    int shorts_count;
    char feedback[200];
} order_details[1000];

int pant_count = 0, shirt_count = 0, tshirt_count = 0, kurta_count = 0, shorts_count = 0;
struct customer customers[1000];
int customer_count = 0;

void write_customer_to_file(struct customer *s)
{
    FILE *file = fopen("customer_details.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    fprintf(file, "%s %d %lld %d %d\n", s->name, s->age, s->phone_number, s->id, s->password);
    fclose(file);
}

void read_customers_from_file(struct customer *s, int *customer_count)
{
    FILE *file = fopen("customer_details.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    while (fscanf(file, "%s %d %lld %d %d", s[*customer_count].name, &s[*customer_count].age, &s[*customer_count].phone_number, &s[*customer_count].id, &s[*customer_count].password) == 5)
    {
        (*customer_count)++;
    }

    fclose(file);
}

int find_customer_by_phone(struct customer *s, long long phone, int password, int customer_count)
{
    for (int i = 0; i < customer_count; i++)
    {
        if (s[i].phone_number == phone)
        {
            return i;
        }
    }
    return -1;
}

void register_customer(struct customer *s, int *customer_count, char *name, int age, long long phone_number, int password)
{
    // Check if the phone number already exists
    int existing_customer_id = find_customer_by_phone(s, phone_number, password, *customer_count);
    if (existing_customer_id != -1)
    {
        printf("You have already registered. Your ID is %d.\n", s[existing_customer_id].id);
        return;
    }

    // Find a new ID
    int new_id = *customer_count + 1;

    // Setting up passowrd
    password = rand() % 10000;

    // Store the details
    s[*customer_count].age = age;
    s[*customer_count].id = new_id;
    s[*customer_count].phone_number = phone_number;
    s[*customer_count].password = password;
    strcpy(s[*customer_count].name, name);
    strcpy(order_details[*customer_count].status,"NOT RECIEVED");

    // Increment customer count
    (*customer_count)++;

    // Write the new customer to the file
    write_customer_to_file(&s[*customer_count - 1]);

    printf("\nCongratulations!!!\nYour account has been successfully made.\n\nYour ID is %d and your password is %d.\n\n", new_id, password);
}

int place_order(int id)
{
    int i = 0;
    i++;
    int j = 0;
    int selected_choice;
    int sum = 0;

    if (id >= customer_count || customers[id].id != id + 1)
    {
        printf("Invalid customer ID. Please enter a valid ID.\n");
        return 0;
    }

    int m = 1;
    while (m == 1)
    {
        printf("Please select the cloth type-: \n");
        printf("1. Pant(Rs. 25 each)\n");
        printf("2. Shirt(Rs. 20 each)\n");
        printf("3. T-Shirt(Rs. 15 each)\n");
        printf("4. Kurta(Rs. 20 each)\n");
        printf("5. Shorts(Rs. 10 each)\n");
        printf("6. Done\n");
        scanf("%d", &selected_choice);

        if (selected_choice < 1 || selected_choice > 6)
        {
            printf("Please choose a valid option!\n");
        }
        else
        {
            int *ptr_sum = &sum;
            switch (selected_choice)
            {
            case 1:
                printf("ENTER NUMBER OF PANTS-:\n");
                scanf("%d", &order_details[id].pant_count);
                printf("ORDER RECIEVED SUCCESSFULLY\n");
                sum += order_details[id].pant_count;
                break;
            case 2:
                printf("ENTER NUMBER OF SHIRTS-:\n");

                scanf("%d", &order_details[id].shirt_count);
                sum += order_details[id].shirt_count;
                printf("ORDER RECIEVED SUCCESSFULLY\n");
                break;
            case 3:
                printf("ENTER NUMBER OF TSHIRTS-:\n");

                scanf("%d", &order_details[id].tshirt_count);
                sum += order_details[id].tshirt_count;
                printf("ORDER RECIEVED SUCCESSFULLY\n");
                break;
            case 4:
                printf("ENTER NUMBER OF KURTAS-:\n");

                scanf("%d", &order_details[id].kurta_count);
                sum += order_details[id].kurta_count;

                printf("ORDER RECIEVED SUCCESSFULLY\n");
                break;
            case 5:
                printf("ENTER NUMBER OF SHORTS-:\n");

                scanf("%d", &order_details[id].shorts_count);
                sum += order_details[id].shorts_count;
                break;
            case 6:

                printf("Thank you for ordering from us!!\n");
                printf("Total clothes ordered are-: %d\n", sum);
                strcpy(order_details[id].status, "RECIEVED");

                return sum;
                break;
            }
        }
    }
    order_details[id].total_order = sum;
}

int main()
{

    // Load existing customer details from file
    read_customers_from_file(customers, &customer_count);

    int selected_choice;
    int age, customer_id = customer_count + 1;
    long long phone_number;
    char name[50];
    int place_order_id;
    int passcode;
    int a;

    int c = 0;

    while (c != 1)
    {
        printf("Please select your desired option:\n");
        printf("1. Register The Customer\n");
        printf("2. Place Order\n");
        printf("3. Status\n");
        printf("4. Billing\n");
        printf("5. Feedback\n");
        printf("6. Quit\n");
        scanf("%d", &selected_choice);
        fflush(stdin);

        switch (selected_choice)
        {
        case 1:

            printf("\nPLEASE ENTER YOUR NAME-: \n");
            scanf("%s", name);
            fflush(stdin);
            printf("\nPLEASE ENTER YOUR AGE-: \n");
            scanf("%d", &age);
            while (1)
            {
                printf("\nPLEASE ENTER YOUR PHONE NUMBER-: \n");
                scanf("%lld", &phone_number);
                if (phone_number < 6000000000 || phone_number > 9999999999)
                {
                    printf("\nInvalid phone number!!\n\n");
                    printf("ENTER 0 FOR MENU\n");
                    printf("ENTER 1 TO RETRY\n");
                    scanf("%d", &a);
                    if (a == 0)
                    {
                        break;
                    }
                }
                else
                {
                    register_customer(customers, &customer_count, name, age, phone_number, passcode);
                    break;
                }
            }
            break;
        case 2:
            while (1)
            {
                printf("PLEASE ENTER YOUR ID-:\n");
                scanf("%d", &place_order_id);
                if (place_order_id != customers[place_order_id - 1].id)
                {
                    printf("INCORRECT ID!!\n");
                    printf("ENTER 0 FOR MENU\n");
                    printf("ENTER 1 TO RETRY\n");
                    scanf("%d", &a);
                    if (a == 0)
                    {
                        break;
                    }
                }
                else
                {
                    printf("PLEASE ENTER YOUR PASSWORD-: \n");
                    scanf("%d", &passcode);
                    if (passcode != customers[place_order_id - 1].password)
                    {
                        printf("INCORRECT PASSWORD!!\n");
                        printf("ENTER 0 TO RESET\n");
                        printf("ENTER 1 TO RETRY\n");
                        scanf("%d", &a);
                        if (a == 0)
                        {
                            while (1)
                            {

                                printf("ENTER YOUR PHONE NUMBER\n");
                                scanf("%lld", &phone_number);
                                if (phone_number != customers[place_order_id - 1].phone_number)
                                {
                                    printf("INCORRECT PHONE NUMBER\n");
                                    printf("ENTER 0 FOR MENU\n");
                                    printf("ENTER 1 TO RETRY\n");
                                    scanf("%d", &a);
                                    if (a == 0)
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("PLEASE ENTER YOUR NEW PASSWORD\n");
                                    printf("(PASSWORD MUST BE AN INTEGER)\n");
                                    while (1)
                                    {
                                        
                                        if (scanf("%d", &passcode) == 1)
                                        {
                                            customers[place_order_id - 1].password = passcode;
                                            printf("PASSWORD CHANGED SUCCESSFULLY\n");
                                            break;
                                        }
                                        else
                                        {
                                            fflush(stdin);
                                            printf("PLEASE ENTER AN INTEGER!!\n");
                                            printf("ENTER 0 TO EXIT\n");
                                            printf("ENTER  1 TO RETRY\n");
                                            scanf("%d", &a);
                                            if (a == 0)
                                            {
                                                break;
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                if (place_order_id <= customer_id && place_order_id == customers[place_order_id - 1].id && passcode == customers[place_order_id - 1].password)
                {
                    order_details[place_order_id - 1].total_order = place_order(place_order_id - 1);
                    break;
                }
            }
            break;
        case 3:
            while (1)
            {
                printf("PLEASE ENTER YOUR ID-:\n");
                scanf("%d", &place_order_id);

                if (place_order_id <= customer_id)
                {
                    printf("PLEASE CHOOSE A OPTION:\n");
                    printf("1.CHECK STATUS\n");
                    printf("2.UPDATE STATUS(FOR PEOPLE WITH GRANTED ACCESS ONLY)\n");
                    int status_choice;
                    scanf("%d", &status_choice);
                    switch (status_choice)
                    {
                    case 1:
                        printf("%s\n", order_details[place_order_id - 1].status);
                        break;
                    case 2:
                        printf("ENTER THE PASSCODE-:\n");
                        scanf("%d", &passcode);
                        if (passcode == 12345)
                        {
                            printf("PLEASE UPDATE THE CURRENT STATUS\n");
                            scanf("%s", order_details[place_order_id-1].status);
                        }
                    }
                    break;
                }
                else
                {
                    printf("INCORRECT ID!!\n");
                    printf("ENTER 0 FOR MENU\n");
                    printf("ENTER 1 TO RETRY\n");
                    scanf("%d", &a);
                    if (a == 0)
                    {
                        break;
                    }
                }
            }
            break;
        case 4:
            while (1)
            {
                printf("PLEASE ENTER YOUR ID-:\n");
                scanf("%d", &place_order_id);

                if (place_order_id <= customer_id)
                {
                    printf("YOUR BILL_:\n");
                    printf("PANTS : %d * Rs.25 = %d\n", order_details[place_order_id - 1].pant_count, order_details[place_order_id - 1].pant_count * 25);
                    printf("SHIRTS : %d * Rs.20 = %d\n", order_details[place_order_id - 1].shirt_count, order_details[place_order_id - 1].shirt_count * 20);
                    printf("TSHIRTS : %d * Rs.15 = %d\n", order_details[place_order_id - 1].tshirt_count, order_details[place_order_id - 1].tshirt_count * 15);
                    printf("KURTA : %d * Rs.20 = %d\n", order_details[place_order_id - 1].kurta_count, order_details[place_order_id - 1].kurta_count * 20);
                    printf("SHORTS : %d * Rs.10 = %d\n", order_details[place_order_id - 1].shorts_count, order_details[place_order_id - 1].shorts_count * 10);
                    printf("TOTAL : Rs.%d\n", order_details[place_order_id - 1].pant_count * 25 + order_details[place_order_id - 1].shirt_count * 20 + order_details[place_order_id - 1].tshirt_count * 15 + order_details[place_order_id - 1].kurta_count * 20 + order_details[place_order_id - 1].shorts_count * 10);
                    break;
                }
                else
                {
                    printf("INCORRECT ID!!\n");
                    printf("ENTER 0 FOR MENU\n");
                    printf("ENTER 1 TO RETRY\n");
                    scanf("%d", &a);
                    if (a == 0)
                    {
                        break;
                    }
                }
            }
            break;
        case 5:
            printf("PLEASE ENTER YOUR ID-: \n");
            scanf("%d", &place_order_id);
            if (place_order_id <= customer_id)
            {
                if (order_details[place_order_id - 1].total_order > 0)
                {
                    printf("PLEASE GIVE YOUR FEEDBACK!!\n");
                    scanf("%s", order_details[place_order_id - 1].feedback);
                    printf("THANK YOU VERY MUCH. WE APPRECIATE YOUR FEEDBACK\n");
                }
                else if (order_details[place_order_id - 1].total_order == 0)
                {
                    printf("Please place an order before giving your feedback.\n\n");
                }
                else
                {
                    printf("Kindly wait till you receive your order to give your feedback\n\n");
                }
            }
            else
            {
                printf("Please enter a valid ID\n");
            }
            fflush(stdin);
            break;
        case 6:
            printf("THANKS FOR USING OUR SERVICES...\n");
            c = 1;
            break;
        }
    }
    // Exit the program and save customer details to the file
    FILE *file = fopen("customer_details.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    for (int i = 0; i < customer_count; i++)
    {
        fprintf(file, "%s %d %lld %d %d\n", customers[i].name, customers[i].age, customers[i].phone_number, customers[i].id, customers[i].password);
        fclose(file);
    }
    return 0;
}
