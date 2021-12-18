#include "dynsystem.h"

#include <cmath>

#define _USE_MATH_DEFINES

double f1(double w1){return w1;};

double f2(double w2){return w2;};

double f3(double m1,double m2, double l1, double l2, double g, double alpha1, double alpha2, double w1, double w2)
{
    return ((m1+m2)*g*sin(alpha1)+m2*l2*w2*w2*sin(alpha1-alpha2)+(l1*w1*w1*sin(alpha1-alpha2)-g*sin(alpha2))*m2*cos(alpha1-alpha2))/(l1*(-m2*sin(alpha1-alpha2)*sin(alpha1-alpha2)-m1));
}

double f4(double m1,double m2, double l1, double l2, double g, double alpha1, double alpha2, double w1, double w2)
{
    return (sin(alpha1-alpha2)*((m1+m2)*(l1*w1*w1+g*cos(alpha1))+l2*m2*w2*w2*cos(alpha1-alpha2)))/(l2*(m1+m2*sin(alpha1-alpha2)*sin(alpha1-alpha2)));
}

DynSystem::DynSystem(double m1, double m2, double l1, double l2,double g, double alpha1_0, double alpha2_0, double w1_0, double w2_0, double t, double dt):
    m1_(m1),m2_(m2),l1_(l1),l2_(l2),g_(g),alpha1_(alpha1_0),alpha2_(alpha2_0),w1_(w1_0),w2_(w2_0),t_(t),dt_(dt)
{}

void DynSystem::step()
{
    double k11=dt_*f1(w1_);
    double k12=dt_*f2(w2_);
    double k13=dt_*f3(m1_,m2_,l1_,l2_,g_,alpha1_,alpha2_,w1_,w2_);
    double k14=dt_*f4(m1_,m2_,l1_,l2_,g_,alpha1_,alpha2_,w1_,w2_);
    double k21=dt_*f1(w1_+k13/2);
    double k22=dt_*f2(w2_+k14/2);
    double k23=dt_*f3(m1_,m2_,l1_,l2_,g_,alpha1_+k11/2,alpha2_+k12/2,w1_+k13/4,w2_+k14/2);
    double k24=dt_*f4(m1_,m2_,l1_,l2_,g_,alpha1_+k11/2,alpha2_+k12/2,w1_+k13/4,w2_+k14/2);
    double k31=dt_*f1(w1_+k23/2);
    double k32=dt_*f2(w2_+k24/2);
    double k33=dt_*f3(m1_,m2_,l1_,l2_,g_,alpha1_+k21/2,alpha2_+k22/2,w1_+k23/2,w2_+k24/2);
    double k34=dt_*f4(m1_,m2_,l1_,l2_,g_,alpha1_+k21/2,alpha2_+k22/2,w1_+k23/2,w2_+k24/2);
    double k41=dt_*f1(w1_+k33);
    double k42=dt_*f2(w2_+k34);
    double k43=dt_*f3(m1_,m2_,l1_,l2_,g_,alpha1_+k31,alpha2_+k32,w1_+k33,w2_+k34);
    double k44=dt_*f4(m1_,m2_,l1_,l2_,g_,alpha1_+k31,alpha2_+k32,w1_+k33,w2_+k34);
    alpha1_+=(k11+2*k21+2*k31+k41)/6;
    alpha2_+=(k12+2*k22+2*k32+k42)/6;
    w1_+=(k13+2*k23+2*k33+k43)/6;
    w2_+=(k14+2*k24+2*k34+k44)/6;
    t_+=dt_;
}

