#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100

// ---------- STRUCT ----------
struct Employee {
    int id;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    int joinDay, joinMonth, joinYear;
    char phone[15];
    char email[50];
};

// ---------- GLOBAL EMPLOYEE STORAGE ----------
struct Employee emp[MAX];
int count = 0;

// ---------- GET CURRENT YEAR ----------
int getCurrentYear() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

// ---------- CALCULATE EXPERIENCE ----------
int experienceYears(struct Employee e) {
    int currentYear = getCurrentYear();
    return currentYear - e.joinYear;
}

// ---------- ADD EMPLOYEE ----------
void addEmployee() {
    printf("\n--- ADD NEW EMPLOYEE ---\n");

    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Name: ");
    fflush(stdin);
    fgets(emp[count].name, 50, stdin);
    emp[count].name[strcspn(emp[count].name, "\n")] = '\0';

    printf("Enter Department (IT/HR/Finance/Marketing/Operations): ");
    fflush(stdin);
    fgets(emp[count].department, 20, stdin);
    emp[count].department[strcspn(emp[count].department, "\n")] = '\0';

    printf("Enter Designation (Intern/Junior/Senior/Manager/Director): ");
    fflush(stdin);
    fgets(emp[count].designation, 20, stdin);
    emp[count].designation[strcspn(emp[count].designation, "\n")] = '\0';

    printf("Enter Salary: ");
    scanf("%f", &emp[count].salary);

    printf("Enter Joining Date (DD MM YYYY): ");
    scanf("%d %d %d", &emp[count].joinDay, &emp[count].joinMonth, &emp[count].joinYear);

    printf("Enter Phone Number: ");
    scanf("%s", emp[count].phone);

    printf("Enter Email: ");
    scanf("%s", emp[count].email);

    count++;
    printf("\n? Employee Added Successfully!\n");
}

// ---------- DISPLAY ONE EMPLOYEE ----------
void displayEmployee(struct Employee e) {
    printf("\n--- EMPLOYEE DETAILS ---\n");
    printf("ID: %d\n", e.id);
    printf("Name: %s\n", e.name);
    printf("Department: %s\n", e.department);
    printf("Designation: %s\n", e.designation);
    printf("Salary: %.2f\n", e.salary);
    printf("Joining Date: %02d-%02d-%d\n", e.joinDay, e.joinMonth, e.joinYear);
    printf("Experience: %d years\n", experienceYears(e));
    printf("Phone: %s\n", e.phone);
    printf("Email: %s\n\n", e.email);
}

// ---------- SEARCH BY DEPARTMENT ----------
void searchByDepartment() {
    char dept[20];
    printf("\nEnter department to search: ");
    fflush(stdin);
    fgets(dept, 20, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    printf("\n--- RESULT ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].department, dept) == 0) {
            displayEmployee(emp[i]);
        }
    }
}

// ---------- SEARCH BY DESIGNATION ----------
void searchByDesignation() {
    char des[20];
    printf("\nEnter designation to search: ");
    fflush(stdin);
    fgets(des, 20, stdin);
    des[strcspn(des, "\n")] = '\0';

    printf("\n--- RESULT ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].designation, des) == 0) {
            displayEmployee(emp[i]);
        }
    }
}

// ---------- SEARCH BY EXPERIENCE ----------
void searchByExperience() {
    int years;
    printf("\nEnter minimum experience in years: ");
    scanf("%d", &years);

    printf("\n--- RESULT ---\n");
    for (int i = 0; i < count; i++) {
        if (experienceYears(emp[i]) >= years) {
            displayEmployee(emp[i]);
        }
    }
}

// ---------- SALARY STATISTICS PER DEPARTMENT ----------
void departmentSalaryStats() {
    char dept[20];
    printf("\nEnter department: ");
    fflush(stdin);
    fgets(dept, 20, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    float total = 0;
    int c = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].department, dept) == 0) {
            total += emp[i].salary;
            c++;
        }
    }

    if (c == 0) {
        printf("\nNo employees in this department.\n");
        return;
    }

    printf("\n--- SALARY STATISTICS (%s Department) ---\n", dept);
    printf("Total Salary: %.2f\n", total);
    printf("Average Salary: %.2f\n", total / c);
}

// ---------- ANNUAL APPRAISAL ----------
void annualAppraisal() {
    int id;
    float percent;

    printf("\nEnter Employee ID for appraisal: ");
    scanf("%d", &id);

    printf("Enter increment percentage (5 - 15): ");
    scanf("%f", &percent);

    if (percent < 5 || percent > 15) {
        printf("\n? Invalid appraisal percent!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            float inc = emp[i].salary * (percent / 100);
            emp[i].salary += inc;
            printf("\n? Appraisal applied! New Salary: %.2f\n", emp[i].salary);
            return;
        }
    }

    printf("\n? Employee ID not found!\n");
}

// ---------- PROMOTION ELIGIBILITY (>3 YEARS) ----------
void promotionEligibility() {
    printf("\n--- EMPLOYEES ELIGIBLE FOR PROMOTION (>3 years) ---\n");

    for (int i = 0; i < count; i++) {
        if (experienceYears(emp[i]) > 3) {
            displayEmployee(emp[i]);
        }
    }
}

// ---------- MAIN MENU ----------
int main() {
    int choice;

    while (1) {
        printf("\n\n===== EMPLOYEE RECORD SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Search by Department\n");
        printf("3. Search by Designation\n");
        printf("4. Search by Experience\n");
        printf("5. Department Salary Statistics\n");
        printf("6. Annual Appraisal\n");
        printf("7. Promotion Eligibility\n");
        printf("8. Display All Employees\n");
        printf("9. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: searchByDepartment(); break;
            case 3: searchByDesignation(); break;
            case 4: searchByExperience(); break;
            case 5: departmentSalaryStats(); break;
            case 6: annualAppraisal(); break;
            case 7: promotionEligibility(); break;
            case 8:
                for (int i = 0; i < count; i++)
                    displayEmployee(emp[i]);
                break;
            case 9: 
                printf("\nThank you!\n");
                return 0;
            default: 
                printf("\n? Invalid choice!\n");
        }
    }

    return 0;
}

