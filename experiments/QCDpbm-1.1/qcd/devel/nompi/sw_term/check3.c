
/*******************************************************************************
*
* File check3.c
*
* Copyright (C) 2005 Martin Luescher
*
* This software is distributed under the terms of the GNU General Public
* License (GPL)
*
* Test of mul_pauli_dble
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.h"
#include "start.h"
#include "sw_term.h"


int main(void)
{
   int i,j,k;
   complex_dble *a,*s,*r1,*r2,z;
   pauli_dble *m;

   printf("\n");
   printf("Test of mul_pauli_dble\n");
   printf("----------------------\n\n");

   a=amalloc(54*sizeof(complex_dble),4);
   m=amalloc(1*sizeof(pauli_dble),4);
   error((a==NULL)||(m==NULL),1,"main [check3.c]",
         "Unable to allocate auxiliary arrays");

   rlxd_init(1,3898);
   ranlxd((double*)(a),108);

   s=a+36;
   r1=s+6;
   r2=r1+6;

   for (i=0;i<6;i++)
   {
      for (j=i;j<6;j++)
      {
         if (j>i)
         {
            a[6*i+j].re=a[6*j+i].re;
            a[6*i+j].im=-a[6*j+i].im;
         }
         else
            a[6*i+j].im=0.0;
      }
   }

   k=6;
   
   for (i=0;i<6;i++)
   {
      (*m).u[i]=a[6*i+i].re;

      for (j=i+1;j<6;j++)
      {
         (*m).u[k]=a[6*i+j].re;
         k+=1;
         (*m).u[k]=a[6*i+j].im;
         k+=1;
      }
   }
   
   for (i=0;i<6;i++)
   {
      z.re=0.0;
      z.im=0.0;
      
      for (j=0;j<6;j++)
      {
         z.re+=(a[6*i+j].re*s[j].re-a[6*i+j].im*s[j].im);
         z.im+=(a[6*i+j].re*s[j].im+a[6*i+j].im*s[j].re);
      }

      r1[i].re=z.re;
      r1[i].im=z.im;
   }
   
   mul_pauli_dble(m,(weyl_dble*)(s),(weyl_dble*)(r2));

   printf("r1: expected result, r2: actual result\n\n");
   
   for (i=0;i<6;i++)
   {
      printf("r1[%d]=(%.16e,%.16e)\n",i,r1[i].re,r1[i].im);
      printf("r2[%d]=(%.16e,%.16e)\n\n",i,r2[i].re,r2[i].im);
   }

   exit(0);
}
