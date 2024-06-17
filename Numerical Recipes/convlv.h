void conclv(VecDoub_I &data, VecDoub_I &respons, const Int isign, VecDoub_I &ans){
  Int i,no2,n=data.size(),m=respons.size();
  Doub mag2,tmp;
  VecDoub temp(n); 
  temp[0]=respons[0];
  for(i=1;i<(m+1);i++){
    temp[i]=respons[i];
    temp[n-i]=respons[m-i];
  }
  for(i=(m+1)/2;i<n-(m-1)/2;i++){
    temp[i]=0.0;
  }
  for(i=0;i<n;i++){
    ans[i]=data[i];
  }
  realft(ans,1);
  realft(temp,1);
  if(isign==1){
    for(i=2;i<n;i+=2){
      tmp=ans[i];
      ans[i]=(ans[i]*temp[i]-ans[i+1]*temp[i+1])/no2;
      ans[i+1]=(ans[i+1]*temp[i]+tmp*temp[i+1])/no2;
    }
    ans[0]=ans[0]*temp[0]/no2;
    ans[1]=ans[1]*temp[1]/no2;
  } else if (isign == -1){
      for(i=2;i<n;i+=2){
        if((mag2=SQR(temp[i])+SQR(temp[i+1])) == 0.0)
          throw("Deconvolving at repsponse zero in convlv");
        tmp=ans[i];
        ans[i]=(ans[i]*temp[i]+ans[i+1]*temp[i+1])/mag2/no2;
        ans[i+1]=(ans[i+1]*temp[i]-tmp*temp[i+1])/mag2/no2;
      }
      if(temp[0]==0.0|| temp[1]==0.0)
        throw("Deconvolving at response zero in convlv");
      ans[0]=ans[0]/temp[0]/no2;
      ans[1]=ans[1]/temp[1]/no2;
  } else throw("No meaing for isign in convlv");
  relaft(ans,-1);
}
