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