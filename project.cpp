#include <bits/stdc++.h>
#include <map>
#include <stdexcept>
using namespace std;

bool validate()
{
    map<string,string> m;
    //saving passwords

    m["tariq"]="tariq@3011";
    m["bhavya"]="bhavya@3007";
    m["kaif"]="kaif@3012";
    m["aman"]="aman@3025";

    string name,password;
    char x;

    cout<<"Enter user name: ";
    cin>>name;
    cin.ignore();
    cout<<"Enter user password: ";
    cin>>password;


    if(m[name]==password)
    {
        return true;
    }
    return false;
}

class library {
    class book {
    public:
        int id, quantity;
        string name;
        string author;
        string publication;
        book(int id, string name, string author, string publication) {
            this->id = id;
            this->name = name;
            this->author = author;
            this->publication = publication;
            this->quantity = 1;
        }
    };
    class node {
    public:
        book* data;
        node* next;
        node(book* val) {
            data = val;
            next = nullptr;
        }
    };

    queue<node*> history;

    node* head = nullptr;

    bool ifexists(node* head, int val) {
        if (head == nullptr) {
            return false;
        }
        node* temp = head;
        while (temp != NULL) {
            if (temp->data->id == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    node* search(node* head, int val) {
        if (head == nullptr) {
            return nullptr;
        }
        node* temp = head;
        while (temp != NULL) {
            if (temp->data->id == val) {
                return temp;
            }
            temp = temp->next;
        }
        return head;
    }

    node* insert(node* &head, book* newbook) {  // Insertion at tail
        if (head == nullptr) {
            head = new node(newbook);
            return head;
        }
        else {
            if (!ifexists(head, newbook->id)) {
                node* temp = head;
                node* mover = nullptr;
                while (temp != NULL) {
                    mover = temp;
                    temp = temp->next;
                }
                node* newnode = new node(newbook);
                mover->next = newnode;
            }
            else {  // Book already exists
                node* temp = search(head, newbook->id);
                temp->data->quantity++;
            }
        }
        return head;
    }

    void display(node* head) {
        if (head == nullptr) {
            cout << "NO BOOKS AVAILABLE." << endl;
            return;
        }

        node* temp = head;
        cout << "BOOK ID \t\t NAME \t\t\t AUTHOR \t\t PUBLICATION \t\t QUANTITY" << endl;
        cout << "----------------------------------------------------------------------------------------------------------" << endl;

        while (temp != nullptr) {
            cout << temp->data->id << "\t\t "
                 << temp->data->name << "\t\t\t"
                 << temp->data->author << "\t\t\t "
                 << temp->data->publication << "\t\t "
                 << temp->data->quantity << endl;
            temp = temp->next;
        }
        cout << endl;
    }
    int totalbooks(node* head) {
        int total = 0;
        node* temp = head;
        while (temp != nullptr) {
            total = total + temp->data->quantity;
            temp = temp->next;
        }
        return total;
    }

    node* issue(node* &head, int bid) {
        if (head == nullptr) {
            cout << "NO BOOKS AVAILABLE." << endl;
            return nullptr;
        }
        if (!ifexists(head, bid)) {
            cout << "Requested book is currently Unavailable or does not Exist." << endl << "Make sure you have entered the correct Book ID" << endl;
            return nullptr;
        }
        else {
            node* temp = search(head, bid);
            if (temp->data->quantity > 0) {
                temp->data->quantity--;
                history.push(temp);
            }
            else {
                cout << "Requested Book is currently Unavailable." << endl;
            }
        }
        return head;
    }

    void displayhistory() {
        if (history.empty()) {
            cout << "NO BOOKS HAVE BEEN ISSUED." << endl;
            return;
        }
        cout << "BOOK ID \t NAME \t\t\t AUTHOR \t\t PUBLICATION \t\t QUANTITY" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        queue<node*> hist = history;
        while (!hist.empty()) {
            node* curr = hist.front();
            cout << curr->data->id << "\t\t "
                 << curr->data->name << "\t\t"
                 << curr->data->author << "\t\t "
                 << curr->data->publication << "\t\t "
                 << curr->data->quantity << endl;
            hist.pop();
        }
        cout << endl;
    }

public:
    library() {
        head = insert(head, new book(101, "Economics", "Tariq Sami", "S. Chand"));
        head = insert(head, new book(127, "DS & Algo", "Mohd. Kaif", "GK Publishers"));
        head = insert(head, new book(133, "Pointers C++", "Aman Luthra", "S. Chand"));
        head = insert(head, new book(129, "Algorithms", "Bhavya Gupta", "Beehive Publn."));
        head = insert(head, new book(145, "Web Develop.", "Mohd. Kaif", "Bright Studio"));
        head = insert(head, new book(101, "eco", "Tariq", "S. Chand"));
    }

    void addbooks() {
        int n;
        cout << "Enter the total number of books to enter: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            int id;
            string name, author, publication;
            cout << "Enter the " << i + 1 << " book: " << endl;
            cout << "Enter book id: ";
            cin >> id;
            cin.ignore();
            cout << "Enter book name: ";
            getline(cin, name);
            cout << "Enter author name: ";
            getline(cin, author);
            cout << "Enter publication name: ";
            getline(cin, publication);
            head = insert(head, new book(id, name, author, publication));
        }
        cout << endl;
    }

    void issuebook() {
        int bid;
        cout << "Enter the Book ID to issue the book: ";
        cin >> bid;
        head = issue(head, bid);
    }

    void displaybooks() {
        cout << "BOOKS AVAILABLE:" << endl;
        display(head);
    }

    void totalbooks() {
        cout << "Total Books Currently Available: " << totalbooks(head) << endl;
    }

    void displayissuedbooks() {
        cout << "ISSUED BOOKS:" << endl;
        displayhistory();
    }
};

class studentmanagement {
private:
    class student {
    public:
        int id;
        string name;
        int age;

        student(int id, string &stname, int age) {
            this->id = id;
            this->name = stname;
            this->age = age;
        }
    };

    class Node {
    public:
        student *data;
        Node *left;
        Node *right;

        Node(student *st){
            data = st;
            left = nullptr;
            right = nullptr;
        }
    };

    class bst {
    private:
        Node *root;

        void insert(Node *&node, student *student) {
            if (node == nullptr) {
                node = new Node(student);
            } else if (student->id < node->data->id) {
                insert(node->left, student);
            } else if(student->id > node->data->id){
                insert(node->right, student);
            }
            else{ //duplicate id case
                return;
            }
        }

        Node* search(Node *node, int id) {
            if (node == nullptr || node->data->id == id)
                return node;
            if (id < node->data->id)
                return search(node->left, id);
            else {
                return search(node->right, id);
            }
        }
        void inorder(Node *node, vector<student*> &records) {
            if (node != nullptr) {
                inorder(node->left, records);
                records.push_back(node->data);
                inorder(node->right, records);
            }
        }

        Node* deletenode(Node *node, int id) {
            if (node == nullptr) return node;

            if (id < node->data->id) {
                node->left = deletenode(node->left, id);
            } else if (id > node->data->id) {
                node->right = deletenode(node->right, id);
            } else { // one child case
                if (node->left == nullptr) {
                    Node *temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node *temp = node->left;
                    delete node;
                    return temp;
                }
                //no child case
                Node *temp = minimumnode(node);
                node->data = temp->data;
                node->right = deletenode(node->right, temp->data->id);
            }
            return node;
        }

        Node* minimumnode(Node *node) {
            Node *current = node->right;
            while (current && current->left != nullptr) {
                current = current->left;
            }
            return current;
        }

    public:
        bst() {
            root = nullptr;
        }

                void insert(student *st) {
            insert(root, st);
        }

        student* searchid(int id) {
            Node *n = search(root, id);
            if (n) {
                return n->data;
            }
            return nullptr;
        }

        void deletestudent(int id) {
            root = deletenode(root, id);
        }

        void display(student* st) {
            cout << "ID: " << st->id << " Name: " << st->name << " Age: " << st->age << endl;
        }

        void displaysorted() {
            vector<student*> students;
            if(root==nullptr)
            {
                cout<<"NO STUDENT RECORD AVAILABLE"<<endl;
            }
            inorder(root, students);
            vector<student*>::iterator it = students.begin();
            while (it != students.end()) {
                display(*it);
                it++;
            }
        }
    };

    bst studentbst;

public:
    void addstudents() {
        int num;
        cout << "Enter the total number of Data to Enter: ";
        cin >> num;
        while (num != 0) {
            int id, age;
            string name;
            cin.ignore();
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            studentbst.insert(new student(id, name, age));
            cout << endl;
            num--;
        }
    }

    void searchstudent() {
        int id;
        cout << "Enter Student ID to search: ";
        cin >> id;
        student *st = studentbst.searchid(id);
        if (st) {
            studentbst.display(st);
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void deletestudent() {
        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;
        studentbst.deletestudent(id);
        cout << "Student deleted (if existed)." << endl;
    }

    void displayallstudents() {
        cout << "Displaying all students:\n";
        studentbst.displaysorted();
    }
};


class facultymanagementsystem {
private:
    const static int tsize = 10;

    class faculty {
    public:
        int id;
        string name;
        string department;
        faculty* next;

        faculty(int i, string n, string d) {
            this->id = i;
            this->name = n;
            this->department = d;
            next = nullptr;
        }
    };

    faculty* table[tsize];

    int hashfunction(int id) {
        return id % tsize;
    }

    bool checkduplicateid(int id) {
        int hashindex = hashfunction(id);
        faculty* temp = table[hashindex];
        while (temp != nullptr) {
            if (temp->id == id)
                return true;
            temp = temp->next;
        }
        return false;
    }

public:
    facultymanagementsystem() {
        for (int i = 0; i < tsize; i++)
            table[i] = nullptr;
    }

    void addfaculty(int id, string name, string department) {
        if (checkduplicateid(id)) {
            throw runtime_error("Error: Faculty ID must be unique.");
        }

        int hashindex = hashfunction(id);
        faculty* newfaculty = new faculty(id, name, department);

        if (!table[hashindex]) { //if it is empty it will insert
            table[hashindex] = newfaculty;
        } else {// else it traverse the linked list present and will insert at its tail
            faculty* temp = table[hashindex];
            while (temp->next)
                temp = temp->next;
            temp->next = newfaculty; //for assigning the next pointer
        }
        cout << "Faculty added successfully!\n";
    }

    void searchfaculty(int id) {
        int hashindex = hashfunction(id);
        faculty* temp = table[hashindex];

        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Faculty Found:\n";
                cout << "ID: " << temp->id << "\n";
                cout << "Name: " << temp->name << "\n";
                cout << "Department: " << temp->department << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Faculty not found.\n";
    }

    void displayfaculty() {
        for (int i = 0; i < tsize; i++) {
            faculty* temp = table[i];
            if (temp) {
                cout << "Table[" << i << "]:\n";
                while (temp) {
                    cout << " ID: " << temp->id << ", Name: " << temp->name
                         << ", Department: " << temp->department << "\n";
                    temp = temp->next;
                }
            }
        }
    }

    ~facultymanagementsystem() {
        for (int i = 0; i < tsize; i++) {
            faculty* temp = table[i];
            while (temp) {
                faculty* todelete = temp;
                temp = temp->next;
                delete todelete;
            }
        }
    }
};

class coursemanagementsystem {
private:
    class course {
    public:
        int id;
        string name;
        int credits;
        course* left;
        course* right;

        course(int courseid, string coursename, int credithours)
            : id(courseid), name(coursename), credits(credithours), left(NULL), right(NULL) {}
    };

    course* root;

    course* insertcourse(course* node, int id, string name, int credits) {
        if (node == NULL) {
            return new course(id, name, credits);
        }
        if (name < node->name) {
            node->left = insertcourse(node->left, id, name, credits);
        } else if (name > node->name) {
            node->right = insertcourse(node->right, id, name, credits);
        }
        return node;
    }

    course* minvaluenode(course* node) {
        course* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    course* deletecourse(course* node, string name) {
        if (node == NULL) return node;

        if (name < node->name) {
            node->left = deletecourse(node->left, name);
        } else if (name > node->name) {
            node->right = deletecourse(node->right, name);
        } else {
            if (node->left == NULL) {
                course* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                course* temp = node->left;
                delete node;
                return temp;
            }

            course* temp = minvaluenode(node->right);
            node->id = temp->id;
            node->name = temp->name;
            node->credits = temp->credits;
            node->right = deletecourse(node->right, temp->name);
        }
        return node;
    }

    void inorderdisplay(course* node) {
        if (node != NULL) {
            inorderdisplay(node->left);
            cout << "Course ID: " << node->id << ", Name: " << node->name << ", Credits: " << node->credits << endl;
            inorderdisplay(node->right);
        }
    }

    course* searchcourse(course* node, string name) {
        if (node == NULL || node->name == name) {
            return node;
        }
        if (name < node->name) {
            return searchcourse(node->left, name);
        }
        return searchcourse(node->right, name);
    }

public:
    coursemanagementsystem() : root(NULL) {}

    void addcourse(int id, string name, int credits) {
        root = insertcourse(root, id, name, credits);
    }

    void removecourse(string name) {
        root = deletecourse(root, name);
    }

    void displaycourses() {
        if (root == NULL) {
            cout << "No courses available.\n";
        } else {
            inorderdisplay(root);
        }
    }

    void findcourse(string name) {
        course* result = searchcourse(root, name);
        if (result != NULL) {
            cout << "Course found:\n";
            cout << "Course ID: " << result->id << ", Name: " << result->name << ", Credits: " << result->credits << endl;
        } else {
            cout << "Course not found.\n";
        }
    }

    void addcoursemenu() {
        int id, credits;
        string name;
        cout << "Enter Course ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Course Name: ";
        getline(cin, name);
        cout << "Enter Credits: ";
        cin >> credits;
        addcourse(id, name, credits);
        cout << "Course added successfully.\n";
    }

    void removecoursemenu() {
        string name;
        cin.ignore();
        cout << "Enter Course Name to Remove: ";
        getline(cin, name);
        removecourse(name);
        cout << "Course removed successfully (if it existed).\n";
    }

    void displaycoursesmenu() {
        cout << "Displaying all courses:\n";
        displaycourses();
    }

    void searchcoursemenu() {
        string name;
        cin.ignore();
        cout << "Enter Course Name to Search: ";
        getline(cin, name);
        findcourse(name);
    }
};


int main() {
    if(!validate())
    {
        cout<<endl<<"Invalid Username or Password. ACCESS DENIED"<<endl;
        return 0;
    }

    char syschoice, mchoice;

    library lib;
    studentmanagement sm;
    facultymanagementsystem fms;
    coursemanagementsystem cms;

    do {
        cout << "\nMAIN MENU\n";
        cout << "1. LIBRARY MANAGEMENT SYSTEM\n";
        cout << "2. STUDENT MANAGEMENT SYSTEM\n";
        cout << "3. FACULTY MANAGEMENT SYSTEM\n";
        cout << "4. COURSE MANAGEMENT SYSTEM\n";
        cout << "5. EXIT\n";
        cout << "Enter your choice: ";
        cin >> syschoice;

        switch (syschoice) {
            case '1':
                do {
                    cout << "\nLibrary Management System\n";
                    cout << "1. Add a Book to Library\n";
                    cout << "2. Issue a Book\n";
                    cout << "3. Display Available Books\n";
                    cout << "4. Total Books Available\n";
                    cout << "5. Display Audit Log\n";
                    cout << "6. Exit Library Management\n";
                    cout << "Enter your choice: ";
                    cin >> mchoice;

                    switch (mchoice) {
                        case '1':
                            lib.addbooks();
                            break;
                        case '2':
                            lib.issuebook();
                            break;
                        case '3':
                            lib.displaybooks();
                            break;
                        case '4':
                            lib.totalbooks();
                            break;
                        case '5':
                            lib.displayissuedbooks();
                            break;
                        case '6':
                            cout << "Exiting Library Management System...\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (mchoice != '6');
                break;

            case '2':
                do {
                    cout << "\nStudent Management System\n";
                    cout << "1. Add Student\n";
                    cout << "2. Search Student\n";
                    cout << "3. Delete Student\n";
                    cout << "4. Display All Students\n";
                    cout << "5. Exit Student Management\n";
                    cout << "Enter your choice: ";
                    cin >> mchoice;

                    switch (mchoice) {
                        case '1':
                            sm.addstudents();
                            break;
                        case '2':
                            sm.searchstudent();
                            break;
                        case '3':
                            sm.deletestudent();
                            break;
                        case '4':
                            sm.displayallstudents();
                            break;
                        case '5':
                            cout << "Exiting Student Management System...\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                } while (mchoice != '5');
                break;

            case '3':
                do {
                    cout << "\nFaculty Management System\n";
                    cout << "1. Add Faculty\n";
                    cout << "2. Search Faculty\n";
                    cout << "3. Display All Faculty\n";
                    cout << "4. Exit Faculty Management\n";
                    cout << "Enter your choice: ";
                    cin >> mchoice;

                    try {
                        switch (mchoice) {
                            case '1': {
                                int id;
                                string name, department;
                                cout << "Enter Faculty ID: ";
                                cin >> id;
                                cout << "Enter Faculty Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Faculty Department: ";
                                getline(cin, department);
                                fms.addfaculty(id, name, department);
                                break;
                            }
                            case '2': {
                                int id;
                                cout << "Enter Faculty ID to search: ";
                                cin >> id;
                                fms.searchfaculty(id);
                                break;
                            }
                            case '3':
                                fms.displayfaculty();
                                break;
                            case '4':
                                cout << "Exiting Faculty Management System...\n";
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                        }
                    }
                    catch (const runtime_error& e) {
                        cout << e.what() << "\n";
                    }
                    catch (const invalid_argument& e) {
                        cout << e.what() << "\n";
                    }
                } while (mchoice != '4');
                break;

            case '4':
                do {
                    cout << "\nCourse Management System\n";
                    cout << "1. Add Course\n";
                    cout << "2. Remove Course\n";
                    cout << "3. Display All Courses\n";
                    cout << "4. Search Course\n";
                    cout << "5. Exit Course Management\n";
                    cout << "Enter your choice: ";
                    cin >> mchoice;

                    switch (mchoice) {
                        case '1':
                            cms.addcoursemenu();
                            break;
                        case '2':
                            cms.removecoursemenu();
                            break;
                        case '3':
                            cms.displaycoursesmenu();
                            break;
                        case '4':
                            cms.searchcoursemenu();
                            break;
                        case '5':
                            cout << "Exiting Course Management System...\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                } while (mchoice != '5');
                break;

            case '5':
                cout << "EXITING THE SYSTEM. THANKS\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (syschoice != '5');
    return 0;
}




