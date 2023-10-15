struct NRsparseCol{
  Int nrows;
  Int nvals;
  VecInt row_ind;
  VecDoub val;
  
  NRsparseCol(Int m,Int nnvals) : nrows(m), nvals(nnvals), row_ind(nnvals,0), val(nnvals,0.0) {}

  void resize(Int m,Int nnvals){
    nrows = m;
    nvals = nnvals;
    row_ind.assign(nnvals,0);
    val.assign(nnvals,0.0);
  }
};
