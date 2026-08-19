#include <stdio.h>
#include <stdlib.h>

struct Account {
    int acc_no;
    char name[50];
    float balance;
};

void deposit(struct Account *acc, float amount) {
    acc->balance += amount;
    printf("Deposited %.2f successfully!\n", amount);
}

void withdraw(struct Account *acc, float amount) {
    if (amount > acc->balance) {
        printf("Insufficient balance!\n");
    } else {
        acc->balance -= amount;
        printf("Withdrawn %.2f successfully!\n", amount);
    }
}

void balanceEnquiry(struct Account *acc) {
    printf("Account No: %d\n", acc->acc_no);
    printf("Name: %s\n", acc->name);
    printf("Balance: %.2f\n", acc->balance);
}

int main() {
    struct Account acc = {1001, "Kushala", 0.0};
    int choice;
    float amount;

    FILE *fp;
    fp = fopen("account.dat", "wb+");  // file to store account
    fwrite(&acc, sizeof(struct Account), 1, fp);

    do {
        printf("\n--- Banking System ---\n");
        printf("1. Deposit\n2. Withdraw\n3. Balance Enquiry\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                deposit(&acc, amount);
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw(&acc, amount);
                break;
            case 3:
                balanceEnquiry(&acc);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

        // update file after each operation
        fseek(fp, 0, SEEK_SET);
        fwrite(&acc, sizeof(struct Account), 1, fp);

    } while(choice != 4);

    fclose(fp);
    return 0;
}
