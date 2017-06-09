# Source Files

.)2a.c, 2d.c y 2e.c son los mains que se utilizaron para correr cada punto de la guía
.)ising.c y MvsT.c son unos tests preeliminares que se realizaron antes de correr los mains.
.)bimodal.c se encarga de acumular muchas repeticiones de E y M a una temperatura fija, para poder ver la distribucion de probabilidad

.)metropolis.c y metropolis.h contienen las funciones necesarias para correr el algoritmo de metropolis:
	-)metropolis() avanza un paso en la cadena de metropolis, actualizando los valores de energia y magnetizacion, ademas de cambiar la configuración del sistema si corresponde
	-)pick_site() se encarga de elegir un elemento de la red al azar
	-)flip() se encarga de cambiar la configuración del sistema
	-)energia() calcula la energia de la red
	-)vecinos() calcula el producto del spin iesimo con sus 4 vecinos, aplicando condiciones de contorno periodicas
	-)las funciones con el mismo nombre que las anteriores pero terminando en "2" se encargan de extender las interacciones a 2dos vecinos

.)lattice.c y lattice.h son las encargadas de llenar e imprimir la red:
	-)fill_lattice() llena la red con probabilidad p
	-)print_lattice() imprime la red en pantalla

.)correlacion.c y correlacion.h contienen las funciones de autocorrelacion:
	-)autocorr() llena un vector rho con las autocorrelaciones de la red
	-)esperanza() devuelve la esperanza de una tira de datos
	-)float_abs() es la funcion valor absoluto pero acepta flotantes

.)vecinos2test.c y vecinostest.c son dos mains chiquitos creados con el objetivo de testear las funciones vecinos2 y vecinos respectivamente