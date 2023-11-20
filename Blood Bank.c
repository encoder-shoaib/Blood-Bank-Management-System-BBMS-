#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

struct Donor {
    char name[100];
    char bloodType[5];
    int age;
    char contactNumber[15];
};

struct User {
    char username[100];
    char password[100];
    struct Donor donorInfo;
    struct User* next;
};

// Function prototypes
struct User* createUser();
int userCount(struct User* head);
int userExists(struct User* head, char* username, char* password);
void displayDonors(struct User* head);
void searchDonors(struct User* head);
void searchDonorsByBloodType(struct User* head, char* bloodType);
void searchDonorsByName(struct User* head, char* donorName);
void deleteUsers(struct User* head);
void deleteUser(struct User** head, char* username);
void logoutUser();
void cleanup(struct User* head);

int main() {
    struct User* head = NULL;
    int loggedIn = 0;
    int choice;

    do {
        printf("Blood Bank Management System\n");
        if (!loggedIn) {
            printf("1. Register User\n");
            printf("2. Log In\n");
        } else {
            printf("4. Display Donors\n");
            printf("5. Search Donors\n");
            printf("8. Logout\n");
            printf("9. Delete User\n");
            printf("11. Exit\n");
        }

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue; // Restart the loop
        }

        switch (choice) {
            case 1:
                if (!loggedIn) {
                    if (head == NULL) {
                        head = createUser();
                        if (head != NULL) {
                            printf("User registered successfully!\n");
                        }
                    } else if (head != NULL && userCount(head) < MAX_USERS) {
                        struct User* newUser = createUser();
                        if (newUser != NULL) {
                            struct User* current = head;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->next = newUser;
                            printf("User registered successfully!\n");
                        }
                    } else {
                        printf("User database is full. Cannot register more users.\n");
                    }
                } else {
                    printf("You are already logged in. Logout to register a new user.\n");
                }
                break;
            case 2:
                if (!loggedIn) {
                    if (head == NULL) {
                        printf("No users registered yet. Please register first.\n");
                    } else {
                        char username[100];
                        char password[100];
                        int userFound = 0;
                        printf("Enter username: ");
                        scanf("%99s", username);
                        printf("Enter password: ");
                        scanf("%99s", password);

                        if (userExists(head, username, password)) {
                            printf("Login successful!\n");
                            loggedIn = 1; // Set the flag to indicate that the user is logged in
                            userFound = 1;
                        }

                        if (!userFound) {
                            printf("Login failed. Invalid username or password.\n");
                        }
                    }
                } else {
                    printf("You are already logged in.\n");
                }
                break;
            case 3:
                if (loggedIn) {
                    displayDonors(head);
                } else {
                    printf("Please log in to display donors.\n");
                }
                break;
            case 4:
                if (loggedIn) {
                    searchDonors(head);
                } else {
                    printf("Please log in to search donors.\n");
                }
                break;
            case 8:
                if (loggedIn) {
                    loggedIn = 0; // Logout the user
                    printf("Logged out successfully.\n");
                } else {
                    printf("You are not logged in.\n");
                }
                break;
            case 9:
                if (loggedIn) {
                    char currentUsername[100];
                    strcpy(currentUsername, head->username); // Assuming the logged-in user is the first node
                    deleteUser(&head, currentUsername);
                    loggedIn = 0; // Log out the user after deletion
                } else {
                    printf("You are not logged in.\n");
                }
                break;
            case 11:
                cleanup(head);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}

struct User* createUser() {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        printf("Memory allocation failed. User registration failed.\n");
        return NULL;
    }

    memset(newUser, 0, sizeof(struct User));
    printf("Enter username: ");
    scanf("%99s", newUser->username);
    printf("Enter password: ");
    scanf("%99s", newUser->password);

    printf("Enter Donor Name: ");
    scanf("%99s", newUser->donorInfo.name);
    printf("Enter Blood Type: ");
    scanf("%4s", newUser->donorInfo.bloodType);
    printf("Enter Age: ");
    int age;
    if (scanf("%d", &age) != 1) {
        printf("Invalid input for age. User registration failed.\n");
        free(newUser);
        while (getchar() != '\n'); // Clear the input buffer
        return NULL;
    }
    newUser->donorInfo.age = age;

    newUser->next = NULL;

    return newUser;
}

int userCount(struct User* head) {
    int count = 0;
    struct User* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int userExists(struct User* head, char* username, char* password) {
    struct User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            return 1; // User exists and password is correct
        }
        current = current->next;
    }
    return 0; // User not found or incorrect password
}

void displayDonors(struct User* head) {
    printf("Donor List:\n");
    struct User* current = head;
    while (current != NULL) {
        printf("Username: %s\n", current->username);
        printf("Donor Name: %s\n", current->donorInfo.name);
        printf("Blood Type: %s\n", current->donorInfo.bloodType);
        printf("Age: %d\n", current->donorInfo.age);
        printf("--------------------\n");
        current = current->next;
    }
}

void searchDonors(struct User* head) {
    printf("Search Options:\n");
    printf("1. Search by Blood Type\n");
    printf("2. Search by Donor Name\n");
    printf("Enter your choice: ");
    int searchChoice;
    scanf("%d", &searchChoice);

    switch (searchChoice) {
        case 1: {
            char bloodType[5];
            printf("Enter blood type to search: ");
            scanf("%4s", bloodType);
            printf("Search Results:\n");
            searchDonorsByBloodType(head, bloodType);
            break;
        }
        case 2: {
            char donorName[100];
            printf("Enter donor name to search: ");
            scanf("%99s", donorName);
            printf("Search Results:\n");
            searchDonorsByName(head, donorName);
            break;
        }
        default:
            printf("Invalid choice for search.\n");
    }
}

void searchDonorsByBloodType(struct User* head, char* bloodType) {
    struct User* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->donorInfo.bloodType, bloodType) == 0) {
            printf("Username: %s\n", current->username);
            printf("Donor Name: %s\n", current->donorInfo.name);
            printf("Blood Type: %s\n", current->donorInfo.bloodType);
            printf("Age: %d\n", current->donorInfo.age);
            printf("--------------------\n");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No donors found with blood type %s\n", bloodType);
    }
}

void searchDonorsByName(struct User* head, char* donorName) {
    struct User* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->donorInfo.name, donorName) == 0) {
            printf("Username: %s\n", current->username);
            printf("Donor Name: %s\n", current->donorInfo.name);
            printf("Blood Type: %s\n", current->donorInfo.bloodType);
            printf("Age: %d\n", current->donorInfo.age);
            printf("--------------------\n");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No donors found with name %s\n", donorName);
    }
}

void deleteUsers(struct User* head) {
    struct User* current = head;
    while (current != NULL) {
        struct User* next = current->next;
        free(current);
        current = next;
    }
}

void deleteUser(struct User** head, char* username) {
    struct User* current = *head;
    struct User* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            if (prev == NULL) {
                // If the user to be deleted is the first node
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            printf("We're Sorry to See You Go '%s'  \n Account deleted successfully.\n", username);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("User '%s' not found. Deletion failed.\n", username);
}

void logoutUser() {
    printf("Logged out successfully.\n");
}

void cleanup(struct User* head) {
    deleteUsers(head);
    // Any additional cleanup steps if needed
}
