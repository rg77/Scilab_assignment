**# Scilab_assignment_1**

**Q:** Write a C/C++ function multiply(mat1,mat2) which accepts two double matrices- mat1 & mat2 from Scilab console, checks if 
   the dimensions are correct for matrix multiplication, computes the product and displays the product on Scilab console.
   
 
**Sol:** Make sure that the current directory for Scilab is the one in which you have installed Scilab.
  Copy the file `"matrixMultiplication.c"` in this directory.
  Now execute the following command from the Scilab console:
  
 `files=["matrixMultiplication.c"];`
 
 `WITHOUT_AUTO_PUTLHSVAR = %t;`
 
 `ilib_build('build_lib',['multiply','multiply'],files,[]);`
 
 `exec loader.sce`
 
    
  Now perform the multiplication using the function multiply(mat1, mat2)   
  
  
  **eg 1)**-->result = multiply([1 2 ; 3 4] , [1 2; 3 4])
  
   result  =
 
    7.     10.  
    15.    22.` 
  
  
  **eg 2)**--> result2 = multiply([6 2 ; 9 0 ; -5 4] , [5 2 -7 0 5 ; 23 8 99 -1 5])
  
   result2  =
 
    76.    28.    156.  - 2.    40.  
    45.    18.  - 63.     0.    45.  
    67.    22.    431.  - 4.  - 5.`   
 
  
  **eg 3)** --> result3 = multiply([6 2 1 ; 9 0 1 ; -5 4 1] , [5 2 -7 0 5 ; 23 8 99 -1 5])
  
                                                             !--error 999 
multiply: Wrong size for input arguments: No. of column in 1st matrix should be equal to no. of row of 2nd matrix.
 
 **eg 4)**-->result4 = multiply([6 2 ],[%t %t])

                             !--error 999 
multiply: Wrong type for input argument #2: A real matrix expected.
