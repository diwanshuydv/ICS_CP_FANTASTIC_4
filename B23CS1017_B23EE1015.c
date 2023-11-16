#include <stdio.h>
#include <stdlib.h>
struct customer
{
	char name[50];
	int age;
	long phone_number;
	int id;
};

void register_customer(struct customer *s,char *name, int age, long phone_number,int id)
{
	s[id].age = age;
	s[id].id = id;
	s[id].phone_number = phone_number;
	strcpy(s[id].name,name);
	printf("Congratulations!!!\n Your account has been successfully made.\n Your ID is %d.\n",id);
}


int main()
{   struct customer* customers=(struct customer*)malloc(sizeof(struct customer)*1000);
    int selected_choice,i=0;
    int age, customer_id=1;
      long phone_number;
      char name[50];


    while(i==0)
    {

        printf("Please select your desired option:\n");
                   printf("1. Register The Customer\n");
                   printf("2. Place Order\n");
                   printf("3. Status Check\n");
                   printf("4. Billing\n");
                   printf("5. Feedback\n");
                   printf("6. Quit \n");
                   scanf("%d",&selected_choice);
                   fflush(stdin);
                   switch(selected_choice){
                   case 1:
                       printf("PLEASE ENTER YOUR NAME-: \n");
                       scanf("%[^\n]s",name);
                       printf("PLEASE ENTER YOUR AGE-: \n");
                       scanf("%d",&age);
                       printf("PLEASE ENTER YOUR PHONE NUMBER-: \n");
                       scanf("%d",&phone_number);
                       register_customer(customers,name,age,phone_number,customer_id);
                       customer_id++;
                       break;
                   case 2:
                    place_order();
                    break;
                   case 3:
                   // status();
                    break;
                   case 4:
                  //  bill();
                    break;
                   case 5:
                  //  Feedback();
                        break;
                   case 6:
                   // quit();
                    break;

                   }


    }
    return 0;
}
