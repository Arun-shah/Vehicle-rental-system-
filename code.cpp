#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>
using namespace std;

class Check{
	protected :
	string name, username, password, mobile, email;
    string savedUsername, savedPassword;
	public:
		bool validMobile(string mobile){
		if (mobile.length() != 10)
        return false;

    if (mobile.substr(0, 2) != "98" &&
        mobile.substr(0, 2) != "97")
        return false;

    for (int i = 0; i < mobile.length(); i++)
    {
        if (mobile[i] < '0' || mobile[i] > '9')    
            return false;
    return true;
	}
	}
bool validEmail(string email)
{
    int at = email.find('@');

    if (at == string::npos || at == 0)
        return false;
        
    if (email.find('@', at + 1) != string::npos)
        return false;

    int dot = email.find('.', at + 1);

    if (dot == string::npos)
        return false;

    if (dot == at + 1)
        return false;

    if (dot == email.length() - 1)
        return false;

    return true;
}

void registerUser()
{


    system("cls");
    cout<<"\n========== USER REGISTRATION ==========\n";

    cout<<"Enter Full Name: ";
    cin.ignore(10000, '\n');
    getline(cin, name);

	userName:
    cout<<"Create Username: ";
    cin>>username;

 	ifstream userFile("users.txt");

    while (userFile >> savedUsername >> savedPassword)
    {
        if (savedUsername == username)
        {
            cout<<"\nUsername already exists!\nChoose other username.\n";
            userFile.close();
            goto userName;
        }
    }
    userFile.close();

    cout<<"Create Password: ";
    cin>>password;

    do
    {
        cout<<"Enter Mobile Number: ";
        cin>>mobile;

        if (!validMobile(mobile))
        {
            cout<<"Invalid mobile number!\n";
            cout<<"It must be 10 digits and start with 98 or 97.\n";
        }
    } while (!validMobile(mobile));

    do
    {
        cout<<"Enter Email: ";
        cin>>email;

        if (!validEmail(email))
        {
            cout<<"Invalid email!\n";
            cout<<"Email must contain @ and a dot after @.\n";
        }
    } while (!validEmail(email));

    ofstream userOut("users.txt", ios::app);
    userOut << username << " " << password << endl;
    userOut.close();

    ofstream profileOut("profiles.txt", ios::app);
    profileOut << username << "|" << name << "|"
               << mobile << "|" << email << endl;
    profileOut.close();
	system("cls");
    cout<<"\nRegistration Successful!\n";
    cout<<"Welcome, " << name << "!\n";
}
};
class Login{
	public:
	string username, password;
	string savedUsername, savedPassword;
	
	
	void regesterUser(){
    cout<<"\n========== USER REGISTRATION ==========\n";
    cout<<"Create Username: ";
    cin>>username;
    cout<<"Create Password: ";
    cin>>password;
 
    ofstream file("users.txt", ios::app);
     if (!file)
    {
        cout<<"Error opening file!\n";
        return;
    }
    file << username << " " << password << endl;
    file.close();
    cout<<"\nRegistration Successful!\n";
    
}

bool userLogin()
{

    cout<<"\n========== USER LOGIN ==========\n";

    cout<<"Username: ";
    cin>>username;

    cout<<"Password: ";
    cin>>password;
    ifstream file("users.txt");
    if (!file)
    {
    	 system("cls");
        cout<<"\nNo users registered yet!\n";
        return false;
    }

    while (file >> savedUsername >> savedPassword)
    {
        if (username == savedUsername &&
            password == savedPassword)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
bool adminLogin()
{

	system("cls");
    cout<<"\n========== ADMIN LOGIN ==========\n";

    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    if (username == "admin" && password == "admin")
    {
        return true;
    }

    return false;
}

};
class Vehicle{
	protected :
    int vehicleID = 1001;
    int lastID,id;
    string search;
    string name;
    string type;
    string model;
    string numberPlate;
    int rentPerDay;
    string status;

	public:
void addVehicle()
{

    ifstream readFile("vehicles.txt");

    while (readFile >> lastID)
    {
    
        string temp;
        getline(readFile, temp);

        vehicleID = lastID + 1;
    }
	system("cls");
    cout<<"\n========== ADD VEHICLE ==========\n";

    cout<<"Vehicle ID: " << vehicleID << endl;

    cout<<"Enter Vehicle Name: ";
    cin>>name;

    cout<<"Enter Vehicle Type: ";
    cin>>type;

    cout<<"Enter Model: ";
    cin>>model;

    cout<<"Enter Number Plate: ";
    cin.ignore();
    getline(cin,numberPlate);

    cout<<"Enter Rent Per Day: ";
    cin>>rentPerDay;

    ofstream file("vehicles.txt", ios::app);

    if (!file)
    {
        cout<<"\nError opening file!\n";
        return;
    }

    file << vehicleID << " "
         << name << " "
         << type << " "
         << model << " "
         << numberPlate << " "
         << rentPerDay << " "
         << "Available" << endl;

    file.close();
	system("cls");
    cout<<"\nVehicle added successfully!";
    cout<<"\nVehicle ID: " << vehicleID << endl;
}
void viewAllVehicles()
{
    ifstream file("vehicles.txt");

    if (!file)
    {
        cout<<"\nNo vehicle data found!\n";
        return;
    }
  
    system("cls");

    cout<<"\n==============================================================\n";
    cout<<"                  ALL VEHICLES\n";
    cout<<"==============================================================\n";

    cout<<"ID\tName\tType\tModel\tNumber Plate\tRent\tStatus\n";
    cout<<"--------------------------------------------------------------\n";

    bool found = false;

    while (file >>vehicleID>>name>>type>>model>>numberPlate>>rentPerDay>>status)
    {
        found = true;
        cout<<vehicleID<<"\t"<<name<<"\t"<<type<<"\t"<<model<<"\t"<<numberPlate<<"\t"<<rentPerDay<<"\t"<<status<<endl;
    }
    file.close();
    if (!found)
    {
        cout<<"No vehicles available.\n";
    }
    cout<<"==============================================================\n";
}

void updateVehicle()
{
  

    bool found = false;
    cout<<"\n========== UPDATE VEHICLE ==========\n";
    cout<<"Enter Vehicle ID: ";
    cin>>id;

    ifstream inFile("vehicles.txt");
    if (!inFile)
    {
        cout<<"\nVehicle file not found!\n";
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile)
    {
        cout<<"\nError creating temporary file!\n";
        inFile.close();
        return;
    }

    while (inFile>>vehicleID>>name>>type>>model>>numberPlate>>rentPerDay>>status)
    {
        if (vehicleID == id)
        {
            found = true;

            cout<<"\nCurrent Vehicle Details:\n";
            cout<<"Name: " << name << endl;
            cout<<"Type: " << type << endl;
            cout<<"Model: " << model << endl;
            cout<<"Number Plate: " << numberPlate << endl;
            cout<<"Rent Per Day: " << rentPerDay << endl;

            cout<<"\nEnter New Details:\n";
            cout<<"Enter Name: ";
            cin>>name;
            cout<<"Enter Type: ";
            cin>>type;
            cout<<"Enter Model: ";
            cin>>model;
            cout<<"Enter Number Plate: ";
            cin>>numberPlate;
            cout<<"Enter Rent Per Day: ";
            cin>>rentPerDay;
        }

        outFile << vehicleID << " "<<name <<" "<<type<<" "<<model<<" "<<numberPlate<<" "<<rentPerDay<< " "<<status<<endl;
    }

    inFile.close();
    outFile.close();

    if (found)
    {
        remove("vehicles.txt");
        if (rename("temp.txt", "vehicles.txt") == 0)
        {
        	system("cls");
            cout<<"\nVehicle updated successfully!\n";
        }
        else
        {
            cout<<"\nError replacing vehicle file!\n";
        }
    }
    else
    {
    	system("cls");
        remove("temp.txt");
        cout<<"\nVehicle ID not found!\n";
    }
}
void deleteVehicle()
{

    bool found = false;

    cout<<"\n========== DELETE VEHICLE ==========\n";
    cout<<"Enter Vehicle ID: ";
    cin>>id;

    ifstream inFile("vehicles.txt");

    if (!inFile)
    {
        cout<<"\nVehicle file not found!\n";
        return;
    }

    ofstream outFile("temp.txt");

    if (!outFile)
    {
        cout<<"\nError creating temporary file!\n";
        inFile.close();
        return;
    }

    while (inFile >> vehicleID >> name >> type
                  >> model >> numberPlate
                  >> rentPerDay >> status)
    {
        if (vehicleID == id)
        {
            found = true;

            cout<<"\nVehicle found!\n";
            cout<<"Vehicle ID: " << vehicleID << endl;
            cout<<"Name: " << name << endl;
            cout<<"Type: " << type << endl;

            cout<<"\nVehicle deleted successfully!\n";
        }
        else
        {
            outFile << vehicleID << " "
                    << name << " "
                    << type << " "
                    << model << " "
                    << numberPlate << " "
                    << rentPerDay << " "
                    << status << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found)
    {
        if (remove("vehicles.txt") == 0)
        {
            if (rename("temp.txt", "vehicles.txt") != 0)
            {
                cout<<"Error replacing vehicle file!\n";
            }
        }
        else
        {
            cout<<"Error deleting original file!\n";
        }
    }
    else
    {
        remove("temp.txt");
        system("cls");
        cout<<"\nVehicle ID not found!\n";
    }
}

void rentVehicle(string username)
{

    string mobile, email, line;
    bool userFound = false;

    ifstream profileFile("profiles.txt");

    while (getline(profileFile, line))
    {
        stringstream ss(line);
        string uname;

        getline(ss, uname, '|');
        getline(ss, name, '|');
        getline(ss, mobile, '|');
        getline(ss, email, '|');

        if (uname == username)
        {
            userFound = true;
            break;
        }
    }
    profileFile.close();

    if (!userFound)
    {
        cout << "User profile not found!\n";
        return;
    }

    string searchId;
    cout << "\n========== RENT VEHICLE ==========\n";
    cout << "Enter Vehicle ID: ";
    cin >> searchId;

    ifstream vehicleFile("vehicles.txt");

    if (!vehicleFile)
    {
        cout << "Unable to open vehicles.txt!\n";
        return;
    }

    string id, vname, type, model, plate, status;
    int rate = 0;
    bool found = false;
    bool available = false;

    while (vehicleFile >> id >> vname >> type
                       >> model >> plate >> rate >> status)
    {
        if (id == searchId)
        {
            found = true;

            if (status == "Available")
                available = true;

            break;
        }
    }
    vehicleFile.close();

    if (!found)
    {
        cout << "Vehicle not found!\n";
        return;
    }

    if (!available)
    {
        cout << "Vehicle is already rented!\n";
        return;
    }

    ifstream activeCheck("active_rentals.txt");

    string record;
    while (getline(activeCheck, record))
    {
        stringstream ss(record);
        string u, vid;

        getline(ss, u, '|');
        getline(ss, vid, '|');

        if (u == username)
        {
            cout << "You already have an active rental.\n";
            activeCheck.close();
            return;
        }
    }
    activeCheck.close();

    time_t startTime = time(nullptr);
    string startDate = ctime(&startTime);

    if (!startDate.empty() && startDate.back() == '\n')
        startDate.pop_back();

    ofstream activeFile("active_rentals.txt", ios::app);

    if (!activeFile)
    {
        cout << "Unable to save active rental!\n";
        return;
    }

    activeFile << username << '|'
               << id << '|'
               << name << '|'
               << mobile << '|'
               << email << '|'
               << vname << '|'
               << type << '|'
               << model << '|'
               << plate << '|'
             //  << setprecision(12)
			  << rate << '|'
               << static_cast<long long>(startTime) << '|'
               << startDate << '\n';

    activeFile.close();

    ifstream in("vehicles.txt");
    ofstream out("vehicles_temp.txt");

    if (!in || !out)
    {
        cout << "Unable to update vehicle status!\n";
        return;
    }

    while (in >> id >> vname >> type
               >> model >> plate >> rate >> status)
    {
        if (id == searchId)
            status = "Rented";

        out << id << ' ' << vname << ' ' << type
            << ' ' << model << ' ' << plate
            << ' ' << rate << ' ' << status << '\n';
    }

    in.close();
    out.close();

    if (remove("vehicles.txt") != 0 ||
        rename("vehicles_temp.txt", "vehicles.txt") != 0)
    {
        cout << "Error updating vehicle status!\n";
        return;
    }

    cout << "\nVehicle rented successfully!\n";
    cout << "Username: " << username << '\n';
    cout << "Vehicle ID: " << searchId << '\n';
    cout << "Rent per day: Rs. " << fixed
		 << rate << '\n';
    cout << "Rent start: " << startDate << '\n';
}

void returnVehicle(string username)
{
    system("cls");

    string searchId;
    cout << "\n========== RETURN VEHICLE ==========\n";
    cout << "Enter Vehicle ID: ";
    cin >> searchId;
    
    ifstream activeFile("active_rentals.txt");

    if (!activeFile)
    {
        cout << "No active rentals found!\n";
        return;
    }

    ofstream activeTemp("active_rentals_temp.txt");

    if (!activeTemp)
    {
        cout << "Unable to create temporary file!\n";
        activeFile.close();
        return;
    }

    string line;
    bool rentalFound = false;

    string uname, id, name, mobile, email;
    string vname, type, model, plate, startDate;
    int rate = 0;
    long long startEpoch = 0;

    while (getline(activeFile, line))
    {
        stringstream ss(line);

        string u, vid, nm, mob, em;
        string vn, vt, vm, vp, rateText, epochText, dateText;

        getline(ss, u, '|');
        getline(ss, vid, '|');
        getline(ss, nm, '|');
        getline(ss, mob, '|');
        getline(ss, em, '|');
        getline(ss, vn, '|');
        getline(ss, vt, '|');
        getline(ss, vm, '|');
        getline(ss, vp, '|');
        getline(ss, rateText, '|');
        getline(ss, epochText, '|');
        getline(ss, dateText);

        if (u == username && vid == searchId)
        {
            rentalFound = true;

            uname = u;
            id = vid;
            name = nm;
            mobile = mob;
            email = em;
            vname = vn;
            type = vt;
            model = vm;
            plate = vp;
            rate = stod(rateText);
            startEpoch = stoll(epochText);
            startDate = dateText;

        }
        else
        {
            activeTemp << line << '\n';
        }
    }

    activeFile.close();
    activeTemp.close();

    if (!rentalFound)
    {
        remove("active_rentals_temp.txt");
        cout << "\nNo active rental for this vehicle "
             << "was found under your username!\n";
        return;
    }

    time_t returnEpoch = time(nullptr);

    if (returnEpoch < startEpoch)
    {
        remove("active_rentals_temp.txt");
        cout << "Invalid rental time!\n";
        return;
    }

    long long secondsUsed =
        static_cast<long long>(returnEpoch) - startEpoch;

    int days = static_cast<int>(
        (secondsUsed + 86400 - 1) / 86400
    );

    if (days < 1)
        days = 1;

    int totalBill = rate * days;

    time_t returnTime = static_cast<time_t>(returnEpoch);
    string returnDate = ctime(&returnTime);

    if (!returnDate.empty() && returnDate.back() == '\n')
        returnDate.pop_back();

    ifstream vehicleFile("vehicles.txt");
    ofstream vehicleTemp("vehicles_temp.txt");

    if (!vehicleFile || !vehicleTemp)
    {
        cout << "Unable to update vehicle file!\n";
        return;
    }

    string vid, vn, vt, vm, vp, st;
    int dailyRate;
    bool vehicleFound = false;

    while (vehicleFile >> vid >> vn >> vt
                       >> vm >> vp >> dailyRate >> st)
    {
        if (vid == searchId && st == "Rented")
        {
            vehicleFound = true;
            st = "Available";
        }

        vehicleTemp << vid << ' ' << vn << ' '
                    << vt << ' ' << vm << ' '
                    << vp << ' ' << dailyRate
                    << ' ' << st << '\n';
    }

    vehicleFile.close();
    vehicleTemp.close();

    if (!vehicleFound)
    {
        remove("vehicles_temp.txt");
        remove("active_rentals_temp.txt");
        cout << "Vehicle status is invalid!\n";
        return;
    }

    ofstream billFile("bills.txt", ios::app);

    if (!billFile)
    {
        remove("vehicles_temp.txt");
        remove("active_rentals_temp.txt");
        cout << "Unable to save bill!\n";
        return;
    }

    billFile << "\n========== RENTAL BILL ==========\n";
    billFile << "Username       : " << uname << '\n';
    billFile << "Full Name      : " << name << '\n';
    billFile << "Mobile         : " << mobile << '\n';
    billFile << "Email          : " << email << '\n';
    billFile << "Vehicle ID     : " << id << '\n';
    billFile << "Vehicle Name   : " << vname << '\n';
    billFile << "Vehicle Type   : " << type << '\n';
    billFile << "Vehicle Model  : " << model << '\n';
    billFile << "Number Plate   : " << plate << '\n';
    billFile << "Rent Start     : " << startDate << '\n';
    billFile << "Return Date    : " << returnDate << '\n';
    billFile << "Rental Days    : " << days << '\n';
    billFile << fixed ;
    billFile << "Rate Per Day   : Rs. " << rate << '\n';
    billFile << "Total Bill     : Rs. " << totalBill << '\n';
    billFile << "=================================\n";
    billFile.close();

    if (remove("vehicles.txt") != 0 ||
        rename("vehicles_temp.txt", "vehicles.txt") != 0)
    {
        cout << "Error updating vehicle status!\n";
        cout << "Please check the files before retrying.\n";
        return;
    }

    if (remove("active_rentals.txt") != 0 ||
        rename("active_rentals_temp.txt",
               "active_rentals.txt") != 0)
    {
        cout << "Warning: active rental file was not updated!\n";
        return;
    }

    cout << "\n========== RENTAL BILL ==========\n";
    cout << "Username       : " << uname << '\n';
    cout << "Full Name      : " << name << '\n';
    cout << "Mobile         : " << mobile << '\n';
    cout << "Email          : " << email << '\n';
    cout << "Vehicle ID     : " << id << '\n';
    cout << "Vehicle Name   : " << vname << '\n';
    cout << "Vehicle Type   : " << type << '\n';
    cout << "Vehicle Model  : " << model << '\n';
    cout << "Number Plate   : " << plate << '\n';
    cout << "Rent Start     : " << startDate << '\n';
    cout << "Return Date    : " << returnDate << '\n';
    cout << "Rental Days    : " << days << '\n';
    cout << fixed ;
    cout << "Rate Per Day   : Rs. " << rate << '\n';
    cout << "Total Bill     : Rs. " << totalBill << '\n';
    cout << "=================================\n";
}


void historyCheck()
{
    ifstream file("history.txt");

    string username, action, vehicleID, date;

    bool found = false;

    cout<<"\n========== RENTAL HISTORY ==========\n";

    while (file >> username >> vehicleID >> action >> date)
    {
        found = true;

        cout<<"Username   : " << username << endl;
        cout<<"Vehicle ID : " << vehicleID << endl;
        cout<<"Action     : " << action << endl;
        cout<<"Date       : " << date << endl;
        cout<<"------------------------------------\n";
    }

    file.close();

    if (!found)
    {
        cout<<"No rental history found!" << endl;
    }
}
void searchVehicle()
{
	bool found = false;

    cout << "\n========== SEARCH VEHICLE ==========\n";
    cout << "Enter Vehicle ID, Name, Type or Model: ";
    cin >> search;

    ifstream file("vehicles.txt");

    if (!file)
    {
        cout << "Unable to open vehicle file!" << endl;
        return;
    }

 //   int vehicleID, model, rentPerDay;
 //   string name, type, numberPlate, status;
	int model;
    while (file >> vehicleID >> name >> type >> model
                >> numberPlate >> rentPerDay >> status)
    {
        string idStr = to_string(vehicleID);
        string modelStr = to_string(model);

        if (search == idStr ||
            search == name ||
            search == type ||
            search == modelStr)
        {
            found = true;

            cout << "\n========== VEHICLE DETAILS ==========\n";
            cout << "Vehicle ID    : " << vehicleID << endl;
            cout << "Vehicle Name  : " << name << endl;
            cout << "Vehicle Type  : " << type << endl;
            cout << "Model         : " << model << endl;
            cout << "Number Plate  : " << numberPlate << endl;
            cout << "Rent Per Day  : Rs. " << rentPerDay << endl;
            cout << "Status        : " << status << endl;
            cout << "=====================================\n";
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nVehicle not found!" << endl;
    }
}

void viewUserBills()
{
    system("cls");

    string searchUsername;
    string line;
    bool found = false;
    bool matchingBill = false;

    cout << "\n========== VIEW USER BILLS ==========\n";
    cout << "Enter Username: ";
    cin >> searchUsername;

    ifstream file("bills.txt");

    if (!file)
    {
        cout << "\nUnable to open bills.txt!\n";
        return;
    }

    while (getline(file, line))
    {
        if (line.find("Username       : ") == 0)
        {
            string username =
                line.substr(string("Username       : ").length());

            matchingBill = (username == searchUsername);
        }

        if (matchingBill)
        {
            cout << line << endl;
            found = true;
        }

        if (matchingBill &&
            line.find("=================================") == 0)
        {
            cout << endl;
            matchingBill = false;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nNo bills found for username: "
             << searchUsername << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}



};


int main()
{
	Login login;
	Vehicle vehicle;
	Check check;
	int choice;
	login:
	cout<<"\n==========================================";
    cout<<"\n     VEHICLE RENTAL MANAGEMENT SYSTEM";
    cout<<"\n==========================================";
    cout<<"\n\n1. Admin Login";
    cout<<"\n2. User Registration";
 	cout<<"\n3. User Login";
	cout<<"\n4. Exit";
	cout<<"\n\nEnter your choice: ";
	cin>>choice;
	system("cls");
        if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout<<"Invalid Input";
			goto login;
        }
        switch(choice){
    case 1:{
        	if(login.adminLogin())
        	{
        		
				system("cls");
        		system("color 02");
        		cout<<"\nAdmin Login Successful!\n";
				system("color 0F");
				Admin_menu:
                cout<<"\n===== ADMIN MENU =====\n";
                cout<<"1. Add Vehicle\n";
                cout<<"2. View Vehicle\n";
                cout<<"3. Update Vehicle\n";
                cout<<"4. Delete Vehicle\n";
                cout<<"5. User Bill\n";
                cout<<"6. log Out!!\n";
                int casechoice;
                cout<<"Enter your choice ";
                cin>>casechoice;
              
			    if(cin.fail())
				{
					system("cls");
        			cin.clear();
	        		cin.ignore(1000,'\n');
    	    		cout<<"Invalid Input";
        			goto Admin_menu;
            	}
            	switch(casechoice){
                	case 1:{
                		vehicle.addVehicle();
						goto Admin_menu;
					}
					case 2:{
						vehicle.viewAllVehicles();
						goto Admin_menu;
					}
					case 3:{
						vehicle.viewAllVehicles();
						vehicle.updateVehicle();
						goto Admin_menu;
					}
					case 4: {
						vehicle.viewAllVehicles();
						vehicle.deleteVehicle();	
						goto Admin_menu;
					}
					case 5 : {
						vehicle.viewUserBills();
						goto Admin_menu;
					}
					case 6 :{
						system("cls");
						cout<<"\n Logout sucessfully\n  Thank You!!";
						goto login;
					}
					default	:
					{
						system("cls");
						cout<<"\nInvalid choice !!\n";
						cin.ignore(1000,'\n');
						cin.get();
        				goto Admin_menu;
					}
			}
		}
		else

       	{
       		system("cls");
        	cout<<"\nInvalid Username or Password!\n";
        	cout<<"\nTry again !!";
        	goto login;
        }
        
        break;
        
    }
    case 2:{
    		check.registerUser();
			goto login;	
    	
		}
	case 3:{
			USERLOGIN:
			if(login.userLogin()){
				system("cls");
					
				usermenu:
                cout<<"\n===== USER MENU =====\n";
                cout<<"1. View Vehicles\n";
                cout<<"2. Search Vehicle\n";
                cout<<"3. Rent Vehicle\n";
                cout<<"4. Return Vehicle\n";
                cout<<"5. Log Out !! \n";
                int userchoice;
                cout<<"Enter your choice ";
                cin>>userchoice;
	        if(cin.fail())
			{
				cin.clear();
				cin.ignore(1000,'\n');
				cout<<"Invalid Input";
				goto login;
        	}
        	switch(userchoice)
        	{
        		case 1:{
        			vehicle.viewAllVehicles();
        			goto usermenu;
				}
				case 2:{
					system("cls");
					vehicle.searchVehicle();
					goto usermenu;
				}
				case 3:{
        			vehicle.viewAllVehicles();
					vehicle.rentVehicle(login.username);
					goto usermenu;
				}
				case 4:{
					vehicle.returnVehicle(login.username);
					goto usermenu;
					
				}
				case 5:{
					system("cls");
					goto login;
					break;
				}
				default	:
					{
						system("cls");
						cout<<"\nInvalid choice !!\n";
						cin.ignore(1000,'\n');
						cin.get();
        				goto Admin_menu;
					}
	
            }
	}
	else
       	{
       		system("cls");
        	cout<<"\nInvalid Username or Password!\n";
        	cout<<"\nTry again !!";
        	goto USERLOGIN;
        }
        break;
}
	case 4:{
		system("cls");
		cout<<"Bye Bye!!";
		break;
	}
	default	:
			{
			cout<<"\nInvalid choice !!\n";
			cin.ignore(1000,'\n');
			cin.get();
			goto login;
			}
}//ending of switch
        return 0;
}











