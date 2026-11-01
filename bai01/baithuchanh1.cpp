#include<iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<cctype>
using namespace std;
string toLower(string s) {
	for (int i = 0;i < s.length();i++) {
		s[i] = tolower((unsigned char)s[i]);
	}
	return s;
}
bool ktr(const string& type) {
	string lower = toLower(type);
	return (lower == "car" || lower == "motorcycle" || lower == "bicycle");
}
class Vehicle {
private:
	int vehicleID;
	string vehicleType;
	int entryTime;
	int parkingDuration;
	double parkingFee;
	bool isOccupied;

public:
	Vehicle()
		: vehicleID(-1), vehicleType(""), entryTime(0), parkingDuration(0), parkingFee(0.0), isOccupied(false) {
	}
	Vehicle(int id, string type, int entry, int duration)
		: vehicleID(id), vehicleType(type), entryTime(entry), parkingDuration(duration), parkingFee(0.0), isOccupied(true) {
		calculateFee();
	}
	int getvehicleID() const {
		return vehicleID;
	}
	void setvehicleID(int id) {
		vehicleID = id;
	}
	string getvehicleType() const {
		return vehicleType;
	}
	void setvehicleType(const string& type) {
		vehicleType = type;
		calculateFee();
	}
	int getentryTime()const {
		return entryTime;
	}
	void setentryTime(int entry) {
		entryTime = entry;
		calculateFee();
	}
	int getparkingDuration()const {
		return parkingDuration;
	}
	void setparkingDuration(int duration) {
		parkingDuration = duration;
		calculateFee();
	}
	double getparkingFee() const {
		return parkingFee;
	}
	bool getisOccupied() const {
		return isOccupied;
	}
	void setisOccupied(bool status) {
		isOccupied = status;
	}
	void calculateFee() {
		if (!isOccupied) {
			parkingFee = 0.0;
			return;
		}
		double rate = 0.0;
		string typeLower = toLower(vehicleType);
		if (typeLower == "car") {
			rate = 6.0;
		}
		else if (typeLower == "motorcycle") {
			rate = 4.0;
		}
		else if (typeLower == "bicycle") {
			rate = 2.0;
		}
		bool isPeakHour = (entryTime >= 6 && entryTime < 10) || (entryTime >= 15 && entryTime < 19);
		if (isPeakHour) {
			if (parkingDuration <= 2)
				parkingFee = rate * parkingDuration * 1.3;
			else
				parkingFee = (2 * rate * 1.3) + ((parkingDuration - 2) * rate * 0.9);
		}
		else {
			if (parkingDuration <= 2)
				parkingFee = rate * parkingDuration * 0.95;
			else
				parkingFee = (2 * rate * 0.95) + ((parkingDuration - 2) * rate * 0.9);
		}
	}
	void display() const {
		cout << "ID xe: " << vehicleID << endl;
		cout << "Loai xe: " << vehicleType << endl;
		cout << "Thoi gian nhap: " << entryTime << endl;
		cout << "Thoi gian dong bo: " << parkingDuration << endl;
		cout << fixed << setprecision(2);
		cout << "Phi dong bo: $" << parkingFee << endl;
		cout << "Dang su dung: " << (isOccupied ? "Co" : "Khong") << endl;
	}
};
class ParkingLot {
private:
	int parkID;
	char size;
	Vehicle vehicle1;
	Vehicle vehicle2;
	Vehicle vehicle3;
	bool hasVehicle1;
	bool hasVehicle2;
	bool hasVehicle3;
public:
	ParkingLot()
		: parkID(-1), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {
	}
	ParkingLot(int id, char s)
		: parkID(id), size(s), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {
	}
	int getparkID() const {
		return parkID;
	}
	void setparkID(int id) {
		parkID = id;
	}
	char getsize() const {
		return size;
	}
	void setsize(char s) {
		size = s;
	}
	int getMaxVehicles() const {
		if (size == 'S') return 1;
		else if (size == 'M') return 2;
		else if (size == 'L') return 3;
		else return 0;
	}
	int getcurrentcount() const {
		int count = 0;
		if (hasVehicle1) count++;
		if (hasVehicle2) count++;
		if (hasVehicle3) count++;
		return count;
	}
	bool isFull() const {
		return getcurrentcount() >= getMaxVehicles();
	}
	bool containsVehicle(int id) const {
        return (hasVehicle1 && vehicle1.getvehicleID() == id) ||
               (hasVehicle2 && vehicle2.getvehicleID() == id) ||
               (hasVehicle3 && vehicle3.getvehicleID() == id);
    }
	bool addVehicle(const Vehicle& v) {
		if (isFull()) {
			cout << "Bai do xe da day." << endl;
			return false;
		}
		if (!hasVehicle1) {
			vehicle1 = v;
			hasVehicle1 = true;
			return true;
		}
		else if (!hasVehicle2) {
			vehicle2 = v;
			hasVehicle2 = true;
			return true;
		}
		else if (!hasVehicle3) {
			vehicle3 = v;
			hasVehicle3 = true;
			return true;
		}
		return false;
	}
	bool removeVehicle(int vehicleID) {
		if (hasVehicle1 && vehicle1.getvehicleID() == vehicleID) {
			hasVehicle1 = false;
			return true;
		}
		else if (hasVehicle2 && vehicle2.getvehicleID() == vehicleID) {
			hasVehicle2 = false;
			return true;
		}
		else if (hasVehicle3 && vehicle3.getvehicleID() == vehicleID) {
			hasVehicle3 = false;
			return true;
		}
		else cout << "Khong tim thay xe voi ID: " << vehicleID << endl;
		return false;
	}
	void displayLotInfo() const {
		cout << "ID bai do xe: " << parkID << endl;
		cout << "Kich thuoc bai do xe: " << size << endl;
		cout << "So luong xe hien tai: " << getcurrentcount() << "/" << getMaxVehicles() << endl;
		if (hasVehicle1) {
			cout << "Thong tin xe 1:" << endl;
			vehicle1.display();
		}
		if (hasVehicle2) {
			cout << "Thong tin xe 2:" << endl;
			vehicle2.display();
		}
		if (hasVehicle3) {
			cout << "Thong tin xe 3:" << endl;
			vehicle3.display();
		}
		if(getcurrentcount()==0){
			cout<<"Bai Trong"<<endl;
	}
	}
	bool displayVehiclesOfType(const std::string& type) const {
		string targetType = toLower(type);
		bool found = false;
		if (hasVehicle1 && toLower(vehicle1.getvehicleType()) == targetType) {
			cout << "  - Bai [" << parkID << "]: ";
			vehicle1.display();
			found = true;
		}
		if (hasVehicle2 && toLower(vehicle2.getvehicleType()) == targetType) {
			cout << "  - Bai [" << parkID << "]: ";
			vehicle2.display();
			found = true;
		}
		if (hasVehicle3 && toLower(vehicle3.getvehicleType()) == targetType) {
			cout << "  - Bai [" << parkID << "]: ";
			vehicle3.display();
			found = true;
		}
		return found;
	}
	void collectFeeReport(
	double& cartotal,
	double& motortotal,
	double& biketotal,
	int& carcount,
	int& motorcount, 
	int& bikecount
	) const {
		if (hasVehicle1) {
			string type = toLower(vehicle1.getvehicleType());

			if (type == "car") {
				cartotal += vehicle1.getparkingFee();
				carcount++;
			}
			else if (type == "motorcycle") {
				motortotal += vehicle1.getparkingFee();
				motorcount++;
			}
			else if (type == "bicycle") {
				biketotal+=vehicle1.getparkingFee();
				bikecount++;
			}
		}
		if (hasVehicle2) {
			string type = toLower(vehicle2.getvehicleType());

			if (type == "car") {
				cartotal += vehicle2.getparkingFee();
				carcount++;
			}
			else if (type == "motorcycle") {
				motortotal += vehicle2.getparkingFee();
				motorcount++;
			}
			else if (type == "bicycle") {
				biketotal+=vehicle2.getparkingFee();
				bikecount++;
			}
		}
		if (hasVehicle3) {
			string type = toLower(vehicle3.getvehicleType());

			if (type == "car") {
				cartotal += vehicle3.getparkingFee();
				carcount++;
			}
			else if (type == "motorcycle") {
				motortotal += vehicle3.getparkingFee();
				motorcount++;
			}
			else if (type == "bicycle") {
				biketotal+=vehicle3.getparkingFee();
				bikecount++;
			}
		}
	}
};
class SystemInterface {
private:
	ParkingLot parkingLot1;
	ParkingLot parkingLot2;
	ParkingLot parkingLot3;
	bool hasLot1;
	bool hasLot2;
	bool hasLot3;
public:
	SystemInterface()
		: hasLot1(false), hasLot2(false), hasLot3(false) {
	}
	bool isLotIDExists(int id) const {
		return (hasLot1 && parkingLot1.getparkID() == id) ||
			(hasLot2 && parkingLot2.getparkID() == id) ||
			(hasLot3 && parkingLot3.getparkID() == id);
	}
		bool isVehicleIDExists(int id) const {
		return (hasLot1 && parkingLot1.containsVehicle(id)) ||
			(hasLot2 && parkingLot2.containsVehicle(id)) ||
			(hasLot3 && parkingLot3.containsVehicle(id));
	}
	void createParkingLot() {
		int id;
		char size;
		cout << "Nhap ID bai do xe: ";
		cin >> id;
		cout << "Nhap kich thuoc bai do xe (S, M, L): ";
		cin >> size;
		size = toupper(size);
		if (size != 'S' && size != 'M' && size != 'L') {
			cout << "Kich thuoc khong hop le. Vui long nhap lai." << endl;
			return;
		}
		if (!hasLot1) {
			parkingLot1 = ParkingLot(id, size);
			hasLot1 = true;
			cout << "Tao bai do xe thanh cong." << endl;
		}
		else if (!hasLot2) {
			parkingLot2 = ParkingLot(id, size);
			hasLot2 = true;
			cout << "Tao bai do xe thanh cong." << endl;
		}
		else if (!hasLot3) {
			parkingLot3 = ParkingLot(id, size);
			hasLot3 = true;
			cout << "Tao bai do xe thanh cong." << endl;
		}
		else {
			cout << "Da dat day so luong bai do xe toi da." << endl;
		}
	}
	void addVehicleToLot() {
		if (!hasLot1 && !hasLot2 && !hasLot3) {
			cout << "Chua co bai do xe nao duoc tao." << endl;
			return;
		}
		int vID, entryTime, duration;
		string type;
		cout << "nhap ma phuong tien: ";
		cin >> vID;
		cout << "nhap loai xe (car, motorcycle, bicycle): ";
		cin >> type;
		if(!ktr(type)){
			return;
		}
		cout << "nhap thoi gian nhap (0-23): ";
		cin >> entryTime;
		if(entryTime<0 || entryTime>23){return;}
		cout << "nhap thoi gian do bo (gio): ";
		cin >> duration;
		if(duration<0 || duration>23){return;}
		Vehicle newVehicle(vID, type, entryTime, duration);
		if (hasLot1 && !parkingLot1.isFull()) {
			parkingLot1.addVehicle(newVehicle);
			cout << "Them xe vao bai do xe 1 thanh cong." << endl;
			cout << "phi do xe: " << fixed << setprecision(2) << newVehicle.getparkingFee() << endl;
		}
		else if (hasLot2 && !parkingLot2.isFull()) {
			parkingLot2.addVehicle(newVehicle);
			cout << "Them xe vao bai do xe 2 thanh cong." << endl;
			cout << "phi do xe: " << fixed << setprecision(2) << newVehicle.getparkingFee() << endl;
		}
		else if (hasLot3 && !parkingLot3.isFull()) {
			parkingLot3.addVehicle(newVehicle);
			cout << "Them xe vao bai do xe 3 thanh cong." << endl;
			cout << "phi do xe: " << fixed << setprecision(2) << newVehicle.getparkingFee() << endl;
		}
		else cout << "Tat ca bai do xe da day hoac khong co bai do xe nao duoc tao." << endl;
	}
	void removeParkingLot() {
		int id;
		cout << "Nhap ID bai do xe can xoa: ";
		cin >> id;
		if (hasLot1 && parkingLot1.getparkID() == id) {
			hasLot1 = false;
			cout << "Xoa bai do xe 1 thanh cong." << endl;
		}
		else if (hasLot2 && parkingLot2.getparkID() == id) {
			hasLot2 = false;
			cout << "Xoa bai do xe 2 thanh cong." << endl;
		}
		else if (hasLot3 && parkingLot3.getparkID() == id) {
			hasLot3 = false;
			cout << "Xoa bai do xe 3 thanh cong." << endl;
		}
		else {
			cout << "Khong tim thay bai do xe voi ID: " << id << endl;
		}
	}
	void removeVehicleFromLot() {
		int vID;
		cout << "Nhap ma phuong tien can lay ra: ";
		cin >> vID;
		if (hasLot1 && parkingLot1.removeVehicle(vID)) {
			cout << "Lay xe ra khoi bai do xe 1 thanh cong." << endl;
		}
		else if (hasLot2 && parkingLot2.removeVehicle(vID)) {
			cout << "Lay xe ra khoi bai do xe 2 thanh cong." << endl;
		}
		else if (hasLot3 && parkingLot3.removeVehicle(vID)) {
			cout << "Lay xe ra khoi bai do xe 3 thanh cong." << endl;
		}
		else {
			cout << "Khong tim thay xe voi ID: " << vID << endl;
		}
	}
	void displayAllParkingLots() const {
		if (hasLot1) {
			cout << "Thong tin bai do xe 1:" << endl;
			parkingLot1.displayLotInfo();
		}
		if (hasLot2) {
			cout << "Thong tin bai do xe 2:" << endl;
			parkingLot2.displayLotInfo();
		}
		if (hasLot3) {
			cout << "Thong tin bai do xe 3:" << endl;
			parkingLot3.displayLotInfo();
		}
		if (!hasLot1 && !hasLot2 && !hasLot3) {
			cout << "Khong co bai do xe nao duoc tao." << endl;
		}
	}
	void displayParkingLotByID() const {
		int id;
		cout << "Nhap ID bai do xe can hien thi: ";
		cin >> id;
		if (hasLot1 && parkingLot1.getparkID() == id) {
			cout << "Thong tin bai do xe 1:" << endl;
			parkingLot1.displayLotInfo();
		}
		else if (hasLot2 && parkingLot2.getparkID() == id) {
			cout << "Thong tin bai do xe 2:" << endl;
			parkingLot2.displayLotInfo();
		}
		else if (hasLot3 && parkingLot3.getparkID() == id) {
			cout << "Thong tin bai do xe 3:" << endl;
			parkingLot3.displayLotInfo();
		}
		else {
			cout << "Khong tim thay bai do xe voi ID: " << id << endl;
		}
	}
	void displayVehicleByType() {
		string type;
		cout << "Nhap loai xe can hien thi (car, motorcycle, bicycle): ";
		cin >> type;
		if (!ktr(type)) {
			cout << "Khong hop le. Vui long nhap lai";
			return;
		}
		cout << "Danh sach cac loai xe" << type;
		if (hasLot1) parkingLot1.displayVehiclesOfType(type);
		if (hasLot2) parkingLot2.displayVehiclesOfType(type);
		if (hasLot3) parkingLot3.displayVehiclesOfType(type);
	}

	void displayFeeReport() {
		double cartotal=0.0, motortotal=0.0,biketotal=0.0;
		int carcount=0, motorcount=0, bikecount=0;
			if (hasLot1)
				parkingLot1.collectFeeReport(cartotal,motortotal,biketotal,carcount,motorcount,bikecount);

			if (hasLot2)
				parkingLot2.collectFeeReport(cartotal,motortotal,biketotal,carcount,motorcount,bikecount);

			if (hasLot3)
				parkingLot3.collectFeeReport(cartotal,motortotal,biketotal,carcount,motorcount,bikecount);
			cout << "\n===== BAO CAO PHI DO XE =====\n";
			 cout<<"Car"<<"| so luong: "<<carcount<<"| Phi TB : ";
			 if(carcount>0){
			 	cout<<fixed<<setprecision(2)<<cartotal/carcount;
			 }
			 else cout<<"chua co du lieu";
			 cout<<"\n";
			 cout<<"Motorcycle"<<"| so luong: "<<motorcount<<"| Phi TB : ";
			 if(motorcount>0){
			 	cout<<fixed<<setprecision(2)<<motortotal/motorcount;
			 }
			 else cout<<"chua co du lieu";
			 cout<<"\n";
			 cout<<"Bicycle"<<"| so luong: "<<bikecount<<"| Phi TB : ";
			 if(bikecount>0){
			 	cout<<fixed<<setprecision(2)<<biketotal/bikecount;
			 }
			 else cout<<"chua co du lieu";
			 cout<<"\n";
	};
	void runMenu() {
		int choice;
		do {
			cout << "\n===== HE THONG QUAN LY BAI DO XE =====\n";
			cout << "1. Tao bai do xe\n";
			cout << "2. Them xe vao bai do xe\n";
			cout << "3. Lay xe ra khoi bai do xe\n";
			cout << "4. Xoa bai do xe\n";
			cout << "5. Hien thi tat ca bai do xe\n";
			cout << "6. Hien thi bai do xe theo ID\n";
			cout << "7. Hien thi danh sach xe theo loai\n";
			cout << "8. Bao cao phi do xe\n";
			cout << "0. Thoat\n";
			cout << "Nhap lua chon cua ban: ";
			cin >> choice;
			switch (choice) {
			case 1:
				createParkingLot();
				break;
			case 2:
				addVehicleToLot();
				break;
			case 3:
				removeVehicleFromLot();
				break;
			case 4:
				removeParkingLot();
				break;
			case 5:
				displayAllParkingLots();
				break;
			case 6:
				displayParkingLotByID();
				break;
			case 7:
				displayVehicleByType();
				break;
			case 8:
				displayFeeReport();
				break;
			case 0:
				cout << "Thoat chuong trinh." << endl;
				break;
			default:
				cout << "Lua chon khong hop le. Vui long thu lai." << endl;
				break;
			}
		} while (choice != 0);
	}
};
int main() {
	SystemInterface systemInterface;
	systemInterface.runMenu();
	return 0;
}
