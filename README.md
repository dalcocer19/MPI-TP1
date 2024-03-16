# MPI-TP1
Detalles de la implementacion

La rutina MPI_Scatter() solicita en uno de sus parametros indicarle la longitud del particionado del vector original es decir cuantos elementos tiene que recibir cada proceso. Por lo que al ejecutar el comando mpirun -np 4 doy a entender que existen 4 procesos por lo que un numero impar de elementos del vector original puede ocasionar que algunos de los procesos reciba un elemento o ninguno. Por lo tanto, el numero de nucleos (core) tiene que ser multiplo de la longitud del vector original para que haya una correcta operacion entre el escalar y el vector.
