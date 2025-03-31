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
    if(addr % PAGE_SIZE ==0){
        return addr + PAGE_SIZE - (addr % PAGE_SIZE); // Se o endereço for multriplo de 4KB, retorna o próprio endereço
    }
    
}

//inicializa a lista de descritores do heap
void page_init(){
    uint8 *desc = (uint8*)HEAP_START;
    int reserverd_pages; //paginas reservadas para os descritores 
    total_pages = HEAP_SIZE / PAGE_SIZE;
    reserverd_pages = total_pages / PAGE_SIZE;
    if(total_pages %PAGE_SIZE != 0 ){
        reserverd_pages++;
    }

}
