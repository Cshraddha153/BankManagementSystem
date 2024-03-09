 // BANK MANAGEMENT SYSTEM  

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

class Bank_Account{
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

    public:
       void modify();

       void report() const;
       int retacno() const{
        return account_number;
       }

       void dep(int x){
        Money_Deposit+=x;
       }

       void draw(int x){
        Money_Deposit+=x;
       }
         
       int retdeposit() const{
          return Money_Deposit;
       }
       void create_account();
       void Display_Account();
};

void Bank_Account::report() const{
    cout<<account_number<<setw(10)<<" "<< name<<setw(10)<<type<<setw(8)<<Money_Deposit<<endl;
}
void Bank_Account::create_account(){
    system("cls");
    cout<<"\t Enter the account number : ";
    cin>>account_number;
    cout<<"\t Enter the name of the account holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Enter the type of the account (C/S) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount (>=500 for saving account and >= 1000 for current ) : ";
    cin>>Money_Deposit; 
    cout<<"\n Account created... :) \n";
}

void Bank_Account::Display_Account(){
    cout<<"\t Bank Account Number : "<<account_number<<endl;
    cout<<"\t Account Holder Name : "<<name<<endl;
    cout<<"\t Type of Account : "<<type<<endl;
    cout<<"\t Balance amount : "<<Money_Deposit<<endl; 
}
void Bank_Account::modify(){
    cout<<"\t Account Number :  "<<account_number<<endl;
    cout<<"\t Modify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify type of account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Modify Balance amount : ";
    cin>>Money_Deposit;
}
void write_account(){// function to write record in binary file
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int n){
    Bank_Account ac;
    ifstream inFile;   //input file stream
    ofstream outFile;  //output file stream
    inFile.open("account.dat",ios::binary);
    if(inFile){
        cout<<"File could not be open || press any key....";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))){
        if(ac.retacno()!=n){
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.data","Bank_Account.dat");
    cout<<"\t RECORD DELETED......."<<endl;
}

void display_details(int n){
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! press any key...";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))){
        if(ac.retacno()==n){
            ac.Display_Account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\t Account number doesn't exist"<<endl;
    }
}

void display_All(){
   system("cls");
   Bank_Account ac;
   ifstream inFile;
   inFile.open("account.dat",ios::binary);
   if(!inFile){
    cout<<"File could not be open !! press any key....";
    return;
   }
   cout<<"\t Bank Account Holder List "<<endl;
   cout<<"----------------------------------------------------------"<<endl;
   cout<<" A/C  no.         NAME         TYPE         BALANCE"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
   while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
   {
    ac.report();
   }
   inFile.close();
}

void Money_deposit_withdraw(int n,int option){
    int amt;
    bool found=false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open !! press any key...";
        return;
    }
    while(!File.eof() && found==false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(option==1){
                cout<<"\t ENter the amount to be deposited :  ";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2){
                cout<<"\t Enter amount to be withdraw ";
                cin>>amt;
                int balance = ac.retdeposit() - amt;
                if(balance < 0){
                    cout<<"\t Insuffcient Balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur);   // move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));   // write the record in the file
            cout<<"\t Record Update "<<endl;
            found=true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record Not Found "<<endl;
    }
}

void Updation_bank_account(int n){
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.det", ios::binary|ios::in|ios::out);   // open the file in binary mode
    if(!File){
        cout<<"File could not be open  !!  press any key.... ";
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));  // read the record from the file;
        if(ac.retacno() == n){
            ac.Display_Account();
            cout<<endl;
            cout<<"\t Enter the new details of the account "<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));  // move the pointer to the position of the file
            File.seekp(pos,ios::cur); //move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));  //write the record int he file
            cout<<"\t Record Updated"<<endl;
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record NOt FOund "<<endl;
    }
}
int main(){
    char ch;
    int num;
    
    do{

    cout<<"\t\t ---------------------------------------------------------------------------------"<<endl;
    cout<<"\t\t |                WELCOME    TO    BANK    MANAGEMENT    SYSTEM                |"<<endl;
    cout<<"\t\t ---------------------------------------------------------------------------------"<<endl;

    cout<<endl;
    cout<<"\t----- MAIN MENU ------"<<endl;
    cout<<"\t 1. Create Account "<<endl;
    cout<<"\t 2. Deposit Money "<<endl;
    cout<<"\t 3. Withdraw Money "<<endl;
    cout<<"\t 4. Balance Enquiry "<<endl;
    cout<<"\t 5. All Account Holder List"<<endl;
    cout<<"\t 6. Close an Account "<<endl;
    cout<<"\t 7. Modify an Account "<<endl;
    cout<<"\t 8. Exit "<<endl;
    cout<<endl;

    cout<<"Enter Your Choice (1-8) : ";
    cin>>ch;

    switch (ch)
    {   
        case '1':
            write_account();
            break;
        case '2':
            system("cls");
            cout<<"\t Enter the account number : ";
            cin>>num;
            Money_deposit_withdraw(num, 1);      //deposit function
            break;
        case '3':
            system("cls");
            cout<<"\t Enter the account number : ";
            cin>>num;
            Money_deposit_withdraw(num, 2);      //withdraw function
            break;       
        case '4':
            system("cls");
            cout<<"\t Enter the account number : ";
            cin>>num;
            display_details(num);                //balance enquiry function
            break;
        case '5':
            display_All();                       //display all functiom
            break;
        case '6':
            system("cls");
            cout<<"\t Enter the account number : ";
            cin>>num;
            delete_account(num);                 //close account function
            break;
        case '7':
            system("cls");
            cout<<"\t Enter the account number : ";
            cin>>num;
            Updation_bank_account(num);          // modify account function
            break;
        case '8':
             cout<<"\t Thanks for using the Bank Managemnet Sytem  "<<endl;
            break;
    }
    cin.ignore();
    cin.get();
    }while(ch!='8');
    return 0;   
}