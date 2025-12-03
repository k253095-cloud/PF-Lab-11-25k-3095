#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[50];
    int roll;
    float marks[3];
    float percentage;
    char grade;
};

// -------- Function Prototypes --------
void inputStudent(struct Student *s);
char calculateGrade(float p);
void displayStudent(struct Student s);
float classAverage(struct Student s[], int n);
void findByGrade(struct Student s[], int n, char grade);
void searchStudent(struct Student s[], int n);
void rankStudents(struct Student s[], int n);

// -------------------------------------

// Input 1 student's data
void inputStudent(struct Student *s) {
    printf("\nEnter Name: ");
    getchar();                 // remove newline
    fgets(s->name, 50, stdin);
    s->name[strcspn(s->name, "\n")] = '\0';

    printf("Enter Roll Number: ");
    scanf("%d", &s->roll);

    // Marks input with validation
    for (int i = 0; i < 3; i++) {
        do {
            printf("Enter marks of subject %d (0-100): ", i + 1);
            scanf("%f", &s->marks[i]);
            if (s->marks[i] < 0 || s->marks[i] > 100)
                printf("Invalid! Marks must be between 0-100.\n");
        } while (s->marks[i] < 0 || s->marks[i] > 100);
    }

    // Calculate percentage
    s->percentage = (s->marks[0] + s->marks[1] + s->marks[2]) / 3.0;

    // Grade
    s->grade = calculateGrade(s->percentage);
}

// Grade function
char calculateGrade(float p) {
    if (p >= 90) return '1';     // A+
    else if (p >= 80) return '2'; // A
    else if (p >= 70) return '3'; // B+
    else if (p >= 60) return '4'; // B
    else if (p >= 50) return '5'; // C
    else return '6';             // F
}

// Display 1 student
void displayStudent(struct Student s) {
    printf("\nName: %s\n", s.name);
    printf("Roll: %d\n", s.roll);
    printf("Marks: %.1f, %.1f, %.1f\n", s.marks[0], s.marks[1], s.marks[2]);
    printf("Percentage: %.2f\n", s.percentage);

    // Convert 1–6 back to grade name
    char *gradeNames[] = {"", "A+", "A", "B+", "B", "C", "F"};
    printf("Grade: %s\n", gradeNames[s.grade - '0']);
}

// Class average
float classAverage(struct Student s[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += s[i].percentage;
    return sum / n;
}

// Find students by grade
void findByGrade(struct Student s[], int n, char grade) {
    printf("\n--- Students with Grade %c ---\n", grade);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].grade == grade) {
            displayStudent(s[i]);
            found = 1;
        }
    }
    if (!found) printf("No students found with this grade.\n");
}

// Search by name or roll
void searchStudent(struct Student s[], int n) {
    int choice;
    printf("\nSearch by:\n1. Roll Number\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int r;
        printf("Enter Roll Number: ");
        scanf("%d", &r);
        for (int i = 0; i < n; i++)
            if (s[i].roll == r) {
                displayStudent(s[i]);
                return;
            }
        printf("Student not found.\n");

    } else if (choice == 2) {
        char name[50];
        printf("Enter Name: ");
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';

        for (int i = 0; i < n; i++)
            if (strcmp(s[i].name, name) == 0) {
                displayStudent(s[i]);
                return;
            }
        printf("Student not found.\n");
    }
}

// Rank students based on percentage (descending)
void rankStudents(struct Student s[], int n) {
    struct Student temp;

    // Bubble sort
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].percentage < s[j + 1].percentage) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }

    printf("\n--- Student Ranking (Highest to Lowest) ---\n");
    for (int i = 0; i < n; i++) {
        printf("\nRank %d:\n", i + 1);
        displayStudent(s[i]);
    }
}

// ---------------- MAIN ----------------

int main() {
    struct Student s[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Input all students
    for (int i = 0; i < n; i++) {
        printf("\n--- Enter data for student %d ---\n", i + 1);
        inputStudent(&s[i]);
    }

    // Menu
    int choice;
    do {
        printf("\n\n========= MENU =========\n");
        printf("1. Display All Students\n");
        printf("2. Find Students by Grade\n");
        printf("3. Search Student (Name/Roll)\n");
        printf("4. Display Class Average\n");
        printf("5. Display Ranking\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < n; i++)
                    displayStudent(s[i]);
                break;

            case 2: {
                char g;
                printf("Enter Grade Code (1=A+, 2=A, 3=B+, 4=B, 5=C, 6=F): ");
                scanf(" %c", &g);
                findByGrade(s, n, g);
                break;
            }

            case 3:
                searchStudent(s, n);
                break;

            case 4: {
                float avg = classAverage(s, n);
                printf("Class Average = %.2f\n", avg);
                break;
            }

            case 5:
                rankStudents(s, n);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}

