#include<iostream>
#include<cmath>

using namespace std;

int main(){

	double r=0.5,d=0.3,y=0.15,theta=2,frameR=0.2,frameG=0.2,frameB=0.0;

	for (int i = 0; i < 360; i+=theta)
	{
		cout<<(r+d/2)<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.1<<endl;
		cout<<(r+d/2)+r*cos(i*M_PI/180)<<" "<<+r*sin(i*M_PI/180)<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.2<<endl;	
		cout<<(r+d/2)+r*cos((i+theta)*M_PI/180)<<" "<<+r*sin((i+theta)*M_PI/180)<<" "<<0.0<<" "<<0.0<<" "<<0.2<<" "<<0.4<<endl;
		cout<<endl;		
	}


	for (int i = 0; i < 360; i+=theta)
	{
		cout<<-(r+d/2)<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.1<<endl;
		cout<<-(r+d/2)+r*cos(i*M_PI/180)<<" "<<+r*sin(i*M_PI/180)<<" "<<0.0<<" "<<0.0<<" "<<0.0<<" "<<0.2<<endl;	
		cout<<-(r+d/2)+r*cos((i+theta)*M_PI/180)<<" "<<+r*sin((i+theta)*M_PI/180)<<" "<<0.0<<" "<<0.0<<" "<<0.2<<" "<<0.4<<endl;
		cout<<endl;		
	}

	cout<<-d/2*1.1 <<" "<<y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<-d/2*1.1 <<" "<<-y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<d/2 <<" "<<0.0 <<" "<<0.1 <<" "<<0.0 <<" "<<0.0 <<" "<<0.0 <<"\n";
	cout<<endl;

	cout<<d/2*1.1 <<" "<<y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<d/2*1.1 <<" "<<-y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<-d/2 <<" "<<0.0 <<" "<<0.1 <<" "<<0.0 <<" "<<0.0 <<" "<<0.0 <<"\n";
	cout<<endl;

	cout<<-d/2*1.1 - 2*r <<" "<<y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<-d/2*1.1 - 2*r<<" "<<-y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<-d/2*0.9 - 2*r <<" "<<0.0 <<" "<<-1.5 <<" "<<0.0 <<" "<<0.0 <<" "<<0.0 <<"\n";
	cout<<endl;

	cout<<d/2*1.1 + 2*r <<" "<<y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<d/2*1.1 + 2*r<<" "<<-y/2 <<" "<<0.0 <<" "<<frameR <<" "<<frameG <<" "<<frameB <<"\n";
	cout<<d/2*0.9 + 2*r <<" "<<0.0 <<" "<<-1.5 <<" "<<0.0 <<" "<<0.0 <<" "<<0.0 <<"\n";
	cout<<endl;

	//cout<< <<" "<< <<" "<< <<" "<< <<" "<< <<" "<< <<"\n";
	//cout<<sin(theta*M_PI/2);
}