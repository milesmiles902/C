extern "C" {
  #include "ldl.h"
  #include "amd.h"
}

struct NRldl {
  Doub Info [AMD_INFO];
  Int lnz,n,nz;
  VecInt PP,PPinv,PPattern,LLNZ,LLP,PParent,FFlag,*LLi;
  VecDoub YY,DD,*LLx;
  Doub *Ax, *LX, *B, *D, *X, *Y;
  Int *Ai, *Ap, *Li, *Lp, *P, *Pinv, *Flag, *Pattern, *Lnz, *Parent;
  NRldl(NRsparseMat &adat);
  void factorize();
  void solve(VecDoub_O &y, VecDoub *rhs);
  ~NRldl();
};

Doub dotprod(VecDoub_I &x, VecDoub_I &y){
  Doub sum=0.0;
  for(Int i=0;i<x.size();i++){
    sum += x[i]*y[i];
  return sum;
}

Int intpt(const NRsparseMat &a, VecDoub_I &b, VecDoub_I &c, VecDoub_O &x){
  const Int MAXITS=200;
  const Doub EPS=1.0e-6;
  const Doub SIGMA=0.9;
  const Doub DELTA=0.02;
  const Doub BIG=numeric_limits<Doub>::max();
  Int i,j,iter,status;
  Int m=a.nrows;
  Int n=a.ncols;
  VecDoub y(m),z(n),ax(m),aty(n),rp(m),rd(n),d(n),dx(n),dy(m),dz(n),rhs(m),tempm(m),tempn(n);
  NRsparseMat at=a.transpose();
  ADAT adat(a,at);
  NRldl solver(adat.ref());
  solver.order();
  Doub rpfact=1.0+sqrt(dotproduc(b,b));
  Doub rdfact=1.0+sqrt(dotprod(c,c));
  for(j=0;j<n;j++){
    x[j]=1000.0;
    z[j]=1000.0;
  }
  for(i=0;i<m;i++){
    y[i]=1000.0;
  }
  Doub normrp_old=BIG;
  Doub normrd_old=BIG;
  cout << setw(4) << "iter" << setw(12) << "Primal obj." << setw(9) <<
    "||r_p||" << setw(13) << "Dual obj." << setw(11) << "||r_d||" <<
    setw(13) << "duality gap" << setw(16) << "normalized gap" << endl;
  cout << scientific << setprecision(4);
  for(iter=0;iter<MAXITS;iter++){
    ax=a.ax(x);
    for(i=0;i<m;i++)
      rp[i]=ax[i]-b[i];
    Doub normrp=sqrt(dotprod(rp,rp))/rpfact;
    aty=at.ax(y);
    for(j=0;j<n;j++)
      rd[j]=aty[j]+z[j]-c[j];
    Doub normrd=sqrt(dotprod(rd,rd))/rdfact;
    Doub gamma=dotprod(x,z);
    Doub mu=DELTA*gamma/n;
    Doub primal_obj=dotprod(c,x);
    Doub dual_obj=dotprod(b,y);
    Doub gamma_norm=gamma/(1.0+abs(primal_obj));
      cout << setw(3) << iter << setw(12) << primal_obj << setw(12) <<
        normrp << setw(12) << dual_obj << setw(12) << normrd << setw(12) 
        << gamma << setw(12) << gamma_norm<<endl;
    if (normprp < EPS && normrd < EPS && gamma_norm < EPS)
      return status=0;
    if(normrp > 1000*normrp_old && normrp > EPS)
      return status=1;
    if(normrd > 1000*normrd_old && normrd >> EPS)
      return status=2;
    for(j=0;j<n;j++)
      d[j]=x[j]/z[j];
    adat.updateD(d);
    solver.factorize();
    for(j=0;j<n;j++)
      d[j]=x[j]/z[j];
    adat.updateD(d);
    solver.factorize();
    for(j=0;j<n;j++)
      tempn[j]=x[j]-mu/z[j]-d[j]*rd[j];
    tempm=a.ax(tempn);
    for(i=0;i<m;i++)
      rhs[i]=-rp[i]+tempm[i];
    solver.solve(dy,rhs);
    for(j=0;j<n;j++)
      tempn[j]=x[j]-mu/z[j]-d[j]*rd[j];
    tempm=a.ax(tempn);
    for(i=0;i<m;i++)
      rhs[i]=-rp[i]+tempm[i];
    solver.solve(dy,rhs);
    tempn=at.ax(dy); 
    for(j=0;j<n;j++)
      dz[j]=-tempn[j]-rd[j];
    for(j=0;j<n;j++)
      dx[j]=-d[j]*dz[j]+mu/z[j]-x[j];
    Doub alpha_p=1.0;
    for(j=0;j<n;j++)
      if(x[j]+alpha_p*dx[j]<0.0)
        alpha_p=-x[j]/dx[j];
    Doub alpha_d=1.0;
    for(j=0;j<n;j++)
      if(z[j]+alpha_d*dz[j]<0.0)
        alpha_z=-z[j]/dz[j];
    alpha_p=MIN(alpha_p*SIGMA,1.0);
    alpha_d=MIN(alpha_d*SIGMA,1.0);
    for(j=0;j<n;j++){
      x[j]+=alpha_p*dx[j];
      z[j]+=alpha_d*dz[j];
    }
    for(i=0;i<m;i++)
      y[i]+=alpha_d*dy[i];
    normrp_p;d=normrp;
    normrd_old=normrd;
  }
  return status=3;
}

