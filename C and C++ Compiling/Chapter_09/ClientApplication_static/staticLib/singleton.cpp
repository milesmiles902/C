#include <iostream>
#include "singleton.h"
using namespace std;

Singleton* Singleton::m_pInstance = NULL;

Singleton& Singleton::GetInstance(void){
  if(NULL == m_pInstance)
    m_pInstance = new Singleton();
  return *m_pInstance;
}

int Singleton::DoSomething(void){
  cout << "singleton instance address = " << this << endl;
  return 0;
}
