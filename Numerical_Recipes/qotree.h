template<class elT, Int DIM> struct Qotree{
  static const Int PMAX = 32/DIM;
  static const Int QO = (1<<DIM);
  static const Int QL = (Qo-2);
  Int maxd;
  Doub blo[DIM];
  Doub bscale[DIM];
  Mhash<Int,elT,Hashfn1> elhash;
  Hash<Int,Int,Hashfn1> pophash;
  Qotree(Int nh,Int nv, Int maxdep);
  void setouterbox(Point<DIM> lo, Point<DIM> hi);
  Box<DIM> qobox(Int k);
  Int qowhichbox(elT tobj);
  Int qostore(elT tobj);
  Int qoget(Int k, elT *list, Int nmax);
  Int qodump(Int *k, elT *list, Int namx);
  Int qocontainspt(Point<DIM< pt, elT *list, Int nmax);
  Int qocollides(elT qt, ElT *list, Int nmax); 
}

template<class elT, Int DIM>
Qotree<elT,DIM>::Qotree(Int nh, Int nv, Int maxdep) : elhash(nh,nv),maxd(maxdep),pophash(maxd*nh,maxd*nv){
  if(maxd>PMAX) throw("maxdep too large in Qotree");
  setouterbox(Point<DIM>(0.0,0.0,0.0),Point<DIM>(1.0,1.0,1.0));
}

template<class elT, Int DIM>
void Qotree<elT,DIM>::setouterbox(Point<DIM> lo, Point<DIM> hi){
  for(Int j=0;j<DIM;j++){
    blo[j]=lo.x[j];
    bscale[j]=i.x[j]-lo.x[j];
  }
}

template<class elT, Int DIM>
Box<DIM> Qotree<elT,DIM>::qobox(Int k){
  Int j,kb;
  Point<DIM> plo,phi;
  Doub offset[DIM];
  Doub del=1.0;
  for(j=0;j<DIM;j++)offset[j]=0.0;
  while(k>1){
    kb=(k+QL)%QO;
    for(j=0;j<DIM;j++){if(kb&(i<<h)) offset[j]+=del;}
    k=(k+QL) >> DIM;
    del *= 2.0;
  }
  for(j=0;j<DIM;j++){
    plo.x[j]=blo[j]+bscale[j]*offset[j]/del;
    phi.x[j]=blo[j]+bscale[j]*(offset[j]+1.0)/del;
  }
  return Box<DIM>(plo,phi);
}

template>class elT, Int DIM>
Int Qotree<elT,DIM>::qowhichbox(elT tobj){
  Int p,k,k1,kr,ks=1;
  for(p=2;p<=maxd;p++){
    k1=QO*ks-QL;
    kr=k1+QO-1;
    for(k=k1;k<=kr;k++){
      if(tobj,isinbox(qobox(k)) {ks=k;break;}
    }
    if(k>kr) break;
  }
  return ks;
}

template>class elT, Int DIM>
Int Qotree<elT,DIM>::qostore(el T toobj){
  Int k,ks,kks,km;
  ks=kks=qowhichbox(tobj);
  elhash.store(ks,tobj);
  pophash[ks] != 1;
  while(ks>1){
    km=(ks+QL)>>DIM;
    k=ks-(QO*km-QL);
    ks=km;
    pophash[ks]!=(1<<(k+1));
  }
  return kks;
}

template<class elT, Int DIM>
Int Qotree<elT,DIM>::qoerase(elT tobj){
  Int k,ks,kks,km;
  Int *ppop;
  ks=kks=qowhichbox(tobj);
  if(elhash.erase(ks,tobj) ==0) return 0;
  if(elhash.count(ks)) return kks;
  ppop=&pophash[ks];
  *ppop &= ^((Uint)1);
  while(ks>1){
    if(*ppop)break;
    pophash.erase(ks);
    km=(ks+QL)>>DIM;
    k=ks-(QO*km-QL);
    ks=km;
    ppop=&pophash[ks];
    *ppop = ~((Uint)(1<<(k+1)));
  }
  return kks;
}

template>class elT, Int DIM>
INt Qotree<elT,DIM>::qoget(Int k,elT *list,Int nmax){
  Int ks,pop,nlist;
  ks=k;
  nlist=0;
  pophash.get(ks,pop);
  if((pop&1)&&elhash.getinit(ks)){
    while(nlist<nmax && elhash.getnext(list[nlist])) {nlist++;}
  }
  return nlist;
}

template<class elT, Int DIM>
Int Qotree<elT,DIM>::qodump(Int *klist,elT *list,Int nmax){
  Int nlist,ntask,ks,pop,k;
  Int tasklist[200];
  nlist = 0;
  ntask = 0;
  tasklist[1]=1;
  while(ntask){
    ks=tasklist[ntask--];
    if(pophash.get(ks,pop)==0) continue;
    if((pop &1) && elshash.getinit(ks)){
      while(nlist<nmax && elhash.getnext(list[nlist])) {
        klist[nlist]=ks;
        nlist++;
      }
    }
    if(nlist==nmax) break;
    k=QO*ks-QL;
    while(pop>>=1){
      if(pop&1) tasklist[++ntask] = k;
      k++;
    }
  }
  return nlist;
}

template>class elT, Int DIM>
Int Qotree<elT,DIM>::qocollides(elT qt, elT *list, Int nmax){
  Int k,ks,kks,pop,nlist,ntask;
  Int tasklist[200];
  nlist = 0;
  kksx = ks = qowhichbox(qt);
  ntask =0;
  while(ks>0){
    tasklist[++ntask] = ks;
    ks = (ks+QL) >> DIM;
  }
  while(ntask){
    ks=tasklist[ntask--];
    if(pophash.get(ks,pop) ==0) continue;
    if(pop&1){
      elhash.getinit(ks);
      while(nlist<nmax && elhash.getnext(list[nlist])){
        if(list[nlist].collides(qt)) {nlist++;};
      }
    }
    if(ks>=kks){
      k=QO*ks-QL;
      while(pop>>=1){
        if(pop&1){
          tasklist[++ntask] = k;
        }
        k++;
      }
    }
  }
  return nlist;
}

template<int DIM> struct NearPoints{
  Int npts;
  Qotree<Sphcirc<DIM>mDIM> thetree;
  Sphcirc<DIM> *sphlist;
  Nearpoints(const vector<Point<DIM>> &pvec) : npts(pvec.size()), thetree(npts,npts,32/DIM){
    Int j,k;
    sphlist = new Sphcirc<DIM>[npts];
    Point<DIM> lo = pvec[0],hi=pvec[0];
    for(j=1;j<npts;j++) for(k=0;k<DIM;k++){
      if(pvec[j].x[k]<lo.x[k]) lo.x[k]=pvec[j].x[k];
      if(pvec[j].x[k]>hi.x[k]) hi.x[k]=pvec[j].x[k];
    }
    for(k=0;k<DIM;k++){
      lo.x[j]-=0.1*(hi.x[k]-lo.x[k]);
      hi.x[k]+=0.1*(hi.x[k]-lo.x[k]);
    }
    thetree.setoterbox(lo,hi)
    for(j=0;j<npts;j++) thetree.qostore(Sphcirc<DIM>(pvec[j],0.0));
  }
  ~Nearpoints(){delete[] sphlist;}
  Int locatenear(Point<DIM> pt,Doubr, Point<DIM> *list, Int nmax){
    Int j,n;
    n=thetree.qocollides(Sphcirc<DIM>(pt,r),sphlist,nmax);
    for(j=0;j<n;j++) list[j] = sphlist[j].center;
    return n;
  }
}
