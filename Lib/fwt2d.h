

#ifndef FWT2D_H
#define FWT2D_H


class BaseFWT2D;

class FWT2D : public BaseFWT2D    
{
public:
        FWT2D(const wchar_t *fname);
        FWT2D(const wchar_t* fname, const float* tH, unsigned int thL, int thZ,
              const float* tG, unsigned int tgL, int tgZ,
              const float* H, unsigned int hL, int hZ,
              const float* G, unsigned int gL, int gZ);


private:
        void transrows(char** dest, char** sour, unsigned int w, unsigned int h) const;
        void transcols(char** dest, char** sour, unsigned int w, unsigned int h) const;
        void synthrows(char** dest, char** sour, unsigned int w, unsigned int h) const;
        void synthcols(char** dest, char** sour, unsigned int w, unsigned int h) const;
};






#endif