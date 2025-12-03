#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100

// ----------- STRUCTS -----------
struct Transaction {
    char type[20];        // Deposit or Withdrawal
    float amount;
    char date[30];        // Date and time
};

struct Account {
    char name[50];
    int accountNumber;
    char accountType[20]; // Savings / Current / Fixed Deposit
    float balance;
    char creationDate[30];
    char lastTransactionDate[30];

    struct Transaction history[MAX_TRANSACTIONS];
    int transactionCount;
};

// ----------- GLOBAL ACCOUNT -----------
struct Account acc;

// ----------- GET CURRENT DATE-TIME AS STRING -----------
void getDate(char *buffer) {
    time_t t;
    time(&t);
    strcpy(buffer, ctime(&t));
}

// ----------- GET MINIMUM BALANCE -----------
float getMinimumBalance(char type[]) {
    if (strcmp(type, "Savings") == 0) return 1000;
    if (strcmp(type, "Current") == 0) return 5000;
    if (strcmp(type, "Fixed") == 0) return 10000;
    return 0;
}

// ----------- GET INTEREST RATE -----------
float getInterestRate(char type[]) {
    if (strcmp(type, "Savings") == 0) return 4;
    if (strcmp(type, "Fixed") == 0) return 7;
    if (strcmp(type, "Current") == 0) return 0;
    return 0;
}

// ----------- ADD TRANSACTION -----------
void addTransaction(char type[], float amount) {
    if (acc.transactionCount < MAX_TRANSACTIONS) {
        strcpy(acc.history[acc.transactionCount].type, type);
        acc.history[acc.transactionCount].amount = amount;
        getDate(acc.history[acc.transactionCount].date);
        acc.transactionCount++;
        getDate(acc.lastTransactionDate);
    }
}

// ----------- CREATE ACCOUNT -----------
void createAccount() {
    printf("\nEnter your name: ");
    fflush(stdin);
    fgets(acc.name, sizeof(acc.name), stdin);

    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);

    printf("Select account type (Savings / Current / Fixed): ");
    fflush(stdin);
    fgets(acc.accountType, sizeof(acc.accountType), stdin);

    acc.accountType[strcspn(acc.accountType, "\n")] = '\0';

    float minBal = getMinimumBalance(acc.accountType);

    printf("Enter initial deposit (Minimum %.2f): ", minBal);
    scanf("%f", &acc.balance);

    if (acc.balance < minBal) {
        printf("\n? ERROR: Deposit must be at least %.2f\n", minBal);
        acc.balance = minBal;
        printf("? Automatically set to minimum balance.\n");
    }

    getDate(acc.creationDate);
    strcpy(acc.lastTransactionDate, acc.creationDate);

    acc.transactionCount = 0;
    addTransaction("Initial Deposit", acc.balance);

    printf("\n? Account created successfully!\n");
}

// ----------- DEPOSIT -----------
void deposit() {
    float amount;
    printf("\nEnter amount to deposit: ");
    scanf("%f", &amount);

    acc.balance += amount;
    addTransaction("Deposit", amount);

    printf("\n? Deposit Successful!\n");
}

// ----------- WITHDRAW -----------
void withdraw() {
    float amount;
    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amount);

    float minBal = getMinimumBalance(acc.accountType);

    if (acc.balance - amount < minBal) {
        printf("\n? ERROR: Cannot withdraw. Minimum balance %.2f required.\n", minBal);
        return;
    }

    acc.balance -= amount;
    addTransaction("Withdrawal", amount);

    printf("\n? Withdrawal Successful!\n");
}

// ----------- SHOW DETAILS -----------
void showDetails() {
    printf("\n----- ACCOUNT DETAILS -----\n");
    printf("Name: %s", acc.name);
    printf("Account Number: %d\n", acc.accountNumber);
    printf("Type: %s\n", acc.accountType);
    printf("Balance: %.2f\n", acc.balance);
    printf("Interest Rate: %.2f%%\n", getInterestRate(acc.accountType));
    printf("Account Created: %s", acc.creationDate);
    printf("Last Transaction: %s", acc.lastTransactionDate);
}

// ----------- SHOW TRANSACTION HISTORY -----------
void showHistory() {
    printf("\n----- TRANSACTION HISTORY -----\n");

    for (int i = 0; i < acc.transactionCount; i++) {
        printf("%d. %s - %.2f on %s",
               i + 1,
               acc.history[i].type,
               acc.history[i].amount,
               acc.history[i].date);
    }
}

// ----------- MAIN MENU -----------
int main() {
    int choice;

    printf("=== BANK ACCOUNT MANAGEMENT SYSTEM ===\n");
    createAccount();

    while (1) {
        printf("\n\n----- MENU -----\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Show Account Details\n");
        printf("4. Show Transaction History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: deposit(); break;
        case 2: withdraw(); break;
        case 3: showDetails(); break;
        case 4: showHistory(); break;
        case 5: printf("\nThank you!\n"); return 0;
        default: printf("? Invalid choice!\n");
        }
    }

    return 0;
}

