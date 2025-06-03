#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <cstdlib>

using namespace std;
COORD CursorPosition;

class PointManagementException {
private:
    string message;

public:
    PointManagementException(const string& msg) : message(msg) {}

    const string& what() const {
        return message;
    }
};

void gotoline(int x, int y){
	COORD pos = {(short)x, (short)y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clearScreen()
{
    system("cls");
}

void print(const string msg, int x, int y, int times, int pause, int charSpeed){
	for(int i = 0 ; i < times ; i++){
		gotoline(x, y);
		for(int i = 0 ; msg[i] != '\0' ; i++){
			cout << msg[i];
            Sleep(charSpeed);
		}
		Sleep(pause);
		x++;
	}
}
void print(vector<string> msg, int x, int y, int times, int pause, int charSpeed){
    for(int l = 0 ; l < times ; l++){
		gotoline(x + l, y);
		for(int i = 0 ; i < msg.size() ; i++){
            gotoline(x + l, y + i);
            cout << msg[i];
        }
        Sleep(charSpeed);
	}
}

void Routes()
{
    ifstream file("Routes.txt");

    if (!file.is_open())
    {
        throw PointManagementException("Failed to open file 'Routes.txt'");
    }

    string line;

    while (getline(file, line))
    {
        cout << line << "" << endl;
    }

    cout << "\n\n" << endl;

    file.close();
}

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}
void SeatsAvailable()
{
    ifstream file("SeatsAvailable.txt");

    if (!file.is_open())
    {
        throw PointManagementException("Failed to open file 'SeatsAvailable.txt'");
    }

    string line;

    while (getline(file, line))
    {
        cout << line << "" << endl;
    }

    cout << "\n\n" << endl;

    file.close();
}



void ReadEmails()
{
    ifstream file("Email.txt");

    if (!file.is_open())
    {
        cout << "No Latest Updates Found!!!" << endl;
        return;
    }

    cout << "\nLatest Updates:" << endl;
    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}





void NewUpdate()
{
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);

    ofstream file("Email.txt", ios::out | ios::app);
    if (!file.is_open())
    {
        throw PointManagementException("Failed to open file for writing!");
    }

    string update;
    cout << "\nEnter the Latest Update to publish: ";
    cin >> ws; // discards whitespace 
    getline(cin, update);


    file << put_time(localTime, "[ %Y-%m-%d %H:%M:%S ]") << endl;
    file << update << "\n" << endl;

    file.close();
}





void UpdateAvailableSeats()
{
    int route_num, num;
    string line, updated;
    vector<string> lines;

    cout << "\n\nUpdating Seats Availability......";
    bool correct = false;
    
    do {
        cout << "\nEnter Point Route # : ";
        cin >> route_num;

        if (cin.fail() || route_num < 1 || route_num > 5) {
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            clearInputBuffer(); 
        } else {
            correct = true;
        }
    } while (!correct);

    cout << "Enter the updated number of Seats Available: ";
    cin >> num;
    updated = to_string(num) + " Seats Available";

    int row_num = 1 + ((route_num - 1) * 3);

    ifstream file("SeatsAvailable.txt");

    if (!file.is_open())
    {
        throw PointManagementException("Failed to open file 'SeatsAvailable.txt'");
    }

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    if (row_num >= 0 && row_num < lines.size())
    {
        lines.erase(lines.begin() + row_num);
        lines.insert(lines.begin() + row_num, updated);
    }

    ofstream outfile("SeatsAvailable.txt");

    if (!outfile.is_open())
    {
        throw PointManagementException("Failed to open file 'SeatsAvailable.txt'");
    }
    for (const auto &copy : lines)
    {
        outfile << copy << endl;
    }

    outfile.close();
}




void ViewReservation()
{
    ifstream file("ReservationRequests.txt");

    if (!file.is_open())
    {
        throw PointManagementException("Failed to open file 'ReservationRequests.txt'");
    }

    string line;
	
	cout << "<<< Reservations >>>";
    while (getline(file, line))
    {
        cout << line << "" << endl;
    }

    file.close();
}








class User 
{
protected:
    string id;
    string name;
    string password;

public:
    User(const string& id, const string& name, const string& password)
        : id(id), name(name), password(password) {}

    virtual ~User() {}

    virtual void displayMenu() const = 0;

    string getID() const 
	{
        return id;
    }

    string getName() const 
	{
        return name;
    }
    
    string getPassword() const 
	{
        return password;
    }
};







class Admin : public User 
{
public:
    Admin(const string& id, const string& name, const string& password)
        : User(id, name, password) {}

    void displayMenu() const override 
	{
	string admin_menu = R"(
    
                                        +-----------------------------------------------+
                                        |                   Admin Menu                  |
                                        +-----------------------------------------------+
                                        | Option |                Description           |
                                        +--------+--------------------------------------+
                                        |   1    | Email New Update                     |
                                        |   2    | Update Available Seats               |
                                        |   3    | View Reservation Requests            |
                                        |   4    | Logout                               |
                                        +-----------------------------------------------+
                                                    Enter your choice (1-4): 
)";
    cout << admin_menu << endl;
    }
    
    static vector<Admin>readAdminsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw PointManagementException("Failed to open file 'Admins.txt' ");
            exit(1);
        }

        vector<Admin> admins;
        string username, password;
        while (getline(file, username) && getline(file, password)) {
            admins.emplace_back("admin", username, password);
        }

        file.close();
        return admins;
    }
};





class RegularUser : public User 
{
public:
    RegularUser(const string& id, const string& name, const string& password)
        : User(id, name, password) {}

    void displayMenu() const override 
	{

        string user_menu = R"(
    
                                        +-----------------------------------------------+
                                        |                   User Menu                   |
                                        +-----------------------------------------------+
                                        | Option |          Description                 |
                                        +--------+--------------------------------------+
                                        |   1    | View Point Routes                    |
                                        |   2    | Available Seats                      |
                                        |   3    | Issue Reservation Request            |
                                        |   4    | Read Latest Updates                  |
                                        |   5    | Logout                               |
                                        +-----------------------------------------------+
                                                    Enter your choice (1-5): 
)";
        cout << user_menu << endl;

    }
    
    static vector<RegularUser>readRegularUsersFromFile(const string& filename) {
        ifstream file("Users.txt");
        if (!file.is_open()) {
            throw PointManagementException("Failed to open file 'Users.txt' ");
            exit(1);
        }

        vector<RegularUser> regularUsers;
        string ID, username, password;
        while (getline(file, ID) && getline(file, username) && getline(file, password)) {
            regularUsers.emplace_back(ID, username, password); // Assuming "admin" is the ID for all admins
        }

        file.close();
        return regularUsers;
    }
};




class Reservation 
{
private:
    string username;
    string userID;
    int route_num;
    int seat_num;
    string reservation_type;

public:
    Reservation(string username, string userID) : username(username), userID(userID) {
        cout << "Point Seating Arrangement:" << endl;
        int count = 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                if (j == 2) {
                    cout << "     ";
                }
                cout << setw(3) << count << "  ";
                count++;
            }
            cout << endl;
        }
        cout << " ";
        for (int i = 21; i <= 35; i++) {
            cout << setw(2) << i << "   ";
            if (i == 25 || i == 30) {
                cout << "\n ";
            }
        }

        ifstream inFile("SeatsAvailable.txt");
        if (!inFile.is_open()) {
            throw PointManagementException("Failed to open file 'SeatsAvailable.txt'");
            return;
        }

        int route;
        int seats;
        bool correct = false;
        
        do {
            cout << "\nEnter Point Route # : ";
            cin >> route_num;

            if (cin.fail() || route_num < 1 || route_num > 5) {
                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                clearInputBuffer(); 
            } else {
                correct = true;
            }
        } while (!correct);

        correct = false; 

        do {
            cout << "Select Seat Number to Reserve: ";
            cin >> seat_num;

            if (cin.fail() || seat_num < 1 || seat_num > 35) {
                cout << "Invalid input. Please enter a number between 1 and 35." << endl;
                clearInputBuffer(); 
            } else {
                correct = true;
            }
        } while (!correct);        
        correct = false;
        do {
            cout << "Request 'Annual' or 'Semester' Reservation: ";
            cin >> reservation_type;
            string lower_reservation_type = reservation_type;
            for (char &c : lower_reservation_type) {
                c = tolower(c);
            }
            if (lower_reservation_type != "annual" && lower_reservation_type != "semester") {
                cout << "Invalid reservation type. Please enter 'Annual' or 'Semester'." << endl;
            } else {
                correct = true;
            }
        } while (!correct);
    }        

    void saveToFile() const 
	{
        ofstream file("ReservationRequests.txt", ios::app);
        if (!file.is_open()) 
		{
            throw PointManagementException("Failed to open file 'ReservationRequests.txt'");
            return;
        }
		
        file << "\nRequestee ID: " << userID;
        file << "\nName: " << username;
        file << "\nRoute # : " << route_num;
        file << "\nSeat Number: " << seat_num;
        file << "\nReservation Type: " << reservation_type;
        cout << endl;
        cout << "Please wait while we process your data..............." << endl;
        cout << "Writing data to file................................." << endl;
        cout << endl;
        cout << "Requestee ID: " << userID << endl;
        cout << "Name: " << username << endl;
        cout << "Route # : " << route_num << endl;
        cout << "Seat Number: " << seat_num << endl;
        cout << "Reservation Type: " << reservation_type << endl;

        file.close();
    }
};





class PointManagementSystem 
{
private:
    vector<User*> users;

public:
    PointManagementSystem() {}

    ~PointManagementSystem() 
	{
        for (auto user : users) 
		{
            delete user;
        }
    }

    void run() 
	{
        displayWelcomeScreen();

        while (true) 

		{
            int choice = -1;
			displayOnboardingMenu();
			if (!(cin >> choice)) 
    		{
                clearInputBuffer();
        		clearScreen();
        		cout << "Invalid input. Please enter a valid number." << endl;
        		continue;
    		}		
			cin.ignore();
			
            switch (choice) 
			{
                case 1:
                	clearScreen();
                    adminLogin();
                    break;
                case 2:
                	clearScreen();
                    userLogin();
                    break;
                case 3:
                	clearScreen();
                    registerUser();
                    break;
                case 4:
                	clearScreen();
                    cout << "Exiting the Point Management System. Goodbye!" << endl;
                    return;
                    
                default:
                	clearScreen();
                    cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                    
                    
            }
        }
    }

private:

    void displayWelcomeScreen() const 
	{
        string welcome = R"(
                -------------------------------------------------------------------------------------------------
                |                                WELCOME TO THE OFFICIAL                                        |
                |                ______ ___   _____ _____   _   _ _   _ _____  _____ _____                      |
                |                |  ___/ _ \ /  ___|_   _| | \ | | | | /  __ \|  ___/  ___|                     |
                |                | |_ / /_\ \\ `--.  | |   |  \| | | | | /  \/| |__ \ `--.                      |
                |                |  _||  _  | `--. \ | |   | . ` | | | | |    |  __| `--. \                     |
                |                | |  | | | |/\__/ / | |   | |\  | |_| | \__/\| |___/\__/ /                     |
                |                \_|  \_| |_/\____/  \_/   \_| \_/\___/ \____/\____/\____/                      |
                |                                                                                               |
                |                                                                                               |
                |                                ______     _       _                                           |
                |                                | ___ \   (_)     | |                                          |
                |                                | |_/ /__  _ _ __ | |_                                         |
                |                                |  __/ _ \| | '_ \| __|                                        |
                |                                | | | (_) | | | | | |_                                         |
                |                                \_|  \___/|_|_| |_|\__|                                        |
                |                                                                                               |
                |                                                                                               |
                |                ___  ___                                                  _                    |
                |                |  \/  |                                                 | |                   |
                |                | .  . | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_                  |
                |                | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|                 |
                |                | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_                  |
                |                \_|  |_/\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|                 |
                |                                           __/ |                                               |
                |                                           |___/                                               |
                |                                                                                               |
                |                             _____           _                                                 |
                |                            /  ___|         | |                                                |
                |                            \ `--. _   _ ___| |_ ___ _ __ ___                                  |
                |                             `--. \ | | / __| __/ _ \ '_ ` _ \                                 |
                |                            /\__/ / |_| \__ \ ||  __/ | | | | |                                |
                |                            \____/ \__, |___/\__\___|_| |_| |_|                                |
                |                                    __/ |                                                      |
                |                                   |___/                                                       |
                |                                                                                               |
                -------------------------------------------------------------------------------------------------
               
            )";

            vector<string> members = {
    {"                 G R O U P    M E M B E R S                      "},
    {"                                                                 "},
    {" .-------------------------------------------------------------. "},
    {" '------..-------------..----------..----------..----------..--.|"},
    {" |       \\  Shehryar  ||  Sameed  ||  Raahim  || Driver:  ||  ||"},
    {" |        \\   0503    ||   0812   ||   0837   || Shehzad  ||  ||"},
    {" |    ..   ||  _    _  ||    _   _ || _    _   ||    _    _||  ||"},
    {" |    ||   || //   //  ||   //  // ||//   //   ||   //   //|| /||"},
    {" |_.------\"\'\'----------\'\'----------\'\'----------\'\'----------\'\'--\'|"},
    {" |)|      |       |       |       |    |         |      ||==|  | "},
    {" | |      |  _-_  | Route |   04  |    |  .-.    |      ||==| C| "},
    {" | |  __  |.\'.-.\' |   _   |   _   |    |.\'.-.\'.  |  __  | \"__==\' "},
    {" \'---------\'|( )|\'----------------------\'|( )|\'----------\"\"      "},
    {"             \'-\'                          \'-\'                    "}
};

        // changeColor(75);
        print(welcome, 0,3,1,0,0.99);

        cout << endl;
        cin.ignore();
        print(members, 0,45,50,0,60);
    }
    void displayOnboardingMenu() const {
        string onboarding_menu = R"(
    
                                            +-----------------------------------------------+
                                            |                 Onboarding Menu               |
                                            +-----------------------------------------------+
                                            | Option |            Description               |
                                            +--------+--------------------------------------+
                                            |   1    | Sign in as an Administrator          |
                                            |   2    | Sign in as a User                    |
                                            |   3    | Register as a New User               |
                                            |   4    | Exit                                 |
                                            +-----------------------------------------------+
                                                        Enter your choice (1-4): 
)";


    cout << onboarding_menu << endl;
     }







    void adminLogin() {
        string username, password;

        cout << "Signing in as Admin..." << endl;
        cout << "\n\nEnter Administrator's Username: ";
        fflush(stdin);
        getline(cin, username);
        cout << "Enter Administrator's Password: ";
        getline(cin, password);
        

        vector<Admin> admins = Admin::readAdminsFromFile("Admins.txt");
        

        bool validCredentials = false;
        for (const auto& admin : admins) {
            if (admin.getName() == username && admin.getPassword() == password) {
                validCredentials = true;
                break;
            }
        }

        if (validCredentials) {
            clearScreen();
            cout << "\t Welcome " << "'" << username << "'" << " To The POINT MANAGEMENT SYSTEM!!!" << endl;
            bool flag = true;
            int choice;
            while (flag) {
                
                Admin adm("admin", username, "");
                adm.displayMenu();

                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1:
                        clearScreen();
                        NewUpdate();
                        break;
                    case 2:
                        clearScreen();
                        UpdateAvailableSeats();
                        break;
                    case 3:
                        clearScreen();
                        ViewReservation();
                        break;
                    case 4:
                        clearScreen();
                        cout << "Logging Out.........Completed!" << endl;
                        return;
                    default:
                        clearScreen();
                        cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                }
            }
            clearScreen();
        } 
        else 
        {
            cout << "INVALID USERNAME OR PASSWORD!!!" << endl;
        }
    }







void userLogin() 
{
    string id, username, password;
    cout << "Signing in as User...";
    cout << "\n\nEnter User ID: ";
    fflush(stdin);
    getline(cin, id); 
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);

    vector<RegularUser> regularUsers = RegularUser::readRegularUsersFromFile("Users.txt"); 

    bool validCredentials = false;
    for (const auto& regular : regularUsers) 
    {
        if (regular.getName() == username && regular.getPassword() == password) 
        {
            validCredentials = true;
            break;
        }
    }

    if (validCredentials)
    {
    	
    	clearScreen();
        cout << "\t Welcome " << "'" << username << "'" << " To The POINT MANAGEMENT SYSTEM!!!" << endl;
        bool flag = true; 
        int choice; 
        while (flag) 
		{
	        RegularUser user("", username, ""); 
	        user.displayMenu();
	
	        int choice; 
	        cin >> choice;
	        cin.ignore();
	
	        switch (choice)
	        {
	            case 1:
	            	clearScreen();
	                Routes();
	                break;
	
	            case 2:
	            	clearScreen();
	                SeatsAvailable();
	                break;
	
	            case 3:
	            {
	            	clearScreen();
	                Reservation booking(username, id);
	                booking.saveToFile();
	                break;
	            }
	            case 4:
	            	clearScreen();
	                ReadEmails(); 
	                break;
	
    	        case 5:	
	                clearScreen();
	                cout << "Logging Out.........Completed!" << endl;
	                return;
	                break;
	            default:
 		           	clearScreen();
 	                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
 	       }
		}
	}
 	else 
    {
        cout << "INVALID USERNAME OR PASSWORD!!!" << endl;
    }
	
}
    
    
    
    
    
    

    void registerUser() 
	{
        string id, username, password;
        cout << "<<< User Registration >>>";
        cout << "\n\nEnter User ID: ";
        cin >> id;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        for (auto user : users) 
		{
            if (user->getID() == id) 
			{
                cout << "User with the same ID already exists!" << endl;
                return;
            }
        }

        ofstream file("Users.txt", ios::app);
        if (!file.is_open()) 
		{
            throw PointManagementException("Failed to open file 'Users.txt' for writing!");
        }
        file << id << "" << endl;
        file << username << "" << endl;
        file << password << "" << endl;
        file.close();

        User* newUser = new RegularUser(id, username, password);
        users.push_back(newUser);
        cout << "User registration successful!!!" << endl;
    }
};










int main() {
    system("Color 4F");
    try {
        PointManagementSystem pms;
        pms.run();
    } catch (const PointManagementException& e) {
        cout << "Point Management Exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Unknown error occurred." << endl;
        return 1;
    }
}
