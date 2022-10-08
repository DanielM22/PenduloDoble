#include<iostream>
#include<math.h>
using namespace std;

# define g 9.8

//Definición variables y condiciones iniciales

double m1=1.0;
double m2=0.5;
double l1=2.0;
double l2=1.5;
double theta01=0.17;
double theta02=0.52;
double v01=0;
double v02=0.0;
double a01,a02=0;

double x1,x2,yy1,y2,vx1,vx2,vy1,vy2,theta1,theta2,v1,v2,a1,a2;

//Definición funciones

//Aceleración angular masa 1
double acel1(double theta01, double theta02, double v01, double v02){
  double a=(-m2*a02*l1*l2*cos(theta01-theta02)-m2*v02*v02*l1*l2*sin(theta01-theta02)-(m1+m2)*g*l1*sin(theta01))/((m1+m2)*l1*l1);

  return a;
}

//Aceleración angular masa 2
double acel2(double theta01, double theta02, double v01, double v02){

  double a=(-m2*a01*l1*l2*cos(theta01-theta02)+m2*v01*v01*l1*l2*sin(theta01-theta02)-m2*g*l2*sin(theta02))/(m2*l2*l2);

  return a;
}

//Posición x masa 1
double posx1(double theta01){

  double px1=l1*sin(theta01);
 
return px1;
}

//posición x masa 2
double posx2(double px1, double theta02){

  double px2=px1+l2*sin(theta02);
 
return px2;
}

//Posición y masa 1
double posy1(double theta01){

  double py1=-l1*cos(theta01);
 
return py1;
}

//posición y masa 2
double posy2(double posy1, double theta02){

  double py2=posy1-l2*cos(theta02);
 
return py2;
}


int main(){

  double t=0;
  double N=3000; //Número de iteraciones
  double h=0.01; //Paso
  double k1,l1,k2,l2,k3,l3,k4,l4,q1,m1,q2,m2,q3,m3,q4,m4;
  cout<<"t"<<"\t"<<"theta01"<<"\t"<<"theta02"<<"\t"<<"x1"<<"\t"<<"x2"<<"\t"<<"y1"<<"\t"<<"y2"<<"\t"<<"v01"<<"\t"<<"v02"<<endl;
 
  for(int i=0; i<=N; i++){

    x1=posx1(theta01);
    x2=posx2(x1,theta02);
    yy1=posy1(theta01);
    y2=posy2(yy1,theta02);
    a01=acel1(theta01,theta02,v01,v02);
    a02=acel2(theta01,theta02,v01,v02);

    //Pendientes RK4
    k1=h*v01;
    l1=h*acel1(theta01,theta02,v01,v02);
    q1=h*v02;
    m1=h*acel2(theta01,theta02,v01,v02);
    k2=h*(v01+(0.5)*l1);
    l2=h*acel1(theta01+(k1/2),theta02+(q1/2),v01+(l1/2),v02+(m1/2));
    q2=h*(v02+(0.5)*m1);
    m2=h*acel2(theta01+(k1/2),theta02+(q1/2),v01+(l1/2),v02+(m1/2));
    k3=h*(v01+(0.5)*l2);
    l3=h*acel1(theta01+(k2/2),theta02+(q2/2),v01+(l2/2),v02+(m2/2));
    q3=h*(v02+(0.5)*m2);
    m3=h*acel2(theta01+(k2/2),theta02+(q2/2),v01+(l2/2),v02+(m2/2));
    k4=h*(vx1+l3);
    l4=h*acel1(theta01+(k3),theta02+(q3),v01+(l3),v02+(m3));
    q4=h*(v02+m3);
    m4=h*acel2(theta01+(k3),theta02+(q3),v01+(l3),v02+(m3));

   
    theta1=theta01+((1./6)*(k1+(2*k2)+(2*k3)+k4));
    theta2=theta02+((1./6)*(q1+(2*q2)+(2*q3)+q4));
    v1=v01+((1./6)*(l1+(2*l2)+(2*l3)+l4));
    v2=v02+((1./6)*(m1+(2*m2)+(2*m3)+m4));
   
    cout<<t<<"\t"<<theta01<<"\t"<<theta02<<"\t"<<x1<<"\t"<<x2<<"\t"<<yy1<<"\t"<<y2<<"\t"<<v01<<"\t"<<v02<<endl;


    //Actualización de datos
    theta01=theta1;
    theta02=theta2;
    v01=v1;
    v02=v2;
    t=t+h;
   
    }
 
  return 0;
}