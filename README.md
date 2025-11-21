# 📚 Course Registration System (C — DSA Project)

A modular **Course Registration System** implemented in **C**, showcasing key Data Structures & Algorithms such as:

- **Binary Search Trees (BSTs)**
- **Circular Queues**
- **Dynamic Memory Allocation**
- **String Handling**
- **Modular Architecture**

This project simulates a university-style course enrollment portal, supporting prerequisites, waitlists, conflict detection, course dropping, and completion tracking.

---

## 🚀 Features

### 🔹 Add Course
- Assign ID, name, start & end time  
- Enter up to 5 prerequisites  
- Initializes BST + waitlist structure  

### 🔹 Register Student
Performs:
- Prerequisite check  
- Time-conflict detection  
- Adds to **Enrolled BST** or **Circular Queue waitlist**  

### 🔹 View Course Waitlist
- Prints queue contents in order  

### 🔹 Complete Course
- Moves course from student's **enrolled BST → completed BST**

### 🔹 Drop Course
- Removes student from BST  
- Automatically promotes next waitlisted student  

### 🔹 View Student’s Enrolled Courses
- Inorder traversal of enrollment BST  

---

## 🧱 Data Structures Used

| Component | Data Structure |
|----------|----------------|
| Enrolled Students | Binary Search Tree |
| Completed Courses | Binary Search Tree |
| Waitlist | Circular Queue |
| Student Directory | Array |
| Course Directory | Array |

---

## 📂 Project Structure

