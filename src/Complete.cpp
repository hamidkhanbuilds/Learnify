#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Constants
const int MaxOptions = 5;
const int MaxQuestions = 10;
const int MaxQuizzes = 20;
const int MaxCourses = 50;
const int MaxUsers = 100;

// Forward declarations
class User;
class Admin;
class Instructor;
class Student;
class Question;
class Quiz;
class Course;


// Question class
class Question {
    private:
        string Text;
        string Options[MaxOptions];
        int OptionCount;
        int CorrectOption;
    
    public:
        Question(const string& text, const string options[], int optionCount, int correctOption);
        void Display() const;
        bool CheckAnswer(int answer) const;
        int GetOptionCount() const;
        int GetCorrectOption() const;
        const string& GetText() const { return Text; }
    };
    
    Question::Question(const string& text, const string options[], int optionCount, int correctOption)
        : Text(text), OptionCount(optionCount), CorrectOption(correctOption) {
        for (int i = 0; i < optionCount; i++) {
            Options[i] = options[i];
        }
    }
    
    void Question::Display() const {
        cout << "\n" << Text << endl;
        for (int i = 0; i < OptionCount; i++) {
            cout << i + 1 << ". " << Options[i] << endl;
        }
    }
    
    bool Question::CheckAnswer(int answer) const {
        return (answer - 1) == CorrectOption;
    }
    
    int Question::GetOptionCount() const {
        return OptionCount;
    }
    
    int Question::GetCorrectOption() const {
        return CorrectOption;
    }
    
    // ---------------- QUIZ CLASS ----------------
    class Quiz {
    private:
        string Title;
        Question* Questions[MaxQuestions];
        int QuestionCount;
    
    public:
        Quiz(const string& title);
        ~Quiz();
        string GetTitle() const;
        void AddQuestion(Question* question);
        int TakeQuiz() const;
    };
    
    Quiz::Quiz(const string& title) : Title(title), QuestionCount(0) {
        for (int i = 0; i < MaxQuestions; i++) {
            Questions[i] = nullptr;
        }
    }
    
    Quiz::~Quiz() {
        for (int i = 0; i < QuestionCount; i++) {
            delete Questions[i];
        }
    }
    
    string Quiz::GetTitle() const {
        return Title;
    }
    
    void Quiz::AddQuestion(Question* question) {
        if (QuestionCount < MaxQuestions) {
            Questions[QuestionCount++] = question;
        }
    }
    
    int Quiz::TakeQuiz() const {
        int score = 0;
        cout << "\n=== Quiz: " << Title << " ===\n";
        for (int i = 0; i < QuestionCount; i++) {
            Questions[i]->Display();
            int answer;
            cout << "Your answer (1-" << Questions[i]->GetOptionCount() << "): ";
            cin >> answer;
            cin.ignore();
    
            if (Questions[i]->CheckAnswer(answer)) {
                cout << " Correct!\n";
                score++;
            } else {
                cout << " Wrong! The correct answer was option " << Questions[i]->GetCorrectOption() + 1 << ".\n";
            }
        }
        int percentage = QuestionCount > 0 ? (score * 100) / QuestionCount : 0;
        cout << "\nYour score: " << percentage << "% (" << score << "/" << QuestionCount << " correct)" << endl;
        return percentage;
    }


// Course class
class Course {
private:
    string Title;
    string Description;
    string InstructorId;
    Quiz* Quizzes[MaxQuizzes];
    int QuizCount;

public:
    Course(const string& title, const string& desc, const string& instructorId);
    ~Course();
    string GetTitle() const;
    string GetDescription() const;
    string GetInstructorId() const;
    int GetQuizCount() const;
    void AddQuiz(Quiz* quiz);
    void DisplayInfo() const;
    void DisplayQuizzes() const;
    Quiz* GetQuiz(int index) const;
};

Course::Course(const string& title, const string& desc, const string& instructorId)
    : Title(title), Description(desc), InstructorId(instructorId), QuizCount(0) {
    for (int i = 0; i < MaxQuizzes; i++) {
        Quizzes[i] = nullptr;
    }
}

Course::~Course() {
    for (int i = 0; i < QuizCount; i++) {
        delete Quizzes[i];
    }
}

string Course::GetTitle() const { return Title; }
string Course::GetDescription() const { return Description; }
string Course::GetInstructorId() const { return InstructorId; }
int Course::GetQuizCount() const { return QuizCount; }

void Course::AddQuiz(Quiz* quiz) {
    if (QuizCount < MaxQuizzes) {
        Quizzes[QuizCount++] = quiz;
    }
}

void Course::DisplayInfo() const {
    cout << "\nCourse: " << Title << "\nDescription: " << Description 
         << "\nInstructor: " << InstructorId << endl;
}

void Course::DisplayQuizzes() const {
    cout << "\nQuizzes in this course:\n";
    for (int i = 0; i < QuizCount; i++) {
        cout << i+1 << ". " << Quizzes[i]->GetTitle() << endl;
    }
}

Quiz* Course::GetQuiz(int index) const {
    if (index < 0 || index >= QuizCount) {
        return nullptr;
    }  
    return Quizzes[index];
}

// User class
class User {
protected:
    string Username;
    string Name;
    string Email;
    string Password;
    string Address;
    string ContactNo;
    static int Totalusers;

    virtual void DisplayDashboard() const = 0;

public:
    User(const string &username, const string &name, const string &email,
         const string &password, const string &address, const string &contactNo);
    virtual ~User() =default;

    void ShowDashboard() const;
    string GetUname() const;
    string GetName() const;
    string GetEmail() const;
    string GetPass() const;
    string GetAddress() const;
    string GetContact() const;
    static int GetTotalusers();
    bool CheckPass(const string &identifier, const string &password) const;
    virtual void Role() const = 0;
    virtual string GetRole() const = 0;
    bool operator==(const User &other) const;
    virtual void SaveData(ofstream &file) const;
    virtual void ViewProfile() const;

    friend ostream &operator<<(ostream &os, const User &user);
};

int User::Totalusers = 0;

User::User(const string &username, const string &name, const string &email,
     const string &password, const string &address, const string &contactNo)
    : Username(username), Name(name), Email(email), Password(password),
      Address(address), ContactNo(contactNo) {
    Totalusers++;
}

// User::~User() {
//     Totalusers--;
// }

void User::ShowDashboard() const {
    DisplayDashboard();
}

string User::GetUname() const { return Username; }
string User::GetName() const { return Name; }
string User::GetEmail() const { return Email; }
string User::GetPass() const { return Password; }
string User::GetAddress() const { return Address; }
string User::GetContact() const { return ContactNo; }

int User::GetTotalusers() { return Totalusers; }

bool User::CheckPass(const string &identifier, const string &password) const {
    return Password == password && (Username == identifier || Email == identifier);
}

bool User::operator==(const User &other) const {
    return Username == other.Username && Email == other.Email;
}

void User::SaveData(ofstream &file) const {
    file << GetRole() << endl
         << Username << endl
         << Name << endl
         << Email << endl
         << Password << endl
         << Address << endl
         << ContactNo << endl;
}

void User::ViewProfile() const {
    cout << *this;
}

ostream &operator<<(ostream &os, const User &user) {
    os << "Username: " << user.Username << endl
       << "Name: " << user.Name << endl
       << "Email: " << user.Email << endl
       << "Address: " << user.Address << endl
       << "Contact: " << user.ContactNo << endl;
    return os;
}

// Admin class
class Admin : public User {
protected:
    void DisplayDashboard() const override;
public:
    Admin(const string &username, const string &name, const string &email,
          const string &password, const string &address, const string &contactNo);
    
    void Role() const override;
    string GetRole() const override;
};

Admin::Admin(const string &username, const string &name, const string &email,
      const string &password, const string &address, const string &contactNo)
    : User(username, name, email, password, address, contactNo) {}

void Admin::Role() const {
    cout << "Administrator" << endl;
}

string Admin::GetRole() const {
    return "Admin";
}

void Admin::DisplayDashboard() const {
    cout << "\n=== ADMIN DASHBOARD ===" << endl;
    cout << "1. Create Course" << endl;
    cout << "2. View All Courses" << endl;
    cout << "3. Manage Users" << endl;
    cout << "4. View Profile" << endl;
    cout << "5. Logout" << endl;
}

// Instructor class
class Instructor : public User {
    Course* TeachingCourses[MaxCourses];
    int TeachingCount;

public:
    Instructor(const string &username, const string &name, const string &email,
               const string &password, const string &address, const string &contactNo);
    ~Instructor();
    
    void Role() const override;
    string GetRole() const override;
    
    void AddTeachingCourse(Course* course);
    int GetCourseCount() const;
    Course* GetCourse(int index) const;
    void ViewTeachingCourses() const;
    void CreateQuiz(Course* course);

protected:
    void DisplayDashboard() const override;
};

Instructor::Instructor(const string &username, const string &name, const string &email,
           const string &password, const string &address, const string &contactNo)
    : User(username, name, email, password, address, contactNo), TeachingCount(0) {
    for (int i = 0; i < MaxCourses; i++) {
        TeachingCourses[i] = nullptr;
    }
}

Instructor::~Instructor() {
    // managed by UserManagement
}

void Instructor::Role() const {
    cout << "Instructor" << endl;
}

string Instructor::GetRole() const {
    return "Instructor";
}

void Instructor::AddTeachingCourse(Course* course) {
    if (TeachingCount < MaxCourses) {
        TeachingCourses[TeachingCount++] = course;
    }
}

int Instructor::GetCourseCount() const { 
    return TeachingCount; 
}

Course* Instructor::GetCourse(int index) const {
    if (index >= 0 && index < TeachingCount) {
        return TeachingCourses[index];
    }
    return nullptr;
}

void Instructor::ViewTeachingCourses() const {
    cout << "\n=== TEACHING COURSES ===\n";
    if (TeachingCount == 0) {
        cout << "No courses assigned to you.\n";
        return;
    }
    for (int i = 0; i < TeachingCount; i++) {
        cout << i+1 << ". ";
        TeachingCourses[i]->DisplayInfo();
    }
}

void Instructor::CreateQuiz(Course* course) {
    string title;
    cout << "Enter quiz title: ";
    getline(cin, title);
    
    Quiz* quiz = new Quiz(title);
    
    int questionCount;
    cout << "How many questions? (max " << MaxQuestions << "): ";
    cin >> questionCount;
    cin.ignore();
    
    for (int i = 0; i < questionCount && i < MaxQuestions; i++) {
        string text;
        cout << "Enter question " << i+1 << ": ";
        getline(cin, text);
        
        string options[MaxOptions];
        int optionCount;
        cout << "How many options? (max " << MaxOptions << "): ";
        cin >> optionCount;
        cin.ignore();
        
        for (int j = 0; j < optionCount && j < MaxOptions; j++) {
            cout << "Option " << j+1 << ": ";
            getline(cin, options[j]);
        }
        
        int correct;
        cout << "Correct option (1-" << optionCount << "): ";
        cin >> correct;
        cin.ignore();
        
        quiz->AddQuestion(new Question(text, options, optionCount, correct-1));
    }
    
    course->AddQuiz(quiz);
    cout << "Quiz created successfully!\n";
}

void Instructor::DisplayDashboard() const {
    cout << "\n=== INSTRUCTOR DASHBOARD ===" << endl;
    cout << "1. View Teaching Courses" << endl;
    cout << "2. Create Quiz" << endl;
    cout << "3. View Profile" << endl;
    cout << "4. Logout" << endl;
    cout << "5. Remove Student" << endl;
}

// Student class
class Student : public User {
    Course* EnrolledCourses[MaxCourses];
    int EnrolledCount;
    int QuizScores[MaxCourses][MaxQuizzes];
    bool QuizCompleted[MaxCourses][MaxQuizzes];

public:
    Student(const string &username, const string &name, const string &email,
            const string &password, const string &address, const string &contactNo);
    
    void Role() const override;
    string GetRole() const override;
    
    void EnrollCourse(Course* course);
    int GetEnrolledCount() const;
    Course* GetEnrolledCourse(int index) const;
    void ViewEnrolledCourses() const;
    void TakeQuiz(Course* course, int quizIndex);
    void ViewProgress() const;

protected:
    void DisplayDashboard() const override;
};

Student::Student(const string &username, const string &name, const string &email,
        const string &password, const string &address, const string &contactNo)
    : User(username, name, email, password, address, contactNo), EnrolledCount(0) {
    for (int i = 0; i < MaxCourses; i++) {
        EnrolledCourses[i] = nullptr;
        for (int j = 0; j < MaxQuizzes; j++) {
            QuizScores[i][j] = 0;
            QuizCompleted[i][j] = false;
        }
    }
}

void Student::Role() const {
    cout << "Student" << endl;
}

string Student::GetRole() const {
    return "Student";
}

void Student::EnrollCourse(Course* course) {
    if (EnrolledCount < MaxCourses) {
        EnrolledCourses[EnrolledCount++] = course;
        cout << "Enrolled in course: " << course->GetTitle() << endl;
    } else {
        cout << "Maximum enrollment limit reached!\n";
    }
}

int Student::GetEnrolledCount() const { 
    return EnrolledCount; 
}

Course* Student::GetEnrolledCourse(int index) const {
    if (index >= 0 && index < EnrolledCount) {
        return EnrolledCourses[index];
    }
    return nullptr;
}

void Student::ViewEnrolledCourses() const {
    cout << "\n=== ENROLLED COURSES ===\n";
    if (EnrolledCount == 0) {
        cout << "You are not enrolled in any courses.\n";
        return;
    }
    for (int i = 0; i < EnrolledCount; i++) {
        cout << i+1 << ". ";
        EnrolledCourses[i]->DisplayInfo();
    }
}

void Student::TakeQuiz(Course* course, int quizIndex) {
    Quiz* quiz = course->GetQuiz(quizIndex);
    if (quiz) {
        int score = quiz->TakeQuiz();
        
        int courseIndex = -1;
        for (int i = 0; i < EnrolledCount; i++) {
            if (EnrolledCourses[i] == course) {
                courseIndex = i;
                break;
            }
            
        }
        
        if (courseIndex != -1) {
            QuizCompleted[courseIndex][quizIndex] = true;
            if (score > QuizScores[courseIndex][quizIndex]) {
                QuizScores[courseIndex][quizIndex] = score;
                cout << "New high score saved!\n";
            } else {
                cout << "Your previous score was higher. High score remains.\n";
            }
        }
        else {
        cout << "Invalid quiz selection!\n";
    }
}}

void Student::ViewProgress() const {
    cout << "\n=== YOUR PROGRESS ===\n";
    if (EnrolledCount == 0) {
        cout << "You are not enrolled in any courses.\n";
        return;
    }
    
    for (int i = 0; i < EnrolledCount; i++) {
        cout << "\nCourse: " << EnrolledCourses[i]->GetTitle() << endl;
        int quizCount = EnrolledCourses[i]->GetQuizCount();
        int completed = 0;
        
        for (int j = 0; j < quizCount; j++) {
            if (QuizCompleted[i][j]) {
                completed++;
                cout << "  Quiz " << j+1 << ": " << QuizScores[i][j] << "%" << endl;
            }
        }
        
        if (quizCount > 0) {
            int progress = (completed * 100) / quizCount;
            cout << "Overall progress: " << progress << "% (" << completed 
                 << "/" << quizCount << " quizzes completed)" << endl;
        } else {
            cout << "No quizzes available in this course." << endl;
        }
    }
}

void Student::DisplayDashboard() const {
    cout << "\n=== STUDENT DASHBOARD ===" << endl;
    cout << "1. View All Courses" << endl;
    cout << "2. Enroll in Course" << endl;
    cout << "3. View Enrolled Courses" << endl;
    cout << "4. Take Quiz" << endl;
    cout << "5. View Progress" << endl;
    cout << "6. View Profile" << endl;
    cout << "7. Logout" << endl;
}

// UserManagement class
class UserManagement {
private:
    User* Users[MaxUsers];
    int UsersCount;
    Course* Courses[MaxCourses];
    int CoursesCount;

    bool isValidName(const string &name);
    bool isValidUsername(const string &uname);
    bool isValidPassword(const string &pass);
    bool isValidEmail(const string &email);
    bool isValidContact(const string &contact);
    bool isUsernameTaken(const string& uname);
    bool isEmailTaken(const string &email);
    
    
    Instructor* FindInstructor(const string& username);
   
public:
    UserManagement();
    ~UserManagement();

    User* CreateUser(const string &role, const string &username, const string &name,
                     const string &email, const string &password, const string &address,
                     const string &contactNo);
    void Register();
    User* Login();
    void CreateCourse(User* user);
    void ViewAllCourses(User* user);
    void EnrollCourse(User* user);
    void ViewTeachingCourses(User* user);
    void CreateQuiz(User* user);
    void TakeQuiz(User* user);
    void ViewProgress(User* user);
    void SaveUsers();
    void LoadUsers();
    void SaveCourses();
    void LoadCourses();
    void RemoveStudent(User* requester);

};

UserManagement::UserManagement() : UsersCount(0), CoursesCount(0) {
    for (int i = 0; i < MaxUsers; i++) {
        Users[i] = nullptr;
    }
    for (int i = 0; i < MaxCourses; i++) {
        Courses[i] = nullptr;
    }
    LoadUsers();
    LoadCourses();
}

UserManagement::~UserManagement() {
    SaveUsers();
    SaveCourses();
    for (int i = 0; i < UsersCount; i++) {
        delete Users[i];
    }
    for (int i = 0; i < CoursesCount; i++) {
        delete Courses[i];
    }
}

bool UserManagement::isValidName(const string &name) {
    if (name.length() == 0) return false;
    for (char c : name) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ' || c == '.' || c == '\'')) {
            return false;
        }
    }
    return true;
}

bool UserManagement::isValidUsername(const string &uname) {
    if (uname.length() == 0) return false;
    for (char c : uname) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
             (c >= '0' && c <= '9') || c == '_' || c == '-')) {
            return false;
        }
    }
    return true;
}

bool UserManagement::isValidPassword(const string &pass) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    if (pass.length() < 8) return false;
    
    for (char c : pass) {
        if (c >= 'A' && c <= 'Z') hasUpper = true;
        else if (c >= 'a' && c <= 'z') hasLower = true;
        else if (c >= '0' && c <= '9') hasDigit = true;
        else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || 
                 c == '^' || c == '&' || c == '*' || c == '(' || c == ')' || 
                 c == '-' || c == '_') {
            hasSpecial = true;
        }
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool UserManagement::isValidEmail(const string &email) {
    bool hasAt = false, hasDotAfterAt = false;
    for (char c : email) {
        if (c == '@') hasAt = true;
        else if (hasAt && c == '.') hasDotAfterAt = true;
    }
    return hasAt && hasDotAfterAt;
}

bool UserManagement::isValidContact(const string &contact) {
    if (contact.length() == 0) return false;
    for (char c : contact) {
        if (!(c >= '0' && c <= '9') && c != '+' && c != '-' && 
            c != ' ' && c != '(' && c != ')') {
            return false;
        }
    }
    return true;
}

void UserManagement::RemoveStudent(User* requester) {
    if (requester->GetRole() != "Admin" && requester->GetRole() != "Instructor") {
        cout << "Only Admin or Instructor can remove a student.\n";
        return;
    }

    cout << "\nEnter username of the student to remove: ";
    string uname;
    getline(cin, uname);

    for (int i = 0; i < UsersCount; i++) {
        if (Users[i]->GetRole() == "Student" && Users[i]->GetUname() == uname) {
            delete Users[i];
            for (int j = i; j < UsersCount - 1; j++) {
                Users[j] = Users[j + 1];
            }
            Users[--UsersCount] = nullptr;
            cout << "Student removed successfully.\n";
            SaveUsers(); // Save updated list
            return;
        }
    }
    cout << "Student not found!\n";
}

Instructor* UserManagement::FindInstructor(const string& username) {
    for (int i = 0; i < UsersCount; i++) {
        if (Users[i]->GetRole() == "Instructor" && Users[i]->GetUname() == username) {
            return (Instructor*)Users[i];
        }
    }
    return nullptr;
}

User* UserManagement::CreateUser(const string &role, const string &username, const string &name,
                 const string &email, const string &password, const string &address,
                 const string &contactNo) {
    if (role == "Admin") {
        return new Admin(username, name, email, password, address, contactNo);
    } else if (role == "Instructor") {
        return new Instructor(username, name, email, password, address, contactNo);
    } else if (role == "Student") {
        return new Student(username, name, email, password, address, contactNo);
    }
    return nullptr;
}
bool UserManagement::isUsernameTaken(const string& username) {
    for (int i = 0; i < UsersCount; i++) {
        if (Users[i]->GetUname() == username) {
            return true;
        }
    }
    return false;
}

bool UserManagement::isEmailTaken(const string& email) {
    for (int i = 0; i < UsersCount; i++) {
        if (Users[i]->GetEmail() == email) {
            return true;
        }
    }
    return false;
}

void UserManagement::Register() {
    if (UsersCount >= MaxUsers) {
        cout << "System has reached maximum user capacity." << endl;
        return;
    }

    string role, name, username, password, email, address, contactNo;

    cout << "\n=== REGISTRATION ===" << endl;
    
    while (true) {
        cout << "Select role (Admin/Instructor/Student): ";
        getline(cin, role);
        if (role == "Admin" || role == "Instructor" || role == "Student") break;
        cout << "Invalid role! Please try again." << endl;
    }

    while (true) {
        cout << "Full Name: ";
        getline(cin, name);
        if (isValidName(name)) break;
        cout << "Invalid name! Use only letters and spaces." << endl;
    }

    while (true) {
        cout << "Username: ";
        getline(cin, username);
        if (!isValidUsername(username)) {
            cout << "Invalid username! Use only letters, numbers, underscores or hyphens." << endl;
            continue;
        }
        if (isUsernameTaken(username)) {
            cout << "Username already taken! Please choose another one." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Password (min 8 chars with upper, lower, number & special): ";
        getline(cin, password);
        if (isValidPassword(password)) break;
        cout << "Weak password! Must include:" << endl;
        cout << "- At least 8 characters" << endl;
        cout << "- At least one uppercase letter" << endl;
        cout << "- At least one lowercase letter" << endl;
        cout << "- At least one digit" << endl;
        cout << "- At least one special character (!@#$%^&*()_-)" << endl;
    }

    while (true) {
        cout << "Email: ";
        getline(cin, email);
        if (!isValidEmail(email)) {
            cout << "Invalid email format! Must contain @ and . after @" << endl;
            continue;
        }
        if (isEmailTaken(email)) {
            cout << "Email already registered! Please use another email." << endl;
            continue;
        }
        break;
    }

    cout << "Address: ";
    getline(cin, address);

    while (true) {
        cout << "Contact Number: ";
        getline(cin, contactNo);
        if (isValidContact(contactNo)) break;
        cout << "Invalid contact number! Only digits and +-() spaces allowed." << endl;
    }

    Users[UsersCount++] = CreateUser(role, username, name, email, password, address, contactNo);
    cout << "\nRegistration successful! Welcome " << name << "!" << endl;
}

User* UserManagement::Login() {
    string identifier, password;
    cout << "\nEnter username or email: ";
    getline(cin, identifier);
    cout << "Password: ";
    getline(cin, password);

    for (int i = 0; i < UsersCount; i++) {
        if (Users[i]->CheckPass(identifier, password)) {
            return Users[i];
        }
    }
    return nullptr;
}

void UserManagement::CreateCourse(User* user) {
    if (user->GetRole() != "Admin") {
        cout << "Only admins can create courses!\n";
        return;
    }

    string title, desc, instructorUsername;
    cout << "Enter course title: ";
    getline(cin, title);
    cout << "Enter course description: ";
    getline(cin, desc);
    
    cout << "Enter instructor username: ";
    getline(cin, instructorUsername);
    
    Instructor* instructor = FindInstructor(instructorUsername);
    if (!instructor) {
        cout << "Instructor not found!\n";
        return;
    }

    if (CoursesCount < MaxCourses) {
        Courses[CoursesCount] = new Course(title, desc, instructor->GetUname());
        instructor->AddTeachingCourse(Courses[CoursesCount]);
        CoursesCount++;
        cout << "Course created successfully with instructor " << instructor->GetName() << "!\n";
    } else {
        cout << "Maximum courses limit reached!\n";
    }
}

void UserManagement::ViewAllCourses(User* user) {
    if (CoursesCount == 0) {
        cout << "No courses available.\n";
        return;
    }

    cout << "\n=== ALL COURSES ===\n";
    for (int i = 0; i < CoursesCount; i++) {
        cout << i+1 << ". ";
        Courses[i]->DisplayInfo();
    }
}

void UserManagement::EnrollCourse(User* user) {
    if (user->GetRole() != "Student") {
        cout << "Only students can enroll in courses!\n";
        return;
    }

    ViewAllCourses(user);
    if (CoursesCount == 0) {
        cout << "No courses available to enroll in.\n";
        return;
    }

    cout << "Select course to enroll (1-" << CoursesCount << "): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice > 0 && choice <= CoursesCount) {
        ((Student*)user)->EnrollCourse(Courses[choice-1]);
        cout << "Enrollment successful!\n";
    } else {
        cout << "Invalid course selection!\n";
    }
}

void UserManagement::ViewTeachingCourses(User* user) {
    if (user->GetRole() != "Instructor") {
        cout << "Only instructors can view teaching courses!\n";
        return;
    }
    ((Instructor*)user)->ViewTeachingCourses();
}

void UserManagement::CreateQuiz(User* user) {
    if (user->GetRole() != "Instructor") {
        cout << "Only instructors can create quizzes!\n";
        return;
    }

    Instructor* instructor = (Instructor*)user;
    instructor->ViewTeachingCourses();
    
    if (instructor->GetCourseCount() == 0) {
        cout << "You are not teaching any courses to create quizzes for.\n";
        return;
    }

    int courseChoice;
    cout << "Select course to add quiz (1-" << instructor->GetCourseCount() << "): ";
    cin >> courseChoice;
    cin.ignore();

    if (courseChoice > 0 && courseChoice <= instructor->GetCourseCount()) {
        instructor->CreateQuiz(instructor->GetCourse(courseChoice-1));
    } else {
        cout << "Invalid course selection!\n";
    }
}

void UserManagement::TakeQuiz(User* user) {
    if (user->GetRole() != "Student") {
        cout << "Only students can take quizzes!\n";
        return;
    }

    Student* student = (Student*)user;
    student->ViewEnrolledCourses();
    
    if (student->GetEnrolledCount() == 0) {
        cout << "You are not enrolled in any courses to take quizzes.\n";
        return;
    }

    int courseChoice;
    cout << "Select course to take quiz (1-" << student->GetEnrolledCount() << "): ";
    cin >> courseChoice;
    cin.ignore();

    if (courseChoice > 0 && courseChoice <= student->GetEnrolledCount()) {
        Course* course = student->GetEnrolledCourse(courseChoice-1);
        course->DisplayQuizzes();
        
        if (course->GetQuizCount() == 0) {
            cout << "This course has no quizzes available.\n";
            return;
        }

        int quizChoice;
        cout << "Select quiz to take (1-" << course->GetQuizCount() << "): ";
        cin >> quizChoice;
        cin.ignore();

        if (quizChoice > 0 && quizChoice <= course->GetQuizCount()) {
            student->TakeQuiz(course, quizChoice-1);
        } else {
            cout << "Invalid quiz selection!\n";
        }
    } else {
        cout << "Invalid course selection!\n";
    }
}

void UserManagement::ViewProgress(User* user) {
    if (user->GetRole() != "Student") {
        cout << "Only students can view progress!\n";
        return;
    }
    ((Student*)user)->ViewProgress();
}

void UserManagement::SaveUsers() {
    ofstream file("users.txt");
    if (!file) {
        cerr << "Error saving user data." << endl;
        return;
    }

    file << UsersCount << endl;
    for (int i = 0; i < UsersCount; i++) {
        Users[i]->SaveData(file);
    }
    file.close();
}

void UserManagement::LoadUsers() {
    ifstream file("users.txt");
    if (!file) {
        cerr << "No existing user data found. Starting fresh." << endl;
        return;
    }

    file >> UsersCount;
    file.ignore();

    for (int i = 0; i < UsersCount && i < MaxUsers; i++) {
        string role, username, name, email, password, address, contactNo;
        
        getline(file, role);
        getline(file, username);
        getline(file, name);
        getline(file, email);
        getline(file, password);
        getline(file, address);
        getline(file, contactNo);

        Users[i] = CreateUser(role, username, name, email, password, address, contactNo);
    }
    file.close();
}

void UserManagement::SaveCourses() {
    ofstream file("courses.txt");
    if (!file) {
        cerr << "Error saving course data." << endl;
        return;
    }

    file << CoursesCount << endl;
    for (int i = 0; i < CoursesCount; i++) {
        file << Courses[i]->GetTitle() << endl
             << Courses[i]->GetDescription() << endl
             << Courses[i]->GetInstructorId() << endl;
    }
    file.close();
}

void UserManagement::LoadCourses() {
    ifstream file("courses.txt");
    if (!file) {
        cerr << "No existing course data found. Starting fresh." << endl;
        return;
    }

    file >> CoursesCount;
    file.ignore();

    for (int i = 0; i < CoursesCount && i < MaxCourses; i++) {
        string title, desc, instructorId;
        
        getline(file, title);
        getline(file, desc);
        getline(file, instructorId);

        Courses[i] = new Course(title, desc, instructorId);
        
        Instructor* instructor = FindInstructor(instructorId);
        if (instructor) {
            instructor->AddTeachingCourse(Courses[i]);
        }
    }
    file.close();
}

// LearnifyApp class
class LearnifyApp {
private:
    UserManagement userManager;

    void AdminMenu(Admin* admin);
    void InstructorMenu(Instructor* instructor);
    void StudentMenu(Student* student);

public:
    void Run();
};

void LearnifyApp::AdminMenu(Admin* admin) {
    while (true) {
        admin->ShowDashboard();
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: // Create Course
                userManager.CreateCourse(admin);
                break;
            case 2: // View All Courses
                userManager.ViewAllCourses(admin);
                break;
            case 3: // Manage Users
                cout << "User management feature coming soon!\n";
                break;
            case 4: // View Profile
                admin->ViewProfile();
                break;
            case 5: // Logout
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void LearnifyApp::InstructorMenu(Instructor* instructor) {
    while (true) {
        instructor->ShowDashboard();
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: // View Teaching Courses
                userManager.ViewTeachingCourses(instructor);
                break;
            case 2: // Create Quiz
                userManager.CreateQuiz(instructor);
                break;
            case 3: // View Profile
                instructor->ViewProfile();
                break;

            case 4: // Logout
                return;
            case 5: // Remove Student
                userManager.RemoveStudent(instructor);
                break;
           

            default:
                cout << "Invalid choice!\n";
        }
    }
}

void LearnifyApp::StudentMenu(Student* student) {
    while (true) {
        student->ShowDashboard();
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: // View All Courses
                userManager.ViewAllCourses(student);
                break;
            case 2: // Enroll in Course
                userManager.EnrollCourse(student);
                break;
            case 3: // View Enrolled Courses
                student->ViewEnrolledCourses();
                break;
            case 4: // Take Quiz
                userManager.TakeQuiz(student);
                break;
            case 5: // View Progress
                student->ViewProgress();
                break;
            case 6: // View Profile
                student->ViewProfile();
                break;
            case 7: // Logout
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void LearnifyApp::Run() {
    while (true) {
        cout << "\n=== LEARNIFY E-LEARNING PLATFORM ===" << endl;
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                userManager.Register();
                break;
            case 2: {
                User* user = userManager.Login();
                if (user) {
                    cout << "\nLogin successful!\n";
                    user->Role();
                    
                    if (user->GetRole() == "Admin") {
                        AdminMenu((Admin*)user);
                    } else if (user->GetRole() == "Instructor") {
                        InstructorMenu((Instructor*)user);
                    } else if (user->GetRole() == "Student") {
                        StudentMenu((Student*)user);
                    }
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 3:
                cout << "Thank you for using Learnify!\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

// Main function
int main() {
    LearnifyApp app;
    app.Run();
    return 0;
}
