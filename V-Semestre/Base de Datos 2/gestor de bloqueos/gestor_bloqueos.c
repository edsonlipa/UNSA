#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct data {
	int bloqueado;
	char identificador;
	char * dato_string;
	int dato_int;
	// std::vector<int> trans;
};

void Read(struct data dato) {

printf("/* leendo dato */ %s y entero: %d\n",dato.dato_string,dato.dato_int );

}

void Write(struct data *dato,char * new_data,int nuevo) {
	dato->dato_string=new_data;
	dato->dato_int+=nuevo;
	printf("/* sobreescribiendo dato */ %s y entero: %d\n",dato->dato_string,dato->dato_int );
}
void wait(struct data* dato) {
	while (dato->bloqueado==1) {
		// std::cout << "esperando" << '\n';
		printf("esperando ...\n" );
	}
}
void lock_X(struct data* dato) {//bloqueo exclusivo
	dato->bloqueado=1;
}
void unlock(struct data* dato) {//desbloqueo exclusivo
	dato->bloqueado=0;
}

void lock_S(struct data* dato) {//bloqueo compartido
	wait(dato);
	// dato.bloqueado=false;
}
void add_data(struct data *manager,char id, char * data_string,int dato_i) {
	struct data new_data;
	new_data.identificador=id;
	new_data.dato_string=data_string;
	new_data.dato_int=dato_i;
	int code=(int) id;
	manager[code]=new_data;
}
void * T1 ( void * arg ) {

	struct data *manager=(struct data *)arg;

	int code=(int) 'A';
	lock_X(&manager[code]);
	Read(manager[code]);
	Write(&manager[code],"actualizacion T1 A",-50);
	usleep (1000050);
	unlock(&manager[code]);
	// printf("%s\n",dato.dato_string );

	return NULL ;
}

void * T2 ( void * arg ) {
		struct data *manager=(struct data *)arg;
		int codea=(int) 'A';
		usleep (1000000);
		lock_S(&manager[codea]);

		Read(manager[codea]);
		// usleep (1000000);
		unlock(&manager[codea]);

		return NULL ;
}
void * T3 ( void * arg ) {

	struct data *dato=(struct data *)arg;
	int code=(int) 'B';

	printf("%d\n",code );
	lock_X(&dato[code]);
	Read(dato[code]);
	Write(&dato[code],"actualizacion t3 B",-50);
	usleep (1000000);
	unlock(&dato[code]);
	// usleep (1000000);

	int codea=(int) 'A';
	printf("%d\n",codea );
	lock_X(&dato[codea]);
	Read(dato[codea]);
	Write(&dato[codea],"actualizacion t3 A",-50);
	usleep (1000000);
	unlock(&dato[codea]);
	// printf("%s\n",dato.dato_string );

	return NULL ;
}

void * T4 ( void * arg ) {
		struct data *manager=(struct data *)arg;
		int codea=(int) 'A';
		usleep (1000000);
		lock_S(&manager[codea]);
		Read(manager[codea]);
		unlock(&manager[codea]);

		int codeb=(int) 'B';
		lock_S(&manager[codeb]);
		Read(manager[codeb]);
		unlock(&manager[codeb]);
		Read(manager[codea]);
		Read(manager[codeb]);

		usleep (1000000) ;
		return NULL ;
}

int main(int argc, char const *argv[]) {
  struct data manager[100];
	add_data(manager,'A',"informacion del dato A",100);
	add_data(manager,'B',"informacion del dato B",500);

	pthread_t h1;
	pthread_t h2;

	pthread_create(&h2 , NULL , T1 , (void *) manager );
	pthread_create(&h1 , NULL , T2 , (void *) manager );
	pthread_join ( h1 , NULL ) ;
	pthread_join ( h2 , NULL ) ;
	printf ( " Fin \n ");

	return 0;
}
