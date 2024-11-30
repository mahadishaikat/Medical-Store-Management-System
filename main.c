#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 100
#define MAX_USERS 10
#define LOCATION_LENGTH 10
#define MAX_CART_ITEMS 50

struct Medicine {
    char name[50];
    float price;
    int quantity;
    int shelfNumber;
    char location[LOCATION_LENGTH];
};

struct CartItem {
    char name[50];
    int quantity;
};

struct User {
    char username[50];
    char password[50];
    int isAdmin;
};

struct Medicine inventory[MAX_MEDICINES];
struct CartItem cart[MAX_CART_ITEMS];
struct User users[MAX_USERS];
int medicineCount = 0;
int cartItemCount = 0;
int userCount = 0;
int loggedInUserIndex = -1;

void choice() {
    printf("Press y to return to menu or n to exit: ");
    char c;
    scanf(" %c", &c);
    if (c == 'y') {
        system("cls");
    } else if (c == 'n') {
        printf("Thank you for using the system.\n");
        exit(0);
    }
}

void addMedicine() {
    if (medicineCount == MAX_MEDICINES) {
        printf("Error: Inventory limit reached.\n");
        return;
    }

    struct Medicine newMed;
    getchar();
    printf("Enter Medicine Name: ");
    gets(newMed.name);
    printf("Enter Price: ");
    scanf("%f", &newMed.price);
    printf("Enter Quantity: ");
    scanf("%d", &newMed.quantity);
    printf("Enter Shelf Number (1-10): ");
    scanf("%d", &newMed.shelfNumber);
    getchar();
    printf("Enter Location (top/middle/bottom): ");
    gets(newMed.location);

    inventory[medicineCount++] = newMed;
    printf("Medicine added successfully.\n");
    choice();
}

void displayMedicines() {
    if (medicineCount == 0) {
        printf("No medicines to display.\n");
        return;
    }
    printf("%-20s%-10s%-10s%-10s%-10s\n", "Name", "Price", "Quantity", "Shelf", "Location");
    for (int i = 0; i < medicineCount; i++) {
        printf("%-20s%-10.2f%-10d%-10d%-10s\n", inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].shelfNumber, inventory[i].location);
    }
    choice();
}

void searchMedicine() {
    char searchName[50];
    int found = 0;
    getchar();
    printf("Enter Medicine Name to search: ");
    gets(searchName);
    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(inventory[i].name, searchName) == 0) {
            printf("Medicine Found: %s | Price: %.2f | Quantity: %d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Medicine not found.\n");
    }
    choice();
}

void updateMedicine() {
    char searchName[50];
    int found = 0;
    getchar();
    printf("Enter Medicine Name to update: ");
    gets(searchName);
    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(inventory[i].name, searchName) == 0) {
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new Shelf Number (1-10): ");
            scanf("%d", &inventory[i].shelfNumber);
            getchar();
            printf("Enter new Location (top/middle/bottom): ");
            gets(inventory[i].location);
            printf("Medicine updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Medicine not found.\n");
    }
    choice();
}

void deleteMedicine() {
    char searchName[50];
    int found = 0;
    getchar();
    printf("Enter Medicine Name to delete: ");
    gets(searchName);
    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(inventory[i].name, searchName) == 0) {
            for (int j = i; j < medicineCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            medicineCount--;
            printf("Medicine deleted successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Medicine not found.\n");
    }
    choice();
}

void addToCart() {
    char medicineName[50];
    int quantity;
    getchar();
    printf("Enter Medicine Name to add to cart: ");
    gets(medicineName);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(inventory[i].name, medicineName) == 0) {
            if (inventory[i].quantity >= quantity) {
                strcpy(cart[cartItemCount].name, medicineName);
                cart[cartItemCount].quantity = quantity;
                cartItemCount++;
                printf("%d of %s added to cart.\n", quantity, medicineName);
            } else {
                printf("Insufficient stock for %s.\n", medicineName);
            }
            return;
        }
    }
    printf("Medicine not found.\n");
}

void checkoutCart() {
    if (cartItemCount == 0) {
        printf("Cart is empty. Add items to the cart first.\n");
        return;
    }

    printf("\n=== Checkout Summary ===\n");
    for (int i = 0; i < cartItemCount; i++) {
        for (int j = 0; j < medicineCount; j++) {
            if (strcmp(cart[i].name, inventory[j].name) == 0) {
                inventory[j].quantity -= cart[i].quantity;
                printf("Medicine: %s | Quantity: %d\n", cart[i].name, cart[i].quantity);
                break;
            }
        }
    }
    cartItemCount = 0;
    printf("Checkout complete. Thank you for your purchase.\n");
    choice();
}

void saveData() {
    FILE *file = fopen("medicine_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < medicineCount; i++) {
        fprintf(file, "%s,%.2f,%d,%d,%s\n", inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].shelfNumber, inventory[i].location);
    }
    fclose(file);
    printf("Data saved to file successfully.\n");
    choice();
}

void loadData() {
    FILE *file = fopen("medicine_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file doesn't exist.\n");
        return;
    }
    medicineCount = 0;
    while (fscanf(file, "%[^,],%f,%d,%d,%[^\n]\n", inventory[medicineCount].name, &inventory[medicineCount].price, &inventory[medicineCount].quantity, &inventory[medicineCount].shelfNumber, inventory[medicineCount].location) != EOF) {
        medicineCount++;
    }
    fclose(file);
    printf("Data loaded from file successfully.\n");
    choice();
}

void saveUsers() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%d\n", users[i].username, users[i].password, users[i].isAdmin);
    }
    fclose(file);
    printf("User data saved to file successfully.\n");
}

void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file or file doesn't exist. Starting fresh.\n");
        return;
    }
    userCount = 0;
    while (fscanf(file, "%[^,],%[^,],%d\n", users[userCount].username, users[userCount].password, &users[userCount].isAdmin) != EOF) {
        userCount++;
    }
    fclose(file);
    printf("User data loaded from file successfully. Total users: %d\n", userCount);
}

void registerUser() {
    if (userCount == MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    struct User newUser;
    getchar();
    printf("Enter Username: ");
    gets(newUser.username);
    printf("Enter Password: ");
    gets(newUser.password);

    int isAdminChoice;
    printf("Are you an admin? (1 for yes, 0 for no): ");
    scanf("%d", &isAdminChoice);

    if (isAdminChoice == 1) {
        char masterKey[20];
        getchar();
        printf("Enter Master Key: ");
        gets(masterKey);

        if (strcmp(masterKey, "admin1040") == 0) {
            newUser.isAdmin = 1;
            printf("Admin access granted.\n");
        } else {
            newUser.isAdmin = 0;
            printf("Invalid Master Key. Registered as a regular user.\n");
        }
    } else {
        newUser.isAdmin = 0;
    }

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
            return users[i].isAdmin;
        }
    }
    printf("Invalid username or password.\n");
    return -1;
}

void adminMenu() {
    int option;
    while (1) {
        printf("\n=== Admin Menu ===\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Search Medicine\n");
        printf("4. Update Medicine\n");
        printf("5. Delete Medicine\n");
        printf("6. Save Data\n");
        printf("7. Load Data\n");
        printf("0. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        if (option == 0) {
            loggedInUserIndex = -1;
            break;
        }

        switch (option) {
            case 1: addMedicine(); break;
            case 2: displayMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: saveData(); break;
            case 7: loadData(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

void userMenu() {
    int option;
    while (1) {
        printf("\n=== User Menu ===\n");
        printf("1. Display Medicines\n");
        printf("2. Search Medicine\n");
        printf("3. Add to Cart\n");
        printf("4. Checkout\n");
        printf("0. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        if (option == 0) {
            loggedInUserIndex = -1;
            break;
        }

        switch (option) {
            case 1: displayMedicines(); break;
            case 2: searchMedicine(); break;
            case 3: addToCart(); break;
            case 4: checkoutCart(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    int option;
    while (1) {
        printf("\n=== Medical Store Management System ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Save Users\n");
        printf("4. Load Users\n");
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
            case 3:
                saveUsers();
                break;
            case 4:
                loadUsers();
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
