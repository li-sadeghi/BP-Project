#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include "cJSON.h"
#include "cJSON.c"
void Menu();
void Log_In();
void Forgot_Pass();
int CheckBanUser(char*Username);
void Sign_Up();
int IsUserOk(char*Username);
int isPassOK(char*Username,char *Pass);
void AddJsonToFile(char*ShopUser,char*Username);
void User_Page(char *Username);
void Customer(char*Username);
void Retailer(char*Username);
void Admin(char*Username);
void View_Profile(char*Username,int role);
void View_Product(char*Username);
void Buy_Product(char*Username,char *ProdName);
float Check_Discount_Code(char*Code);
void History(char*Username);
void New_Comment(char*Username,char *Name);
void View_Categories(char*Username);
void New_Product(char*Username);
int isNameOk(char *Name);
int isCatOk(char*Cat);
void Sales_list(char*Username);
void View_User_list(char*Username);
void Ban_User(char*Username);
int isUSERBAN(char*Username);
void Unban_user(char*Username);
int isUSERUNBAN(char*Username);
void Get_Discount_Code(char *Username);
void Add_Auction(char *Username);
void Buy_Auction(char *Username);
void View_Auction(char*Usernames);
void Delete_Auction(char *Username,int which);
void View_Confirm_Comment(char*Username);

int main(){
    printf("Hello User! Press Enter-Key to continue :))");
    getchar();
    system("cls");
    Menu();
    return 0;
}
void Menu(){
    printf("These are your options.Please enter an option:\n1.Sign Up\n2.Log In\n3.Exit\n");
    char Choosen;
    do
    {
        scanf("%c",&Choosen);
        switch (Choosen)
        {
        case '1':
            system("cls");
            Sign_Up();
            return;
            break;
        case '2':
            system("cls");
            Log_In();
            return;
            break;
        case '3':
            system("cls");
            return ;
            break;
        default:
            system("cls");
            printf("Ther is not your choosen option!Please enter 1 ,2 or 3:\n1.Sign Up\n2.Log In\n3.Exit\n");
            break;
        }
    } while (1);
    return;
}
void Log_In(){
    char *Username=(char*)malloc(30*sizeof(char));
    char *Pass=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of  logging in to your account you can return to the main menu by entering the number 0!\n");
        printf("If you forget your password, Enter -1 !\n");
        printf("Username:");scanf("%s",Username);
        if(strcmp(Username,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        else if(strcmp(Username,"-1")==0){
            system("cls");
            Forgot_Pass();
            return;
        }
        else if(IsUserOk(Username)==0){
            system("cls");
            printf("There is no user with this username!Try again!\n");
        }
        else if(CheckBanUser(Username)==1){
            printf("You are on the banned list and you are not allowed to enter the store...\n");
            printf("Press Enter-Key to return to the main menu...");
            getchar();
            getchar();
            system("cls");
            Menu();
            return;
        }
        else break;
    } while (1);
    do
    {
        printf("Password:");scanf("%s",Pass);
        if(strcmp(Pass,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        else if(strcmp(Pass,"-1")==0){
            system("cls");
            Forgot_Pass();
            return;
        }
        else if(isPassOK(Username,Pass)==0){
            system("cls");
            printf("Note that at each stage of  logging in to your account you can return to the main menu by entering the number 0!\nYour password is not correct!Try again!\n");
            printf("If you forget your password, Enter -1 !\n");
        }
        else break;
    } while (1);
    getchar();
    system("cls");
    printf("You have successfully logged in to your account!\n");
    sleep(2);
    system("cls");
    free(Pass);
    User_Page(Username);
    return;
}
void Forgot_Pass(){
    printf("You have successfully entered your password forgetting page...");
    sleep(2);
    system("cls");
    char *Username=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of forgetting pass you can return to the main menu by entering the number 0!\n");
        printf("At first you must enter your username\n");
        printf("Username:");scanf("%s",Username);
        if(strcmp(Username,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        else if(IsUserOk(Username)==0){
            system("cls");
            printf("There is no user with this username!Try again!\n");
        }
        else if(CheckBanUser(Username)==1){
            printf("You are on the banned list and you are not allowed to enter the store...\n");
            printf("Press Enter-Key to return to the main menu...");
            getchar();
            getchar();
            system("cls");
            Menu();
            return;
        }
        else break;
    } while (1);
    system("cls");
    printf("Then you need to answer the two security questions you were asked during registration.\n");
    strcat(Username,".json");
    FILE *Userfile=fopen(Username,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,Userfile);
    cJSON *UserJson,*Q1,*Q2;
    UserJson=cJSON_Parse(jsonData);
    Q1=cJSON_GetObjectItem(UserJson,"Question1");
    Q2=cJSON_GetObjectItem(UserJson,"Question2");
    char *Qu1=(char*)malloc(30*sizeof(char));
    char *Qu2=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of forgetting pass you can return to the main menu by entering the number 0!\n");
        printf("What month is your birth month?:");scanf("%s",Qu1);
        if(strcmp(Qu1,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        else if(strcmp(Qu1,Q1->valuestring)!=0){
            system("cls");
            printf("Your answer is not correct!Try again\n");
        }
        else break;
    } while (1);
    do
    {
        printf("What color is your favorite color?:");scanf("%s",Qu2);
        if(strcmp(Qu2,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        else if(strcmp(Qu2,Q2->valuestring)!=0){
            system("cls");
            printf("Your answer is not correct!Try again\n");
            printf("Note that at each stage of forgetting pass you can return to the main menu by entering the number 0!\n");
        }
        else break;
    } while (1);
    system("cls");
    printf("You have successfully completed the password forgetting steps. \nNow just enter your new password to change your password.\n");
    char *newPass=(char*)malloc(30*sizeof(char));
    printf("you can return to the main menu by entering the number 0!\n");
    printf("New Password:");scanf("%s",newPass);
    if(strcmp(newPass,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    printf("Your password was changed successfully! You will return to the main menu in a few seconds...");
    cJSON *Pass;
    Pass=cJSON_GetObjectItem(UserJson,"Password");
    cJSON_SetValuestring(Pass,newPass);
    fclose(Userfile);
    Userfile=fopen(Username,"w");
    fputs(cJSON_Print(UserJson),Userfile);
    fclose(Userfile);
    sleep(3);
    free(jsonData);
    free(newPass);
    free(Qu1);
    free(Qu2);
    cJSON_Delete(UserJson);
    Menu(Username);
    return;
}
int CheckBanUser(char*Username){
    FILE *file;
    file=fopen("BanUsers.json","r");
    if(file==NULL)return 0;
    else{
        char*jsonData=(char*)malloc(10000*sizeof(char));
        fread(jsonData,100,100,file);
        cJSON *Bans,*ArrOfBans,*Element;
        Bans=cJSON_Parse(jsonData);
        ArrOfBans=cJSON_GetObjectItem(Bans,"BanUsers");
        cJSON_ArrayForEach(Element,ArrOfBans){
            if(strcmp(Element->valuestring,Username)==0){
                free(jsonData);
                cJSON_Delete(Bans);
                return 1;
            }
        }
        free(jsonData);
        cJSON_Delete(Bans);
        return 0;
    }
}
void Sign_Up(){
    char *User=(char*)malloc(30*sizeof(char));
    char *Pass=(char*)malloc(30*sizeof(char));
    char *FName=(char*)malloc(30*sizeof(char));
    char *LName=(char*)malloc(30*sizeof(char));
    char *role=(char*)malloc(10*sizeof(char));
    char R;
    unsigned long long SMoney;
    char *Q1=(char*)malloc(30*sizeof(char));
    char *Q2=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of registration you can return to the main menu by entering the number 0!\n");
        printf("Username:");scanf("%s",User);
        if(strcmp(User,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
        }
        if(IsUserOk(User)==0)break;
        else{
            system("cls");
            printf("This user already exists!Try again!!\n");
        }
    } while (1);
    printf("Password:");scanf("%s",Pass);
    if(strcmp(Pass,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    printf("Firstname:");scanf("%s",FName);
    if(strcmp(FName,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    printf("Lastname:");scanf("%s",LName);
    if(strcmp(LName,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    getchar();
    printf("Please enter your role:\n1.Customer\n2.Retailer\n3.Admin\n");
    do
    {
        scanf("%c",&R);
        switch (R)
        {

        case '1':
            strcpy(role,"Customer");
            break;
        case '2':
            strcpy(role,"Retailer");
            break;
        case '3':
            strcpy(role,"Admin");
            break;
        case '0':
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            sleep(2);
            Menu();
            return;
            break;
        default:
            printf("Ther is not your choosen option!Please enter 1 ,2 or 3:\n1.Customer\n2.Retailer\n3.Admin\n");
            break;
        }
        getchar();
    } while (!(R=='1'||R=='2'||R=='3'));
    printf("StartingMoney:");scanf("%llu",&SMoney);
    if(SMoney==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    system("cls");
    printf("Then you have to answer two security questions.\nThese questions will help you when you forget your password:\n");
    printf("What month is your birth month?:");scanf("%s",Q1);
    if(strcmp(Q1,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    printf("What color is your favorite color?:");scanf("%s",Q2);
    if(strcmp(Q2,"0")==0){
        system("cls");
        printf("You have successfully returned to the main menu!please wait...");
        sleep(2);
        Menu();
        return;
    }
    cJSON *ShopUser=cJSON_CreateObject(),*History=cJSON_CreateArray();
    cJSON_AddStringToObject(ShopUser,"UserName",User);
    cJSON_AddStringToObject(ShopUser,"Password",Pass);
    cJSON_AddStringToObject(ShopUser,"FirstName",FName);
    cJSON_AddStringToObject(ShopUser,"LastName",LName);
    cJSON_AddStringToObject(ShopUser,"Role",role);
    cJSON_AddNumberToObject(ShopUser,"StartingMoney",SMoney);
    cJSON_AddStringToObject(ShopUser,"Question1",Q1);
    cJSON_AddStringToObject(ShopUser,"Question2",Q2);
    cJSON_AddNumberToObject(ShopUser,"Number of successful purchases",0);
    cJSON_AddNumberToObject(ShopUser,"Points",0);    
    cJSON_AddItemToObject(ShopUser,"History",History);
    AddJsonToFile(cJSON_Print(ShopUser),User);
    FILE *file;
    file=fopen("Users.json","r+");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *Users,*Array,*newUser,*p;
    Users=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(Users,"Users");
    newUser=cJSON_CreateString(User);
    cJSON_AddItemToArray(Array,newUser);
    fclose(file);
    file=fopen("Users.json","w");
    fputs(cJSON_Print(Users),file);
    fclose(file);
    printf("Your registration was successful!\nPlease wait 3 seconds to get to the main menu...");
    sleep(3);
    system("cls");
    free(User);
    free(Pass);
    free(FName);
    free(LName);
    free(role);
    free(jsonData);
    free(Q1);
    free(Q2);
    cJSON_Delete(ShopUser);
    cJSON_Delete(Users);
    Menu();
    return;
}
int IsUserOk(char*Username){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"r");
    if(file==NULL)return 0;
    else return 1;
    free(newUser);
}
void AddJsonToFile(char*ShopUser,char*Username){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"w");
    fputs(ShopUser,file);
    fclose(file);
    free(newUser);
}
int isPassOK(char*Username,char *Pass){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *User,*Password;
    User=cJSON_Parse(jsonData);
    Password=cJSON_GetObjectItem(User,"Password");
    if(strcmp(Password->valuestring,Pass)==0)return 1;
    else return 0;
    free(newUser);
    free(jsonData);
    cJSON_Delete(User);
}
void User_Page(char *Username){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *User,*Role;
    User=cJSON_Parse(jsonData);
    Role=cJSON_GetObjectItem(User,"Role");
    if(strcmp(Role->valuestring,"Customer")==0){
        Customer(Username);
    }
    else if(strcmp(Role->valuestring,"Retailer")==0){
        Retailer(Username);
    }
    else if(strcmp(Role->valuestring,"Admin")==0){
        Admin(Username);
    }
    free(newUser);
    free(jsonData);
    cJSON_Delete(User);
}
void Customer(char*Username){
    char option;
    do
    {
        printf("Enter your desired option:\n1.View Profile\n2.View products\n3.History\n4.Get Discount Code\n5.View Auctions\n6.Logout\n");
        scanf("%c",&option);
        switch (option)
        {
        case '1':
            system("cls");
            View_Profile(Username,1);
            return;
            break;
        case '2':
            system("cls");
            View_Product(Username);
            return;
            break;
        case '3':
            system("cls");
            History(Username);
            return;
            break;
        case '4':
            system("cls");
            Get_Discount_Code(Username);
            return;
            break;
        case '5':
            system("cls");
            Buy_Auction(Username);
            return;
            break;
        case '6':
            system("cls");
            printf("You have successfully logged out of your account!Please wait...");
            getchar();
            sleep(2);
            system("cls");
            Menu();
            return;
            break;
        default:
            system("cls");
            printf("Invalid option!\n");
            sleep(1);
            system("cls");
            break;
        }
        if(option=='1'||option=='2'||option=='3')break;
    } while (1);
    
}
void Retailer(char*Username){
    char option;
    do
    {
        printf("Enter your desired option:\n1.View Profile\n2.View Categories\n3.Create a new product\n4.Sales list\n5.Add Auction\n6.View your Auctions\n7.Logout\n");
        scanf("%c",&option);
        switch (option)
        {
        case '1':
            system("cls");
            View_Profile(Username,2);
            return;
            break;
        case '2':
            system("cls");
            View_Categories(Username);
            return;
            break;
        case '3':
            system("cls");
            New_Product(Username);
            return;
            break;
        case '4':
            system("cls");
            Sales_list(Username);
            return;
            break;
        case '5':
            system("cls");
            Add_Auction(Username);
            return;
            break;
        case '6':
            system("cls");
            View_Auction(Username);
            return;
            break;
        case '7':
            system("cls");
            printf("You have successfully logged out of your account!Please wait...");
            getchar();
            sleep(2);
            system("cls");
            Menu();
            return;
            break;
        default:
            system("cls");
            printf("Invalid input!\n");
            break;
        }
        if(option=='1'||option=='2'||option=='3'||option=='4')break;
    } while (1);
        
}
void Admin(char*Username){
    char option;
    do
    {
        printf("Enter your desired option:\n1.View Profile\n2.View user list\n3.Ban user\n4.Unban user\n5.View and Confirm Comments\n6.Logout\n");
        scanf("%c",&option);
        switch (option)
        {
        case '1':
            system("cls");
            View_Profile(Username,3);
            return;
            break;
        case '2':
            system("cls");
            View_User_list(Username);
            return;
            break;
        case '3':
            system("cls");
            Ban_User(Username);
            return;
            break;
        case '4':
            system("cls");
            Unban_user(Username);
            return;
            break;
        case '5':
            system("cls");
            View_Confirm_Comment(Username);
            return;
            break;
        case '6':
            system("cls");
            printf("You have successfully logged out of your account!Please wait...");
            getchar();
            sleep(2);
            system("cls");
            Menu();
            return;
            break;
        default:
            system("cls");
            printf("Invalid input!\n");
            break;
        }
        if(option=='1'||option=='2'||option=='3'||option=='4')break;
    } while (1);
}
void View_Profile(char*Username,int role){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *User,*Fname,*Lname,*Balance,*NOSP,*Points;
    User=cJSON_Parse(jsonData);
    Fname=cJSON_GetObjectItem(User,"FirstName");
    Lname=cJSON_GetObjectItem(User,"LastName");
    Balance=cJSON_GetObjectItem(User,"StartingMoney");
    NOSP=cJSON_GetObjectItem(User,"Number of successful purchases");
    Points=cJSON_GetObjectItem(User,"Points");
    printf("This is your profile:\n");
    printf("Fisrtname: %s\nLastname: %s\nUsername: %s\n",Fname->valuestring,Lname->valuestring,Username);
    if(role==1||role==2){
        printf("Number of successful purchases: %g\nBalance: %g\n",NOSP->valuedouble,Balance->valuedouble);
    }
    if(role==1){
        printf("Your Points: %g\n",Points->valuedouble);
    }
    getchar();
    printf("Press Enter-key to return to the previous menu...");
    char ch;
    scanf("%c",&ch);
    if(role==1){
        system("cls");
        Customer(Username);
        return;
    }
    else if(role==2){
        system("cls");
        Retailer(Username);
        return;
    }
    else{
        system("cls");
        Admin(Username);
        return;
    }
    free(newUser);
    free(jsonData);
    cJSON_Delete(User);
}
void View_Product(char *Username){
    FILE *file;
    file=fopen("PRODUCTSNAME.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *ArrayOfNames,*ProductsNames,*Products,*OneProduct,*part;
    ProductsNames=cJSON_Parse(jsonData);
    ArrayOfNames=cJSON_GetObjectItem(ProductsNames,"Names");
    int i=0;
    cJSON_ArrayForEach(part,ArrayOfNames){
        i++;
    }
    if(i==0){
        printf("The product has not been added yet!\n");
        getchar();
        printf("\n\nPress Enter-key to return to the previous menu...");
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
    else{
        i=1;
        cJSON_ArrayForEach(part,ArrayOfNames){
            char *name=(char*)malloc(30*sizeof(char));
            char *jsonData2=(char*)malloc(10000*sizeof(char));
            strcpy(name,part->valuestring);
            strcat(name,"-Pro.json");
            FILE *Pro=fopen(name,"r");
            fread(jsonData2,100,100,Pro);
            cJSON *newPro,*Name,*Price,*category,*Seller_Name,*Available_number,*ArrOfComm,*Element;
            OneProduct=cJSON_Parse(jsonData2);
            newPro=cJSON_GetObjectItem(OneProduct,part->valuestring);
            Name=cJSON_GetObjectItem(newPro,"Name");
            Price=cJSON_GetObjectItem(newPro,"Price");
            category=cJSON_GetObjectItem(newPro,"category");
            Seller_Name=cJSON_GetObjectItem(newPro,"Seller Name");
            Available_number=cJSON_GetObjectItem(newPro,"Available number");
            ArrOfComm=cJSON_GetObjectItem(newPro,"BuyersComments");
            printf("#########################\n#   %d.%-18s#\n#########################\n",i,Name->valuestring);
            printf("**Price: %g\n**Category: %s\n**Seller Name: %s\n**Available Number: %g\n",Price->valuedouble,category->valuestring,Seller_Name->valuestring,Available_number->valuedouble);
            int k=1;
            printf("****Comments****\n");
            cJSON_ArrayForEach(Element,ArrOfComm){
                printf("%d. %s\n",k,Element->valuestring);
                k++;
            }
            fclose(Pro);
            i++;
            free(name);
            free(jsonData2);
        }
    }
    int entry;
    printf("\nTo buy a product, enter the number associated with it,\nor enter 0 to return to the previous menu...\n");
    scanf("%d",&entry);
    if(entry==0){
        fclose(file);
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
    else{
        i=1;
        cJSON_ArrayForEach(part,ArrayOfNames){
            if(i==entry){
                Buy_Product(Username,part->valuestring);
                return;
            }
            i++;
        }
    }
    free(jsonData);
    cJSON_Delete(ArrayOfNames);
    cJSON_Delete(OneProduct);
}
void Buy_Product(char*Username,char *ProdName){
    system("cls");
    char *name=(char*)malloc(30*sizeof(char));
    strcpy(name,ProdName);
    strcat(name,"-Pro.json");
    char*User=(char*)malloc(30*sizeof(char));
    strcpy(User,Username);
    strcat(User,".json");
    FILE *Userfile=fopen(User,"r"),*ProdFile=fopen(name,"r");
    char *jsonData1=(char*)malloc(10000*sizeof(char)),*jsonData2=(char*)malloc(10000*sizeof(char));
    fread(jsonData1,100,100,Userfile);
    fread(jsonData2,100,100,ProdFile);
    cJSON *UserJson,*ProdJson,*Prod,*ArrOfUser,*strName,*Num,*Price;
    UserJson=cJSON_Parse(jsonData1);
    ProdJson=cJSON_Parse(jsonData2);
    Prod=cJSON_GetObjectItem(ProdJson,ProdName);
    ArrOfUser=cJSON_GetObjectItem(UserJson,"History");
    int entry;
    if(cJSON_GetObjectItem(Prod,"Available number")->valuedouble==0){
        printf("Unfortunately, this product is out of stock!\n");
        printf("You will be returned to the previous menu...please wait...");
        sleep(3);
        system("cls");
        View_Product(Username);
        return;
    }
    do
    {
        printf("Note that at each stage of Buying you can return to the previous menu by entering the number 0!\n");
        printf("How many of these products do you want?\n");
        printf("This number should be less than %g :",cJSON_GetObjectItem(Prod,"Available number")->valuedouble+1);
        scanf("%d",&entry);
        if(entry==0){
            system("cls");
            printf("You have successfully returned to the previous menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Customer(Username);
            return;
            break;
        }
        else if(entry>cJSON_GetObjectItem(Prod,"Available number")->valuedouble){
            printf("This number of required items is not available. Please enter a smaller number ...");
            sleep(2);
            system("cls");
        }
        else break;
    } while (1);
    char *Code=(char*)malloc(30*sizeof(char));
    double Discount;
    do
    {
        printf("If you have a discount code, enter it. Otherwise, enter -1 to skip this step.\n");
        printf("Discount Code:");scanf("%s",Code);
        if(strcmp(Code,"-1")==0){
            Discount=0;
            break;
        }
        else if(strcmp(Code,"0")==0){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Customer(Username);
            return;
            break;
        }
        else{
            if(Check_Discount_Code(Code)==0){
                printf("The discount code entered is incorrect or may have been used before\n");
                sleep(2);
                system("cls");
                printf("Note that at each stage of Buying you can return to the previous menu by entering the number 0!\n");
            }
            else{
                printf("Your discount code was used successfully. You can not use this code anymore.\n");
                Discount=Check_Discount_Code(Code);
                break;
            }
        }
    } while (1);
    double price=(1-Discount)*entry*cJSON_GetObjectItem(Prod,"Price")->valuedouble;
    if(cJSON_GetObjectItem(UserJson,"StartingMoney")->valuedouble-price<0){
        printf("Your account balance is not enough for this purchase.\n");
        printf("You will be returned to the previous menu...please wait...");
        sleep(3);
        system("cls");
        View_Product(Username);
        return;
    }
    system("cls");
    printf("Your purchase was completed successfully!\n");
    printf("Your payment is $%g which will be deducted from your balance!\n",price);
    sleep(3);
    system("cls");
    strName=cJSON_CreateString(ProdName);
    Num=cJSON_CreateNumber(entry);
    Price=cJSON_CreateNumber(price);
    cJSON_AddItemToArray(ArrOfUser,strName);
    cJSON_AddItemToArray(ArrOfUser,Num);
    cJSON_AddItemToArray(ArrOfUser,Price);
    cJSON *SMoney,*AvNumber,*NumOfSucPur,*Points,*UserOfSeller;
    SMoney=cJSON_GetObjectItem(UserJson,"StartingMoney");
    AvNumber=cJSON_GetObjectItem(Prod,"Available number");
    UserOfSeller=cJSON_GetObjectItem(Prod,"Seller Username");
    char *U=(char*)malloc(30*sizeof(char));
    strcpy(U,UserOfSeller->valuestring);
    strcat(U,".json");
    FILE *SellerFile=fopen(U,"r");
    fread(jsonData1,100,100,SellerFile);
    cJSON *SellerUser,*SellerBalance;
    SellerUser=cJSON_Parse(jsonData1);
    SellerBalance=cJSON_GetObjectItem(SellerUser,"StartingMoney");
    cJSON_SetNumberValue(SellerBalance,cJSON_GetObjectItem(SellerUser,"StartingMoney")->valuedouble+entry*cJSON_GetObjectItem(Prod,"Price")->valuedouble);
    fclose(SellerFile);
    SellerFile=fopen(U,"w");
    fputs(cJSON_Print(SellerUser),SellerFile);
    fclose(SellerFile);
    NumOfSucPur=cJSON_GetObjectItem(UserJson,"Number of successful purchases");
    Points=cJSON_GetObjectItem(UserJson,"Points");
    cJSON_SetNumberValue(SMoney,cJSON_GetObjectItem(UserJson,"StartingMoney")->valuedouble-price);
    cJSON_SetNumberValue(AvNumber,cJSON_GetObjectItem(Prod,"Available number")->valuedouble-entry);
    cJSON_SetNumberValue(NumOfSucPur,cJSON_GetObjectItem(UserJson,"Number of successful purchases")->valuedouble+1);
    cJSON_SetNumberValue(Points,cJSON_GetObjectItem(UserJson,"Points")->valuedouble+10);
    fclose(Userfile);
    fclose(ProdFile);
    Userfile=fopen(User,"w");
    ProdFile=fopen(name,"w");
    fputs(cJSON_Print(UserJson),Userfile);
    fputs(cJSON_Print(ProdJson),ProdFile);
    fclose(Userfile);
    fclose(ProdFile);
    free(jsonData1);
    free(jsonData2);
    free(User);
    free(name);
    cJSON_Delete(UserJson);
    getchar();
    printf("Press Enter-Key to return to the previous menu...");
    getchar();
    system("cls");
    Customer(Username);
    return;
}
float Check_Discount_Code(char*Code){
    FILE *DCodes;
    DCodes=fopen("DiscountsCode.json","r");
    char*jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,DCodes);
    cJSON *DisCodes,*ArrOfCodes,*Element;
    DisCodes=cJSON_Parse(jsonData);
    ArrOfCodes=cJSON_GetObjectItem(DisCodes,"Codes");
    int i=0,j=-1,exist=0;
    double Dis;
    cJSON_ArrayForEach(Element,ArrOfCodes){
        if(j==i){
            Dis=Element->valuedouble;
            break;
        }
        else if(i%2==1)continue;
        else if(strcmp(Element->valuestring,Code)==0){
            j=i+1;
            exist=1;
        }
        i++;
    }
    if(exist==0){
        return 0;
    }
    else{
        cJSON_DeleteItemFromArray(ArrOfCodes,i);
        cJSON_DeleteItemFromArray(ArrOfCodes,i-1);
        fclose(DCodes);
        DCodes=fopen("DiscountsCode.json","w");
        fputs(cJSON_Print(DisCodes),DCodes);
        fclose(DCodes);
        if(Dis==10){
            return 0.1;
        }
        else if(Dis==25){
            return 0.25;
        }
        else{
            return 0.5;
        }
    }
    free(jsonData);
    cJSON_Delete(DisCodes);
}
void History(char*Username){
    FILE *file;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    file=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *User,*History,*product;
    User=cJSON_Parse(jsonData);
    History=cJSON_GetObjectItem(User,"History");
    int i=0,counter=1;
    cJSON_ArrayForEach(product,History){
        i++;
    }
    if(i==0){
        printf("No goods available!\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
    else{
        i=1;
        cJSON_ArrayForEach(product,History){
            if(i==1){
                printf("#########################\n#   %d.%-18s#\n#########################\n",counter,product->valuestring);
            }
            else if(i==2){
                printf("Numbers: %g\n",product->valuedouble);
            }
            else if(i==3){
                i=0;
                printf("Price: %g\n",product->valuedouble);
                counter++;
            }
            i++;
        }
    }
    int option;
    printf("\n\nYou can return to the previous menu by entering number 0 !\n");
    printf("Or you can enter your opinion about that product by entering the desired purchase number.\n");
    printf("Your comment will be displayed after the admin approval.\n");
    scanf("%d",&option);
    if(option==0){
        system("cls");
        getchar();
        Customer(Username);
        free(newUser);
        free(jsonData);
        return;
    }
    else{
        i=1;
        char Name[30];
        cJSON_ArrayForEach(product,History){
            if(i==(option-1)*3+1){
                strcpy(Name,product->valuestring);
                break;
            }
            i++;
        }
        system("cls");
        getchar();
        New_Comment(Username,Name);
        free(newUser);
        free(jsonData);
        return;
    }
    cJSON_Delete(User);
}
void New_Comment(char*Username,char *Name){
    FILE *CommFile=fopen("Comments.json","r");
    char*jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,CommFile);
    cJSON *CommJson,*ArrOfComm;
    CommJson=cJSON_Parse(jsonData);
    ArrOfComm=cJSON_GetObjectItem(CommJson,"Comments");
    printf("You can return to the previous menu by entering number 0 !.\n");
    printf("Enter your comment about this product.\n");
    printf("Your comment will be displayed after approval by the store admin.\n");
    char*newComment=(char*)malloc(10000*sizeof(char));
    gets(newComment);
    if(strcmp(newComment,"0")==0){
        system("cls");
        free(jsonData);
        free(newComment);
        History(Username);
        return;
    }
    else{
        cJSON_AddStringToObject(ArrOfComm,"Comments",Name);
        cJSON_AddStringToObject(ArrOfComm,"Comments",newComment);
        fclose(CommFile);
        CommFile=fopen("Comments.json","w");
        fputs(cJSON_Print(CommJson),CommFile);
        fclose(CommFile);
        system("cls");
        printf("Your comment was successfully sent to the store admin.\n");
        printf("Press Enter-Key to return to the previous menu.\n");
        getchar();
        system("cls");
        free(jsonData);
        free(newComment);
        History(Username);
        return;
    }
    cJSON_Delete(CommJson);
}
void View_Categories(char*Username){
    FILE *file;
    file=fopen("Categories.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *Cat,*Array,*Element;
    Cat=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(Cat,"Categories");
    int i=0;
    cJSON_ArrayForEach(Element,Array){
        i++;
    }
    if(i==0)printf("No category has been created yet!\n");
    else{
        i=1;
        printf("All available categories are as follows:\n");
        cJSON_ArrayForEach(Element,Array){
            printf("%d.%s\n",i,Element->valuestring);
            i++;
        }
    }
    fclose(file);
    getchar();
    printf("Press Enter-key to return to the previous menu...");
    getchar();
    system("cls");
    free(jsonData);
    cJSON_Delete(Cat);
    Retailer(Username);
    return;
}
void New_Product(char*Username){
    char *Name=(char*)malloc(30*sizeof(char)),*category=(char*)malloc(30*sizeof(char));
    unsigned long long price,Available_num;
    do
    {
        printf("Note that at each stage of adding product you can return to the previous menu by entering the number 0!\n");
        printf("Enter a name for your product: ");scanf("%s",Name);
        if(strcmp(Name,"0")==0){
            system("cls");
            printf("You have successfully returned to the previous menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Retailer(Username);
            return;
        }
        if(isNameOk(Name)==0){
            system("cls");
            printf("This product is already available!\n");
        }
        else break;
    } while (1);
    printf("Enter the price of your product: ");scanf("%llu",&price);
    if(price==0){
        system("cls");
        printf("You have successfully returned to the previous menu!please wait...");
        getchar();
        sleep(2);
        system("cls");
        Retailer(Username);
        return;
    }
    do
    {
        printf("Enter the category of your product: ");scanf("%s",category);
        if(strcmp(category,"0")==0){
            system("cls");
            printf("You have successfully returned to the previous menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Retailer(Username);
            return;
        }
        if(isCatOk(category)==0){
            system("cls");
            printf("Note that at each stage of adding product you can return to the main menu by entering the number 0!\nThis category does not exist!\n");
        }
        else break;
    } while (1);
    printf("Enter the available number of your product: ");scanf("%llu",&Available_num);
    if(Available_num==0){
        system("cls");
        printf("You have successfully returned to the previous menu!please wait...\n");
        getchar();
        sleep(2);
        system("cls");
        Retailer(Username);
        return;
    }
    cJSON *newProduct,*productPTR;
    newProduct=cJSON_CreateObject();
    productPTR=cJSON_CreateObject();
    cJSON_AddStringToObject(productPTR,"Name",Name);
    cJSON_AddNumberToObject(productPTR,"Price",price);
    cJSON_AddStringToObject(productPTR,"category",category);
    FILE *UserFile;
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    char Suffix[]=".json";
    strcat(newUser,Suffix);
    UserFile=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,UserFile);
    cJSON *User,*Fname,*Lname,*Buyers;
    char *FullName=(char*)malloc(30*sizeof(char));
    User=cJSON_Parse(jsonData);
    Fname=cJSON_GetObjectItem(User,"FirstName");
    Lname=cJSON_GetObjectItem(User,"LastName");
    strcpy(FullName,Fname->valuestring);
    strcat(FullName," ");
    strcat(FullName,Lname->valuestring);
    cJSON_AddStringToObject(productPTR,"Seller Name",FullName);
    cJSON_AddStringToObject(productPTR,"Seller Username",Username);
    cJSON_AddNumberToObject(productPTR,"Available number",Available_num);
    Buyers=cJSON_CreateArray();
    cJSON_AddItemToObject(productPTR,"BuyersComments",Buyers);
    cJSON_AddItemToObject(newProduct,Name,productPTR);
    FILE *Pnames=fopen("PRODUCTSNAME.json","r");
    char *jsonData2=(char*)malloc(10000*sizeof(char));
    fread(jsonData2,100,100,Pnames);
    cJSON *Prodnames,*Array,*newprod;
    Prodnames=cJSON_Parse(jsonData2);
    Array=cJSON_GetObjectItem(Prodnames,"Names");
    newprod=cJSON_CreateString(Name);
    cJSON_AddItemToArray(Array,newprod);
    fclose(Pnames);
    Pnames=fopen("PRODUCTSNAME.json","w");
    fputs(cJSON_Print(Prodnames),Pnames);
    fclose(Pnames);
    char *Suffix2="-Pro.json";
    strcat(Name,Suffix2);
    FILE *prod;
    prod=fopen(Name,"w");
    fputs(cJSON_Print(newProduct),prod);
    fclose(prod);
    free(jsonData);
    free(jsonData2);
    free(Name);
    free(category);
    free(FullName);
    cJSON_Delete(newProduct);
    cJSON_Delete(User);
    cJSON_Delete(Prodnames);
    printf("Your product has been successfully registered for sale...\n");
    sleep(1);
    getchar();
    printf("Press Enter-Key to return to the previous menu...\n");
    getchar();
    system("cls");
    Retailer(Username);
    return;
}
int isNameOk(char *Name){
    char *newname=(char*)malloc(30*sizeof(char));
    strcpy(newname,Name);
    strcat(newname,"-Pro.json");
    FILE *file=fopen(newname,"r");
    if(file==NULL)return 1;
    else return 0;
    free(newname);
}
int isCatOk(char*Cat){
    FILE *file=fopen("Categories.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *Cats,*Array,*Element;
    Cats=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(Cats,"Categories");
    int ok=0;
    cJSON_ArrayForEach(Element,Array){
        if(strcmp(Element->valuestring,Cat)==0){
            ok=1;
        }
    }
    fclose(file);
    free(jsonData);
    cJSON_Delete(Cats);
    return ok;
}
void Sales_list(char*Username){
    int j=0;
    FILE *file=fopen("Users.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *Users,*ArrOfUsers,*Element;
    Users=cJSON_Parse(jsonData);
    ArrOfUsers=cJSON_GetObjectItem(Users,"Users");
    cJSON_ArrayForEach(Element,ArrOfUsers){
        char *newUsername=(char*)malloc(30*sizeof(char));
        strcpy(newUsername,Element->valuestring);
        strcat(newUsername,".json");
        FILE *UserFile=fopen(newUsername,"r");
        char *jsonData2=(char*)malloc(10000*sizeof(char));
        fread(jsonData2,100,100,UserFile);
        cJSON *UserJson,*FName,*LName,*ArrOfHistory,*Element;
        UserJson=cJSON_Parse(jsonData2);
        FName=cJSON_GetObjectItem(UserJson,"FirstName");
        LName=cJSON_GetObjectItem(UserJson,"LastName");
        ArrOfHistory=cJSON_GetObjectItem(UserJson,"History");
        int i=0;
        cJSON_ArrayForEach(Element,ArrOfHistory){
            i++;
        }
        if(i==0)continue;
        printf("#########################\n#   %-10s%-10s#\n#########################\n",FName->valuestring,LName->valuestring);
        printf("%-20s%-20s%-20s\n","Name","Numbers","Price");
        i=0;
        cJSON_ArrayForEach(Element,ArrOfHistory){
            j++;
            i++;
            if(i==1){
                printf("%-20s",Element->valuestring);
            }
            else if(i==2){
                printf("%-20g",Element->valuedouble);
            }
            else if(i==3){
                printf("%-20g",Element->valuedouble);
                i=0;
                printf("\n");
            }
        }
        free(jsonData2);
        free(newUsername);
        cJSON_Delete(UserJson);
    }
    if(j==0){
        printf("Has not yet made a purchase from the store!\n");
    }
    fclose(file);
    free(jsonData);
    cJSON_Delete(Users);
    getchar();
    printf("Press Enter-key to return to the previous menu...");
    getchar();
    system("cls");
    Retailer(Username);
    return;
}
void View_User_list(char*Username){
    FILE *file=fopen("Users.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *Users,*Array,*Element;
    Users=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(Users,"Users");
    printf("This is the list of Users!:\n");
    printf("#  %-24s#  %-24s#\n","Username","Role");
    for (int i = 0; i < 55; i++)
    {
        printf("#");
    }
    printf("\n");
    cJSON_ArrayForEach(Element,Array){
        char *username=(char*)malloc(30*sizeof(char));
        strcpy(username,Element->valuestring);
        strcat(username,".json");
        FILE *userfile;
        userfile=fopen(username,"r");
        fread(jsonData,100,100,userfile);
        cJSON *User,*role;
        User=cJSON_Parse(jsonData);
        role=cJSON_GetObjectItem(User,"Role");
        printf("#  %-24s#  %-24s#\n",Element->valuestring,role->valuestring);
        
        fclose(userfile);
        free(username);
        cJSON_Delete(User);
    }
    free(jsonData);
    fclose(file);
    cJSON_Delete(Users);
    getchar();
    printf("\n\nPress Enter-key to return to the previous menu...");
    getchar();
    system("cls");
    Admin(Username);
    return;
}
void Ban_User(char*Username){
    char *UserBan=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of Ban-User Steps you can return to the main menu by entering the number 0!\n");
        printf("Enter the username of the person you want to ban:");
        scanf("%s",UserBan);
        if(strcmp(UserBan,"0")==0){
            system("cls");
            printf("You have successfully returned to the previous menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Admin(Username);
            return;
        }
        if(isUSERBAN(UserBan)==0){
            system("cls");
            printf("This user does not exist or is a store admin!\nOr it may already be on the ban list!\n");
            sleep(3);
            system("cls");
        }
        else break;
    } while (1);
    FILE *file=fopen("BanUsers.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,file);
    cJSON *BanUsers,*Array,*str;
    BanUsers=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(BanUsers,"BanUsers");
    str=cJSON_CreateString(UserBan);
    cJSON_AddItemToArray(Array,str);
    fclose(file);
    file=fopen("BanUsers.json","w");
    fputs(cJSON_Print(BanUsers),file);
    fclose(file);
    system("cls");
    printf("The user was successfully added to the list of bans!\n");
    getchar();
    printf("Press Enter-key to return to the previous menu...");
    getchar();
    system("cls");
    free(jsonData);
    free(UserBan);
    cJSON_Delete(BanUsers);
    Admin(Username);
    return;
}
int isUSERBAN(char*Username){
    FILE *Bans=fopen("BanUsers.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,Bans);
    cJSON *BanUsers,*Array,*Element;
    BanUsers=cJSON_Parse(jsonData);
    Array=cJSON_GetObjectItem(BanUsers,"BanUsers");
    cJSON_ArrayForEach(Element,Array){
        if(strcmp(Element->valuestring,Username)==0){
            return 0;
        }
    }
    char*Suffix=".json";
    char *newUsername=(char*)malloc(30*sizeof(char));
    strcpy(newUsername,Username);
    strcat(newUsername,Suffix);
    FILE *file=fopen(newUsername,"r");
    if(file==NULL)return 0;
    else{
        fread(jsonData,100,100,file);
        cJSON *User,*role;
        User=cJSON_Parse(jsonData);
        role=cJSON_GetObjectItem(User,"Role");
        if(strcmp(role->valuestring,"Admin")==0){
            return 0;
        }
        else{
            return 1;
        }
    }
    free(jsonData);
    free(newUsername);
    cJSON_Delete(BanUsers);
}
void Unban_user(char*Username){
    char *UserUnBan=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of UnBan-User Steps you can return to the main menu by entering the number 0!\n");
        printf("Enter the username of the person you want to unban:");
        scanf("%s",UserUnBan);
        if(strcmp(UserUnBan,"0")==0){
            system("cls");
            printf("You have successfully returned to the previous menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Admin(Username);
            return;
        }
        if(isUSERUNBAN(UserUnBan)==0){
            system("cls");
            printf("The user does not exist or is not in the list of bans!\n");
            sleep(2);
            system("cls");
        }
        else break;
    } while (1);
    FILE *Bans=fopen("BanUsers.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,Bans);
    cJSON *BanUsers,*Array,*str,*Element;
    BanUsers=cJSON_Parse(jsonData);
    str=cJSON_CreateString(UserUnBan);
    Array=cJSON_GetObjectItem(BanUsers,"BanUsers");
    int i=-1;
    cJSON_ArrayForEach(Element,Array){
        i++;
        if(strcmp(Element->valuestring,UserUnBan)==0){
            break;
        }
    }
    cJSON_DeleteItemFromArray(Array,i);
    fclose(Bans);
    Bans=fopen("BanUsers.json","w");
    fputs(cJSON_Print(BanUsers),Bans);
    fclose(Bans);
    system("cls");
    printf("The user was successfully deleted from the list of bans!\n");
    getchar();
    printf("Press Enter-key to return to the previous menu...");
    getchar();
    system("cls");
    free(jsonData);
    free(UserUnBan);
    cJSON_Delete(BanUsers);
    Admin(Username);
    return;
}
int isUSERUNBAN(char*Username){
    char*Suffix=".json";
    char *newUsername=(char*)malloc(30*sizeof(char));
    strcpy(newUsername,Username);
    strcat(newUsername,Suffix);
    FILE *file=fopen(newUsername,"r");
    if(file==NULL)return 0;
    else{
        FILE *Bans=fopen("BanUsers.json","r");
        char *jsonData=(char*)malloc(10000*sizeof(char));
        fread(jsonData,100,100,Bans);
        cJSON *BanUsers,*Array,*Element;
        BanUsers=cJSON_Parse(jsonData);
        Array=cJSON_GetObjectItem(BanUsers,"BanUsers");
        cJSON_ArrayForEach(Element,Array){
            if(strcmp(Element->valuestring,Username)==0){
                return 1;
            }
        }
        free(jsonData);
        cJSON_Delete(BanUsers);
    }
    free(newUsername);
    return 0;
}
void Get_Discount_Code(char *Username){
    printf("You have successfully entered the Get Discount Code page...\n");
    sleep(2);
    system("cls");
    getchar();
    char option;
    do
    {
        printf("Note that you can return to the previous menu by entering number 0 !\n");
        printf("This is your options.Enter your desired option:\n");
        printf("1.Deduct 100 points and receive a 10%% code\n2.Deduct 200 points and receive a 25%% code\n3.Deduct 300 points and receive a 50%% code\n");
        scanf("%c",&option);
        if(option=='0'){
            system("cls");
            printf("You have successfully returned to the main menu!please wait...");
            getchar();
            sleep(2);
            system("cls");
            Customer(Username);
            return;
        }
        else if (option=='1'||option=='2'||option=='3'){
            break;
        }
        else{
            system("cls");
            printf("Invalid option!\n");
            sleep(1);
            system("cls");
            break;
        }
    } while (1);
    int opt=option-'0';
    char *newUser=(char*)malloc(30*sizeof(char));
    strcpy(newUser,Username);
    strcat(newUser,".json");
    FILE *Userfile;
    Userfile=fopen(newUser,"r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,Userfile);
    cJSON *UserJson,*Points;
    UserJson=cJSON_Parse(jsonData);
    Points=cJSON_GetObjectItem(UserJson,"Points");
    if(Points->valuedouble<opt*100){
        system("cls");
        printf("You do not have enough points to receive the discount code.\nYou can add 10 points to your points with each purchase.\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
    else{
        char *Code=(char*)malloc(30*sizeof(char));
        cJSON_SetNumberValue(Points,cJSON_GetObjectItem(UserJson,"Points")->valuedouble-(opt*100));
        fclose(Userfile);
        Userfile=fopen(newUser,"w");
        fputs(cJSON_Print(UserJson),Userfile);
        system("cls");
        printf("This is Your Discount Code. Copy it so you can use it:\n");
        for (int i = 0; i < 10; i++){
            int j=(rand()%26)+65;
            printf("%c",j);
            Code[i]=(char)j;
        }
        Code[10]='\0';
        FILE *CodesFile;
        CodesFile=fopen("DiscountsCode.json","r");
        fread(jsonData,100,100,CodesFile);
        cJSON *Codes,*ArrOfCodes;
        Codes=cJSON_Parse(jsonData);
        ArrOfCodes=cJSON_GetObjectItem(Codes,"Codes");
        cJSON_AddStringToObject(ArrOfCodes,"Codes",Code);
        if(opt==1){
            cJSON_AddNumberToObject(ArrOfCodes,"Codes",10);
        }
        else if(opt==2){
            cJSON_AddNumberToObject(ArrOfCodes,"Codes",25);
        }
        else{
            cJSON_AddNumberToObject(ArrOfCodes,"Codes",50);
        }
        fclose(CodesFile);
        CodesFile=fopen("DiscountsCode.json","w");
        fputs(cJSON_Print(Codes),CodesFile);
        fclose(CodesFile);
        fclose(Userfile);
        free(jsonData);
        cJSON_Delete(UserJson);
        cJSON_Delete(Codes);
        printf("\nPress enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
}
void Add_Auction(char *Username){
    FILE *AucFile=fopen("Auctions.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,AucFile);
    cJSON *AucJson,*ArrOfAuc;
    AucJson=cJSON_Parse(jsonData);
    ArrOfAuc=cJSON_GetObjectItem(AucJson,"Auctions");
    char *AucName=(char*)malloc(30*sizeof(char)),*Copy=(char*)malloc(30*sizeof(char));
    do
    {
        printf("Note that at each stage of Auction Steps you can return to the previous menu by entering the number 0!\n");
        printf("Enter the name of the item you want to auction:");scanf("%s",AucName);
        strcpy(Copy,AucName);
        strcat(Copy,"-Pro.json");
        FILE *Prod=fopen(Copy,"r");
        if(strcmp(AucName,"0")==0){
            system("cls");
            printf("You have been successfully returned to the user menu...");
            sleep(2);
            system("cls");
            Retailer(Username);
            return;
        }
        else if(Prod==NULL){
            system("cls");
            printf("Imported goods do not exist. Try again...\n");
            sleep(2);
            system("cls");
        }
        else break;
    } while (1);
    int discount;
    printf("Enter the percentage of the discount you want to consider for the product as a percentage.\n");
    scanf("%d",&discount);
    if(discount==0){
        system("cls");
        printf("You have been successfully returned to the user menu...");
        sleep(2);
        system("cls");
        Retailer(Username);
        return;
    }
    else{
        FILE *ProdFile=fopen(Copy,"r");
        fread(jsonData,100,100,ProdFile);
        cJSON *ProdJson,*Name,*Price,*Cat,*NameOfSeller,*NumOfAv,*UserOfSeller;
        ProdJson=cJSON_GetObjectItem(cJSON_Parse(jsonData),AucName);
        Name=cJSON_GetObjectItem(ProdJson,"Name");
        Price=cJSON_GetObjectItem(ProdJson,"Price");
        Cat=cJSON_GetObjectItem(ProdJson,"category");
        NameOfSeller=cJSON_GetObjectItem(ProdJson,"Seller Name");
        NumOfAv=cJSON_GetObjectItem(ProdJson,"Available number");
        UserOfSeller=cJSON_GetObjectItem(ProdJson,"Seller Username");
        cJSON_AddStringToObject(ArrOfAuc,"Auctions",Name->valuestring);
        cJSON_AddNumberToObject(ArrOfAuc,"Auctions",((100-discount)*Price->valuedouble)/100);
        cJSON_AddStringToObject(ArrOfAuc,"Auctions",Cat->valuestring);
        cJSON_AddStringToObject(ArrOfAuc,"Auctions",NameOfSeller->valuestring);
        cJSON_AddNumberToObject(ArrOfAuc,"Auctions",NumOfAv->valuedouble);
        cJSON_AddStringToObject(ArrOfAuc,"Auctions",UserOfSeller->valuestring);
        fclose(AucFile);
        AucFile=fopen("Auctions.json","w");
        fputs(cJSON_Print(AucJson),AucFile);
        fclose(AucFile);
        cJSON_Delete(ProdJson);
    }
    cJSON_Delete(AucJson);
    system("cls");
    printf("Your product has been successfully added to the auction.\n");
    printf("Press Enter-Key to return to the user menu...");
    getchar();
    getchar();
    system("cls");
    Retailer(Username);
    return;
}
void Buy_Auction(char *Username){
    FILE *Auc=fopen("Auctions.json","r");
    char *jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,Auc);
    cJSON *AucJson,*ArrOfAuc,*Element;
    AucJson=cJSON_Parse(jsonData);
    ArrOfAuc=cJSON_GetObjectItem(AucJson,"Auctions");
    int i=0,j;
    cJSON_ArrayForEach(Element,ArrOfAuc){
        i++;
    }
    if(i==0){
        printf("No item has been added for auction yet!\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        free(jsonData);
        Customer(Username);
        return;
    }
    else{
        cJSON *ArrOfComm,*El;
        i=1;j=1;
        cJSON_ArrayForEach(Element,ArrOfAuc){
            if(i==1){
                printf("#########################\n#   %d.%-18s#\n#########################\n",j,Element->valuestring);
                char *Copy=(char*)malloc(30*sizeof(char));
                char *jsonString=(char*)malloc(10000*sizeof(char));
                strcpy(Copy,Element->valuestring);
                strcat(Copy,"-Pro.json");
                FILE *ProdFile=fopen(Copy,"r");
                fread(jsonString,100,100,ProdFile);
                cJSON *ProJson,*ProdJson;
                ProJson=cJSON_Parse(jsonString);
                ProdJson=cJSON_GetObjectItem(ProJson,Element->valuestring);
                ArrOfComm=cJSON_GetObjectItem(ProdJson,"BuyersComments");
                free(jsonString);
            }
            else if(i==2){
                printf("**Price including discount: %g\n",Element->valuedouble);
            }
            else if(i==3){
                printf("**Category: %s\n",Element->valuestring);
            }
            else if(i==4){
                printf("**Seller Name: %s\n",Element->valuestring);
            }
            else if(i==5){
                printf("**Available Number: %g\n",Element->valuedouble);
                int k=0;
                printf("****Comments****\n");
                cJSON_ArrayForEach(El,ArrOfComm){
                    k++;
                }
                if(k==0){
                    printf("No Comment yet!\n");
                    i++;
                    continue;
                }
                k=1;
                cJSON_ArrayForEach(El,ArrOfComm){
                    printf("%d.%s\n",k,El->valuestring);
                    k++;
                }
            }
            else{
                i=0;
                j++;
            }
            i++;
        }
    }
    int option;
    printf("\n\nYou can return to the main menu by entering number 0 !\n");
    printf("Or if you want to buy a product, enter the number of that product.\n");
    scanf("%d",&option);
    if(option==0){
        system("cls");
        getchar();
        printf("You have successfully returned to the previous menu!...");
        sleep(2);
        system("cls");
        Customer(Username);
        return;
    }

    else{
        char *NameOfProd=(char*)malloc(30*sizeof(char));
        double price;
        double NumOfProd;
        char *UserOfSeller=(char*)malloc(30*sizeof(char));
        i=1;
        cJSON_ArrayForEach(Element,ArrOfAuc){
            if((option-1)*6+1==i){
                strcpy(NameOfProd,Element->valuestring);
            }
            else if((option-1)*6+2==i){
                price=Element->valuedouble;
            }
            else if((option-1)*6+5==i){
                NumOfProd=Element->valuedouble;
            }
            else if((option)*6==i){
                strcpy(UserOfSeller,Element->valuestring);
                break;
            }
            i++;
        }
        if(NumOfProd==0){
            system("cls");
            printf("Unfortunately, this product is out of stock!\n");
            printf("You will be returned to the previous menu...please wait...");
            sleep(3);
            system("cls");
            Buy_Auction(Username);
            return;
        }
        int num;
        printf("How many of these products do you want?\nit must be smaller than %g\nEnter the number:",NumOfProd+1);
        scanf("%d",&num);
        if(num>NumOfProd){
            printf("This number of required items is not available. Please enter a smaller number ...\n");
            printf("You will be returned to the previous menu...please wait...");
            sleep(3);
            system("cls");
            Buy_Auction(Username);
            return;
        }
        char*newUser=(char*)malloc(30*sizeof(char));
        strcpy(newUser,Username);strcat(newUser,".json");
        FILE *User=fopen(newUser,"r");
        fread(jsonData,100,100,User);
        cJSON *Userjson,*SMoney,*Points,*SucPur,*ArrOfHistory;
        Userjson=cJSON_Parse(jsonData);
        SMoney=cJSON_GetObjectItem(Userjson,"StartingMoney");
        if((SMoney->valuedouble)<num*price){
            system("cls");
            printf("Your account balance is not enough for this purchase.\n");
            printf("You will be returned to the previous menu...please wait...");
            sleep(3);
            system("cls");
            Buy_Auction(Username);
            return;
        }
        Points=cJSON_GetObjectItem(Userjson,"Points");
        SucPur=cJSON_GetObjectItem(Userjson,"Number of successful purchases");
        ArrOfHistory=cJSON_GetObjectItem(Userjson,"History");
        cJSON_SetNumberValue(SMoney,SMoney->valuedouble-num*price);
        cJSON_SetNumberValue(Points,Points->valuedouble+10);
        cJSON_SetNumberValue(SucPur,SucPur->valuedouble+1);
        cJSON_AddStringToObject(ArrOfHistory,"History",NameOfProd);
        cJSON_AddNumberToObject(ArrOfHistory,"History",num);
        cJSON_AddNumberToObject(ArrOfHistory,"History",num*price);
        fclose(User);
        User=fopen(newUser,"w");
        fputs(cJSON_Print(Userjson),User);
        fclose(User);
        strcat(UserOfSeller,".json");
        FILE *UserFile=fopen(UserOfSeller,"r");
        char *jsonData2=(char*)malloc(10000*sizeof(char));
        fread(jsonData2,100,100,UserFile);
        cJSON *UserJson,*SM;
        UserJson=cJSON_Parse(jsonData2);
        SM=cJSON_GetObjectItem(UserJson,"StartingMoney");
        cJSON_SetNumberValue(SM,num*price+SM->valuedouble);
        fclose(UserFile);
        UserFile=fopen(UserOfSeller,"w");
        fputs(cJSON_Print(UserJson),UserFile);
        fclose(UserFile);
        cJSON_InsertItemInArray(ArrOfAuc,(option-1)*6+5,cJSON_CreateNumber(NumOfProd-num));
        cJSON_DeleteItemFromArray(ArrOfAuc,(option-1)*6+4);
        fclose(Auc);
        Auc=fopen("Auctions.json","w");
        fputs(cJSON_Print(AucJson),Auc);
        fclose(Auc);
        char name[30];
        strcpy(name,NameOfProd);
        strcat(NameOfProd,"-Pro.json");
        FILE *ProFile=fopen(NameOfProd,"r");
        fread(jsonData2,100,100,ProFile);
        cJSON *Projson,*Prodjson,*AvNum;
        Projson=cJSON_Parse(jsonData2);
        Prodjson=cJSON_GetObjectItem(Projson,name);
        cJSON_SetNumberValue(cJSON_GetObjectItem(Prodjson,"Available number"),cJSON_GetObjectItem(Prodjson,"Available number")->valuedouble-(double)num);
        fclose(ProFile);
        ProFile=fopen(NameOfProd,"w");
        fputs(cJSON_Print(Projson),ProFile);
        fclose(ProFile);
        free(jsonData2);
        free(NameOfProd);
        free(newUser);
        free(UserOfSeller);
        cJSON_Delete(AucJson);
        cJSON_Delete(UserJson);
        cJSON_Delete(Userjson);
        system("cls");
        printf("Your purchase was completed successfully!\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        Customer(Username);
        return;
    }
}
void View_Auction(char*Username){
    int array[100],i=1,j=0,k=1;
    FILE *AucFile=fopen("Auctions.json","r");
    char*jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,AucFile);
    cJSON *AucJson,*ArrOfAuc,*Element;
    AucJson=cJSON_Parse(jsonData);
    ArrOfAuc=cJSON_GetObjectItem(AucJson,"Auctions");
    cJSON_ArrayForEach(Element,ArrOfAuc){
        if(i%6==0){
            if(strcmp(Element->valuestring,Username)==0){
                array[j]=k;
                j++;
            }
            k++;
        }
        i++;
    }
    if(j==0){
        system("cls");
        printf("You have not added any items to the auction yet!\n");
        printf("You will return to the previous menu in a few seconds...\n");
        sleep(3);
        system("cls");
        Retailer(Username);
        return;
    }
    i=1;
    
    for (int r = 0; r < j; r++)
    {
        int s=array[r];
        cJSON_ArrayForEach(Element,ArrOfAuc){
            if((s-1)*6+1==i){
                printf("#########################\n#   %d.%-18s#\n#########################\n",r+1,Element->valuestring);
                break;
            }
            i++;
        }
    }
    int option;
    printf("\n\nYou can return to the previous menu by entering number 0 !\n");
    printf("Or Enter the number of the item you want to remove from the auction:");
    scanf("%d",&option);
    if(option==0){
        getchar();
        system("cls");
        Retailer(Username);
        return;
    }
    else{
        Delete_Auction(Username,array[option-1]);
        system("cls");
        getchar();
        printf("This item successfully deleted!\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        system("cls");
        Retailer(Username);
        return;
    }
    cJSON_Delete(AucJson);
}
void Delete_Auction(char *Username,int which){
    FILE *AucFile=fopen("Auctions.json","r");
    char*jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,AucFile);
    cJSON *AucJson,*ArrOfAuc,*Element;
    AucJson=cJSON_Parse(jsonData);
    ArrOfAuc=cJSON_GetObjectItem(AucJson,"Auctions");
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    cJSON_DeleteItemFromArray(ArrOfAuc,(which-1)*6);
    fclose(AucFile);
    AucFile=fopen("Auctions.json","w");
    fputs(cJSON_Print(AucJson),AucFile);
    fclose(AucFile);
    cJSON_Delete(AucJson);
    return ;
}
void View_Confirm_Comment(char*Username){
    FILE *CommFile=fopen("Comments.json","r");
    char*jsonData=(char*)malloc(10000*sizeof(char));
    fread(jsonData,100,100,CommFile);
    cJSON *CommJson,*ArrOfComm,*Element;
    CommJson=cJSON_Parse(jsonData);
    ArrOfComm=cJSON_GetObjectItem(CommJson,"Comments");
    int i=0,j=1;
    cJSON_ArrayForEach(Element,ArrOfComm){
        i++;
    }
    if(i==0){
        printf("No comments have been posted yet!\n");
        printf("Press Enter-Key to return to the previous menu...");
        getchar();
        getchar();
        system("cls");
        free(jsonData);
        Admin(Username);
        return;
    }
    else{
        printf("These are Unapproved comments so far:\n");
        i=1;
        cJSON_ArrayForEach(Element,ArrOfComm){
            if(i==1){
                printf("#########################\n#   %d.%-18s#\n#########################\n",j,Element->valuestring);
                j++;
            }
            else if(i==2){
                printf("Comment: %s\n",Element->valuestring);
                i=0;
            }
            i++;
        }
    }
    int option;
    printf("\n\nYou can return to the previous menu by entering number 0 !\n");
    printf("And Also You can enter the desired comment number, confirm it for the desired product.\n");
    scanf("%d",&option);
    if(option==0){
        system("cls");
        free(jsonData);
        Admin(Username);
        return;
    }
    else{
        int index=(option-1)*2+1;
        char name[30];
        char*CommentString=(char*)malloc(10000*sizeof(char));
        i=1;
        cJSON_ArrayForEach(Element,ArrOfComm){
            if(i==index){
                strcpy(name,Element->valuestring);
            }
            else if(i==index+1){
                strcpy(CommentString,Element->valuestring);
                break;
            }
            i++;
        }
        cJSON_DeleteItemFromArray(ArrOfComm,index-1);
        cJSON_DeleteItemFromArray(ArrOfComm,index-1);
        fclose(CommFile);
        CommFile=fopen("Comments.json","w");
        fputs(cJSON_Print(CommJson),CommFile);
        fclose(CommFile);
        char Copy[30];
        strcpy(Copy,name);
        strcat(name,"-Pro.json");
        FILE *ProFile=fopen(name,"r");
        fread(jsonData,100,100,ProFile);
        cJSON *ProJson,*ProdJson;
        ProJson=cJSON_Parse(jsonData);
        ProdJson=cJSON_GetObjectItem(ProJson,Copy);
        ArrOfComm=cJSON_GetObjectItem(ProdJson,"BuyersComments");
        cJSON_AddStringToObject(ArrOfComm,"BuyersComments",CommentString);
        fclose(ProFile);
        ProFile=fopen(name,"w");
        fputs(cJSON_Print(ProJson),ProFile);
        fclose(ProFile);
        cJSON_Delete(CommJson);
        cJSON_Delete(ProJson);
        system("cls");
        printf("Your comment has been successfully approved.\n");
        printf("Press Enter-Key to return to the previus menu...");
        getchar();
        getchar();
        system("cls");
        View_Confirm_Comment(Username);
        return;
    }
}
