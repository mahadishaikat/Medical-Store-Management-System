#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEDICINES 100
#define MAX_USERS 10
#define LOCATION_LENGTH 10
#define MAX_CART_ITEMS 50
#define MAX_REQUESTS 100

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

struct MedicineRequest {
    char name[50];
    int quantity;
};

struct Medicine inventory[MAX_MEDICINES];
struct CartItem cart[MAX_CART_ITEMS];
struct User users[MAX_USERS];
int medicineCount = 0;
int cartItemCount = 0;
int userCount = 0;
int loggedInUserIndex = -1;

struct MedicineRequest requestedMedicines[MAX_REQUESTS];
int requestCount = 0;

void choice() {
    printf("\033[1;33mPress y to return to menu or n to exit: \033[0m");
    char c;
    scanf(" %c", &c);
    if (c == 'y') {
        system("cls");
    } else if (c == 'n') {
        printf("\033[1;36mThank you for using the system.\033[0m\n");
        exit(0);
    }
}

void addMedicine() {
    system("cls");
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
    system("cls");
    if (medicineCount == 0) {
        printf("No medicines to display.\n");
        return;
    }
    printf("\033[1;36m%-20s%-10s%-10s%-10s%-10s\n", "Name", "Price", "Quantity", "Shelf", "Location\033[0m");
    for (int i = 0; i < medicineCount; i++) {
        printf("%-20s%-10.2f%-10d%-10d%-10s\n", inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].shelfNumber, inventory[i].location);
    }
    printf("\n");
    choice();
}

void checkLowStocks() {
    system("cls");
    int lowStockFound = 0;

    printf("\033[1;31m+----------------------------------+\n");
    printf("| Medicines with Low Stock (<20)  |\n");
    printf("+----------------------------------+\033[0m\n\n");

    for (int i = 0; i < medicineCount; i++) {
        if (inventory[i].quantity < 20) {
            printf("Medicine: %s | Quantity: %d | Price: %.2f\n",
                   inventory[i].name, inventory[i].quantity, inventory[i].price);
            lowStockFound = 1;
        }
    }

    if (!lowStockFound) {
        printf("No medicines with low stock found.\n");
    }
    choice();
}

void requestMedicine() {
    system("cls");
    char medicineName[50];
    int quantity;
    int found = 0;
    getchar();
    printf("\033[1;33mEnter Medicine Name to request: \033[0m");
    gets(medicineName);
    printf("\033[1;32mEnter Quantity: \033[0m");
    scanf("%d", &quantity);


    for (int i = 0; i < medicineCount; i++) {
        if (strcmp(inventory[i].name, medicineName) == 0) {
            printf("\033[1;32mMedicine is available in inventory. No need to request.\033[0m\n");
            found = 1;
            break;
        }
    }


    if (!found) {

        if (requestCount < MAX_REQUESTS) {
            strcpy(requestedMedicines[requestCount].name, medicineName);
            requestedMedicines[requestCount].quantity = quantity;
            requestCount++;
            printf("\033[1;36mMedicine request for %s (Quantity: %d) has been submitted.\033[0m\n", medicineName, quantity);
        } else {
            printf("\033[1;31mSorry, request limit reached. Cannot process your request.\033[0m\n");
        }
    }
    choice();
}

void displayRequestedMedicines() {
    system("cls");
    if (requestCount == 0) {
        printf("\033[1;31mNo medicine requests found.\033[0m\n");
        choice();
        return;
    }

    printf("\033[1;32m+----------------------------------+\n");
    printf("|  Medicine Request Summary       |\n");
    printf("+----------------------------------+\033[0m\n\n");

    for (int i = 0; i < requestCount; i++) {
        printf("Requested Medicine: %s | Quantity: %d\n", requestedMedicines[i].name, requestedMedicines[i].quantity);
    }

    choice();
}

void searchMedicine() {
    system("cls");

    printf("\033[1;36m%-20s%-10s%-10s%-10s%-10s\n", "Name", "Price", "Quantity", "Shelf", "Location\033[0m");
    for (int i = 0; i < medicineCount; i++) {
        printf("%-20s%-10.2f%-10d%-10d%-10s\n", inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].shelfNumber, inventory[i].location);
    }
    printf("\n");

    char searchName[50];
    int found = 0;
    getchar();
    printf("Enter Medicine Name to search: ");
    gets(searchName);


    for (int i = 0; searchName[i]; i++) {
        searchName[i] = tolower(searchName[i]);
    }

    for (int i = 0; i < medicineCount; i++) {
        char inventoryName[50];
        strcpy(inventoryName, inventory[i].name);


        for (int j = 0; inventoryName[j]; j++) {
            inventoryName[j] = tolower(inventoryName[j]);
        }


        if (strcmp(inventoryName, searchName) == 0) {
            printf("\033[1;32mMedicine Found: %s | Price: %.2f | Quantity: %d\033[0m\n",
                   inventory[i].name, inventory[i].price, inventory[i].quantity);
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
    system("cls");
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
    system("cls");
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
    system("cls");
    printf("\033[1;36m%-20s%-10s%-10s%-10s%-10s\n", "Name", "Price", "Quantity", "Shelf", "Location\033[0m");
    for (int i = 0; i < medicineCount; i++) {
        printf("%-20s%-10.2f%-10d%-10d%-10s\n", inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].shelfNumber, inventory[i].location);
    }
    printf("\n");
    char medicineName[50];
    int quantity;
    getchar();
    printf("\033[1;33mEnter Medicine Name to add to cart: \033[0m");
    gets(medicineName);
    printf("\033[1;32mEnter Quantity: \033[0m");
    scanf("%d", &quantity);


    for (int i = 0; medicineName[i]; i++) {
        medicineName[i] = tolower(medicineName[i]);
    }

    for (int i = 0; i < medicineCount; i++) {
        char inventoryName[50];
        strcpy(inventoryName, inventory[i].name);


        for (int j = 0; inventoryName[j]; j++) {
            inventoryName[j] = tolower(inventoryName[j]);
        }


        if (strcmp(inventoryName, medicineName) == 0) {
            if (inventory[i].quantity >= quantity) {
                strcpy(cart[cartItemCount].name, inventory[i].name);
                cart[cartItemCount].quantity = quantity;
                cartItemCount++;
                system("cls");
                printf("\033[1;36m%d of %s added to cart.\033[0m\n", quantity, inventory[i].name);
                choice();
                return;
            } else {
                system("cls");
                printf("\033[1;31mInsufficient stock for %s.\033[0m\n", inventory[i].name);
                choice();
                return;
            }
        }
    }

    printf("Medicine not found.\n");
    system("cls");
}


void checkoutCart() {
    system("cls");
    if (cartItemCount == 0) {
        system("cls");
        printf("Cart is empty. Add items to the cart first.\n");
        return;
    }
    float grandTotal = 0.0;
    printf("\033[1;32m+----------------------------------+\n");
    printf("|  [ $ ]  Checkout Summary  [ $ ]  |\n");
    printf("+----------------------------------+\033[0m\n\n");
    for (int i = 0; i < cartItemCount; i++) {
        for (int j = 0; j < medicineCount; j++) {
            if (strcmp(cart[i].name, inventory[j].name) == 0) {
                float totalCost = cart[i].quantity * inventory[j].price;
                inventory[j].quantity -= cart[i].quantity;
                grandTotal += totalCost;

                printf("Medicine: %s | Quantity: %d | Unit Price: %.2f | Total Cost: %.2f\n",
                       cart[i].name, cart[i].quantity, inventory[j].price, totalCost);
                break;
            }
        }
    }

    printf("\n\033[1;33mGrand Total: %.2f\033[0m\n", grandTotal);
    cartItemCount = 0;
    printf("\033[1;32mCheckout complete. Thank you for your purchase.\033[0m\n");
    saveData();
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
    printf("\033[1;32m  Medicines Loaded successfully.\033[0m\n");
}
void loadDataUser() {
    loadData();
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
    printf("\033[1;32m  User data saved to file successfully.\033[0m\n");
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
    printf("\033[1;32m  Registered Users: %d\033[0m\n", userCount);
}

void registerUser() {
    if (userCount == MAX_USERS) {
        system("cls");
        printf("\033[1;31m  User limit reached!\033[0m\n\n");
        return;
    }
    system("cls");
    struct User newUser;
    getchar();
    printf("\033[1;36m  Enter Username: \033[1;33m");
    gets(newUser.username);
    printf("\033[1;36m  Enter Password: \033[1;33m");
    gets(newUser.password);

    int isAdminChoice;
    printf("\033[1;31m  Are you an admin? \033[1;32m(1 for yes, 0 for no): \033[1;33m");
    scanf("%d", &isAdminChoice);

    if (isAdminChoice == 1) {
        char masterKey[20];
        getchar();
        printf("\033[1;35m  Enter Master Key: \033[0m");
        gets(masterKey);
        system("cls");
        if (strcmp(masterKey, "admin1040") == 0) {
            newUser.isAdmin = 1;
            printf("\033[1;32m  Admin access granted.\033[0m\n");
        } else {
            newUser.isAdmin = 0;
            printf("\033[1;31m  Invalid Master Key. Registered as a regular user.\033[0m\n");
        }
    } else {
        newUser.isAdmin = 0;
    }

    users[userCount++] = newUser;
    printf("\033[1;33m  User registered successfully.\033[0m\n");
    saveUsers();
    choice();
}

int loginUser() {
    system("cls");
    char username[50], password[50];
    getchar();
    printf("\033[1;36m  Enter Username: \033[1;33m");
    gets(username);
    printf("\033[1;36m  Enter Password: \033[0m\033[1;33m");
    gets(password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUserIndex = i;

            printf("\033[1;32m  Login successful! Welcome %s.\033[0m\n", username);
            printf("\n  Press Enter to continue...");
            getchar();
            return users[i].isAdmin;
        }
    }

    printf("\033[1;31m  Invalid username or password.\033[0m\n");
    printf("\n  Press Enter to try again...");
    getchar();
    return -1;
}

void adminMenu() {
    system("cls");
    int option;
    while (1) {

        printf("\n");
        printf("\033[1;33m");
        printf(".     |__________________________________\n");
        printf("|-----|\033[1;36m- - -|''''|''''|''''|''''|''''|'\033[1;31m##\033[0m\033[1;33m|__\n");
        printf("|- -  |\033[0m    \033[1;32mMedical Store Management\033[0m    \033[1;31m###\033[0m\033[1;33m__]==\033[0m----------------------\033[1;33m\n");
        printf("\033[1;33m|-----|________________________________\033[0m\033[1;31m##\033[0m\033[1;33m|\n");
        printf("'     |");
        printf("\033[0m\n\n");

        printf("       \033[48;5;227m\033[30m");
        printf("  Admin Menu  ");
        printf("\033[0m\n");
        printf("  --------------------------- \n");
        printf(" |  1. Add Medicine          |\n");
        printf(" |  2. Display Medicines     |\n");
        printf(" |  3. Search Medicine       |\n");
        printf(" |  4. Update Medicine       |\n");
        printf(" |  5. Delete Medicine       |\n");
        printf(" |  6. Check Low Stocks      |\n");
        printf(" |  7. Requested Medicines   |\n");
        printf(" |  0. Logout                |\n");
        printf("  --------------------------- \n");
        printf("\033[1;33m  Choose an option: \033[0m");
        scanf("%d", &option);
        loadData();
        if (option == 0) {
            loggedInUserIndex = -1;
            system("cls");
            break;
        }

        switch (option) {
            case 1: addMedicine(); break;
            case 2: displayMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: checkLowStocks(); break;
            case 7: displayRequestedMedicines(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

void userMenu() {
    system("cls");
    int option;
    while (1) {

        printf("\n");
        printf("\033[1;33m");
        printf(".     |__________________________________\n");
        printf("|-----|\033[1;36m- - -|''''|''''|''''|''''|''''|'\033[1;31m##\033[0m\033[1;33m|__\n");
        printf("|- -  |\033[0m    \033[1;32mMedical Store Management\033[0m    \033[1;31m###\033[0m\033[1;33m__]==\033[0m----------------------\033[1;33m\n");
        printf("\033[1;33m|-----|________________________________\033[0m\033[1;31m##\033[0m\033[1;33m|\n");
        printf("'     |");
        printf("\033[0m\n\n");

        printf("       \033[48;5;227m\033[30m");
        printf("  User Menu  ");
        printf("\033[0m\n");

        printf("  ------------------------ \n");
        printf(" |  1. Display Medicine   |\n");
        printf(" |  2. Search Medicine    |\n");
        printf(" |  3. Add to Cart        |\n");
        printf(" |  4. Checkout           |\n");
        printf(" |  5. Request Medicine   |\n");
        printf(" |  0. Logout             |\n");
        printf("  ------------------------ \n");
        printf(" \033[1;33mChoose an option: \033[0m");
        scanf("%d", &option);
        loadData();
        if (option == 0) {
            loggedInUserIndex = -1;
            system("cls");
            break;
        }

        switch (option) {
            case 1: displayMedicines(); break;
            case 2: searchMedicine(); break;
            case 3: addToCart(); break;
            case 4: checkoutCart(); break;
            case 5: requestMedicine(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

void help() {
    system("cls");
    printf("\033[1;33m+-----------------------------+\n");
    printf("|  [ + ]  User Manual  [ + ]  |\n");
    printf("+-----------------------------+\033[0m\n\n");

    printf("Welcome to the Medical Store Management System!\n");
    printf("This software is designed to help manage a medical store, including inventory, user management, and sales. Below is a guide to using the system:\n\n");

    printf("\033[1;32mFor Users:\033[0m\n");
    printf("\033[1;32m-----------------\033[0m\n");
    printf(" 1. Register/Login:\n");
    printf("    - New users can register with a username and password.\n");
    printf("    - Existing users can log in using their credentials.\n");
    printf("    - Admin users require a master key for admin access.\n");
    printf("\n");
    printf(" 2. Add to Cart:\n");
    printf("    - Search for medicines and add them to your cart by specifying the quantity.\n");
    printf("\n");
    printf(" 3. Checkout:\n");
    printf("    - Review your cart and proceed to checkout. The inventory will update automatically.\n");
    printf("\n");

    printf("\033[1;32mFor Admins:\033[0m\n");
    printf("\033[1;32m-----------------\033[0m\n");
    printf(" 1. Add Medicine:\n");
    printf("    - Add new medicines to the inventory by providing details such as name, price, quantity, shelf number, and location.\n");
    printf("\n");
    printf(" 2. Display Medicines:\n");
    printf("    - View all medicines in the inventory with their details.\n");
    printf("\n");
    printf(" 3. Search Medicine:\n");
    printf("    - Search for a specific medicine by name to view its details.\n");
    printf("\n");
    printf(" 4. Update Medicine:\n");
    printf("    - Modify details of an existing medicine, including price, quantity, shelf number, and location.\n");
    printf("\n");
    printf(" 5. Delete Medicine:\n");
    printf("    - Remove a medicine from the inventory by its name.\n");
    printf("\n");
    printf(" 6. Save Data:\n");
    printf("    - Save the current inventory data to a file for future use.\n");
    printf("\n");
    printf(" 7. Load Data:\n");
    printf("    - Load previously saved inventory data from a file.\n");
    printf("\n");

    printf("\033[1;33mAdditional Features:\033[0m\n");
    printf("\033[1;33m-----------------\033[0m\n");
    printf(" - Use the \033[1;36mchoice\033[0m prompt to navigate back to the main menu or exit the software.\n");
    printf(" - All operations provide clear success or error messages to guide you.\n");
    printf(" - Admin privileges allow for full control over inventory management.\n\n");

    printf("\033[1;32mTips:\033[0m\n");
    printf("\033[1;32m-----------------\033[0m\n");
    printf(" - Use meaningful medicine names to make searching easier.\n");
    printf(" - Ensure data is saved after significant changes to avoid losing progress.\n\n");

    printf("For further assistance, contact your system administrator.\n\n");
    choice();
}

int main() {

    int option;
    while (1) {
        system("cls");
        printf("    \033[48;5;227m\033[30m");
        printf("  Guest Menu  ");
        printf("\033[0m\n");
        printf("\033[1;33m  [Choose an Option] \033[0m\n");

        printf("\033[1;36m  --------------------- \n");
        printf(" |  1. Register        |\n");
        printf(" |  2. Login           |\n");
        printf(" |  3. View Medicines  |\n");
        printf(" |  4. Help            |\n");
        printf(" |  0. Exit            |\n");
        printf("  --------------------- \033[0m\n");
        loadUsers();
        loadData();

        printf("  \033[1;33mChoose an option: \033[0m");
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
                displayMedicines();
                break;
            case 4:
                help();
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
