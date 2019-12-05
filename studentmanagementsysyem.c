#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

typedef struct Node node;  // Create new name for struct Node---> node
struct Node
{

    char first_name[50];
    char last_name[50];
    char student_id[30];
    char gender[10];
    char email[50];
    char father_name[50];
    char mother_name[50];
    char date_of_birth[50];
    node *next;

} std,*head=NULL;


void change_password();//to change password
void display_student(); //to show student's details
void add_new_student(); //To add student's info in list
void remove_student(); //to delete student's info in list
void modify_student_data(); //to change student's info in list
void search_student(); //to search student's info in list
void intro(); //Log in page
void date_time(); //date and time
void break_t(unsigned int t); //Loading...
void print_title();//to show title
void saved_data(); //to save data to linked list


FILE *file,*f1;
int f=0,m=0;  //f for Female && m for Male
char rtrv[100],wrtn[100],match[100]; // password restore from file [rtrv]
//password written to file [wrtn]
//password match [match]


void change_password()
{
    int k=0;
    print_title();
    f1=fopen("password.txt","w");
    printf("\n\t\t\t->Enter New Password: ");
    scanf("%s",wrtn);

    if(strcmp(rtrv,wrtn)==0)
    {
        printf("\n\t\t\tPassword Matched with Old Password.\n");
        k=1;
    }
    fprintf(f1,"%s",wrtn);
    if(k==0)
    {
        do
        {
            printf("\n\t\t\t->Confirm Password:");
            scanf("%s",match);
            if(strcmp(wrtn,match)!=0)
                printf("\n\t\t\tPassword not match. Plz try again\n\n");
        }
        while(strcmp(wrtn,match)!=0);
    }
    if(k==0)
    {
        printf("\n\t\t\tYour Password was changed successfully.\n\n");
    }
    printf("\n");
    system("pause"); //Make the screen wait for a key press.


}


void saved_data()
{
    node *temp,*new_node;
    f=0;
    m=0;
    head=NULL;
    rewind(file); //move file position indicator to the beginning
    while((fread(&std,sizeof(std),1,file))==1)
    {
        temp=(node*)malloc(sizeof(node));
        strcpy(temp->first_name,std.first_name);
        strcpy(temp->last_name,std.last_name);
        strcpy(temp->student_id,std.student_id);
        strcpy(temp->gender,std.gender);
        if(strcmp(temp->gender,"F")==0||strcmp(temp->gender,"f")==0)
            f++;
        if(strcmp(temp->gender,"M")==0||strcmp(temp->gender,"m")==0)
            m++;
        strcpy(temp->father_name,std.father_name);
        strcpy(temp->mother_name,std.mother_name);
        strcpy(temp->date_of_birth,std.date_of_birth);

        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
            new_node=temp;
        }
        else
        {
            new_node->next=temp;
            new_node=temp;
        }

    }
}


void print_title()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t*-------------------------------------*\n");
    printf("\n\n");
}
void search_student()
{
    print_title();
    saved_data();

    char flag='y';
    do
    {
        node *c=head,*temp=NULL;
        char id[100];
        printf("\n\t\t\tEnter Student ID:");
        scanf("%s",id);
        printf("\n");
        while(c!=NULL)
        {
            if(strcmp(c->student_id,id)==0)
            {
                temp=c;
                break;
            }
            c=c->next;
        }
        if(temp==NULL)
            printf("\t\tRecord Not found!!!\n\n");
        else
        {

            printf("\n\t\tStudent\tName: %s %s\n",temp->first_name,temp->last_name);
            printf("\n\t\tStudent\tID: %s\n",temp->student_id);
            printf("\n\t\tFather\tName: %s\n",temp->father_name);
            printf("\n\t\tMother\tName: %s\n",temp->mother_name);
            printf("\n\t\tGender\t: %s\n",temp->gender);
            printf("\n\t\tDate of Birth\t: %s\n\n\n",temp->date_of_birth);



        }
        getchar(); //For clearing the input buffer
        printf("Do you want to search more (Y/N) :");
        scanf("%c",&flag);

    }
    while(flag=='y'||flag=='Y');

    printf("\n");
    system("pause"); //Make the screen wait for a key press.



}


void modify_student_data()
{
    print_title();
    int check=0;
    char id[100];
    printf("\n\t\tEnter roll Number to Modify:");
    scanf("%s",id);

    rewind(file); //move file position indicator to the beginning
    while((fread(&std,sizeof(std),1,file)==1))
    {
        if(strcmp(id,std.student_id)==0)
        {
            check=1;
            break;
        }
    }

    if(check==0)
        printf("\n\t\tRecord not found!!!\n\n");
    else
    {
        fseek(file,-sizeof(std),SEEK_CUR);// file position indicator to the current
        printf("\n\t\tEnter new data :\n\n");

        printf("\t\t\t\tEnter First name:");
        scanf("%s",std.first_name);

        printf("\n\t\t\t\tEnter Last name:");
        scanf("%s",std.last_name);

        printf("\n\t\t\t\tEnter Student ID:");
        scanf("%s",std.student_id);

        printf("\n\t\t\t\tIf Female write F or If Male write M:");
        scanf("%s",std.gender);

        getchar();

        printf("\n\t\t\t\tEnter Father name:");
        gets(std.father_name);

        printf("\n\t\t\t\tEnter Mother name:");
        gets(std.mother_name);

        printf("\n\t\t\t\tEnter Date of Birth:");
        scanf("%s",std.date_of_birth);

        fwrite(&std,sizeof(std),1,file);

    }
    if(check==1)
    {
        printf("\n\t\tRecord was changed successfully.\n");
    }
    printf("\n");
    system("pause"); //Make the screen wait for a key press.


}
void remove_student()
{
    print_title();
    char id[100];
    FILE *tmp;
    if((tmp=fopen("tmp.txt","wb+"))==NULL)
    {
        printf("\n\t\tCan not be opened");

    }
    printf("\n\t\tEnter Student ID that to be delete:");
    scanf("%s",id);
    int check=0;
    rewind(file); //move file position indicator to the beginning

    while((fread(&std,sizeof(std),1,file))==1)
    {
        if(strcmp(std.student_id,id)==0)
        {
            check=1;
        }
        else
        {
            fwrite(&std,sizeof(std),1,tmp);
        }

    }
    fclose(file);
    fclose(tmp);
    remove("sectiong.txt"); //the file to delete
    rename("tmp.txt","sectiong.txt"); //rename the file
    if((file=fopen("sectiong.txt","rb+"))==NULL)
    {
        printf("Can not be opened.");

    }
    if(check==1)
    {
        printf("\n\t\tThe record has been deleted successfully.\n");
    }
    if(check==0)
        printf("\n\t\t\tERROR!!Record Not Found..\n");

    printf("\n");
    system("pause"); //Make the screen wait for a key press.


}
void add_new_student()
{

    print_title();
    char check='y';
    int k=1;
    while(check=='y'||check=='Y')
    {
        printf("\t\tStudent %d:\n",k);


        printf("\t\t\t\tEnter First name:");
        scanf("%s",std.first_name);



        printf("\n\t\t\t\tEnter Last name:");
        scanf("%s",std.last_name);

        printf("\n\t\t\t\tEnter Student ID:");
        scanf("%s",std.student_id);

        printf("\n\t\t\t\tIf Female write F or If Male write M:");
        scanf("%s",std.gender);

        getchar();

        printf("\n\t\t\t\tEnter Father name:");
        gets(std.father_name);

        printf("\n\t\t\t\tEnter Mother name:");
        gets(std.mother_name);

        printf("\n\t\t\t\tEnter Date of Birth:");
        scanf("%s",std.date_of_birth);


        fwrite(&std,sizeof(std),1,file);
        printf("\n\t\t\t\tDo You Want to Add More Information (y/n)--> ");
        getchar();
        check=getchar();
        printf("\n");
        k++;
    }

}


void display_student()
{
    print_title();
    saved_data();
    node *c=head;
    if(head!=NULL)
    {
        printf("\t\t\t\t\tSTUDENT NAME:\t\tID:\n\n");

    }
    while(c!=NULL)
    {
        printf("\t\t\t\t\t%s %s\t\t%s\n",c->first_name,c->last_name,c->student_id);
        c=c->next;
    }

    printf("\n\nTotal Female Student: %d && Total Male Student: %d.\n",f,m);
    printf("\n");
    system("pause"); //Make the screen wait for a key press.

}
void break_t(unsigned int t)
{
    clock_t tym=t+clock();
    while(tym>clock());
}

void date_time()
{
    char tim[50];
    char day[50];
    time_t currenttime;
    time(&currenttime);
    struct tm *myt=localtime(&currenttime);
    strftime(tim,sizeof(tim),"%x",myt);
    strftime(day,sizeof(day),"%I:%M%p",myt);

    printf("\t\tDate:%s\t\t\t\t\t\t\t\tTime:%s\n",tim,day);
}

void intro()
{
    while(1)
    {
        int k,p;
        system("cls");//to make the screen clean
        printf("\n\n");
        //printf("************************************************************************************************************************\n\n");
        //printf("\t\t\t\t\tDaffodil International University\n\n");
        //printf("************************************************************************************************************************");
        printf("\n\n\n");
        date_time();
        printf("\n\n\n\n");
        printf("\t\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
        printf("\t\t\t\t\t*-------------------------------------*\n");
        printf("\n\n");
        if(k==1)
        {
            printf("\n\n");
            printf("\t\t\t\t\t\tWrong password!! ,try again\n");
        }
        k=0;
        if(p==1)
        {
            printf("\n");
            printf("\t\t\t\t\t\tIncorrect Username!! ,try again\n");
        }
        p=0;
        char username[100],password[100];
        printf("\n\t\t\t\t\t\tUsername:");
        scanf("%s",username);
        getchar();
        printf("\n");
        printf("\t\t\t\t\t\tPassword:");
        int l=0;


        do
        {
            password[l]=getch();
            if(password[l]!='\r');
            {
                printf("*");
            }
            l++;
        }
        while(password[l-1]!='\r');
        password[l-1]='\0';

        if(strcmp(username,"diu")==0&&strcmp(password,rtrv)==0)
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\tWelcome to student management system");
            for(int i=0; i<10; i++)
            {
                break_t(130);
                printf(".");
            }

            break;
        }
        else
        {
            if(strcmp(password,rtrv)!=0)
            {
                k=1;
            }
            if(strcmp(username,"diu")!=0)
            {
                p=1;
            }

            //system("cls");

        }
    }

}


int main()
{

    if((file=fopen("sectiong.txt","rb+"))==NULL)
    {
        if((file=fopen("sectiong.txt","wb+"))==NULL)
        {
            printf("The file can not be opened\n");
        }
    }


    f1=fopen("password.txt","r");
    fscanf(f1,"%s",&rtrv);

    intro();

    while(1)
    {


        int press;
        printf("\n");
        print_title();

        printf("\t\t\t\t\t\t1. Add New Records\n\n");
        printf("\t\t\t\t\t\t2. Display all Students Records\n\n");
        printf("\t\t\t\t\t\t3. Delete Records\n\n");
        printf("\t\t\t\t\t\t4. Search and View Records\n\n");
        printf("\t\t\t\t\t\t5. Modify Records\n\n");
        printf("\t\t\t\t\t\t6. Change Password\n\n");
        printf("\t\t\t\t\t\t7. Exit\n\n");

        int choice;
        printf("\n\t\t\t\t\t\tEnter Option:--> ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:

        {
            add_new_student( );

        }
        break;
        case 2:

        {
            display_student();

        }
        break;
        case 3:

        {
            remove_student();
        }
        break;
        case 4:

        {
            search_student();

        }
        break;
        case 5:

        {
            modify_student_data();
        }
        break;
        case 6:
        {
            change_password();
        }
        break;
        case 7:

        {
            system("cls");
            exit(0);

        }
        break;
        default:
        {
            printf("Wrong Input.. END!!\n");

        }
        }
    }

    return 0;

}
