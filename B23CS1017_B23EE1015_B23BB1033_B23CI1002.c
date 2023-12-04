#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

struct customer
{
    char name[50];
    int age;
    long long phone_number;
    int id;
    long password;
    int pant_count;
    int shirt_count;
    int tshirt_count;
    int kurta_count;
    int shorts_count;
    int total_bill;
};

struct order
{
    int total_order;
    char cloth_type[50];
};

struct customer customers[1000];
int customer_count = 0;

int find_customer_by_phone(struct customer *s, long long phone, long password, int customer_count)
{
    for (int i = 0; i < customer_count; i++)
    {
        if (s[i].phone_number == phone && s[i].password == password)
        {
            return i;
        }
    }
    return -1;
}

void write_customer_to_file(struct customer *s, struct order *ord)
{
    FILE *file = fopen("customer_details.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    fprintf(file, "%s %d %lld %d %ld\n", s->name, s->age, s->phone_number, s->id, s->password);
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

    while (fscanf(file, "%s %d %lld %d %ld\n", s[*customer_count].name, &s[*customer_count].age, &s[*customer_count].phone_number, &s[*customer_count].id, &s[*customer_count].password) != EOF)
    {
        (*customer_count)++;
    }

    fclose(file);
}

void register_customer(struct customer *s, int *customer_count, char *name, int age, long long phone_number, long password)
{
    // Check if the phone number already exists
    int existing_customer_id = find_customer_by_phone(s, phone_number, password, *customer_count);
    if (existing_customer_id != -1)
    {
        printf("You have already registered. Your ID is %d.\n", s[existing_customer_id].id);
        return;
    }

    // Find a new ID
    int new_id = 0;
    for (int i = 0; i < *customer_count; i++)
    {
        if (s[i].id > new_id)
        {
            new_id = s[i].id;
        }
    }
    new_id++;

    // Store the details
    strcpy(s[*customer_count].name, name);
    s[*customer_count].age = age;
    s[*customer_count].id = new_id;
    s[*customer_count].phone_number = phone_number;
    s[*customer_count].password = password;

    // Update customer count
    (*customer_count)++;

    // Write the customer details to file
    struct order ord;
    write_customer_to_file(s + *customer_count - 1, &ord);

    printf("\nRegistration successful!! Your ID is %d.\n", new_id);
}

void place_order(struct customer *s, int *customer_count, int customer_index)
{
    char cloth_type[50];
    int quantity;

    struct order temp[1000];
    printf("Enter cloth type: ");
    scanf("%s", cloth_type);

    // Update customer's cloth count
    if (strcmp(cloth_type, "Pants") == 0)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        s[customer_index].pant_count += quantity;
    }
    else if (strcmp(cloth_type, "Shirt") == 0)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        s[customer_index].shirt_count += quantity;
    }
    else if (strcmp(cloth_type, "T-shirt") == 0)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        s[customer_index].tshirt_count += quantity;
    }
    else if (strcmp(cloth_type, "Kurta") == 0)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        s[customer_index].kurta_count += quantity;
    }
    else if (strcmp(cloth_type, "Shorts") == 0)
    {
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        s[customer_index].shorts_count += quantity;
    }
    else
    {
        printf("Invalid cloth type.\n");
        return;
    }

    printf("Total clothes ordered are: %d\n", s[customer_index].pant_count + s[customer_index].shirt_count + s[customer_index].tshirt_count + s[customer_index].kurta_count + s[customer_index].shorts_count);
    printf("Order placed successfully!!\n");
}

void view_order_history(struct customer *s, int customer_index)
{
    printf("Order history:\n");
    printf("Pants: %d\n", s[customer_index].pant_count);
    printf("Shirts: %d\n", s[customer_index].shirt_count);
    printf("T-shirts: %d\n", s[customer_index].tshirt_count);
    printf("Kurtas: %d\n", s[customer_index].kurta_count);
    printf("Shorts: %d\n", s[customer_index].shorts_count);
    return;
}

void show_bill(struct customer *s, int customer_index)
{
    printf("Bill for %s (ID: %d):\n", s[customer_index].name, s[customer_index].id);
    printf("Pants: Rs. %d\n", s[customer_index].pant_count * 25);
    printf("Shirts: Rs. %d\n", s[customer_index].shirt_count * 20);
    printf("T-Shirts: Rs. %d\n", s[customer_index].tshirt_count * 15);
    printf("Kurtas: Rs. %d\n", s[customer_index].kurta_count * 20);
    printf("Shorts: Rs. %d\n", s[customer_index].shorts_count * 10);

    s[customer_index].total_bill = (s[customer_index].pant_count * 25) + (s[customer_index].shirt_count * 20) + (s[customer_index].tshirt_count * 15) + (s[customer_index].kurta_count * 20) + (s[customer_index].shorts_count * 10);

    printf("Total Bill: Rs. %d\n", s[customer_index].total_bill);
    return;
}

void pay_bill(struct customer *s, int customer_index)
{
    printf("\nYour bill is: %d\n", s[customer_index].total_bill);
    printf("Please pay Rs. %d on mobile number 5432154321\n");
    sleep(5);
    printf("Thank you for paying!!\n");

    s[customer_index].pant_count = 0;
    s[customer_index].shirt_count = 0;
    s[customer_index].tshirt_count = 0;
    s[customer_index].kurta_count = 0;
    s[customer_index].shorts_count = 0;
    s[customer_index].total_bill = 0;

    return;
}

void login(struct customer *s, int *customer_count)
{
    long long phone_number;
    long password;

    printf("Enter phone number: ");
    scanf("%lld", &phone_number);

    printf("Enter password: ");
    scanf("%ld", &password);

    int customer_index = find_customer_by_phone(s, phone_number, password, *customer_count);
    if (customer_index == -1)
    {
        printf("Invalid phone number or password.\n");
        return;
    }

    printf("\n\nLogin successful!!\n");

    // Display customer details
    printf("\nName: %s\n", s[customer_index].name);
    printf("Age: %d\n", s[customer_index].age);
    printf("Phone number: %lld\n", s[customer_index].phone_number);
    printf("ID: %d\n", s[customer_index].id);
    printf("Pant count: %d\n", s[customer_index].pant_count);
    printf("Shirt count: %d\n", s[customer_index].shirt_count);
    printf("T-shirt count: %d\n", s[customer_index].tshirt_count);
    printf("Kurta count: %d\n", s[customer_index].kurta_count);
    printf("Shorts count: %d\n", s[customer_index].shorts_count);

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Place order\n");
        printf("2. View order history\n");
        printf("3. Bill\n");
        printf("4. Pay bill\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            place_order(s, customer_count, customer_index);
            break;
        }

        case 2:
        {
            view_order_history(s, customer_index);
            break;
        }

        case 3:
        {
            show_bill(s, customer_index);
            break;
        }
        case 4:
        {
            pay_bill(s, customer_index);
            break;
        }
        case 5:
        {
            printf("Logged out successfully.\n");
        }
        }
    } 
    while (choice != 5);
}

int main()
{
    read_customers_from_file(customers, &customer_count);

    int choice;
    do
    {
        printf("\nMain Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char name[50];
            int age;
            long long phone_number;
            long password;

            printf("Enter name: ");
            scanf("%s", name);
            fflush(stdin);

            printf("Enter age: ");
            scanf("%d", &age);

            printf("Enter phone number: ");
            scanf("%lld", &phone_number);

            printf("Enter password (Only integer): ");
            scanf("%ld", &password);

            register_customer(customers, &customer_count, name, age, phone_number, password);
        }
        break;

        case 2:
            login(customers, &customer_count);
            break;

        case 3:
            printf("Thank you for using our service!!\n");
            return 0;
        }
    } 
    while (choice != 3);

    return 0;
}
