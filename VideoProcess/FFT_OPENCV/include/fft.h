void compute_W(int n, double *W_re, double *W_im); 
void permute_bitrev(int n, double *A_re, double *A_im); 
int  bitrev(int inp, int numbits); 
int  log_2(int n);  
void fft_butterfly(int n, double *A_re, double *A_im, double *W_re, double *W_im);

#ifdef __cplusplus
extern "C"
{
#endif

void fft_1d(int N, double *A_re, double *A_im);
void _fft_2d(int W, int H,double *A_re,double *A_im,int shift);
void _ifft_2d(int W, int H,double *A_re,double *A_im,int shift);
#ifdef __cplusplus
};
#endif