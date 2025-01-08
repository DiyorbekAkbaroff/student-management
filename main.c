#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Student* students = NULL;
int student_count = 0;

Lesson* lessons = NULL;
int lesson_count = 0;

Score* scores = NULL;
int score_count = 0;

void add_student();
void get_students();
void get_student_detail();
void get_student_by_name();
void add_lesson();
void add_score();
void get_lesson_statistics();
void menu();

int main() {

    puts("Program is running...");

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

            case 3:
                get_student_detail();
                break;

            case 4:
                get_student_by_name();
                break;

            case 5:
                add_lesson();
                break;

            case 6:
                add_score();
                break;

            case 7:
                get_lesson_statistics();
                break;

            case 8:
                exit(0);
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

void get_student_detail() {
    int id;
    printf("Enter student ID (0 to %d): ", student_count - 1);
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Invalid student ID!\n");
        return;
    }

    Student s = students[id];
    printf("\nFirst Name: %s\n", s.first_name);
    printf("Last Name: %s\n", s.last_name);
    printf("Age: %d\n", s.age);
    printf("Phone: %s\n", s.contact.phone);
    printf("Email: %s\n", s.contact.email);
    printf("Parent's Name: %s\n", s.parent.name);
    printf("Parent's Phone: %s\n", s.parent.contact.phone);
    printf("Parent's Email: %s\n", s.parent.contact.email);
}

void get_student_by_name() {
    char name[50];
    printf("Enter first name to search: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].first_name, name) == 0) {
            printf("%-10s | %-9s | %-3d | %-10s | %-16s | %-13s\n",
                students[i].first_name,
                students[i].last_name,
                students[i].age,
                students[i].contact.phone,
                students[i].contact.email,
                students[i].parent.name
            );
            found = 1;
        }
    }

    if (!found) {
        printf("No student found with the name %s\n", name);
    }
}

void add_lesson() {
    Lesson lesson;

    printf("Enter lesson ID: ");
    scanf("%d", &lesson.id);

    printf("Enter lesson name: ");
    scanf("%s", lesson.name);

    lessons = realloc(lessons, sizeof(Lesson) * (lesson_count + 1));
    lessons[lesson_count] = lesson;

    lesson_count++;
    printf("Lesson added successfully!\n");
}

void add_score() {
    int student_id, lesson_id, score_value;

    printf("Enter student ID (0 to %d): ", student_count - 1);
    scanf("%d", &student_id);

    if (student_id < 0 || student_id >= student_count) {
        printf("Invalid student ID!\n");
        return;
    }

    printf("Enter lesson ID (0 to %d): ", lesson_count - 1);
    scanf("%d", &lesson_id);

    if (lesson_id < 0 || lesson_id >= lesson_count) {
        printf("Invalid lesson ID!\n");
        return;
    }

    printf("Enter score: ");
    scanf("%d", &score_value);

    Score score;
    score.student = students[student_id];
    score.lesson = lessons[lesson_id];
    score.score = score_value;

    scores = realloc(scores, sizeof(Score) * (score_count + 1));
    scores[score_count] = score;

    score_count++;
    printf("Score added successfully!\n");
}

void get_lesson_statistics() {
    if (lesson_count == 0) {
        printf("No lessons available!\n");
        return;
    }

    for (int i = 0; i < lesson_count; i++) {
        int total_score = 0, count = 0;

        for (int j = 0; j < score_count; j++) {
            if (scores[j].lesson.id == lessons[i].id) {
                total_score += scores[j].score;
                count++;
            }
        }

        if (count > 0) {
            printf("Lesson: %s | Average Score: %.2f\n", lessons[i].name, (float)total_score / count);
        } else {
            printf("Lesson: %s | No scores available\n", lessons[i].name);
        }
    }
}
