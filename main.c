// Programming Assignment 2 - Binary File Record Manager
// Author: Ryan Webster
// A menu-driven program where a student can access their information,
// and make changes, if desired.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct StudentRecord  // Student record structure.

{
     char studentID[10];
     char studentName[20];
     char email[20];
     char courseID[10];
     char grade[2];
};
// --------------------------ADD STUDENT INFORMATION----------------------------------

void createBinaryFile() // Main menu option #1

{
     struct StudentRecord student;

     FILE *file; // Declare the file pointer.

     file = fopen("student.dat", "ab"); // Append binary mode.

     if (file == NULL)

     {
          printf("Error creating file.\n");
          return;
     }

     printf("Enter Student ID: ");
     scanf("%s", student.studentID);
     printf("Enter Student Name: ");
     scanf("%s", student.studentName);
     printf("Enter Email ID: ");
     scanf("%s", student.email);
     printf("Enter Course ID: ");
     scanf("%s", student.courseID);
     printf("Enter Grade: ");
     scanf("%s", student.grade);

     fwrite(&student, sizeof(struct StudentRecord), 1, file);

     fclose(file);

     printf("Record added successfully.\n");
}
// --------------------------DISPLAY STUDENT INFORMATION----------------------------------

void displayBinaryFile() // Main menu option #2

{
     struct StudentRecord student;

     FILE *file = fopen("students.dat", "rb");

     if (file == NULL)

     {
          printf("Error opening file.\n");

          return;
     }

     printf("\n------------------STUDENT RECORDS------------------\n");
     while (fread(&student, sizeof(struct StudentRecord), 1, file)) {
          printf("Student ID: %s\n", student.studentID);
          printf("Student Name: %s\n", student.studentName);
          printf("Email ID: %s\n", student.email);
          printf("Course ID: %s\n", student.courseID);
          printf("Grade: %s\n\n", student.grade);
     }

     fclose(file);
}
// --------------------------FIND STUDENT INFORMATION----------------------------------

void seekRecord() // Main menu option #3

{
     struct StudentRecord student;

     char studentID[10];

     FILE *file = fopen("students.dat", "rb");

     if (file == NULL)

     {
          printf("Error opening file.\n");
          return;
     }

     printf("Enter Student ID to search: ");
     scanf("%s", studentID);

     while (fread(&student, sizeof(struct StudentRecord), 1, file))

     {

          if (strcmp(student.studentID, studentID) == 0)

          {
               printf("Record found:\n");
               printf("Student ID: %s\n", student.studentID);
               printf("Student Name: %s\n", student.studentName);
               printf("Email ID: %s\n", student.email);
               printf("Course ID: %s\n", student.courseID);
               printf("Grade: %s\n", student.grade);

               fclose(file);

               return;
          }
     }
}
// --------------------------DISPLAY STUDENT INFORMATION----------------------------------

void updateBinaryFile() // Main menu option #4

{
     struct StudentRecord student;
     char studentID[10];
     FILE *file = fopen("students.dat", "rb+"); // Read/write binary mode

     if (file == NULL)

     {
          printf("Error opening file.\n");

          return;
     }

     printf("Enter Student ID to update: ");
     scanf("%s", studentID);

     while (fread(&student, sizeof(struct StudentRecord), 1, file))

     {
          if (strcmp(student.studentID, studentID) == 0)

          {
               printf("Enter new student name: ");
               scanf("%s", student.studentName);
               printf("Enter new email: ");
               scanf("%s", student.email);
               printf("Enter new course ID: ");
               scanf("%s", student.courseID);
               printf("Enter new grade: ");
               scanf("%s", student.grade);

               fseek(file, -sizeof(struct StudentRecord), SEEK_CUR); // Move back one record
               fwrite(&student, sizeof(struct StudentRecord), 1, file);
               printf("Record updated successfully.\n");

               fclose(file);

               return;
          }
     }

     printf("Record not found.\n");

     fclose(file);
}

void deleteBinaryFile() // Main menu option #5

{
     struct StudentRecord student;

     char studentID[10];

     FILE *file = fopen("students.dat", "rb");
     FILE *tempFile = fopen("temp.dat", "wb");

     if (file == NULL || tempFile == NULL)

     {
          printf("Error opening file.\n");

          return;
     }

     printf("Enter Student ID to delete: ");
     scanf("%s", studentID);

     while (fread(&student, sizeof(struct StudentRecord), 1, file))

     {
          if (strcmp(student.studentID, studentID) != 0)

          {
               fwrite(&student, sizeof(struct StudentRecord), 1, tempFile);
          }
     }

     fclose(file);

     fclose(tempFile);

     remove("students.dat");
     rename("temp.dat", "students.dat");

     printf("Record deleted successfully.\n");
}

int main() // Functionality of Binary File Record Manager.

{
     int choice;

     while (1)

     {
          printf("\n------------------MAIN MENU------------------\n\n");
          printf("1. Create the Binary File\n2. Display the contents of the file\n3. Seek a specific record\n");
          printf("4. Update the contents of a record\n5. Delete a record for the specific name\n6. Exit\n\n");
          printf("Enter your choice: \n");
          scanf("%d", &choice);

          switch (choice)

          {
               case 1:
                    createBinaryFile();
               break;

               case 2:
                    displayBinaryFile();
               break;

               case 3:
                    seekRecord();
               break;

               case 4:
                    updateBinaryFile();
               break;

               case 5:
                    deleteBinaryFile();
               break;

               case 6:
                    exit(0);

               default:
                    printf("Invalid choice. Please try again.\n");
          }
     }

     return 0;
}