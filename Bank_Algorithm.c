#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include  <sys/types.h>

#define uint32 unsigned int
#define TRUE 1
#define FALSE 0
uint32 gTotalAccounts=0;

typedef struct balance_info
{
   uint32 withdrawable;
   uint32 current;
}balance_info_struct;

struct acc_info
{
   char name[10];
   char mail_address[15];
   uint32 acc_number;
   balance_info_struct balance_struct;
   struct acc_info *next;
}*start_bank= NULL, *current_bank = NULL;

typedef struct Transaction
{
   uint32 acc_num;
   uint32 Amount;
}sTransaction;

typedef struct acc_info ACC_INFO_STRUCT ;

typedef struct query_ac_info_struct
{
   ACC_INFO_STRUCT *info;
   uint32 acc_num;
}query_ac_info_struct;

void Initial_all_account_adding();
void display_all_accounts_info();
int account_deletion(uint32);
int query_details(query_ac_info_struct *) ;    
void deposite_money_through_ATM(sTransaction *) ;       
void deposite_money_through_counter(sTransaction * ) ;   
void withdraw_money_through_ATM(sTransaction *) ;       
void withdraw_money_through_counter(sTransaction *) ;   

int main(int argc, char*argv[])
{
   uint32 Option=0;

    while(1)
   {
      printf("\n\n Select one of the option\n 1.Initial all Account adding\n 2.Account Deletion\n 3.Query Account Details using A/c Number\n 4..Deposite Amount Through ATM\n 5.Deposite Amount through Counter\n 6.Withdraw Amount Through ATM\n 7.Withdraw Amount through Counter\n \n");
      scanf("%d",&Option);

      if(Option ==1)
      {
         if(start_bank == NULL)
         {
            Initial_all_account_adding();
         }
         
      }
      else if (Option ==2)
      {
         uint32 acc_num_to_delete;
         int status=0;

         printf("\n Enter Account number to delete\n");
         scanf("%d",&acc_num_to_delete);

         status = account_deletion(acc_num_to_delete);
         pthread_create(&thread_id[2],NULL,&account_deletion,(void*)acc_num_to_delete)
         
         if(status == TRUE)
         {
            printf("\n A/c Deletion is successful\n");
         }
         else
         {
            printf("\n A/c Deletion is Failed \n");
         }

      }
      else if (Option ==3)
      {
         int status=0;
         query_ac_info_struct *query;  

         query = (query_ac_info_struct*) malloc(sizeof(query_ac_info_struct));
                
         printf("\n Enter Person Name for Querying Account details\n");
         scanf("%d",&query->acc_num);
         status= query_details(query);

         if(status == TRUE)
         {
            printf("\n Account details are \n Person name:::%s\n Mailing address:::%s\n Account Number::::%d\n Withdrawable Balance is :::%d\n Current Balance is :::%d\n",query->info->name,query->info->mail_address,query->info->acc_number,query->info->balance_struct.withdrawable,query->info->balance_struct.current) ;
         }
         else
         {
            printf("\n Details Not FOund\n");     
         }
         free(query);
      }
      else if (Option == 4)
      {
         sTransaction Transact;
         printf("\n ATM Deposite:: Enter account number and amount to deposite\n");
         scanf("%d%d",&Transact.acc_num, &(Transact.Amount));
         deposite_money_through_ATM(&Transact) ;       
      }
      else if (Option == 5)
      {
         sTransaction Transact;
         printf("\n Counter Deposite:: Enter account number and amount to deposite\n");
         scanf("%d%d",&Transact.acc_num, &(Transact.Amount));
         deposite_money_through_counter(&Transact ) ;    
      }
      else if (Option == 6)
      {
         sTransaction Transact;
         printf("\n ATM Withdrawal:: Enter account number and amount to deposite\n");
         scanf("%d%d",&Transact.acc_num, &(Transact.Amount));
         withdraw_money_through_ATM(&Transact) ;     
      }
      else if (Option == 7)
      {
         sTransaction Transact;
         printf("\n Counter Withdrawal:: Enter account number and amount to deposite\n");
         scanf("%d%d",&Transact.acc_num, &(Transact.Amount));
         withdraw_money_through_counter(&Transact) ;    
      }
      else if(Option ==8)
      {
         display_all_accounts_info();
      }
      else
      {
         printf("\n Wrong Choice\n");
         break;
      }
   }

   return 0;
}


void Initial_all_account_adding()
{
   int i;
   for(i=0; i<5; i++)
   {
      ACC_INFO_STRUCT *acc_data = (ACC_INFO_STRUCT *) malloc(sizeof(ACC_INFO_STRUCT)) ;

      acc_data->acc_number = i+1; 
      acc_data->balance_struct.current = 1000;
      acc_data->balance_struct.withdrawable = 1000;
      acc_data->next = NULL;

      strcpy(acc_data->name, "A\0");
      *(acc_data->name) = ((*(acc_data->name))+i) ;

      strcpy(acc_data->mail_address, "ADDRESS1\0");
      *(acc_data->mail_address+7) = ((*(acc_data->mail_address+7))+i) ;
    
      if(start_bank == NULL)
      {
         start_bank = acc_data;
         current_bank = acc_data ;
         gTotalAccounts++;
      }
      else
      {
         ACC_INFO_STRUCT *temp1=start_bank, *temp2=start_bank;
         while(temp1 != NULL)
         {
            temp2 = temp1;
            temp1 = temp1->next;
         }
         
         temp2->next = acc_data;
         current_bank = acc_data;
         gTotalAccounts++;
      }
   }
}

int query_details(query_ac_info_struct *query) 
{
   ACC_INFO_STRUCT *tmp = start_bank ;

   while(tmp != NULL)
   {      
      if(query->acc_num == tmp->acc_number)
      {  
         query->info = tmp ;
         return TRUE;
      }
      tmp = tmp->next;
   }

   return FALSE;
}

int account_deletion(uint32 acc_num)
{
   ACC_INFO_STRUCT *tmp1 = start_bank ;
   ACC_INFO_STRUCT *tmp2 = tmp1 ;

   while(tmp1 != NULL)
   {
      if(acc_num == tmp1->acc_number )
      {
         ACC_INFO_STRUCT *tmp3 = tmp1->next ;
         printf("\n Account details before deleting are \n Person name:::%s\n Mailing address:::%s\n Account Number::::%d\n Withdrawable Balance is :::%d\n Current Balance is :::%d\n",tmp1->name,tmp1->mail_address,tmp1->acc_number,tmp1->balance_struct.withdrawable,tmp1->balance_struct.current) ;

         if(tmp1 == start_bank)
         {
            start_bank = start_bank->next;
         }

         free(tmp1);
         if(tmp2)
         {
            tmp2->next = tmp3;
         }         
         return TRUE;
      }
      tmp2 = tmp1;
      tmp1 = tmp1->next;
   }
   return FALSE;
}


void deposite_money_through_ATM(sTransaction Transact )      
{
      ACC_INFO_STRUCT *tmp = start_bank ;
      while(tmp != NULL)
      {
         if(Transact.acc_num == tmp->acc_number )
         { 
            tmp->balance_struct.withdrawable += Transact.Amount;
            tmp->balance_struct.current += Transact.Amount;
            break;
         }
         tmp =tmp->next;
      }
}
void deposite_money_through_counter(sTransaction Transact )  
{
   ACC_INFO_STRUCT *tmp = start_bank ;
   while(tmp != NULL)
   {
      if(Transact.acc_num == tmp->acc_number )
      { 
         tmp->balance_struct.withdrawable += Transact.Amount;
         tmp->balance_struct.current += Transact.Amount;
         break;
      }
      tmp =tmp->next;
   }

}
void withdraw_money_through_ATM(sTransaction Transact  )     
{
   ACC_INFO_STRUCT *tmp = start_bank ;
   while(tmp != NULL)
   {
      if(Transact.acc_num == tmp->acc_number)
      {
         if(tmp->balance_struct.withdrawable >= Transact.Amount)
         {
            tmp->balance_struct.withdrawable -= Transact.Amount;
            tmp->balance_struct.current -= Transact.Amount;
         }
         break;
      }
      tmp =tmp->next;
   }

}

void withdraw_money_through_counter(sTransaction Transact )    
{
   ACC_INFO_STRUCT *tmp = start_bank ;
   while(tmp != NULL )
   {
      if(Transact.acc_num == tmp->acc_number )
      {
         if(tmp->balance_struct.withdrawable >= Transact.Amount)
         {
            tmp->balance_struct.withdrawable -= Transact.Amount;
            tmp->balance_struct.current  -= Transact.Amount;
         }         
         break;
      }
      tmp =tmp->next;
   }
}


void display_all_accounts_info()
{
   ACC_INFO_STRUCT *tmp = start_bank ;
   
   while( tmp != NULL)
   {
      printf("\n Account details before deleting are \n Person name:::%s\n Mailing address:::%s\n Account Number::::%d\n Withdrawable Balance is :::%d\n Current Balance is :::%d\n",tmp->name,tmp->mail_address,tmp->acc_number,tmp->balance_struct.withdrawable,tmp->balance_struct.current) ;
      tmp = tmp->next;
   }
}