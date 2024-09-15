#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollno;
    string name;
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;
};

fstream fp;

void calculate(Student& st) {
    st.per = (st.p_marks + st.c_marks + st.m_marks + st.e_marks + st.cs_marks) / 5.0;
    if (st.per >= 60)
        st.grade = 'A';
    else if (st.per >= 50 && st.per < 60)
        st.grade = 'B';
    else if (st.per >= 33 && st.per < 50)
        st.grade = 'C';
    else
        st.grade = 'F';
}

void getStudentData(Student& st) {
    cout << "\nEnter The roll number of student: ";
    cin >> st.rollno;
    cin.ignore(); // Ignore the newline character in the input buffer
    cout << "\nEnter The Name of student: ";
    getline(cin, st.name);
    cout << "\nEnter The marks in physics out of 100: ";
    cin >> st.p_marks;
    cout << "\nEnter The marks in chemistry out of 100: ";
    cin >> st.c_marks;
    cout << "\nEnter The marks in maths out of 100: ";
    cin >> st.m_marks;
    cout << "\nEnter The marks in english out of 100: ";
    cin >> st.e_marks;
    cout << "\nEnter The marks in computer science out of 100: ";
    cin >> st.cs_marks;
    calculate(st);
}

void showStudentData(const Student& st) {
    cout << "\nRoll number of student: " << st.rollno;
    cout << "\nName of student: " << st.name;
    cout << "\nMarks in Physics: " << st.p_marks;
    cout << "\nMarks in Chemistry: " << st.c_marks;
    cout << "\nMarks in Maths: " << st.m_marks;
    cout << "\nMarks in English: " << st.e_marks;
    cout << "\nMarks in Computer Science: " << st.cs_marks;
    cout << "\nPercentage of student is: " << fixed << setprecision(2) << st.per;
    cout << "\nGrade of student is: " << st.grade << endl;
}

void showStudentTabular(const Student& st) {
    cout << st.rollno << setw(12) << st.name << setw(10) << st.p_marks << setw(3) << st.c_marks << setw(3) << st.m_marks
        << setw(3) << st.e_marks << setw(3) << st.cs_marks << setw(6) << setprecision(3) << st.per << "   " << st.grade << endl;
}

void writeStudentRecord() {
    fp.open("student.dat", ios::out | ios::app);
    Student st;
    getStudentData(st);
    fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
    fp.close();
    cout << "\n\nstudent record has been created ";
    cin.ignore();
    cin.get();
}

void displayAllRecords() {
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat", ios::in);
    Student st;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        showStudentData(st);
        cout << "\n\n====================================\n";
        cin.get();
    }
    fp.close();
    cin.get();
}

void displaySpecificRecord(int n) {
    int flag = 0;
    fp.open("student.dat", ios::in);
    Student st;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.rollno == n) {
            showStudentData(st);
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nrecord not exist";
    cin.get();
}

void modifyStudentRecord() {
    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The roll number of student: ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    Student st;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && found == 0) {
        if (st.rollno == no) {
            showStudentData(st);
            cout << "\nPlease Enter The New Details of student" << endl;
            getStudentData(st);
            int pos = -1 * static_cast<int>(sizeof(Student));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
            cout << "\n\n\tRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\nRecord Not Found ";
    cin.ignore();
    cin.get();
}

void deleteStudentRecord() {
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The roll number of student You Want To Delete: ";
    cin >> no;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    Student st;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.rollno != no) {
            fp2.write(reinterpret_cast<char*>(&st), sizeof(Student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}

void classResult() {
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout << "\n\n\n Program is closing ....";
        cin.ignore();
        cin.get();
        exit(0);
    }

    cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    cout << "====================================================\n";
    cout << "Roll No. Name          P  C  M  E  CS  %age Grade\n";
    cout << "====================================================\n";

    Student st;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        showStudentTabular(st);
    }
    fp.close();
    cin.ignore();
    cin.get();
}

void resultMenu() {
    int ans, rno;
    char ch;
    cout << "\n\n\nRESULT MENU";
    cout << "\n\n\n1. Class Result";
    cout << "\n\n2. Student Report Card";
    cout << "\n\n3. Back to Main Menu";
    cout << "\n\n\nEnter Choice (1/2)? ";
    cin >> ans;
    switch (ans) {
    case 1:
        classResult();
        break;
    case 2:
        do {
            cout << "\n\nEnter Roll Number Of Student: ";
            cin >> rno;
            displaySpecificRecord(rno);
            cout << "\n\nDo you want to See More Result (y/n)? ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
        break;
    case 3:
        break;
    default:
        cout << "\a";
    }
}

void intro() {
    cout << "STUDENT\n";
    cout << "REPORT CARD\n";
    cout << "PROJECT\n";
    cout << "\n\nMADE BY : Code With C";
    cout << "\n\nCONTACT : codewithc.com";
    cin.ignore();
    cin.get();
}

void entryMenu() {
    char ch2;
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout << "\n\n\t3.SEARCH STUDENT RECORD";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6): ";
    ch2 = getche();
    switch (ch2) {
    case '1':
        writeStudentRecord();
        break;
    case '2':
        displayAllRecords();
        break;
    case '3':
        int num;
        cout << "\n\n\tPlease Enter The roll number: ";
        cin >> num;
        displaySpecificRecord(num);
        break;
    case '4':
        modifyStudentRecord();
        break;
    case '5':
        deleteStudentRecord();
        break;
    case '6':
        break;
    default:
        cout << "\a";
        entryMenu();
    }
}

int main() {
    char ch;
    intro();
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. RESULT MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3): ";
        ch = getche();
        switch (ch) {
        case '1':
            resultMenu();
            break;
        case '2':
            entryMenu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
    return 0;
}
