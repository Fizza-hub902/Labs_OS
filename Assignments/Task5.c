#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Thread function to check Dean's List eligibility
void *check_deans_list(void *arg) {
    Student *s = (Student *)arg;

    printf("\n--- Student Info ---\n");
    printf("ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    int *eligible = malloc(sizeof(int));  // Allocate memory for return value
    if (s->gpa >= 3.5) {
        printf("Status: Dean's List ✅\n");
        *eligible = 1;
    } else {
        printf("Status: Not Eligible ❌\n");
        *eligible = 0;
    }

    pthread_exit((void *)eligible);  // Return result via pointer
}

int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Alice Johnson", 3.8},
        {102, "Bob Smith", 3.2},
        {103, "Charlie Brown", 3.9}
    };

    int deans_list_count = 0;

    // Create 3 threads for 3 students
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_deans_list, (void *)&students[i]);
    }

    // Join threads and count eligible students
    for (int i = 0; i < 3; i++) {
        int *result;
        pthread_join(threads[i], (void **)&result);
        deans_list_count += *result;
        free(result);  // Free allocated memory
    }

    printf("\nTotal Students on Dean's List: %d\n", deans_list_count);

    return 0;
}
