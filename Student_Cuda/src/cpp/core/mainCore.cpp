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
//extern bool useSlice(void);
//extern bool useMontecarlo(void);
<<<<<<< HEAD
//extern bool useMontecarloMulti(void);
extern bool useHistogramme();
=======
extern bool useMontecarloMulti(void);
>>>>>>> eef3e8f358f43a0eaa4f448cf1781c703e0bbc35

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
    //isOk &= useSlice();
    //isOk &= useMontecarlo();
<<<<<<< HEAD
    //isOk &= useMontecarloMulti();
    isOk &= useHistogramme();
=======
    isOk &= useMontecarloMulti();
>>>>>>> eef3e8f358f43a0eaa4f448cf1781c703e0bbc35

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

