#include "safe_msg_queue.h"
#include <stdio.h>


char *slogon = 
"\
  _  _       _  _       __      __ ___  _____   ___      _____                     _     _  _ \r\n\
 | || | ___ | || | ___  \\ \\    / /| _ \\|_   _| |_ _| ___|_   _| __ __ __ ___  _ _ | | __| || |\r\n\
 | __ |/ -_)| || |/ _ \\ _\\ \\/\\/ / |   /  | |    | | / _ \\ | |   \\ V  V // _ \\| '_|| |/ _` ||_|\r\n\
 |_||_|\\___||_||_|\\___/( )\\_/\\_/  |_|_\\  |_|   |___|\\___/ |_|    \\_/\\_/ \\___/|_|  |_|\\__,_|(_)\r\n\
                       |/\r\n\                                                                     
\
";
const char *wrt_z3_slogon = 
"\
*****************************************************************************************************************************************************\r\n\
*                                                                                                                                                   *\r\n\
*██╗  ██╗███████╗██╗     ██╗      ██████╗    ██╗    ██╗██████╗ ████████╗   ██╗ ██████╗ ████████╗    ██╗    ██╗ ██████╗ ██████╗ ██╗     ██████╗ ██╗  *\r\n\
*██║  ██║██╔════╝██║     ██║     ██╔═══██╗   ██║    ██║██╔══██╗╚══██╔══╝   ██║██╔═══██╗╚══██╔══╝    ██║    ██║██╔═══██╗██╔══██╗██║     ██╔══██╗██║  *\r\n\
*███████║█████╗  ██║     ██║     ██║   ██║   ██║ █╗ ██║██████╔╝   ██║█████╗██║██║   ██║   ██║       ██║ █╗ ██║██║   ██║██████╔╝██║     ██║  ██║██║  *\r\n\
*██╔══██║██╔══╝  ██║     ██║     ██║   ██║   ██║███╗██║██╔══██╗   ██║╚════╝██║██║   ██║   ██║       ██║███╗██║██║   ██║██╔══██╗██║     ██║  ██║╚═╝  *\r\n\
*██║  ██║███████╗███████╗███████╗╚██████╔╝▄█╗╚███╔███╔╝██║  ██║   ██║      ██║╚██████╔╝   ██║       ╚███╔███╔╝╚██████╔╝██║  ██║███████╗██████╔╝██╗  *\r\n\
*╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚═╝ ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝ ╚═════╝    ╚═╝        ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═════╝ ╚═╝  *\r\n\ 
*                                                                                                                                                   *\r\n\       
*****************************************************************************************************************************************************\r\n\
";

typedef struct{
	int id;
	int sum;
}Student;



int main(int argc, char *argv[])
{

    printf("%s \r\n", wrt_z3_slogon);

    slist_t* list = slist_alloc();

	// + 3 -2 + 3 = 4
	// add 3 items
	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 100;
		student->id = 1;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 200;
		student->id = 2;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 300;
		student->id = 3;
		slist_push_back(list, node);
	}while(0);

	printf("1.size:%zu\n", slist_size(list) );

	// remove 2 items
	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\t RM id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list) );
		}
	}while(0);

	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\t RM id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list)  );
		}
	}while(0);

	printf("2.size:%zu\n", slist_size(list) );
	// add 3 items
	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 400;
		student->id = 4;
		slist_push_back(list, node);
        printf("\t ADD id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list)  );
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 500;
		student->id = 5;
		slist_push_back(list, node);
        printf("\t ADD id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list)  );
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 600;
		student->id = 6;
		slist_push_back(list, node);
        printf("\t ADD id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list)  );
	}while(0);

	printf("3.size:%zu\n", slist_size(list) );

	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\t RM id:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list) );
			continue;
		}

		assert(0 && "Never go to here!");
	}while( slist_size(list) > 0);

	printf("4.size:%zu\n", slist_size(list) );
    return 0;
}