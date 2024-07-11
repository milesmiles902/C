#pragma once

class Singleton{
  public:
    static Singleton& GetInstance(void);
  
  public:
    ~Singleton(){};
    int DoSomething(void);

  private:
    Singleton(){};
    Singleton(Singleton const &);
    void operator=(Singleton const&);

  private:
    static Singleton* m_pInstance;
};
