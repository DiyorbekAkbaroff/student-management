#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct {
    char phone[15];
    char email[50];
} Contact;

typedef struct {
    char name[15];
    Contact contact;
} Parent;

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    Contact contact;
    Parent parent;
} Student;

typedef struct {
    int id;
    char name[122];
} Lesson;

typedef struct {
    Lesson lesson;
    Student student;
    int score;
} Score;

// Global Variables
Student* students = NULL;
int student_count = 0;

Lesson* lessons = NULL;
int lesson_count = 0;

Score* scores = NULL;
int score_count = 0;

// Function Prototypes
void add_student();
void get_students();
// void get_student_detail();
// void get_student_by_name();
// void add_lesson();
// void add_score();
// void get_lesson_statistics();
void menu();

// Main Function
int main() {

    puts("Programm is running...");

    students = malloc(sizeof(Student));
    lessons = malloc(sizeof(Lesson));
    scores = malloc(sizeof(Score));

    while (1) {
        menu();

        int choice;
        printf("Enter your choice: "); scanf("%d", &choice); getchar();

        switch (choice) {
            case 1:
                add_student();
                break;
            
            case 2:
                get_students();
                break;
            
            case 8:
                exit();
                break;
            
            default:
                puts("Invalid choice.");
                break;
        }
    }
    
    return 0;
}

// Function Definitions
void menu() {
    printf("\n1. Add Student\n");
    printf("2. View Students\n");
    printf("3. View Student Details\n");
    printf("4. Find Student by Name\n");
    printf("5. Add Lesson\n");
    printf("6. Add Score\n");
    printf("7. Get Lesson Statistics\n");
    printf("8. Exit\n");
}

void add_student() {
    Student student;

    printf("Enter first name: ");
    scanf("%s", student.first_name);

    printf("Enter last name: ");
    scanf("%s", student.last_name);

    printf("Enter age: ");
    scanf("%d", &student.age);

    printf("Enter phone: ");
    scanf("%s", student.contact.phone);

    printf("Enter email: ");
    scanf("%s", student.contact.email);

    printf("Enter parent's name: ");
    scanf("%s", student.parent.name);

    printf("Enter parent's phone: ");
    scanf("%s", student.parent.contact.phone);

    printf("Enter parent's email: ");
    scanf("%s", student.parent.contact.email);

    students = realloc(students, sizeof(Student) * (student_count + 1));
    students[student_count] = student;

    student_count++;
    printf("Student added successfully!\n");

}

void get_students() {
    puts("First Name | Last Name | Age | Phone        | Email             | Parent's Name | Parent's Phone | Parent's Email");
    puts("-------------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < student_count; i++) {
        printf("%-10s | %-9s | %-3d | %-10s | %-16s | %-13s | %-14s | %-16s\n",
            students[i].first_name,
            students[i].last_name,
            students[i].age,
            students[i].contact.phone,
            students[i].contact.email,
            students[i].parent.name,
            students[i].parent.contact.phone,
            students[i].parent.contact.email
        );
    }
}

void exit() {
    // Free allocated memory before exiting
    free(students);
    free(lessons);
    free(scores);

    puts("Programm is closed...");

    exit(0);
}
