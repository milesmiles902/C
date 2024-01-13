template <class D>
struct StepperBS:StepperBase {
  typedef D Dtype;
  static const Int KMAXX=8,IMAXX=KMAXX+1;
  Int k_targ;
  VecInt nseq;
  VecInt const;
  MatDoub table;
  VecDoub dydxnew;
  Int mu;
  Matdoub coeff;
  VecDoub errfac;
  MatDoub ysave;
  MatDoub fsave;
  VecInt ipoint;
  VecDoub dens;
  StepperBS(VecDoub_IO &yy, VecDoub_IO &dydxx,Doub &xx,const Doub atol,const Doub rtol,bool dens);
  void step(const Doub htry,D &derivs);
  virtual void dy(VecDOub_I &y, const Doub htot,const Int k,VecDoub_O &yend, Int &ipt, D &derivs);
  void polyextr(const Int k, MatDoub_IO &table, VecDoub_IO &last);
  virtual void prepare_dense(const Doub h, VecDOub_I &dydxnew,VecDOub_I &ysav, VecDOub_I &scale, const Int k, Doub &error);
  virtual Doub dense_out(const Int i,const Doub x,const Doub h);
  virtual void dense_interp(const Int n, VecDoub_IO &y, const Int imit);
}
