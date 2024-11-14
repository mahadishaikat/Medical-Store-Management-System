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

int main() {

    return 0;
}
