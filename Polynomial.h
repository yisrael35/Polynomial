#include <stdlib.h> //malloc
#include <stdio.h>
#include <iostream>

#ifndef it
#define it

/*yisrael bar 07-11/01/20*/
        
            ///*
        //decleration on the mathod and the class
         template <typename T>
         class Polynomial ;
         template <typename T>
         Polynomial<T> operator+ (const Polynomial<T> & p1,const Polynomial<T> & p2);
         template <typename T>
         Polynomial<T> operator- (const Polynomial<T> &p1,const Polynomial<T> &other);
         template <typename T>
         Polynomial<T> operator* (const Polynomial<T> &p1,const Polynomial<T>& other);
            //*/
template <typename T>
class Polynomial {
public: 
    T* coefs; 
    int num_of_coefs;
    //constructor
   Polynomial(){
       num_of_coefs=0;
       coefs=NULL;
   }
   //destructor
   ~Polynomial(){
       delete [] coefs;   
   }
   //return a cell from an array
    T& operator[] (int  x ){
        //first time to assignd in the array
       if(this->num_of_coefs==0){

           this->coefs=(T*)malloc ((x+1)*sizeof(T));
            if(this->coefs==NULL)exit(1);
           this->num_of_coefs=x+1;
       }
       //if the cell does not exist
       else if(this->num_of_coefs<x){
        T* t1=(T*)malloc ((x+1)*sizeof(T));
             if(t1==NULL)exit(1);
        for (int i = 0; i < this->num_of_coefs; i++)
        {
            t1[i]=this->coefs[i];
        }
        //delete the old array
        delete [] coefs;
        this->coefs=t1;
        this->num_of_coefs=x+1;
       }
       return this->coefs[x];
   }
   //put object in object
    Polynomial<T>& operator=(Polynomial other ){
        //the same object
        if (this->coefs==other.coefs)
        {
            return *this;
        }
        //delete the old array
        if (this->num_of_coefs!=0)
        {
           delete [] coefs;
        }
        num_of_coefs=other.num_of_coefs;
        T* t1=(T*)malloc(num_of_coefs*sizeof(T));
        if(t1==NULL)exit(1);
        this->coefs=t1;
        //copy the array
        for(int i=0 ;i< this->num_of_coefs; i++){
            coefs[i]=other.coefs[i];
        }
        
      return *this;
   }
    

    //sum of the polynom itself with onther polynom
    Polynomial<T> &operator+=(const Polynomial<T>  &other ){
        //change the size of this 
       int size=0;
       if(this->num_of_coefs > other.num_of_coefs )
       size =this->num_of_coefs;
       else 
       size =other.num_of_coefs;
       this->coefs= (T*)realloc(this->coefs, size*sizeof(T));
       if(this->coefs==NULL)exit(1);
       //do the add
        for (int  i = 0; i < other.num_of_coefs; i++)
        {
            this->coefs[i]+=other.coefs[i];
        }
        //update this to the right size
       this->num_of_coefs=size;
        return *this;

    }
    
    //multiply polynom in onther
    Polynomial<T> &operator*=(const Polynomial<T> & other ){
    int size=this->num_of_coefs * other.num_of_coefs;
        //create a temp array
        T * t1=(T*)malloc (num_of_coefs*sizeof(T));
        if(t1==NULL)exit(1); 
        //copy coefs array       
        for (int i = 0; i < num_of_coefs; i++)
        {
            t1[i]=coefs[i];
        }
        //resizeing coefs
        coefs=(T*)realloc (coefs, size*sizeof(T));
        if(coefs==NULL)exit(1);     
        //clean coefs
          for (int i = 0; i < size; i++)
        {
           coefs[i]=0;
        }
        //do the multiply
        for (int  i = 0; i < num_of_coefs; i++)
        {
            for (int j = 0; j < other.num_of_coefs; j++)
            {
            this->coefs[i+j]+=t1[i]*other.coefs[j];
            }
        }
        //delete the temp array
        delete [] t1;
       this->num_of_coefs=size;
    
        return *this;
    }


    //submits from a polynom
    Polynomial<T> operator-=(const Polynomial<T> & other ){
       int size=0;
       if(this->num_of_coefs > other.num_of_coefs )
       size =this->num_of_coefs;
       else 
       size =other.num_of_coefs;
       //change the size of size
       this->coefs= (T*)realloc(this->coefs, size*sizeof(T));
       if(this->coefs==NULL)exit(1);
       this->num_of_coefs=size;
       //do the submition
        for (int  i = 0; i < other.num_of_coefs; i++)
        {
            this->coefs[i]-=other.coefs[i];
        }
        return *this;

    }    

    //print the polynomail by order
    friend std::ostream &operator <<(std::ostream &output,const Polynomial<T> & other)
    // friend ostream& operator <<(ostream &output , const Polynomial<T> & other )
    {
      bool flag=false;
       for (int i = other.num_of_coefs ; i >=0 ; i--)
       {  
           //first digit
           if (other.coefs[i]!=0 && !flag && i!=0)
           {
               //x^1
              if(i!=1) 
            output << other.coefs[i]<<"*x^"<<i;
            else 
            output << other.coefs[i]<<"*x";
            flag=true;
            continue;
            }
            //other digit
           if(other.coefs[i]!=0 && i!=0 ){
               //positive
               if (other.coefs[i]>0 && flag){
                   ///x^1
                  if (i!=1) 
              output <<"+"<< other.coefs[i]<<"*x^"<<i;
              else
                  output <<"+"<< other.coefs[i]<<"*x";              
               }
               //negative
               else {
                   //x^1
                   if(i!=1) 
               output << other.coefs[i]<<"*x^"<<i;
               else 
               output << other.coefs[i]<<"*x";
               }
           }
           //last digit
           else if (other.coefs[i]!=0){
                output <<"+" << other.coefs[i];
           }         
       }
       return output;
    }
    
        /*
        Polynomial<T> &operator+(const Polynomial<T> &p2 ){
       int size=0;
       if(num_of_coefs > p2.num_of_coefs )
       size =num_of_coefs;
       else 
       size =p2.num_of_coefs;
       Polynomial<T> *p=new Polynomial();
       T * t1=(T*)malloc (size*sizeof(T));
       if(t1==NULL)exit(1);
       p->num_of_coefs=size;
       
        for (int  i = 0; i <= num_of_coefs; i++)
        {
            t1[i]=coefs[i];
        }
         for (int  i = 0; i <= p2.num_of_coefs; i++)
        {
            t1[i]+=p2.coefs[i];
        }   
        p->coefs=t1;
        return *p;
    }
    Polynomial<T> &operator-(const Polynomial<T>& other ){
      int size=0;
       if(this->num_of_coefs > other.num_of_coefs )
       size =this->num_of_coefs;
       else 
       size =other.num_of_coefs;
       Polynomial<T> *p=new Polynomial();
       T * t1=(T*)malloc (size*sizeof(T));
       if(t1==NULL)exit(1);
       p->num_of_coefs=size;
        for (int  i = 0; i < size; i++)
        {
            t1[i]=this->coefs[i]-other.coefs[i];
        }
        p->coefs=t1;
        return *p;
    }
    Polynomial<T> &operator*(const Polynomial<T> &other ){
      int size=this->num_of_coefs * other.num_of_coefs;
       Polynomial<T> *p=new Polynomial();
       T * t1=(T*)malloc (size*sizeof(T));
       if(t1==NULL)exit(1);
        p->num_of_coefs=size;      
        for (int  i = 0; i <= this->num_of_coefs; i++)
        {
            for (int j = 0; j <= other.num_of_coefs; j++)
            {
            t1[i+j]+=this->coefs[i]*other.coefs[j];
                
            }
            
        }
        p->coefs=t1;
        return *p;
    }
    */

    
        ///*   
        //declare on the mathods whoem have freind
        friend Polynomial operator+ <>(const Polynomial<T> & p1,const Polynomial<T> & p2);
        friend Polynomial operator- <>(const Polynomial<T> &p1,const Polynomial<T> &other);
        friend Polynomial operator* <>(const Polynomial<T> &p1,const Polynomial<T>& other);
        //*/
};
  ///*   

    template <typename T>
    //getting to polynoms the sums them to a new one
    Polynomial<T> operator+(const Polynomial<T>& p1,const Polynomial<T> &p2 ){
          int size=0;
       if(p1.num_of_coefs > p2.num_of_coefs )
       size =p1.num_of_coefs;
       else 
       size =p2.num_of_coefs;
       Polynomial<T> p;
       //createing the new array
       T * t1=(T*)malloc (size*sizeof(T));
       if(t1==NULL)exit(1);
       p.num_of_coefs=size;
       //adding to the new array the polynoms
        for (int  i = 0; i <= p1.num_of_coefs; i++)
        {
            t1[i]=p1.coefs[i];
        }
         for (int  i = 0; i <= p2.num_of_coefs; i++)
        {
            t1[i]+=p2.coefs[i];
        }   
        p.coefs=t1;
        return p;
       
     }
 template <typename T>
 //submits polynoms 
   Polynomial<T> operator-(const Polynomial<T> &p1,const Polynomial<T>& other ){
      int size=0;
       if(p1.num_of_coefs > other.num_of_coefs )
       size =p1.num_of_coefs;
       else 
       size =other.num_of_coefs;
       Polynomial<T> p;
       //create the new array
       T * t1=(T*)malloc (size*sizeof(T*));
       p.num_of_coefs=size;
         //submiting to the new array the polynoms
        for (int  i = 0; i < size; i++)
        {
            t1[i]=p1.coefs[i]-other.coefs[i];
        }
        p.coefs=t1;
        return p;
     }

 template <typename T>
 //multiply to polynoms 
   Polynomial<T> operator*(const Polynomial<T> &p1,const Polynomial<T>& other ){
    int size=p1.num_of_coefs * other.num_of_coefs;
    //create a new polynom
       Polynomial<T> p;
       //create a new array
       T * t1=(T*)malloc (size*sizeof(T));
       if(t1==NULL)exit(1);
        p.num_of_coefs=size;    
        //doing the multiply  
        for (int  i = 0; i <= p1.num_of_coefs; i++)
        {
            for (int j = 0; j <= other.num_of_coefs; j++)
            {
            t1[i+j]+=p1.coefs[i]*other.coefs[j];
                
            }
            
        }
        p.coefs=t1;
        return p;
     }

         //*/


#endif