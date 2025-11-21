#ifndef COURSE_REGISTRATION_H
#define COURSE_REGISTRATION_H

#define MAX_COURSES 20
#define MAX_PREREQS 5
#define MAX_STUDENTS 100
#define MAX_WAITLIST 10

typedef struct EnrolledNode 
{
    int id;
    struct EnrolledNode* left;
    struct EnrolledNode* right;
} EnrolledNode;

typedef struct 
{
    int id;
    char name[50];
    EnrolledNode* enrolledRoot;
    EnrolledNode* completedRoot;
} Student;

typedef struct 
{
    int id;
    char name[50];
    char prerequisites[MAX_PREREQS][10];
    EnrolledNode* enrolledRoot;
    int enrolledCount;
    int waitlist[MAX_WAITLIST];
    int waitlistFront;
    int waitlistRear;
    int waitlistCount;
    int startTime;
    int endTime;
} Course;

Course* findCourseById(int courseId);
Student* findStudentById(int studentId);
int hasPrerequisites(Student* s, Course* c);
int detectConflict(int studentId, int newCourseId);
int enqueueWaitlist(Course* c, int studentId);
void addCourse(int courseId, char* name, char* prerequisites[], int startTime, int endTime);
void registerStudent(int studentId, int courseId);
void getWaitlist(int courseId);
void completeCourse(int studentId, int courseId);
void dropCourse(int studentId, int courseId);
void viewEnrolledCourses(int studentId);
EnrolledNode* insertNode(EnrolledNode* root, int id);
EnrolledNode* deleteNode(EnrolledNode* root, int id);
int searchNode(EnrolledNode* root, int id);
void inorderPrint(EnrolledNode* root);

#endif
