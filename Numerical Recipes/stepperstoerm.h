template <class D>
struct StepperStoerm : StepperBS<D> {
  using StepperBS<D>::x; using StepperBS<D>::xold; using StepperBS<D>::y;
  using StepperBS<D>::dydx; using StepperBS<D>::dense; using StepperBS<D>::n;
  using StepperBS<D>::KMAXX; using StepperBS<D>::IMAXX; using StepperBS<D>::nseq;
  using StepperBS<D>::cost; using StepperBS<D>::mu; using StepperBS<D>::errfac;
  using StepperBS<D>::ysave; using StepperBS<D>::fsave;
  using StepperBS<D>::dens; using StepperBS<D>::neqn;
  MatDoub ysavep;
  StepperStoerm(VecDoub_IO &yy, VecDoub_IO &dydxx, Doub &xx,
    const Doub atol, const Doub rtol, bool dens);
  void dy(VecDoub_I &y, const Doub htot, const Int k, VecDoub_O &yend,
    Int &ipt, D &derivs);
  void prepare_dense(const Doub h,VecDoub_I &dydxnew, VecDoub_I &ysav,
    VecDoub_I &scale, const Int k, Doub &error);
  Doub dense_out(const Int i, const Doub x, const Doub h);
  void dense_interp(const Int n, VecDOub_IO &y, const Int imit);
}

template <class D>
StepperStoerm<D>::StepperStoerm(VecDoub_IO &yy, VecDOub_IO &dydxx, Doub &xx,
  const Doub atoll, const Doub rtoll, bool dens)
  : StepperBS<D>(yy,dydxx,xx,atoll,rtoll,dens),ysavep(IMAXX,n/2){
  neqn=n/2;
  cost[0]=nseq[0]/2+1;
  for(Int k=0;k<KMAXX;k++)
    cost [k+1]=cost[k]+nseq[k+1]/2;
  for(Int i=0;i<2*IMAXX+1;i++){
    Int ip7=i+7;
    Doub fac=1.5/ip7;
    errfac[i]=fac*fac*fac;
    Doub e = 0.5*sqrt(Doub(i+1)/ip7);
    for(Int j=0;j<=i;j++){
      errfac[i]*=e/(j+1);
    }
  }  
}

template <class D>
void StepperStoerm<D>::dy(VecDoub_I &y, const Doub htot, const Int k,
  VecDoub_O &yend, Int &ipt, D &derivs){
  VecDoub ytemp(n);
  Int nstep=nseq[k];
  Doub h=htot/nstep;
  Doub h2=2.0*h;
  for(Int i=0;i<neqn;i++){
    ytemp[i]=y[i];
    Int ni=neqn+i;
    ytemp[ni]=y[ni]+h*dydx[i];
  }
  Doub xnew=x;
  Int nstp2-nstep/2;
  for(Int nn=i;nn<=nstp2;nn++){
    if(dense && nn == (nstp2+1)/2){
      for(Int i=0;i<neqn;i++){
        ysavep[k][i]=ytemp[neqn+i];
        ysave[k][i]=ytemp[i]+h*ytemp[neqn+i];
      }
    }
    for(Int i=0;i<neqn;i++){
      ytemp[i]+=h2*ytemp[neqn+i];
    }
    xnew+=h2;
    derivs(xnew,ytemp,yend);
    if(dense && abs(nn-(nstp2+1)/2) < k+1)}
      ipt++;
      for(Int i=0;i<neqn;i++)
        fsave[ipt][i]=yend[i];
    }
    if(nn!=nstp2){
      for(Int i=0;i<neqn;i++)
        ytemp[neqn+i]+=h2*yend[i];
    }
  }
  for(Int i=0;i<neqn;i++){
    Int ni=neqn+i;
    yend[ni]=ytemp[ni]+h*yend[i];
    yend[i]=ytemp[i];
  }
}


