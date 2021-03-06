#ifndef LLIST_H
#define LLIST_H

#define max_name 1024
#define id_size 6

/***************************************************
** Prototypes for struct.  						  **
***************************************************/

// STRUCT PER LISTE
typedef struct lnode
{
  struct lnode* prev; 
  /* Pointer nodo precedente */
  struct lnode* next; 
  /* Pointer nodo successivo */
  void* data; 
  /* User data */
} node;

typedef struct llist
{
  struct lnode* head; 
  /* puntatore a testa */
  struct lnode* tail; 
  /* puntatore a coda */
  unsigned int size; 
  /* Size della linked list */
} list;


/* STRUCT PROTOCLLO */

typedef struct Prodotto{
	char items[max_name];
	float prezzo;
}Prodotto;

typedef struct Ordine{
	char items[max_name];
	int qt;
} Ordine;

typedef struct ristorante{
	char nome_rist[max_name];
	int fd_rist;
} Ristorante;

typedef struct rider{
	char id_rider[id_size];
	int fd_rider;
} Rider;


typedef struct operazione { //Tiene traccia delle richieste client-ristorante nel server
	char id_operazione[id_size];
    int fd_client;
    int fd_ristorante;
    int stato_operazione; 
	/*
		SE LO STATO E UGUALE A:
			1:  ->  per indicare che server prende un qualsiasi client (indicato dal campo "client") che fa richiesta del menu ricevuto dal ristorante.
			2:  ->	per indicare che il serve prende il ristorante (indicato dal campo "ristorante") e gli inoltre l'ordine ricevuto dal client.
			3:  ->  per indicare che il serve prende il client (indicato dal campo "client") e gli inoltre l'id del rider ricevuto dal ristorante.
			4:  ->  vuol dire che l'ordine è in fase di consegna
	*/
} Operazione;


typedef struct Info_ordine{
	list* ordini;
	char id_operazione[id_size]; //per identificarla nel server.
	int fd_rider; // rider che effettuerà la consegna
	int stato_ordine;
	/*
		SE LO STATO E UGUALE A:
		1: -> ordine nuovo
		2: -> ordine assegnato
		3: -> ordine consegnato
	*/
} Info_ordine;


/***************************************************
** Prototypes for linked list library functions.  **
** controlla llist.c.                             **
***************************************************/

/* Creating */
static node* create_node(void* data);
list* create_list(void);

/* Adding */
void push_front(list* llist, void* data);
void push_back(list* llist, void* data);

/* Removing */
int remove_front(list* llist, void (*free_func)(void *data));
int remove_back(list* llist, void (*free_func)(void *data));

/* Querying List */
void* front(list* llist);
void* back(list* llist);
int is_empty(list* llist);
int size(list* llist);

/* Freeing */
void empty_list(list* llist, void (*free_func)(void *data));

/* Traversal */
void traverse(list* llist, void (*do_func)(void *data));




/***************************************************
** Prototypes for function for protocol.  		  **
** controlla llist.c.                             **
***************************************************/

/* CONTROLLARE LA CORRISPONDENZA TIPI-DATO E VALORI PASSATI */

// cancella elemento in mezzo
void delete_node(list* llist, node* llnode);

// funzioni per creare gli oggetti
Prodotto* create_Prodotto (char *items, float prezzo);
Ristorante* create_Ristorante (char*nome_R, int fd_rist);
Ordine* create_Ordine (char*items,int qt);
Rider* create_Rider (char*id_rider, int fd_rider);
Operazione* create_Operazione(char *n, int a, int b, int c);
Info_ordine* create_Info_ordine(list*l, char *c, int s, int fd_rider);

// funzioni per cancellare gli oggetti
void free_Prodotto(void*data);
void free_Ristorante(void*data);
void free_Ordine(void*data);
void free_Rider(void*data);
void free_Operazione(void*data);
void free_Info_ordine(void *data);

// funzioni per stampare i risultati dei dati passati
void print_struct_Prodotto(void*data);
void print_struct_Ristorante(void*data);
void print_struct_Ordine(void*data);
void print_struct_Rider(void*data);
void print_struct_Operazione(void*data);
void print_struct_Info_ordine(void*data);




/* §§§§§§§§§§§ ALTRE FUNZIONI UTILI §§§§§§§§§§§*/

// stampa e scelta Ristorante nella list { usata dal CLIENTE}
int show_choose_resturant(list* llist);  // ritorna direttamente l'fd

// stampa e scelta Prodotti nella list (menu) {usata dal CLIENTE}
list* show_choose_product(list* llist); // ritorna la lista contenente l’ordine

// generare un stringa random
char *rand_string(char *str, size_t size);

// Function che cerca nella lista dei ristoranti dato il nome {usata dal SERVER}
node* find_resturant_by_name (list*l,char*nome_rist); // ritorna il nodo

// Function che cerca nella lista dei ristoranti dato l’fd {usata dal SERVER}
node* find_resturant_by_fd (list*l, int fd); // ritorna il nodo

// cerca l’Operazione dato l'fd del client {usata dal SERVER}
Operazione* find_resturant_operation(list *l,int fd,int st); // ritorna fd ristorante

// cerca l’Operazione dato l'fd del ristorante {usata dal SERVER}
Operazione* find_client_operation(list *l,int fd,int st); // ritorna fd client

// cerca l’Operazione dato l'id della Operazione {usata dal SERVER}
Operazione* find_id_operation(list *l, char*id);

// ritorna il nodo nella lista che ha id pari a quello dato {usata dal SREVER}
node* find_id_operation_node(list*l, char*id);

// cerca tra gli info ordini il nodo con fd pari a quello dato come argomento.
Info_ordine* find_Info_ordine(list*l, char *id);

//* FULL READ & FULL WRITE*//
void FullRead(int fd, void * buf, size_t count); //funzione wrapper fullRead
void FullWrite(int fd, const void * buf, size_t count); //funzione wrapper fullWrite

ssize_t fullRead(int fd, void * buf, size_t count);
ssize_t fullWrite(int fd, const void * buf, size_t count);


#endif

