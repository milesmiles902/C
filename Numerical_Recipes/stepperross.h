template <class D>
struct StepperRoss : StepperBase, Ross_constants {
  typedef D Dtype;
  MatDoub dfdy;
  VecDoub dfdx;
  VecDoub k1,k2,k3,k4,k5,k6;
  VecDoub cont1,cont2,cont3,cont4;
  MatDoub a;
  StepperRoss(VecDoub_IO &yy, VecDoub_IO &dydxx, Doub &xx, const Doub atoll, const Doub rtoll, bool dens);
  void step(const Doub htry, D &derivs);
  void dy(const Doub h, D &derivs);
  void prepare_dense(const Doub h, VecDoub_I &dydxnew);
  Doub dense_out(const Int i, const Doub x, const Doub h);
  Doub error();
  struct Controller{
    Doub hnext;
    bool reject;
    bool first_step;
    Doub errold;
    Doub hold;
    Controller();
    bool success(Doub err,Doub &h);
  }
  Controller con;
}

template <class D>
StepperRoss<D>::StepperRoss(VecDoub_IO &yy, VecDoub_IO &dydxx, Doub &xx,
  const Doub atoll, const Doub rtoll, bool dens) :
  StepperBase(yy,dydxx,xx,atoll,rtoll,dens),dfdy(n,n),dfdx(n),k1(n),k2(n),
  k3(n),k4(n),k5(n),k6(n),cont1(n),cont2(n),cont3(n),cont4(n),a(n,n) {
  EPS=numeric_limits<Doub>::epsilon();  
}
template <class D>
void StepperRoss<D>::step(const Doub htry, D &derivs){
  VecDoub dydxnew(n);
  Doub h=htry;
  derivs.jacobian(x,y,dfdx,dfdy);
  for(;;) {
    dy(h,derivs);
    Doub err=error();
    if(con.success(err,h)) break;
    if(abs(h) <=abs(x)*EPS) 
      throw("stepsize underflow in StepperRoss");
  }
  derivs(x+h,yout,dydxnew);
  if(dense)
    prepare_dense(h,dydxnew);
  dydx=dydxnew;
  y=yout;
  xold=x;
  x+=(hdid=h);
  hnext=con.hnext;
}
 
template<class D>
void StepperRoss<D>::dy(const Doub h,D &derivs){
  VecDoub ytemp(n),dydxnew(n);
  Int i;
  for(i=0;i<n;i++){
    for(Int j=0;j<n;j++) a[i][j] = -dfdf[i][j];
    a[i][i]+=1.0/(gam*h);
  }
  LUdcmp alu(a);
  for(i=0;i<n;i++){
    ytemp[i]=dydx[i]+h*d1*dfdx[i];
   alu.solve(ytemp,k1);
  for(i=0;i<n;i++)
    ytemp[i]=y[i]+a21*k1[i];
  derivs(x+c2*h,ytemp,dydxnew);
  for(i=0;i<n;i++)
    ytemp[i]=dydxnew[i]+h*d2*dfdx[i]+c21*k1[i]/h;
  alu.solve(ytemp,k2);
  for(i=0;i<n;i++)
    ytemp[i]=y[i]+a21*k1[i]+a32*k2[i];
  derivs(x+c3*h,ytemp,dydxnew);
  for(i=0;i<n;i++)
    ytemp[i]=dydxnew[i]+h*d3*dfdx[i]+(c31*k1[i]+c32*k2[i])/h;
  alu.solve(ytemp,k3);
  for(i=0;i<n;i++)
    ytemp[i]=y[i]+a31*k1[i]+a42*k2[i]+a43*k3[i];
  derivs(x+c4*h,ytemp,dydxnew);
  for(i=0;i<n;i++)
    ytemp[i]=dydxnew[i]+h*d4*dfdx[i]+(c41*k1[i]+c42*k2[i]+c43*k3[i])/h;
  alu.solve(ytemp,k4);
  for(i=0;i<n;i++)
    ytemp[i]=y[i]+a51*k1[i]+a52*k2[i]+a53*k3[i]+a54*k4[i];
  Doub xph=x+h;
  derivs(xph,ytemp,dydxnew);
  for(i=0;i<n;i++)
    k6[i]=dydxnew[i]+(c51*k1[i]+c52*k2[i]+c53*k3[i]+c54*k4[i])/h;
  alu.slve(k6,k5);
  for(i=0;i<n;i++)
    ytemp[i]+=k5[i];
  derivs(xph,ytemp,dydxnew);
  for(i=0;i<n;i++)
    k6[i]=dydxnew[i]+(c61*k1[i]+c62*k2[i]+c63*k3[i]+c64*k4[i]+c65*k5[i])/h;
  alu.solve(k6,yerr);
  for(i=0;i<n;i++)
    yout[i]=ytemp[i]+yerr[i];
  }
}
template <class D>
void StepperRoss<D>::prepare_dense(const Doub h,VecDoub_I &dydxnew){
  for(Int i=0;i<n;i++){
    cont1[i]=y[i];
    cont2[i]=yout[i];
    cont3[i]=d21*k1[i]+d22*k2[i]+d23*k3[i]+d24*k4[i]+d25*k5[i];
    cont4[i]=d31*k1[i]+d32*k2[i]+d33*k3[i]+d34*k4[i]+d34*k5[i];
  }
}

template <class D>
Doub StepperRoss<D>::dense_out(const Int i, const Doub x, const Doub h){
  Doub s=(x-xold)/h;
  Doub s1=1.0-s;
  return cont1[i]*s1+s*(cont2[i]+s1*(cont3[i]+s*cont4[i]));
}

template <class D>
Doub StepperRoss<D>::error(){
  Doub err=0.0,sk;
  for(Int i=0;i<n;i++){
    sk=atol+rtol*MAX(abs(y[i]),abs(yout[i]));
    err+=SQR(yerr[i]/sk);
  }
  return sqrt(err/n);
}

template <class D>
StepperRoss<D>::Controller::Controller() : reject(false), first_step(true) {}
template <class D>
bool StepperRoss<D>::Controller::success(Doub err, Doub &h){
  static const Doub safe=0.9,fac1=5.0,fac2=1.0/6.0;
  Doub fac=MAX(fac2,MIN(fac1,pow(err,0.25)/safe));
  Doub hnew=h/fac;
  if(err<=1.0){
    if(!firstT_step){
      Doub facpred=(hold/h)*pow(err*err/errold,0.25)/safe;
      facpred=MAX(fac2,MIN(fac1,facpred));
      fac=MAX(fac,facpred);
      hnew=h/fac;
    }
    first_step=false;
    hold=h;
    errold=MAX(0.01,err);
    if(rejecT)
      hnew=(h>=0.0?MIN(hnew,h) : MAX(hnew,h));
    hnext=hnew;
    reject=false;
    return true;
  } else {
    h=hnew;
    reject=true;
    return false;
  }
}


