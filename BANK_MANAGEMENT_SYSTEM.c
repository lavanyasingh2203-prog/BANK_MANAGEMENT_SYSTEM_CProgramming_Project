#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct account {
    int acc_no;
    char name[50];
    float balance;
};

struct account bank[MAX];
int count = 0;

void loadData();
void saveData();
void createAccount();
void viewAccount();
void deposit();
void withdrawMoney();
void deleteAccount();
void viewAll();

// ---------------- MAIN MENU ---------------- //

int main() {
    int choice;
    loadData();

    while (1) {
        printf("\n======== BANK MANAGEMENT SYSTEM ========\n");
        printf("1. Create New Account\n");
        printf("2. View Account Details\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Delete Account\n");
        printf("6. View All Accounts\n");
        printf("7. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deposit(); break;
            case 4: withdrawMoney(); break;
            case 5: deleteAccount(); break;
            case 6: viewAll(); break;
            case 7: saveData(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

// ---------------- FILE HANDLING ---------------- //

void loadData() {
    FILE *fp = fopen("accounts.dat", "rb");
    if (!fp) return;
    fread(&count, sizeof(int), 1, fp);
    fread(bank, sizeof(struct account), count, fp);
    fclose(fp);
}

void saveData() {
    FILE *fp = fopen("accounts.dat", "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(bank, sizeof(struct account), count, fp);
    fclose(fp);
}

// ---------------- OPERATIONS ---------------- //

void createAccount() {
    if (count == MAX) {
        printf("Bank storage full!\n");
        return;
    }

    struct account a;
    printf("Enter account number: ");
    scanf("%d", &a.acc_no);

    printf("Enter name: ");
    getchar();
    fgets(a.name, sizeof(a.name), stdin);
    a.name[strcspn(a.name, "\n")] = 0;

    printf("Enter initial balance: ");
    scanf("%f", &a.balance);

    bank[count++] = a;
    saveData();
    printf("Account created successfully!\n");
}

void viewAccount() {
    int num;
    printf("Enter account number: ");
    scanf("%d", &num);

    for (int i = 0; i < count; i++) {
        if (bank[i].acc_no == num) {
            printf("\nAccount Number: %d\nName: %s\nBalance: %.2f\n",
                   bank[i].acc_no, bank[i].name, bank[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void deposit() {
    int num;
    float amt;
    printf("Enter account number: ");
    scanf("%d", &num);

    for (int i = 0; i < count; i++) {
        if (bank[i].acc_no == num) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amt);
            bank[i].balance += amt;
            saveData();
            printf("Amount deposited successfully!\n");
            return;
        }
    }
    printf("Account not found!\n");
}

void withdrawMoney() {
    int num;
    float amt;
    printf("Enter account number: ");
    scanf("%d", &num);

    for (int i = 0; i < count; i++) {
        if (bank[i].acc_no == num) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amt);

            if (amt > bank[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                bank[i].balance -= amt;
                saveData();
                printf("Withdrawal successful!\n");
            }
            return;
        }
    }
    printf("Account not found!\n");
}

void deleteAccount() {
    int num;
    printf("Enter account number to delete: ");
    scanf("%d", &num);

    for (int i = 0; i < count; i++) {
        if (bank[i].acc_no == num) {
            for (int j = i; j < count - 1; j++) {
                bank[j] = bank[j + 1];
            }
            count--;
            saveData();
            printf("Account deleted successfully!\n");
            return;
        }
    }
    printf("Account not found!\n");
}

void viewAll() {
    printf("\n===== All Account Details =====\n");
    for (int i = 0; i < count; i++) {
        printf("\nAccount Number: %d\nName: %s\nBalance: %.2f\n",
               bank[i].acc_no, bank[i].name, bank[i].balance);
    }
}
