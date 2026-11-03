#include<iostream>
#include<iomanip>
#include<cctype>
using namespace std;
string chuanhoa(string s){
	for(int i=0;i<s.length();i++){
		s[i]=tolower((unsigned char)s[i]);
	}
	return s;
}
class phuongtien{
	private:
		int maphuongtien;
		string loaixe;
		int giovaobai;
		int thoigiando;
		double phidoxe;
		bool dangdo;
	public:
		phuongtien(){
			maphuongtien=0;
			loaixe="";
			giovaobai=0;
			thoigiando=0;
			phidoxe=0.0;
			dangdo=false;
		}
		phuongtien(int ma, string loai, int gio, int thoigian){
			maphuongtien=ma;
			loaixe=loai;
			giovaobai=gio;
			thoigiando=thoigian;
			phidoxe=0.0;
			dangdo=true;
			calculateFee();
		}
		int getmaphuongtien() const{
			return maphuongtien;
		}
		void setmaphuongtien(int ma){
			maphuongtien=ma;
		}
		string getloaixe() const{
			return loaixe;
		}
		void setloaixe(string& loai){
			loaixe=loai;
		}
		int getgiovaobai() const{
			return giovaobai;
		}
		void setgiovaobai(int gio){
			giovaobai=gio;
		}
		int getthoigiando() const {
			return thoigiando;
		}
		void setthoigiando(int thoigian){
			thoigiando=thoigian;
			calculateFee();
		}
		double getphidoxe() const{
			return phidoxe;
		}
		bool getdangdo() const {
			return dangdo;
		}
		void setdangdo(bool status) {
			dangdo=status;
		}
		void calculateFee(){
			if(!dangdo){
				phidoxe=0.0;
				return;
			}
			double rate =0.0;
			if(chuanhoa(loaixe)=="car"){
				rate =6.0;
			}
			else if(chuanhoa(loaixe)=="motorcycle"){
				rate = 4.0;
			}
			else if(chuanhoa(loaixe)=="bicycle"){
				rate=2.0;
			}
			else{
				cout<<"loai xe khong hop le";
				return;
			}
			double phi2giodau=0.0;
			double giothu3=0.9;
			if((giovaobai>=6 && giovaobai<=10 ) || (giovaobai>=15 && giovaobai<=19)){
				phi2giodau=rate+0.3*rate;
				phidoxe=phi2giodau+(thoigiando-2)*rate*0.9;
			}
			else{
				phi2giodau=rate-0.05*rate;
				phidoxe=phi2giodau+(thoigiando-2)*rate*rate;
			}
		}
		void display(){
			cout<<"Ma xe"<<maxe<<endl;
			cout<<"Loai xe"<<loaixe<<endl;
			cout<<"Gio vao bai"<<gio<<endl;
			cout<<"Thoi gian do xe"<<thoigiando<<endl;
			
		}
};
