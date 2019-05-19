void *compute_multiplication(void *t) {
	int i, sum, t_new;
	pthread_t id;
	
	t_new = *(int *)t;
	sum = 0;
	id = pthread_self();
	for (i=(t_new*dotstr.veclen); i<((t_new*dotstr.veclen) + dotstr.veclen); i++){
		
		sum+=dotstr.a[i] * dotstr.b[i];
		printf("Thread with ID : %u. Counted from %d to %d the Sum %f\n", (unsigned)id, (t_new*dotstr.veclen), ((t_new*dotstr.veclen) + dotstr.veclen), (float)sum);
		
	}
	
	pthread_mutex_lock(&mutexsum);
	dotstr.sum += sum;
	pthread_mutex_unlock(&mutexsum);
	printf("New global value: %f\n", dotstr.sum);
	pthread_exit((void *) 0);
}