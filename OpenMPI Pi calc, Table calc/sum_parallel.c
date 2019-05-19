#include <stdio.h>
#include <mpi.h>
#define SIZE 50000

MPI_Status status;
MPI_Request request;
main (int argc, char *argv[])
{
	int size, proc, rank, dest, index, i, source, chunksize, sum, Tsum;
	int data1[SIZE], data2[SIZE];
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	proc = size; /* Συνολικός Αριθμών proc */
/* πόσο κομμάτι του πίνακα θα στείλουμε σε κάθε rank */
	chunksize = (SIZE / proc);
/* Η διεργασία 0 δίνει αρχικές τιμές, στέλνει σε κάθε υπόλοιπη διεργασία το τμήμα του πίνακα που αναλογεί και λαμβάνει τα αποτελέσματα */
	if (rank == 0) {
/* αρχικές τιμές στον data1[] */
		for (i=0; i < SIZE; i++) { data1[i] = i+1; }
		index = 0;
		for (dest=1; dest < proc; dest++) {
			MPI_Send (&index, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
			MPI_Send (&data1[index], chunksize, MPI_INT, dest, 0, MPI_COMM_WORLD);
			index = index + chunksize; 
		}
		Tsum = 0;
		for (i=1; i < proc; i++) {
		source = i;
/* λήψη αποτελεσμάτων από κάθε διεργασία */
		MPI_Recv (&sum, 1, MPI_INT, source, 0,MPI_COMM_WORLD, &status);
		Tsum = Tsum + sum;
		printf("-------------------------------------------------------------------\n");
		printf("Received from process: %d, Sum: %d \n", source, sum); }
		printf("Total Sum Received: %d \n", Tsum);
		printf("All Done! \n"); 
	}
/* Κάθε διεργασία με rank>0 θα υπολογίζει το άθροισμα */
	if (rank > 0) {
		MPI_Recv (&index, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv (&data2[index], chunksize, MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
		for (i = index; i < index + chunksize; i++) { sum = sum + data2[i]; }
/* κάθε διεργασία με rank>0 θα στέλνει το μερικό άθροισμα */
		MPI_Send (&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return(0);
}
