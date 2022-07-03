#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Product {
    char proID[15];
    char fname[20];
    char bname[20];
    int qty;
    float price;
} Product;
FILE *fp;
Product pro;
char fileName[]="PRO.txt";
char tproFileName[]="tpro.txt";
/* function used in project */
void AddProduct();
void ListProduct();
void SearchProduct();
void ModifyProduct();
void DeleteProduct();
char file();
void main()
{
    char ch='a';
    int gm,x,y;
    clrscr();
    fp=fopen(fileName,"rb+");
    if(fp==NULL) {
        fp=fopen( fileName,"wb+");
        if(fp==NULL) {
            printf("Can't Open File");
            exit(0);
        }
    }
    while(ch!='6') {
        ch=file();
        switch(ch) {
        case '1':
            AddProduct();
            break;
        case '2':
            ListProduct();
            break;
        case '3':
            SearchProduct();
            break;
        case '4':
            ModifyProduct();
            break;
        case '5':
            DeleteProduct();
            break;
        case '6':
            exit(0);
            break;
        default:
            printf("WRONG CHOICE! Please enter valid choice!");
            getch();
            break;
        }
    }
}
void AddProduct()
{
    char another,ch;
    do {
        clrscr();
        fseek(fp,0,SEEK_END);
        another='Y';
        printf("Add product record\n");
        printf("1.Enter product ID : ");
        gets(pro.proID);
        printf("2.Enter name of product : ");
        gets(pro.fname);
        printf("3. Enter brand name of product : ");
        gets(pro.bname);
        printf("4. Enter quantity of product : ");
        scanf("%d",&pro.qty);
        printf("5. Enter product price : ");
        scanf("%f",&pro.price);
        printf("SAVE CHANGE (y/n)?");
        ch=getch();
        if(ch=='y'||ch=='Y') {
            fwrite(&pro,sizeof(pro),1,fp);
            fflush(stdin);
        }
        printf("\nAdd another product record(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
    } while(another=='Y'|| another=='y');
}
void ListProduct()
{
    int i;
    clrscr();
    fseek(fp,0,SEEK_SET);
    printf("\n\t\t\t\tList of Products\n\n\n");
    printf("ProductID\t");
    printf("Name\t");
    printf("Brand name\t");
    printf("Quantity\t");
    printf("Price\t\n");
    for(i=1; i<=80; i++) {
        printf("*");
    }
    printf("\n");
    i=4;
    while(fread(&pro,sizeof(pro),1,fp)==1) {
        printf("%s\t\t",pro.proID);
        printf("%s\t",pro.fname);
        printf("%s\t\t",pro.bname);
        printf("%d\t\t",pro.qty);
        printf("%.2f\t",pro.price);
        i++;
        printf("\n");
    }
    getch();
}
void SearchProduct()
{
    int i,datafound=0;
    char productId[15];
    char another,ch;
    do {
        clrscr();
        fseek(fp,0,SEEK_SET);
        printf("Search product record\n");
        printf("Enter product ID : ");
        gets(productId);
        while(fread(&pro,sizeof(pro),1,fp)==1) {
            if(strcmp(pro.proID,productId)==0) {
                datafound=1;
                break;
            }
        }
        if(datafound==1) {
            printf("Record of product\n");
            printf("Product ID : ");
            printf("%s",pro.proID);
            printf("\nName : ");
            printf("%s",pro.fname);
            printf("\nBrand Name : ");
            printf("%s",pro.bname);
            printf("\nQuantity : ");
            printf("%d",pro.qty);
            printf("\nPrice : ");
            printf("%.2f",pro.price);
        } else {
            printf("PRODUCT NOT FOUND!");
        }
        printf("\nSearch another product record(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
    } while(another=='Y'|| another=='y');
}
void ModifyProduct()
{
    int i, datafound=0,recordNo=0;
    char productId[15];
    char another,ch;
    do {
        clrscr();
        fseek(fp,0,SEEK_SET);
        rewind(fp);
        printf("Modify product record\n");
        printf("Enter product ID to be modified : ");
        gets(productId);
        while(fread(&pro,sizeof(pro),1,fp)==1) {
            if(strcmp(pro.proID,productId)==0) {
                datafound=1;
                break;
            }
            recordNo++;
        }
        if(datafound==1) {
            printf("OLD RECORD IS\n");
            printf("Product ID : ");
            printf("%s",pro.proID);
            printf("\nName : ");
            printf("%s",pro.fname);
            printf("\nBrand Name : ");
            printf("%s",pro.bname);
            printf("\nQuantity : ");
            printf("%d",pro.qty);
            printf("\nPrice : ");
            printf("%.2f",pro.price);
            printf("\nProduct ID : ");
            gets(pro.proID);
            printf("Name : ");
            gets(pro.fname);
            printf("Brand name : ");
            gets(pro.bname);
            printf("Quantity : ");
            scanf("%d",&pro.qty);
            printf("Price : ");
            scanf("%f",&pro.price);
            fseek(fp,sizeof(pro)*(recordNo),SEEK_SET);

            if(fwrite(&pro,sizeof(pro),1,fp)==1)
                printf("Record has been modified!\n");
            else
                printf("ERROR DURING MODIFICATION!\n");
        } else {
            printf("PRODUCT NOT FOUND!\n");
        }
        printf("Modify another product record(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
    } while(another=='Y'||another=='y');
}
void DeleteProduct()
{
    int i,datafound=0;
    char productId[15];
    FILE *fpTpro;
    char another,ch;
    do {
        clrscr();
        fseek(fp,0,SEEK_SET);
        rewind(fp);
        printf("Delete product record \n");
        printf("Enter product ID to be deleted : ");
        gets(productId);
        while(fread(&pro,sizeof(pro),1,fp)==1) {
            if(strcmp(pro.proID,productId)==0) {
                datafound=1;
                break;
            }
        }
        if(datafound==1) {
            fpTpro=fopen(tproFileName,"wb");
            rewind(fp);
            while(fread(&pro,sizeof(pro),1,fp)==1) {
                if(strcmp(pro.proID,productId)!=0)
                    fwrite(&pro,sizeof(pro),1,fpTpro);
            }
            fclose(fp);
            fclose(fpTpro);
            remove(fileName);
            rename(tproFileName,fileName);
            fp=fopen(fileName,"rb+");
            printf("SUCCESSFULLY DELETED!\n");
        } else {
            printf("PRODUCT NOT FOUND!\n");
        }
        printf("Delete another product record(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
    } while(another=='Y'|| another=='y');
}
char file()
{
    char i;
    clrscr();
    printf("PRODUCT INFORMATION SYSTEM\n");
    printf("MAIN MENU\n");
    printf("1-> Add product record \n");
    printf("2-> List of product records \n");
    printf("3-> Search product \n");
    printf("4-> Modify product information \n");
    printf("5-> Delete a product record \n");
    printf("6-> Exit \n");
    printf("Enter your choice : ");
    i=getch();
    return (i);
}
