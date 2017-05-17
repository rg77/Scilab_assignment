// Standard header
#include "api_scilab.h"
#include "BOOL.h"
#include "Scierror.h"


// Function declaration
int multiply(char *fname, unsigned long fname_len)
{
     // Error management variable
    SciErr sciErr;

    ////////// Variables declaration //////////
    int m1 = 0, n1 = 0;
    int *piAddressVarOne = NULL;
    double *mat1 = NULL;
    
    int m2 = 0, n2 = 0;
    int *piAddressVarTwo = NULL;
    double *mat2 = NULL;
    
    double *product_mat = NULL;

    
    //loop variables
    int i,j,k;

    ////////// Check the number of input and output arguments //////////
    /* --> r = multilply(mat1, mat2) */
    /* check that we have only 2 input arguments */
    CheckInputArgument(pvApiCtx, 2, 2) ;
    /* check that we have only 1 output argument */
    CheckOutputArgument(pvApiCtx, 1, 1) ;

    ////////// Manage the first input argument (double) //////////
    /* get Address of inputs */
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    /* Check that the first input argument is a real matrix (and not complex) */
    if ( !isDoubleType(pvApiCtx, piAddressVarOne) ||  isVarComplex(pvApiCtx, piAddressVarOne) )
    {
        Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 1);
        return 0;
    }

    /* get matrix */
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarOne, &m1, &n1, &mat1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    ////////// Manage the second input argument (double) //////////

    /* get Address of inputs */
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    /* Check that the second input argument is a real matrix (and not complex) */
    
    if ( !isDoubleType(pvApiCtx, piAddressVarTwo) ||  isVarComplex(pvApiCtx, piAddressVarTwo) )
    {
        Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 2);
        return 0;
    }

    /* get matrix */
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarTwo, &m2, &n2, &mat2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    ////////// Check the consistency of the two input arguments //////////

    if ( !(n1==m2) )
    {
    
     Scierror(999, "%s: Wrong size for input arguments: No. of column in 1st matrix should be equal to no. of row of 2nd matrix.\n", fname);
        return 0;
    }

    
    ////////// Allocating size for the product matrix //////////
    
    product_mat = (double*)malloc(sizeof(double) * m1 * n2);
    
    
    ////////// Performing multiplication of the 2 input matrices //////////
    /*
        
                                                    --     --
                                                    | 1 4 7 |
     NOTE:  eg. a 3x3 matrix is refferenced as A =  | 2 5 8 |
                                                    | 3 6 9 |
                                                    --     --
    */
    for (i = 0; i < n2; i++) // i is related to column
    {
        
       for (j = 0; j < m1; j++) // j is related to row
       {
            product_mat[i*m1 + j] = 0;
            
            for (k = 0; k < m2; k++)
            {
                
               product_mat[i*m1 + j] += mat1[j + k*m1 ] * mat2[i*m2 + k] ;
            } 
       } 
    
    }  
    
    ////////// Create the output arguments //////////

    /* Create the matrix as return of the function */
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, m1, n2, product_mat);
    free(product_mat); // Data have been copied into Scilab memory
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    ////////// Return the output arguments to the Scilab engine //////////

    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    
    ReturnArguments(pvApiCtx); 
    
    return 0;
}


