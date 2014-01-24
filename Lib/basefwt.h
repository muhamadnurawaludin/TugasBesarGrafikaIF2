

#ifndef BASEFWT2D_H
#define BASEFWT2D_H



class vec1D;

class BaseFWT2D
{        
public:
        BaseFWT2D(const wchar_t* fname);
        BaseFWT2D(const wchar_t* fname, const float* tH, unsigned int thL, int thZ,
                  const float* tG, unsigned int tgL, int tgZ,
                  const float* H, unsigned int hL, int hZ,
                  const float* G, unsigned int gL, int gZ);
        virtual ~BaseFWT2D();


        void init(unsigned int width, unsigned int height);                                
        void init(char* data, char* tdata, unsigned int width, unsigned int height);        
        void close(void);                                                                      

       
        int trans(unsigned int scales, unsigned int th = 0);                             
        int trans(const char* data, unsigned int scales, unsigned int th = 0);            
        int trans(const unsigned char* data, unsigned int scales, unsigned int th = 0);    
        int synth();                                                                       
        int synth(char* data);                                                             
        int synth(unsigned char* data);                                                   

        
        void remove_LLband();


        const wchar_t* status(int& status) const;                                           
        void tracefilters(const wchar_t* fname) const;                                      

        inline unsigned int width() const;                                                
        inline unsigned int height() const;                                                 
        inline char* getspec() const;                                                      
        inline char** getspec2d() const;                                                    
        inline char* gettspec() const;                                                      

        inline unsigned int getJ() const;
        inline void setJ(unsigned int j);                


protected:
        inline const vec1D& gettH() const;
        inline const vec1D& gettG() const;
        inline const vec1D& getH2m() const;
        inline const vec1D& getG2m() const;
        inline const vec1D& getH2m1() const;
        inline const vec1D& getG2m1() const;

        inline unsigned int getTH() const;

        inline char mmxround(float f) const;
        inline char mmxroundTH(float f) const;

       
        virtual void transrows(char** dest, char** sour, unsigned int w, unsigned int h) const = 0;      
        virtual void transcols(char** dest, char** sour, unsigned int w, unsigned int h) const = 0;      
        virtual void synthrows(char** dest, char** sour, unsigned int w, unsigned int h) const = 0;      
        virtual void synthcols(char** dest, char** sour, unsigned int w, unsigned int h) const = 0;     


private:

        int m_status;  


        wchar_t filter[_MAX_PATH];                     

        vec1D* tH;                                     
        vec1D* tG;
        vec1D* H;                                       
        vec1D* G;
        vec1D* H2m;                                   
        vec1D* G2m;
        vec1D* H2m1;                                  
        vec1D* G2m1;

        unsigned int J;                                
        unsigned int TH;                              

        unsigned int m_width;                          
        unsigned int m_height;                         
        char* spec;                                     
        char* tspec;                                    
        char** spec2d;                               
        char** tspec2d;                                


        vec1D* loadfilter(FILE* flt) const;           
        void makeHGsynth(void);                        

        void mmxmemcpy(char* dest, const char* sour, unsigned int size);                 
        void sub128(char* dest, const unsigned char* sour, unsigned int size);          
        void add128(unsigned char *dest, const char* sour, unsigned int size);           




        
        BaseFWT2D(BaseFWT2D& basefwt);
        const BaseFWT2D& operator=(const BaseFWT2D& basefwt);


};






inline unsigned int BaseFWT2D::getJ() const
{
        return J;
}

inline void BaseFWT2D::setJ(unsigned int j)
{
        J = j;
}

inline unsigned int BaseFWT2D::width() const
{
        return m_width;
}

inline unsigned int BaseFWT2D::height() const
{
        return m_height;
}

inline char* BaseFWT2D::getspec() const
{
        return spec;
}

inline char** BaseFWT2D::getspec2d() const
{
        return spec2d;
}

inline char* BaseFWT2D::gettspec() const
{
        return tspec;
}

inline const vec1D& BaseFWT2D::gettH() const
{
        return *tH;
}

inline const vec1D& BaseFWT2D::gettG() const
{
        return *tG;
}

inline const vec1D& BaseFWT2D::getH2m() const
{
        return *H2m;
}

inline const vec1D& BaseFWT2D::getG2m() const
{
        return *G2m;
}

inline const vec1D& BaseFWT2D::getH2m1() const
{
        return *H2m1;
}

inline const vec1D& BaseFWT2D::getG2m1() const
{
        return *G2m1;
}

inline unsigned int BaseFWT2D::getTH() const
{
        return TH;
}

inline char BaseFWT2D::mmxroundTH(float f) const
{
        char c[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        __m64 *mc = (__m64 *)c;

        __m128 mf = _mm_load_ss(&f);
        *mc = _mm_cvtps_pi8(mf);

        _mm_empty();

        int th = TH;
        if (th != 0) {                     
                if (c[0] > 0) {
                        if (c[0] <= th)
                                c[0] = 0;
                } else {
                        if (c[0] >= -th)
                                c[0] = 0;
                }
        }

      

        return c[0];
}

inline char BaseFWT2D::mmxround(float f) const
{
        char c[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        __m64 *mc = (__m64 *)c;

        __m128 mf = _mm_load_ss(&f);
        *mc = _mm_cvtps_pi8(mf);

        _mm_empty();

        return c[0];
}

#endif
