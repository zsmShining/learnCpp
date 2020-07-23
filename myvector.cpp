#include<algorithm>

template<typename Object>
class myvector{
    private:
        int theSize;
        int theCapacity;
        Object *objects;
    public:
        static int SPARE_CAPACITY = 16;
        explicit myvector(int initSize=0):theSize{initSize},theCapacity{initSize+SPARE_CAPACITY}{
            objects = new Object[theCapacity];
        }

        myvector(const myvector &rhs):theSize{rhs.theSize},theCapacity{rhs.theCapacity},objects{nullptr}{
            objects = new Object[theCapacity];
            for(int k=0;k<theSize;++k){
                objects[k] = rhs.objects[k];
            }
        }

        myvector& operator=(const myvector &rhs){
            myvector copy = rhs;
            std::swap(*this,copy);
            return *this;
        }

        ~myvector(){delete[] objects;}

        myvector(myvector &&rhs):theSize{rhs.theSize},theCapacity{rhs.theCapacity},objects{rhs.objects}{
            rhs.objects = nullptr;
            rhs.theSize = 0;
            rhs.theCapacity = 0;
        }

        myvector &operator=(myvector &&rhs){
            std::swap(theSize,rhs.theSize);
            std::swap(theCapacity,rhs.theCapacity);
            std::swap(objects,rhs.objects);

            return *this;
        }

        void resize(int newSize){
            if(newSize>theCapacity)
                reserve(newSize*2);
            theSize = newSize;
        }

        void reserve(int newCapacity){
            if(newCapacity<theSize)
                return;
            Object *newArray = new Object[newCapacity];
            for(int k=0;k<theSize;++k)
                newArray[k] = std::move(objects[k]);
            theCapacity = newCapacity;
            std::swap(objects,newArray);
            delete[] newArray;
        }

        Object & operator[] (int index){return objects[index];}
        const Object & operator[](int index) const{return objects[index];}

        


};