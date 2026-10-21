#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char type[10];
    char title[100];
    double amount;
} Transaction;

Transaction transactions[MAX];

int count = 0;
double income = 0, expenses = 0;

void loadData() {
    FILE *file = fopen("transactions.txt", "r");

    if (file == NULL)
        return;

    while (count < MAX) {
        char type[10], title[100];
        double amount;

        if (fscanf(file, "%9s %lf ", type, &amount) != 2)
            break;

        if (fgets(title, sizeof(title), file) == NULL)
            break;

        title[strcspn(title, "\r\n")] = '\0';

        strcpy(transactions[count].type, type);
        strcpy(transactions[count].title, title);
        transactions[count].amount = amount;

        if (strcmp(type, "INCOME") == 0)
            income += amount;
        else if (strcmp(type, "EXPENSE") == 0)
            expenses += amount;

        count++;
    }

    fclose(file);
}

void addTransaction(char type[]) {
    char title[100];
    double amount;

    if (count >= MAX) {
        printf("\nTransaction limit reached!\n");
        return;
    }

    printf("Enter title/source: ");
    if (fgets(title, sizeof(title), stdin) == NULL)
        return;

    title[strcspn(title, "\r\n")] = '\0';

    printf("Enter amount (Rs.): ");

    if (scanf("%lf", &amount) != 1) {
        printf("Invalid amount!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    if (amount <= 0) {
        printf("Amount must be greater than zero!\n");
        return;
    }

    FILE *file = fopen("transactions.txt", "a");

    if (file == NULL) {
        printf("Unable to save transaction!\n");
        return;
    }

    fprintf(file, "%s %.2f %s\n", type, amount, title);
    fclose(file);

    strcpy(transactions[count].type, type);
    strcpy(transactions[count].title, title);
    transactions[count].amount = amount;

    count++;

    if (strcmp(type, "INCOME") == 0)
        income += amount;
    else
        expenses += amount;

    printf("Transaction saved successfully!\n");
}

void viewTransactions() {
    int i;

    printf("\n========== TRANSACTION HISTORY ==========\n");

    if (count == 0) {
        printf("No transactions found.\n");
        return;
    }

    printf("%-10s %-12s %s\n", "TYPE", "AMOUNT", "TITLE");

    for (i = 0; i < count; i++) {
        printf("%-10s Rs. %-9.2f %s\n",
               transactions[i].type,
               transactions[i].amount,
               transactions[i].title);
    }
}

void checkBalance() {
    printf("\n========== BALANCE SUMMARY ==========\n");
    printf("Total Income   : Rs. %.2f\n", income);
    printf("Total Expenses : Rs. %.2f\n", expenses);
    printf("Current Balance: Rs. %.2f\n", income - expenses);
}

int main() {
    int choice;

    loadData();

    do {
        printf("\n================================\n");
        printf("       EXPENSE TRACKER\n");
        printf("================================\n");

        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View Transactions\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");

        printf("================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");

            while (getchar() != '\n');

            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addTransaction("INCOME");
                break;

            case 2:
                addTransaction("EXPENSE");
                break;

            case 3:
                viewTransactions();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                printf("Thank you for using Expense Tracker!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
}
