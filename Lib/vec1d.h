

#ifndef Vec1D_h
#define Vec1D_h






class vec1D         
{
public:
        vec1D(unsigned int size = 1, int offset = 0, const float* data = 0);
        vec1D(const vec1D& v);
        ~vec1D();

        inline int first() const;                      
        inline int last() const;                        
        inline unsigned int size() const;               
        inline const float* data() const;                 
        inline const float* data(int i) const;          
        inline float& operator()(int x);              
        inline float operator()(int x) const;          
        inline float& operator[](int x);                
        inline float operator[](int x) const;           
        inline const vec1D& operator=(const vec1D& v);  

private:
        int m_offset;
        int m_last;
        unsigned int m_size;
        float* m_data;

        void init(const vec1D& v);
        void close();

};


inline int vec1D::first() const
{ 
        return m_offset; 
}

inline int vec1D::last() const
{ 
        return m_last; 
}

inline unsigned int vec1D::size() const
{ 
        return m_size; 
}

inline float& vec1D::operator()(int x)
{ 
        return m_data[x];
}

inline float vec1D::operator()(int x) const
{
        return m_data[x];
}

inline float& vec1D::operator[](int x)
{ 
        return m_data[x];
}

inline float vec1D::operator[](int x) const
{
        return m_data[x];
}

inline const vec1D& vec1D::operator=(const vec1D& v)
{
        if (this != &v)
                init(v);
        
        return *this;    
}

inline const float* vec1D::data() const
{ 
        return &m_data[first()]; 
}

inline const float* vec1D::data(int i) const
{
        return &m_data[i]; 
}


#endif