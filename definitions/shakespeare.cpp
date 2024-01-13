/*
 * @file Shakespear.cpp
 * @description Infinite Monkey Theorem
 * @brief If a monkey randomly hits keys for an infinite amount time, how many keys will be typed before...
 * 'methinks it is like a weasel' occurs.
 */

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

string sentence = "methinks it is like a weasel";
char alpha[27]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

std::random_device rd;

string generate(){
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0,27);
  int count = 0;
  string str;

  bool flag = true;
  for (count = 0; count < 28; count++){
    int random_number = dis(gen);
    str+= alpha[random_number];
  }
  return str;
}

int score(string str1, string str2){
  int i,j,c,points;
  for(i = 0;i<str1.length();i++){
    if(str2.find(str1[i])>=0){
      c+=1;
    }
    j+=1;
  }
  return c/2;
}

int main(){
   string randstr = "";
   string beststr = "";
   int ctemp,letters,count,trials=10000000;
   letters=0;
   for(count = 0;count < trials;count++){
     randstr = generate();
     ctemp = score(randstr,sentence);
     if(ctemp>letters){beststr=randstr;}     
     if(randstr == sentence){
       cout << "Number of trials: " << count << endl;
       return count;
     } else if (count%999 == 0){
       cout << "Best string in 1000 trials: " << beststr << endl;
     } else if(count == trials-1){
       cout << "No success in " << trials << " trials." << endl;
     } 
   }
}
