#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class User {
public:
    string name;
    string contact;
    string password;
    int role; // 1=Architect, 2=Contractor, 3=Engineer, 4=Client

    string getRoleName() const {
        switch (role) {
            case 1: return "Architect";
            case 2: return "Contractor";
            case 3: return "Engineer";
            case 4: return "Client";
            default: return "Unknown";
        }
    }
};

class Job {
public:
    string title;
    string description;
    string postedBy;
    int role;

    string getRoleName() const {
        switch (role) {
            case 1: return "Architect";
            case 2: return "Contractor";
            case 3: return "Engineer";
            case 4: return "Client";
            default: return "Unknown";
        }
    }
};

// Global STL vectors
vector<User> users;
vector<Job> jobs;
int loggedInIndex = -1;

// ================= FILE HANDLING =================

void saveUsersToFile() {
    ofstream file("users.txt");
    for (auto &u : users) {
        file << u.name << "|" << u.contact << "|" << u.password << "|" << u.role << "\n";
    }
}

void loadUsersFromFile() {
    users.clear();
    ifstream file("users.txt");

    string line;
    while (getline(file, line)) {
        User u;
        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        u.name = line.substr(0, pos1);
        u.contact = line.substr(pos1 + 1, pos2 - pos1 - 1);
        u.password = line.substr(pos2 + 1, pos3 - pos2 - 1);
        u.role = stoi(line.substr(pos3 + 1));

        users.push_back(u);
    }
}

void saveJobsToFile() {
    ofstream file("jobs.txt");
    for (auto &j : jobs) {
        file << j.title << "|" << j.description << "|" << j.postedBy << "|" << j.role << "\n";
    }
}

void loadJobsFromFile() {
    jobs.clear();
    ifstream file("jobs.txt");

    string line;
    while (getline(file, line)) {
        Job j;
        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        j.title = line.substr(0, pos1);
        j.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        j.postedBy = line.substr(pos2 + 1, pos3 - pos2 - 1);
        j.role = stoi(line.substr(pos3 + 1));

        jobs.push_back(j);
    }
}

// ================= CORE LOGIC =================

void signUp() {
    User u;
    cout << "\n--- Sign Up ---\n";
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, u.name);

    cout << "Enter Contact: ";
    getline(cin, u.contact);

    cout << "Choose Role:\n1. Architect\n2. Contractor\n3. Engineer\n4. Client\nChoice: ";
    cin >> u.role;
    cin.ignore();

    cout << "Enter Password: ";
    getline(cin, u.password);

    users.push_back(u);
    saveUsersToFile();

    cout << "\n✅ Registration successful!\n";
}

void login() {
    cin.ignore();
    string name, pass;

    cout << "\n--- Login ---\n";
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Password: ";
    getline(cin, pass);

    for (int i = 0; i < users.size(); i++) {
        if (users[i].name == name && users[i].password == pass) {
            loggedInIndex = i;
            cout << "\n✅ Login successful! Welcome, " << users[i].name
                 << " (" << users[i].getRoleName() << ")\n";
            return;
        }
    }

    cout << "\n❌ Invalid name or password.\n";
    loggedInIndex = -1;
}

void postJob() {
    if (loggedInIndex == -1) {
        cout << "Please login first!\n";
        return;
    }

    Job j;
    cin.ignore();
    cout << "\n--- Post a Job ---\n";

    cout << "Enter Job Title: ";
    getline(cin, j.title);

    cout << "Enter Job Description: ";
    getline(cin, j.description);

    j.postedBy = users[loggedInIndex].name;
    j.role = users[loggedInIndex].role;
    cout<<loggedInIndex;
    jobs.push_back(j);
    saveJobsToFile();

    cout << "\n✅ Job posted successfully!\n";
}

void viewJobs() {
    if (jobs.empty()) {
        cout << "\nNo jobs posted yet!\n";
        return;
    }

    cout << "\n--- All Job Posts ---\n";
    for (int i = 0; i < jobs.size(); i++) {
        cout << i + 1 << ". Title: " << jobs[i].title << endl;
        cout << "   Description: " << jobs[i].description << endl;
        cout << "   Posted by: " << jobs[i].postedBy << " (" << jobs[i].getRoleName() << ")\n";
        cout << "-----------------------------------\n";
    }
}

void searchByRole() {
    int choice;
    cout << "\n--- Search User by Role ---\n";
    cout << "1. Architect\n2. Contractor\n3. Engineer\n4. Client\nChoice: ";
    cin >> choice;

    bool found = false;
    cout << "\n--- Results ---\n";

    for (auto &u : users) {
        if (u.role == choice) {
            cout << "Name: " << u.name << "\nContact: " << u.contact << "\n---------------\n";
            found = true;
        }
    }

    if (!found) cout << "No users found.\n";
}

bool dashboard() {
    int ch;
    while (true) {
        cout << "\n===== Dashboard =====\n";
        cout << "1. Post a Job\n2. View All Jobs\n3. Search User by Role\n4. Logout\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: postJob(); break;
            case 2: viewJobs(); break;
            case 3: searchByRole(); break;
            case 4:
                cout << "\nLogging out...\n";
                loggedInIndex = -1;
                return false;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

// ================= MAIN =================

int main() {
    loadUsersFromFile();
    loadJobsFromFile();

    int choice;
    bool running = true;

    while (running) {
        cout << "\n=============================\n";
        cout << "  Welcome to Construct Link\n";
        cout << "=============================\n";
        cout << "1. Sign Up\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: signUp(); break;
            case 2: 
                login();
                if (loggedInIndex != -1) dashboard();
                break;
            case 3:
                cout << "\nExiting... Thank you for using Construct Link!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
