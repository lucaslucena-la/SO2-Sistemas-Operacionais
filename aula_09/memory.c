#include "types.h"
#include "defs.h"
#include "memlayout.h"


extern char stack_end[]; //do kernel.ld 
extern char stack_start[];
extern char text_end[];

#define HEAP_START stack_end
#define HEAP_END (uint8*)(KERNEL_START + MEMORY_LENGTH)
#define HEAP_SIZE ((uint64)HEAP_END - (uint64)HEAP_START)
#define TEXT_SIZE ((uint64)text_end -KERNEL_START)
#define FREEPG 0x01 
#define LASTPG 0x02

long total_pages;
long alloc_start;

//a pagina desc está livre?
int free_page(uint8 desc){
    //olhar se o bit 0 é zero ou um, usando mascara
    if(desc & FREEPG){
        return 1;
    }else{
        return 0;
    }
}


//quero saber se a pagina desc é a ultima
//usada pelo kfree
int last_page(uint8 desc){
    //olhar se o bit 1 é zero ou um, usando mascara
    if(desc & LASTPG){
        return 1;
    }else{
        return 0;
    }
}

void set_free_page_flag(uint8 *desc, uint8 flag){
    if(flag == FREEPG){
        *desc = *desc | FREEPG;
    }else{//setar o bit 0 para 0
        *desc = *desc & ~FREEPG;
    }
}

void set_last_page_flag(uint8 *desc, uint8 flag){
    if(flag == LASTPG){
        *desc = *desc | LASTPG;
    }else{
        *desc = *desc & ~LASTPG;
    }
}

//arredonda o endereço para a próxima página
uint64 page_round_up(uint64 addr){
    if(addr % PAGE_SIZE ==0) return addr;
    return addr + PAGE_SIZE - (addr % PAGE_SIZE); // Se o endereço for multriplo de 4KB, retorna o próprio endereço
    
    
}

//inicializa a lista de descritores do heap
void page_init(){
    uint8 *desc = (uint8*)HEAP_START;
    int reserverd_pages; //paginas reservadas para os descritores 
    total_pages = HEAP_SIZE / PAGE_SIZE;//quantas paginas tem no heap
    reserverd_pages = total_pages / PAGE_SIZE;//quantas paginas são reservadas para os descritores
    if(total_pages %PAGE_SIZE != 0 ){
        reserverd_pages++;
    }

    total_pages -= reserverd_pages; //paginas disponiveis para a alocação
    for(int i = 0 ; i< total_pages; i++){ //inicializa as paginas disponiveis
        *desc++ =FREEPG; //seta o bit 0 para 1 
    }
    printf("Páginas resverdas para os descritores: %d\n", reserverd_pages);
    alloc_start =  page_round_up(( uint64)(HEAP_START +reserverd_pages * PAGE_SIZE ));// endreço inicial para alocar memória
}

void print_memory_statistics() {
    uint64 text_start = KERNEL_START; //endereço inicial do texto
    uint64 text_end_addr = (uint64)text_end; //endereço final do texto
    uint64 stack_start_addr = (uint64)stack_start; //endereço inicial da pilha
    uint64 stack_end_addr = (uint64)stack_end; // endereço final da pilha   
    
    printf("Codigo start: %p\n" , text_end);
    printf("Codigo end: %p\n" , stack_start);
    printf("Tamanho do código: %d Bytes\n", stack_start - text_end);

    printf("Text Start: %p \n", text_start); //endereço inical do texto
    printf("Text End: %p \n", text_end_addr ); //endereço final do texto
    printf("Text Size: %d Bytes\n", text_end - text_start );//tamanho do texto

    printf("Stack Start: %p \n", stack_start_addr ); //endereço inicial da pilha
    printf("Stack End: %p \n", stack_end_addr );//endereço final da pilha
    printf("Stack Size: %d Bytes\n", (stack_end_addr - stack_start_addr) );//tamanho da pilha
}


void *kalloc(){
    uint8 *ptr;
    uint8 *fp_desc = 0;//descritor da pagina livre encontrada
    for (int i =0; i< total_pages; i++){
        ptr =(uint8*) HEAP_START + i;
        if(free_page(*ptr)){
            fp_desc = ptr;
            break;
        }
    }
    if (fp_desc == 0) return 0;
    set_free_page_flag(fp_desc, !FREEPG);//seta o bit 0 para 0
    //retornar o endereço da pagina alocada
    int desc_pos = (uint64)fp_desc - (uint64)HEAP_START;
    return(void*)(desc_pos * PAGE_SIZE + alloc_start);  

}

void memory_init(){
    page_init();
    printf("Inicio da área de alocação: %p\n", alloc_start);
    //testar a função kalloc
    char *p = kalloc();
    p[0] = 'U';
    p[1] = 'F';
    p[2] = 'M';
    p[3] = 'T';

    printf("Endereço de alocação (pagina 1): %p\n", p);
    printf("String armazenada: %s\n", p);

    char *q = kalloc();
    printf("Endereço de alocação(pagina 2): %p\n", q);

}