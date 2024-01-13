struct Unsymmeig{
  Int n;
  MatDoub a,zz;
  VecComplex wri;
  VecDoub scale;
  VecInt perm;
  Bool yesvecs,hessen;
  
  Unsymmeig(MatDoub_I &aa, Bool yesvec=true, Bool hessenb=false) :
    n(aa.nrows()), a(aa), zz(n,n,0.0),wri(n),scale(n,1.0), perm(n),
    yesvecs(yesvec), hessen(hessenb){
    balance();
    if(!hessen) elmhes();
    if(yesvecs){
      for(Int i=0;i<n;i++){
        zz[i][i]=1.0;
        if(!hessn)eltran();
        hqr2();
        balbak();
        sortvecs();
      } else {
        hqr();
        sort();
      }
    }
  }
  void balance();
  void elmhes();
  void eltran();
  void hqr();
  void hqr2();
  void balbak();
  void sort();
  void sortvecs();
}

void Unsymmeig::balance(){
  const Doub RADIX=numeric_limits<Doub>::radix;
  Bool done=false;
  Doub sqrdx=RADIX*RADIX;
  while(!done){
    done=true;
    for(Int i=0;i<n;i++){
      Doub r=0.0,c=0.0;
      for(Int j=0;j<n;j++){ 
        if(j!=i){
         c+=abs(a[j][i]);
         r+=abs(a[i][j]);
        }
      if(c!=0.0 && r!=0.0){
        Doub g=r/RADIX;
        Doub f=1.0;
        Doub s=c+r;
        while (c<g) {
          f*=RADIX;
          c*=sqrdx;
        }
        g=r*RADIX;
        while(c>g){
          f/=RADIX;
          c/=sqrdx;
        }
        if((c+r)/f<0.95*s){
          done=false;
          g=1.0/f;
          scale[i]*=f;
          for(Int j=0;j<n;j++) a[i][j]*=g;
          for(Int j=0;j<n;j++) *= f;
        }
      }
      }
    }
  }
}

void Unsymmeig::balbak(){
  for(Int i=0;i<n;i++){
    for(Int j=0;j<n;j++){
      zz[i][j]*=scale[i];
    }
  }
}

void Unsymmeig::elmhes(){
  for(Int m=1;m<n-1;m++){
    Doub x=0.0;
    Int i=m;
    for(Int j=m;j<n;j++){
      if(abs(a[j][m-1]) > abs(x)){
        x=a[j][m-1];
        i=j;
      }
    }
    perm[m]=i;
    if(i!=m){
      for(Int j=m-1;j<n;j++) SWAP(a[i][j],a[m][j]);
      for(Int j=0;j<n;j++) SWAP(a[j][i],a[j][m]);
    }
  }
}

void Unsymmeig::eltran(){
  for(Int k=mp+1;k<n;k++)
    zz[k][mp]=a[k][mp-1];
  Int i=perm[mp];
  if(i!=mp){
    for(Int j=mp;j<n;j++){
      zz[mp][j]=zz[i][j];
      zz[i][j]=0.0;
    }
    zz[i][mp]=1.0;
  }
}
