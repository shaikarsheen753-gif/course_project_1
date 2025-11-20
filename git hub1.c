#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRANS 100

// Structure for each transaction
struct Transaction {
    char type[20];
    float amount;
    char timeStr[30];
};

// Structure for Card
struct Card {
    char cardType[10];     // DEBIT / CREDIT
    long long cardNumber;
    int pin;
    float balance;
    float creditLimit;     // only for credit card
    struct Transaction history[MAX_TRANS];
    int transCount;
};

// Function Prototypes
void header();
int login(struct Card *c);
void menu(struct Card *c);
void deposit(struct Card *c);
void withdraw(struct Card *c);
void makePayment(struct Card *c);
void showHistory(struct Card c);
void saveTransaction(struct Card *c, char type[], float amount);

// Get current date & time as string
void getTimeString(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 30, "%d-%m-%Y %H:%M:%S", tm_info);
}

// Program Entry
int main() {
    struct Card debit = {"DEBIT", 9876543210123456, 1234, 20000, 0, {}, 0};
    struct Card credit = {"CREDIT", 1234567890123456, 9999, 5000, 15000, {}, 0};

    int choice;

    while (1) {
        header();
        printf("1. Debit Card\n");
        printf("2. Credit Card\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (login(&debit))
                menu(&debit);
        }
        else if (choice == 2) {
            if (login(&credit))
                menu(&credit);
        }
        else if (choice == 3) {
            printf("Thank you for using our service!\n");
            break;
        } else {
            printf("Invalid selection! Try again.\n");
        }
    }

    return 0;
}

// Display Header
void header() {
    printf("\n=========================================\n");
    printf("     CREDIT & DEBIT CARD SYSTEM\n");
    printf("=========================================\n");
}

// Login using PIN
int login(struct Card *c) {
    int enteredPIN;

    printf("\n--- LOGIN FOR %s CARD ---\n", c->cardType);
    printf("Enter PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN == c->pin) {
        printf("✔ Login successful!\n");
        return 1;
    } else {
        printf("❌ Incorrect PIN! Login failed.\n");
        return 0;
    }
}

// Main Menu
void menu(struct Card *c) {
    int choice;

    while (1) {
        printf("\n============== %s CARD MENU =============\n", c->cardType);
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Make Payment\n");
        printf("4. View Balance\n");
        printf("5. Show Transaction History\n");
        printf("6. Logout\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit(c);
                break;
            case 2:
                withdraw(c);
                break;
            case 3:
                makePayment(c);
                break;
            case 4:
                printf("\nCurrent Balance: ₹%.2f\n", c->balance);
                break;
            case 5:
                showHistory(*c);
                break;
            case 6:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid option! Try again.\n");
        }
    }
}

// Deposit
void deposit(struct Card *c) {
    float amount;
    printf("\nEnter amount to deposit: ₹");
    scanf("%f", &amount);

    c->balance += amount;
    saveTransaction(c, "Deposit", amount);

    printf("✔ Amount deposited successfully!\n");
    printf("New Balance: ₹%.2f\n", c->balance);
}

// Withdraw
void withdraw(struct Card *c) {
    float amount;
    printf("\nEnter withdrawal amount: ₹");
    scanf("%f", &amount);

    if (strcmp(c->cardType, "DEBIT") == 0) {
        if (amount > c->balance) {
            printf("❌ Insufficient balance!\n");
            return;
        }
    }
    else { // CREDIT CARD
        if (amount > c->balance + c->creditLimit) {
            printf("❌ Credit limit exceeded!\n");
            return;
        }
    }

    c->balance -= amount;
    saveTransaction(c, "Withdraw", amount);

    printf("✔ Withdrawal successful!\n");
    printf("Remaining Balance: ₹%.2f\n", c->balance);
}

// Make Payment
void makePayment(struct Card *c) {
    float amount;
    printf("\nEnter payment amount: ₹");
    scanf("%f", &amount);

    if (strcmp(c->cardType, "DEBIT") == 0) {
        if (amount > c->balance) {
            printf("❌ Not enough balance to make payment!\n");
            return;
        }
    }
    else { 
        if (amount > c->balance + c->creditLimit) {
            printf("❌ Payment failed! Limit exceeded.\n");
            return;
        }
    }

    c->balance -= amount;
    saveTransaction(c, "Payment", amount);

    printf("✔ Payment successful!\n");
    printf("Updated Balance: ₹%.2f\n", c->balance);
}

// Save Transaction in History
void saveTransaction(struct Card *c, char type[], float amount) {
    if (c->transCount >= MAX_TRANS) {
        printf("⚠ Transaction history full!\n");
        return;
    }

    strcpy(c->history[c->transCount].type, type);
    c->history[c->transCount].amount = amount;
    getTimeString(c->history[c->transCount].timeStr);

    c->transCount++;
}

// Show All Transactions
void showHistory(struct Card c) {
    printf("\n========== TRANSACTION HISTORY ==========\n");

    if (c.transCount == 0) {
        printf("\nNo transactions found.\n");
        return;
    }

    for (int i = 0; i < c.transCount; i++) {
        printf("\n%d) %s of ₹%.2f", 
                i + 1, 
                c.history[i].type, 
                c.history[i].amount);
        printf("\n   Time: %s\n", c.history[i].timeStr);
    }
}