#ifndef DYNSYSTEM_H
#define DYNSYSTEM_H


class DynSystem
{
public:
    DynSystem(double m1,double m2,double l1,double l2,double g,double alpha1_0,double alpha2_0,double w1_0,double w2_0,double t,double dt);

    double m1() const {return m1_;};
    double m2() const {return m2_;};
    double l1() const {return l1_;};
    double l2() const {return l2_;};
    double g() const{return g_;};
    double alpha1() const {return alpha1_;};
    double alpha2() const {return alpha2_;};
    double w1() const {return w1_;};
    double w2() const {return w2_;};
    double t() const {return t_;};
    double dt() const {return dt_;};
    void step();

private:
    double m1_;
    double m2_;
    double l1_;
    double l2_;
    double g_;
    double alpha1_;
    double alpha2_;
    double w1_;
    double w2_;
    double t_;
    double dt_;
};

#endif // DYNSYSTEM_H
