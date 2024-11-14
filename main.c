#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_medicines 100
#define max_users 10
#define location_length 10

struct Medicine {
    char name[50];
    float price;
    int quantity;
    int shelfNumber;
    char location[location_length];
};

struct User {
    char username[50];
    char password[50];
    int isAdmin;
};

struct Medicine inventory[max_medicines];
struct User users[max_users];
int medicineCount = 0;
int userCount = 0;
int loggedInUserIndex = -1;

void choice() {}
//Habiba's Part
void addMedicine() {}
void displayMedicines() {}

//Samsunnahar's Part
void searchMedicine() {}
void updateMedicine() {}
void deleteMedicine() {}

//Azaz's Part
void addToCart() {}
void checkoutCart() {}
void saveData() {}
void loadData() {}

//Mahadi's Part
void registerUser() {
    if (userCount == max_users) {
        printf("User limit reached.\n");
        return;
    }
    struct User newUser;
    getchar();
    printf("Enter Username: ");
    gets(newUser.username);
    printf("Enter Password: ");
    gets(newUser.password);
    printf("Are you an admin? (1 for yes, 0 for no): ");
    scanf("%d", &newUser.isAdmin);
    users[userCount++] = newUser;
    printf("User registered successfully.\n");
    choice();
}

int loginUser() {
    char username[50], password[50];
    getchar();
    printf("Enter Username: ");
    gets(username);
    printf("Enter Password: ");
    gets(password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUserIndex = i;
            printf("Login successful! Welcome %s.\n", username);
            return users[i].isAdmin; // Return 1 for admin, 0 for regular user
        }
    }
    printf("Invalid username or password.\n");
    return -1; // Login failed
}

void adminMenu() {}
void userMenu() {}

int main() {
    int option;
    while (1) {
        printf("\n=== Medical Store Management System ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                registerUser();
                break;
            case 2:
                {
                    int isAdmin = loginUser();
                    if (isAdmin == 1) {
                        adminMenu();
                    } else if (isAdmin == 0) {
                        userMenu();
                    }
                }
                break;
            case 0:
                printf("Thank you for using the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
