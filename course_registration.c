#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course_registration.h"

Course courseList[MAX_COURSES];
int courseCount = 0;

Student studentList[MAX_STUDENTS];
int studentCount = 0;

Course* findCourseById(int courseId) 
{
    int low = 0;
    int high = courseCount - 1;

    while (low <= high) 
    {
        int mid = low + (high - low) / 2;

        if (courseList[mid].id == courseId) 
        {
            return &courseList[mid];
        }
        else if (courseList[mid].id < courseId) 
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }

    return NULL;
}


Student* findStudentById(int studentId) 
{
    int low = 0;
    int high = studentCount - 1;

    while (low <= high) 
    {
        int mid = low + (high - low) / 2;

        if (studentList[mid].id == studentId) 
        {
            return &studentList[mid];
        }
        else if (studentList[mid].id < studentId) 
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }

    return NULL;
}

EnrolledNode* insertNode(EnrolledNode* root, int id) 
{
    if (!root) 
    {
        EnrolledNode* node = malloc(sizeof(EnrolledNode));
        node->id = id;
        node->left = node->right = NULL;
        return node;
    }
	
    if (id < root->id)
        root->left = insertNode(root->left, id);

    else if (id > root->id)
        root->right = insertNode(root->right, id);

    return root;
}

int searchNode(EnrolledNode* root, int id) 
{
    if (!root) 
	return 0;
    if (id == root->id)
	return 1;
    if (id < root->id) 
	return searchNode(root->left, id);
    return searchNode(root->right, id);
}

EnrolledNode* minNode(EnrolledNode* root) 
{
    while (root && root->left) 
	root = root->left;
    return root;
}

EnrolledNode* deleteNode(EnrolledNode* root, int id) 
{
    if (!root) 
	return NULL;

    if (id < root->id)
        root->left = deleteNode(root->left, id);

    else if (id > root->id)
        root->right = deleteNode(root->right, id);

    else 
    {
        if (!root->left) 
	{
            EnrolledNode* temp = root->right;
            free(root);
            return temp;
        } 

	else if (!root->right) 
	{
            EnrolledNode* temp = root->left;
            free(root);
            return temp;
        }

        EnrolledNode* temp = minNode(root->right);
        root->id = temp->id;
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}

void inorderPrint(EnrolledNode* root) 
{

    if (!root) 
	return;

    inorderPrint(root->left);
    printf("%d\n", root->id);
    inorderPrint(root->right);

}


int hasPrerequisites(Student* s, Course* c) 
{
    for (int i = 0; i < MAX_PREREQS && c->prerequisites[i][0] != '\0'; i++) 
    {
        int prereqId = atoi(c->prerequisites[i]);
        if (!searchNode(s->completedRoot, prereqId))
            return 0;
    }
    return 1;
}


int checkOverlap(EnrolledNode* root, Course* newCourse) 
{
    if (!root) 
	return 0;

    if (checkOverlap(root->left, newCourse)) 
	return 1;

    Course* existing = findCourseById(root->id);
    if (existing && !(newCourse->endTime <= existing->startTime || newCourse->startTime >= existing->endTime)) 
    {
        printf("Conflict: Course %d (%s) overlaps with Course %d (%s)\n",
               newCourse->id, newCourse->name, existing->id, existing->name);
        return 1;
    }

    if (checkOverlap(root->right, newCourse)) 
	return 1;

    return 0;
}

int detectConflict(int studentId, int newCourseId) 
{
    Student* s = findStudentById(studentId);
    Course* newCourse = findCourseById(newCourseId);

    if (!s || !newCourse) 
	return 0;

    return checkOverlap(s->enrolledRoot, newCourse);
}


int enqueueWaitlist(Course* c, int studentId)
{
    if (c->waitlistCount >= MAX_WAITLIST) 
    {
        printf("Waitlist for course %d is full.\n", c->id);
        return 0;
    }
    c->waitlistRear = (c->waitlistRear + 1) % MAX_WAITLIST;
    c->waitlist[c->waitlistRear] = studentId;
    c->waitlistCount++;
    return 1;
}

void addCourse(int courseId, char* name, char* prerequisites[], int startTime, int endTime) 
{
    if (courseCount >= MAX_COURSES) 
    {
        printf("Course list is full.\n");
        return;
    }

    Course* c = &courseList[courseCount++];
    c->enrolledRoot = NULL;
    c->id = courseId;
    strncpy(c->name, name, sizeof(c->name));
    c->name[sizeof(c->name) - 1] = '\0';
    c->startTime = startTime;
    c->endTime = endTime;

    int i = 0;
    while (prerequisites && prerequisites[i] != NULL && i < MAX_PREREQS) 
    {
        strncpy(c->prerequisites[i], prerequisites[i], sizeof(c->prerequisites[i]));
        c->prerequisites[i][sizeof(c->prerequisites[i]) - 1] = '\0';
        i++;
    }

    c->waitlistFront = 0;
    c->enrolledCount = 0;
    c->waitlistRear = -1;
    c->waitlistCount = 0;
}
 
void registerStudent(int studentId, int courseId) 
{
    Course* c = findCourseById(courseId);
    if (!c) 
    { 
	printf("Course not found.\n"); 
	return; 
    }

    Student* s = findStudentById(studentId);

    if (!s) 
    {
        if (studentCount >= MAX_STUDENTS) 
        { 
	    printf("Student list full.\n"); 
	    return; 
	}

        s = &studentList[studentCount++];
        s->id = studentId;
        printf("Enter name for student %d: ", studentId);
        fgets(s->name, sizeof(s->name), stdin);
        s->name[strcspn(s->name, "\n")] = '\0';
        s->enrolledRoot = NULL;
        s->completedRoot = NULL;

    }

    if (searchNode(s->completedRoot, courseId)) 
    {
        printf("Already completed.\n"); 
	return;
    }

    if (searchNode(s->enrolledRoot, courseId)) 
    {
        printf("Already enrolled.\n"); 
	return;
    }

    if (!hasPrerequisites(s, c)) 
    {
        printf("Student %d does not meet prerequisites for course %d.\n", studentId, courseId);
        return;
    }

    if (detectConflict(studentId, courseId)) 
    {
        printf("Student %d has a timing conflict with course %d.\n", studentId, courseId);
        return;
    }
	
    if (c->enrolledCount >= 50) 
    {
    	if (enqueueWaitlist(c, studentId)) 
        {
    	    printf("Course %d is full. Student %d added to waitlist.\n", courseId, studentId);
   	}
   	return;
    }

    s->enrolledRoot = insertNode(s->enrolledRoot, courseId);
    c->enrolledRoot = insertNode(c->enrolledRoot, studentId);
    c->enrolledCount++;
    printf("Student %d enrolled in course %d.\n", studentId, courseId);
}


void getWaitlist(int courseId) 
{
    Course* c = findCourseById(courseId);
    if (!c || c->waitlistCount == 0) 
    {
        if (!c)
            printf("No such course\n");
        else
            printf("No waitlist for course %d.\n", courseId);
        return;
    }

    printf("Waitlist for course %d:\n", courseId);
    int in = c->waitlistFront;
    for (int i = 0; i < c->waitlistCount; i++)
    {
        int studentId = c->waitlist[in];
        Student* s = findStudentById(studentId);
        printf(" %d - %s\n", studentId, s->name);
        in = (in + 1) % MAX_WAITLIST;
    }
}

void completeCourse(int studentId, int courseId) 
{
    Student* s = findStudentById(studentId);
    if (!s) 
    {
        printf("Student %d not found.\n", studentId);
        return;
    }

    if (searchNode(s->completedRoot, courseId)) 
    {
        printf("Student %d already completed course %d.\n", studentId, courseId);
        return;
    }

    if (!searchNode(s->enrolledRoot, courseId)) 
    {
        printf("Student %d is not enrolled in course %d.\n", studentId, courseId);
        return;
    }

    s->enrolledRoot = deleteNode(s->enrolledRoot, courseId);
    s->completedRoot = insertNode(s->completedRoot, courseId);
    Course* c = findCourseById(courseId);
    c->enrolledCount--;

    printf("Student %d marked as completed course %d.\n", studentId, courseId);
}


void dropCourse(int studentId, int courseId) 
{
    Student* s = findStudentById(studentId);
    Course* c = findCourseById(courseId);
    if (!s || !c) 
    { 
	printf("Invalid IDs.\n"); 
	return; 
    }

    if (!searchNode(s->enrolledRoot, courseId)) 
    {
        printf("Student %d not enrolled in course %d.\n", studentId, courseId);
        return;
    }

    s->enrolledRoot = deleteNode(s->enrolledRoot, courseId);
    c->enrolledRoot = deleteNode(c->enrolledRoot, studentId);
    c->enrolledCount--;
    printf("Student %d dropped course %d.\n", studentId, courseId);
}


void viewEnrolledCourses(int studentId) 
{
    Student* s = findStudentById(studentId);
    if (!s) 
    { 
	printf("Invalid student ID.\n"); 
	return; 
    }

    if (!s->enrolledRoot) { printf("No courses enrolled.\n"); return; }
    printf("Student %d is enrolled in:\n", studentId);
    inorderPrint(s->enrolledRoot);
}
