include_directories(.)

# generate_avr_library(matrix
#        MOCK
#        BOARD uno
#        SRCS caxpy.c      cher2.c   csyrk.c  ddot.c    dsdot.c   dtbsv.c   isamax.c  sger.c    ssymm.c   strsm.c      zgeru.c   zswap.c
#        ccopy.c      cher2k.c  ctbmv.c  dgbmv.c   dspmv.c   dtpmv.c   izamax.c  snrm2.c   ssymv.c   strsv.c      zhbmv.c   zsymm.c
#        cdotc_sub.c  cher.c    ctbsv.c  dgemm.c   dspr2.c   dtpsv.c   sasum.c   srot.c    ssyr2.c   xerbla.c     zhemm.c   zsyr2k.c
#        cdotu_sub.c  cherk.c   ctpmv.c  dgemv.c   dspr.c    dtrmm.c   saxpy.c   srotg.c   ssyr2k.c  zaxpy.c      zhemv.c   zsyrk.c
#        cgbmv.c      chpmv.c   ctpsv.c  dger.c    dswap.c   dtrmv.c   scasum.c  srotm.c   ssyr.c    zcopy.c      zher2.c   ztbmv.c
#        cgemm.c      chpr2.c   ctrmm.c  dnrm2.c   dsymm.c   dtrsm.c   scnrm2.c  srotmg.c  ssyrk.c   zdotc_sub.c  zher2k.c  ztbsv.c
#        cgemv.c      chpr.c    ctrmv.c  drot.c    dsymv.c   dtrsv.c   scopy.c   ssbmv.c   stbmv.c   zdotu_sub.c  zher.c    ztpmv.c
#        cgerc.c      cscal.c   ctrsm.c  drotg.c   dsyr2.c   dzasum.c  sdot.c    sscal.c   stbsv.c   zdscal.c     zherk.c   ztpsv.c
#        cgeru.c      csscal.c  ctrsv.c  drotm.c   dsyr2k.c  dznrm2.c  sdsdot.c  sspmv.c   stpmv.c   zgbmv.c      zhpmv.c   ztrmm.c
#        chbmv.c      cswap.c   dasum.c  drotmg.c  dsyr.c    hypot.c   sgbmv.c   sspr2.c   stpsv.c   zgemm.c      zhpr2.c   ztrmv.c
#        chemm.c      csymm.c   daxpy.c  dsbmv.c   dsyrk.c   icamax.c  sgemm.c   sspr.c    strmm.c   zgemv.c      zhpr.c    ztrsm.c
#        chemv.c      csyr2k.c  dcopy.c  dscal.c   dtbmv.c   idamax.c  sgemv.c   sswap.c   strmv.c   zgerc.c      zscal.c   ztrsv.c
#        LIBS)

# our own library
generate_avr_library(matrix
        MOCK
        BOARD uno
        SRCS matrix.c
        LIBS core)