#include <iostream>
#include <stdlib.h>


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

//extern bool useHello(void);
//extern bool useAddVecteur(void);
<<<<<<< HEAD
extern bool useSlice(void);
extern bool useMontecarlo(void);
extern bool useMontecarloMulti(void);
extern bool useHistogramme();
=======
//extern bool useSlice(void);
//extern bool useMontecarlo(void);
extern bool useMontecarloMulti(void);
//extern bool useHistogramme();
>>>>>>> 1593fa2f5fb234a03d52fef245de8c8738ec5fac


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore()
    {
    bool isOk = true;
   // isOk &= useHello();
    //isOk &=useAddVecteur();
<<<<<<< HEAD
    isOk &= useSlice();
    isOk &= useMontecarlo();
    isOk &= useMontecarloMulti();
    isOk &= useHistogramme();
=======
    //isOk &= useSlice();
    //isOk &= useMontecarlo();
    isOk &= useMontecarloMulti();
    //isOk &= useHistogramme();
>>>>>>> 1593fa2f5fb234a03d52fef245de8c8738ec5fac

    cout << "\nisOK = " << isOk << endl;
    cout << "\nEnd : mainCore" << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

