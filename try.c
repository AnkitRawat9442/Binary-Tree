#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>
void mainmenu() ;
void login() ;
void  openacc() ;
void deposite() ;
void details(); 



void login()
{   
    char username[15] ;
    char pass[15] ;
     // clrscr() ;
      printf("\n\n\t\tEnter Username: ") ;
      gets(username) ;
      printf("\n\t\tEnter Password: ") ;
      gets(pass) ;

      if(strcmp(username,"bank123")==0)
      {
          if(strcmp(pass,"bank@123")==0)
          {
              printf("\t\tLogin successfull") ;
               printf("\n\t\tEnter any key for continue") ;
              getch() ;
              mainmenu();
           
          }
          else 
          {
              printf("\t\tWrong password") ;
          }
      }
      else {
          printf("\t\tWrong Username") ;
      }
}

void mainmenu()
{
    int x ; 
    while(1)
    {
        printf("\n1: Open a new account\n") ;
        printf("2: Deposit money\n") ;
        printf("3: Account details\n") ;

        printf("\n\n\tWhat task do you want to do ?") ;
        scanf("%d",&x) ;

        switch(x)
        {
            case 1: 
              openacc() ;
            break ;
            case 2:
            deposite() ;
            break; 
            case 3: 
            details();
            break ; 
            
        }
    }
}

void openacc()
{

    char name[30] ;
    char fname[30] ;
    int age ; 
    long long int phoneno ; 
  char cc;

    printf("Full name: ") ;
    scanf("%c",&cc);
    fgets(name , 30 , stdin) ;
   
    printf("\nFather's name: ") ;
  
    
    
  fgets(fname , 30 , stdin) ;
    
    printf("\nYour Age: ") ;
    scanf("%d",&age) ;
   
    
    printf("\nEnter your Mobile number: ") ;
    scanf("%lli",&phoneno) ;


    printf("Name : %s Father Name :  %s Age :  %d \nMobile number :  %lli",name,fname,age,phoneno);
}
void deposite()
{
   printf("qewr\n") ;
}
void details()
{
    printf("lljhdsl\n") ;
}


int main()
{   
    //clrscr() ;
    printf("\n\n\t\t WELCOME TO BANKING MANAGEMENT SYSTEM: ");
    printf("\n\t\tEnter any key for continue......") ;
    getch() ;
    login() ;
   Systen("clear");
    
return 0 ;
}