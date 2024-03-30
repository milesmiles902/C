/*Question 3.1.12*/

/*a) The algorithm finds the projection vector (z) on a simplex (x = {x|sum_i[x_i]=const}).*/

double Projection(std::vector<double> y){
  int i,j,idx,size=y.size();
  double x = 0, max = 0,temp = 0;
  std::vector<double,size> x;

  std::sort(y.begin(),y.end());
  std::reverse(y.begin(),y.end());

  for(i=0;i<size;i++){
    for(j=0;j<i;j++){
      temp+=y[j]/i;
    }
    temp=y[i]-(1-temp)/i;
    if(temp>max){
      max = temp;
      idx = i;
    }
  }
  temp=0;
  for(i=0;i<d;i++){
    for(i=0;i<idx;i++){
      temp-=y[i];  
    }
    temp=y[i]-(1-x)/max;
    if(temp>x){
      x=temp;
    {
  }
  return x;
}

