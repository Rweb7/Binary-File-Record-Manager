// Programming Assignment 2 - Binary File Record Manager
// Author: Ryan Webster
// A menu-driven program where a student can access their information,
// and make changes, if desired.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StudentRecord // Structure to store student records.

{
    char studentID[10];
    char studentName[20];
    char email[20];
    char courseID[10];
    char grade[2];
};

// --------------------------ADD STUDENT INFORMATION----------------------------------//

void createBinaryFile() // Main menu option #1

{
    struct StudentRecord student; // Create an instance of StudentRecord structure.

    FILE *file; // Declare the file pointer.

    file = fopen("students.dat", "ab"); // Open the binary file for appending.

    if (file == NULL) // Check if file opened successfully.

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

    fwrite(&student, sizeof(struct StudentRecord), 1, file); // Write the structure to the file.

    fclose(file); // Close the file.

    printf("Record added successfully.\n"); // Notify user of success.
}

// --------------------------DISPLAY STUDENT INFORMATION----------------------------------//

void displayBinaryFile() // Main menu option #2

{
    struct StudentRecord student;

    FILE *file;

    file = fopen("students.dat", "rb"); // Open the binary file for reading

    if (file == NULL) // Check if file opened successfully.

    {
        printf("Error opening file.\n");

        return;
    }


    printf("\n------------------STUDENT RECORDS------------------\n");

    while (fread(&student, sizeof(struct StudentRecord), 1, file))

    {
        printf("Student ID: %s\n", student.studentID);
        printf("Student Name: %s\n", student.studentName);
        printf("Email ID: %s\n", student.email);
        printf("Course ID: %s\n", student.courseID);
        printf("Grade: %s\n\n", student.grade);
    }

    fclose(file);
}

// --------------------------FIND STUDENT INFORMATION----------------------------------//

void seekRecord() // Main menu option #3

{
    struct StudentRecord student;

    char studentID[10];

    FILE *file;

    file = fopen("students.dat", "rb"); // Open the binary file for reading.

    if (file == NULL) // Check if file opened successfully.

    {
        printf("Error opening file.\n");

        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%s", studentID);


    while (fread(&student, sizeof(struct StudentRecord), 1, file)) // Read the file and compare each record's student ID.

    {
        if (strcmp(student.studentID, studentID) == 0) // If record found...

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


    printf("Record not found.\n"); // If record not found...

    fclose(file);
}

// --------------------------UPDATE STUDENT INFORMATION----------------------------------//

void updateBinaryFile() // Main menu option #4

{
    struct StudentRecord student; // Create an instance of "StudentRecord"" structure.

    char studentID[10];

    FILE *file;

    file = fopen("students.dat", "rb+"); // Open the binary file for reading and writing.

    if (file == NULL) // Check if file opened successfully.

    {
        printf("Error opening file.\n");

        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%s", studentID);


    while (fread(&student, sizeof(struct StudentRecord), 1, file)) // Read the file and compare each record's student ID.

    {
        if (strcmp(student.studentID, studentID) == 0) // If found...

        {

            printf("Enter new student name: "); // Prompt the user to enter new details.
            scanf("%s", student.studentName);
            printf("Enter new email: ");
            scanf("%s", student.email);
            printf("Enter new course ID: ");
            scanf("%s", student.courseID);
            printf("Enter new grade: ");
            scanf("%s", student.grade);

            fseek(file, -sizeof(struct StudentRecord), SEEK_CUR); // Move back one record.

            fwrite(&student, sizeof(struct StudentRecord), 1, file); // Update record.

            printf("Record updated successfully.\n");

            fclose(file);

            return;
        }
    }


    printf("Record not found.\n"); // If record not found.

    fclose(file);
}

// --------------------------DELETE STUDENT INFORMATION----------------------------------//

void deleteBinaryFile() // Main menu option #5

{
    struct StudentRecord student;

    char studentID[10];

    FILE *file;

    file = fopen("students.dat", "rb"); // Open the binary file for reading.

    FILE *tempFile = fopen("temp.dat", "wb"); // Open a temporary file for writing.

    if (file == NULL || tempFile == NULL) // Check if files opened successfully.

    {
        printf("Error opening file.\n");

        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%s", studentID);


    while (fread(&student, sizeof(struct StudentRecord), 1, file)) // Read the file and copy records except the one to be deleted.

    {
        if (strcmp(student.studentID, studentID) != 0) // If not the record to delete.

        {
            fwrite(&student, sizeof(struct StudentRecord), 1, tempFile); // Copy record.
        }
    }


    fclose(file); // Close both files
    fclose(tempFile); //  "      "


    remove("students.dat"); // Delete the original file and rename the temporary file.
    rename("temp.dat", "students.dat"); //    "                "

    printf("Record deleted successfully.\n");
}

// --------------------------MAIN MENU & CALL FUNCTIONS----------------------------------//

int main()

{
    int choice; // Variable to store user's choice.

    while (1) // Infinite loop to keep the menu active.

    {
        printf("\n------------------MAIN MENU------------------\n\n");
        printf("1. Create the Binary File\n");
        printf("2. Display the contents of the file\n");
        printf("3. Seek a specific record\n");
        printf("4. Update the contents of a record\n");
        printf("5. Delete a record for the specific name\n");
        printf("6. Exit\n\n");
        printf("Please enter your choice .... \n");
        scanf("%d", &choice);


        switch (choice) // Switch case to call appropriate function based on user's choice.

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
                exit(0); // Exit the program

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
