#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookID;
    char title[100];
    char author[100];
    int isAvailable;
};

struct User {
    int userID;
    char name[100];
    int books_issued;
};

// Function prototypes
void displayMenu();
void addUser(struct User users[], int *userCount);
void addBook(struct Book books[], int *bookCount);
void searchBook(struct Book books[], int bookCount, char *searchTitle);
void displayUsers(struct User users[], int userCount);
void displayBooks(struct Book books[], int bookCount);
void borrowBook(struct Book books[], int bookCount, struct User users[], int userCount);

int main() {
    struct User users[100];
    struct Book books[100];
    int userCount = 0;
    int bookCount = 0;
    char searchTitle[100];
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline left by scanf

        switch (choice) {
            case 1:
                addUser(users, &userCount);
                break;
            case 2:
                addBook(books, &bookCount);
                break;
            case 3:
                printf("Enter book title to search: ");
                fgets(searchTitle, sizeof(searchTitle), stdin);
                searchTitle[strcspn(searchTitle, "\n")] = '\0'; // Remove trailing newline
                searchBook(books, bookCount, searchTitle);
                break;
            case 4:
                displayUsers(users, userCount);
                break;
            case 5:
                displayBooks(books, bookCount);
                break;
            case 6:
                borrowBook(books, bookCount, users, userCount);
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

// Function definitions
void displayMenu() {
    printf("\n--- Library Management System ---\n");
    printf("1. Add User\n");
    printf("2. Add Book\n");
    printf("3. Search Book\n");
    printf("4. Display Users\n");
    printf("5. Display Books\n");
    printf("6. Borrow Book\n");
    printf("7. Exit\n");
}

void addUser(struct User users[], int *userCount) {
    printf("Enter user name: ");
    fgets(users[*userCount].name, sizeof(users[*userCount].name), stdin);
    users[*userCount].name[strcspn(users[*userCount].name, "\n")] = '\0'; // Remove trailing newline

    users[*userCount].userID = *userCount + 1;
    (*userCount)++;

    printf("User added successfully!\n");
}

void addBook(struct Book books[], int *bookCount) {
    printf("Enter book title: ");
    fgets(books[*bookCount].title, sizeof(books[*bookCount].title), stdin);
    books[*bookCount].title[strcspn(books[*bookCount].title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter author: ");
    fgets(books[*bookCount].author, sizeof(books[*bookCount].author), stdin);
    books[*bookCount].author[strcspn(books[*bookCount].author, "\n")] = '\0'; // Remove trailing newline

    books[*bookCount].bookID = *bookCount + 1;
    books[*bookCount].isAvailable = 1;

    (*bookCount)++;

    printf("Book added successfully!\n");
}

void searchBook(struct Book books[], int bookCount, char *searchTitle) {
    printf("Search Results for: %s\n", searchTitle);

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, searchTitle) != NULL) {
            printf("ID: %d, Title: %s, Author: %s, Available: %s\n", 
                   books[i].bookID, books[i].title, books[i].author, 
                   books[i].isAvailable ? "Yes" : "No");
        }
    }
}

void displayUsers(struct User users[], int userCount) {
    printf("Users enrolled with library:\n");

    for (int i = 0; i < userCount; i++) {
        printf("User ID: %d\n", users[i].userID);
        printf("User Name: %s\n", users[i].name);
    }
}

void borrowBook(struct Book books[], int bookCount, struct User users[], int userCount) {
    int userID, bookID;

    printf("Enter user ID: ");
    scanf("%d", &userID);
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookID);

    if (userID > 0 && userID <= userCount && bookID > 0 && bookID <= bookCount) {
        if (books[bookID - 1].isAvailable) {
            printf("Book borrowed successfully by user %s!\n", users[userID - 1].name);
            books[bookID - 1].isAvailable = 0;
        } else {
            printf("Book is not available for borrowing.\n");
        }
    } else {
        printf("Invalid user ID or book ID.\n");
    }
}

void displayBooks(struct Book books[], int bookCount) {
    printf("Books in the library:\n");

    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Available: %s\n", 
               books[i].bookID, books[i].title, books[i].author, 
               books[i].isAvailable ? "Yes" : "No");
    }
}
