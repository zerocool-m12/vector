/***************************************************************************
 * 
 * This code is written by zerocool_m12.
 * GitHub: https://github.com/zerocool-m12
 * 
 * This code is released under the MIT License.
 * You are free to use, modify, distribute, and copy this code.
 * No warranty is provided, express or implied.
 * 
 * If you find any issues or have any improvements, feel free to contribute!
 * zerocool_m12@hotmail.com
 ***************************************************************************/
#include<iostream>
#include<initializer_list>
#include<cstring>
template<typename T>
class vector{
    private:
      size_t sze;  // the size of the vector
      T*data;  // the pointer of the data which shall be stored in the vector
    public:
      vector(): sze(0), data(nullptr){}  // default constructor

      vector(std::initializer_list<T>arr){  // constructor with the classic way of array elements
          sze = arr.size();
          size_t index = 0;
          data = new T[sze];
          if(!data) throw std::bad_alloc();
          for(auto &i : arr)
            data[index++] = i;
      }
      vector(const size_t&x){  // constructor with a size only
          sze = x;
          data = new T[sze];
          if(!data) throw std::bad_alloc();
      }
      vector(const vector&other){  // copy constructor
          if(&other == this) return;
          delete [] this->data;
          this->size = other.sze;
          this->data = new T[this->sze];
          if(!data) throw std::bad_alloc();
          memcpy(this->data,other.data,sizeof(T)*this->sze);
      }
      vector &operator=(const vector&other){  // copy assignment operator
          if(&other == this) return *this;
          delete [] this->data;
          this->size = other.sze;
          this->data = new T[this->sze];
          if(!data) throw std::bad_alloc();
          memcpy(this->data,other.data,sizeof(T)*this->sze);          
      }
      vector (vector&&other){  // move constructor
          if(this == &other) return;
          delete [] this->data;
          this->sze = other.sze;
          this->data = other.data;
          other.data = nullptr;
          other.sze = 0;
      }
      vector &operator = (vector&&other){  // move assignment
          if(this == &other) return *this;
          delete [] this->data;
          this->sze = other.sze;
          this->data = other.data;
          other.data = nullptr;
          other.sze = 0;
      }
      ~vector(){  // destructor
          delete [] data;
          sze = 0;
          data = nullptr;
      }
      class iterator; // the iterator of the vector
      iterator begin(){ return iterator(*this,0); } 
      iterator end(){ return iterator(*this,sze); }
      const size_t &size () const {  // method of returning the size of the vector
          return this->sze;
      }
      const T&at(const size_t&x) const{  // the usual 'at' method which returns the element in the specific position
          if(x >= sze) throw std::out_of_range("Out of range element!\n"); // throwing an exception in case the position is out of range
          return this->data[x];
      }
      T&operator[](const size_t&x){  // the classic indexing of array
          if(x >= sze) throw std::out_of_range("Out of range element!\n");
          return this->data[x];
      }
      void push_back(const T&x){  // implementing the method push_back for the vector
          T*new_data = (T*) realloc(data,sizeof(T) * sze + 1);  // allocating memory with adding one more place to the size
          if(!new_data) throw std::bad_alloc(); 
          data = new_data;
          data[sze++] = x;
      }
      void insert(const T&x, const size_t&y){ // adding new elements but in a certain position
          if (y >sze) throw std::out_of_range("Out of range element!\n");
          T* new_data = (T*) realloc (data,sizeof(T) * (sze + 1));
          if(!new_data) throw std::bad_alloc();
          data = new_data;
          for(size_t i  = sze; i >y; --i )
            data[i] = data[i-1]; // copying the elements after the new element insertion
          data[y] = x;
          ++sze;
      }
      void erase(const size_t&x){  // deleting an element in a certain position
          if(x >=sze) throw std::out_of_range("Out of range element!\n");
          for(int i = x; i < sze-1; ++i)
            data[i] = data[i-1];
          sze--;
          T* new_data = (T*) realloc (data, sizeof(T) * sze);
          if(!data) throw std::bad_alloc();
          data = new_data;
      }
      const bool empty() const {return (sze == 0);} // a method that returns true if the vector is empty
};
template<typename T>
class vector<T>::iterator{
    private:
      vector&obj;
      size_t index;
    public:
      iterator() = default;
      iterator(vector&x, const size_t&y): obj(x), index(y){}
      iterator(const iterator&other) : obj(other.obj), index(other.index){}  // copy constructor
      iterator & operator = (const iterator & other){
          if(this == &other) return *this;
          this->obj = other.obj;
          this->index = other.index;
          return *this;
      }
      iterator operator++(){  // post & pre increment operators
          if(index >= this->obj.size()) throw std::out_of_range("Out of range element!\n");
           iterator temp = *this;
           ++index;
          return temp;
      }
      iterator operator++(const int x){
          if(index >= this->obj.size()) throw std::out_of_range("Out of range element!\n");
          iterator temp = *this;
          ++index;
          return temp;
      }
      bool operator != (const iterator&other){  // the uneqal operator 
          return this->index != other.index;
      }
      T&operator*(){   // derefrencing operator for the iterator
          return this->obj[index];
      }
};
int main(){
    vector<int>arr = {12,5434,66,44,22,55};  // declaring the vector fromn the type 'int' and putting some elements on it. 
    for(auto&i:arr) std::cout<<i<<'\t';  // iterating through the elements of the vector using the range base loop
    std::cout<<std::endl;
    arr[2] = 1956;  // modifying the the third element in the vector using the operator []
    arr.insert(666,4);  // using the method 'insert'
    for(vector<int>::iterator it = arr.begin(); it != arr.end(); it++) // iterating through the vector using the classic c++98 method
      std::cout<<*it<<'\t';  // derefrencing the iterator
    std::cout<<std::endl;
    std::cout<<arr.size()<<std::endl;  // trying the method 'size'
    arr.push_back(741);  // adding elements to the vector using the method 'push_back'
    arr.erase(4);  // using the method 'erase' to get rid of the element in the fifth position in the vector
    for(auto&i:arr) std::cout<<i<<'\t';
    std::cout<<std::endl;
    return 0;
}