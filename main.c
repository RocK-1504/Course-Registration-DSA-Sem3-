#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course_registration.h"

int main() 
{
    int choice;

    while (1) 
    {
        printf("\n1. Add Course\n");
        printf("2. Register Student\n");
        printf("3. View Course Waitlist\n");
        printf("4. Move Course to Completion\n");
        printf("5. Drop Course\n");
        printf("6. View Enrolled Courses\n");
        printf("7. Exit\n");
        printf(": ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) 
        {
            int courseId, startTime, endTime;
            char name[50];
            char* prereqs[MAX_PREREQS + 1];
            char buffer[10];
            int prereqCount = 0;

            printf("Enter course ID: ");
            scanf("%d", &courseId);
            getchar();

            printf("Enter course name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter course start time (e.g., 930 for 9:30 am): ");
            scanf("%d", &startTime);
            printf("Enter course end time: ");
            scanf("%d", &endTime);
            getchar();

            printf("Enter prerequisite course IDs (enter -1 to stop):\n");
            while (prereqCount < MAX_PREREQS) 
            {
                printf("Prerequisite %d: ", prereqCount + 1);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strcmp(buffer, "-1") == 0) 
                    break;
                prereqs[prereqCount] = malloc(strlen(buffer) + 1);
                strcpy(prereqs[prereqCount], buffer);
                prereqCount++;
            }
            prereqs[prereqCount] = NULL;

            addCourse(courseId, name, prereqs, startTime, endTime);

            for (int i = 0; i < prereqCount; i++) 
                free(prereqs[i]);
        } 
        else if (choice == 2) 
        {
            int studentId, courseId;
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            printf("Enter course ID to register: ");
            scanf("%d", &courseId);
            getchar();
            registerStudent(studentId, courseId);
        } 
        else if (choice == 3) 
        {
            int courseId;
            printf("Enter course ID to view waitlist: ");
            scanf("%d", &courseId);
            getchar();
            getWaitlist(courseId);
        } 
        else if (choice == 4)
        {
            int studentId, courseId;
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            printf("Enter course ID to complete: ");
            scanf("%d", &courseId);
            getchar();
            completeCourse(studentId, courseId);
        }
	else if (choice == 5) 
        {
	    int studentId, courseId;
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            printf("Enter course ID to drop: ");
            scanf("%d", &courseId);
            getchar();
	    dropCourse(studentId, courseId);
        } 
	else if (choice == 6) 
        {
	    int studentId;
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            getchar();
            viewEnrolledCourses(studentId);
        } 
        else if (choice == 7) 
        {
            break;
        } 
        else 
        {
            printf("Please enter a valid number.\n");
        }
    }
return 0;
}
