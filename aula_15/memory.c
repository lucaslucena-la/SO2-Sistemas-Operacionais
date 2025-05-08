// Gerenciamento de memória (área de heap)

#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "proc.h"
#include "riscv.h"

extern char stack_end[]; //do kernel.ld
extern char stack_start[];
extern char text_end[]; // término do código do kernel

#define HEAP_START stack_end
#define HEAP_END (uint8*)(KERNEL_START + MEMORY_LENGTH)
#define HEAP_SIZE ((uint64)HEAP_END - (uint64)HEAP_START)
#define TEXT_SIZE ((uint64)text_end - KERNEL_START)
#define FREEPG 0x01
#define LASTPG 0x02

long total_pages;
long alloc_start; // início da área de alocação

TrapFrame trapframe; // ponteiro para o trap frame

// A página desc está livre?
int free_page(uint8 desc) {
    if (desc & FREEPG) return 1;
    return 0;
}

 // A página desc é a última página de um bloco previamente alocado?
 // usada pelo kfree
int
last_page(uint8 desc) {
    if (desc & LASTPG) return 1;
    return 0;
}

void set_free_page_flag(uint8 *desc, uint8 flag){
    if(flag == FREEPG){
        *desc = *desc | FREEPG;
    }
    else { // setar o bit 0 para 0
        *desc = *desc & ~FREEPG;
    }
}

void set_last_page_flag(uint8* desc, uint8 flag){
    if(flag == LASTPG){ //LASTPG = 0000.0010
        *desc = *desc | LASTPG;
    }
    else { // setar o bit 1 para 0
        *desc = *desc & ~LASTPG;
    }
}

// ArredondA o endereço para a próxima página
// 5000 -> 8192
// 4090 -> 4096
uint64 page_round_up(uint64 addr) {
    if(addr % PAGE_SIZE == 0) return addr; //já é múltiplo de PAGE_SIZE
    return addr + PAGE_SIZE - (addr % PAGE_SIZE);
}

// Inicializa a lista de descritores do heap
void pages_init() {
    uint8 *desc = (uint8*)HEAP_START;
    int reserved_pages; // páginas reservadas para os descritores
    total_pages = HEAP_SIZE / PAGE_SIZE;
    reserved_pages = total_pages / PAGE_SIZE;
    if(total_pages % PAGE_SIZE != 0) reserved_pages++;

    total_pages -= reserved_pages; // páginas disponíveis para alocação
    for(int i = 0; i < total_pages; i++){
        desc[i] = FREEPG; //ou
        // *desc++ = FREEPG;
    }
    printf("Páginas reservadas p/ os descritores: %d\n", reserved_pages);
    // As páginas precisam ser alinhadas (múltiplo de PAGE_SIZE)
    alloc_start = page_round_up((uint64)HEAP_START + reserved_pages * PAGE_SIZE);
}

void* kalloc2(){
    uint8 *ptr;
    uint8 *fp_desc = 0; // descritor da página livre encontrada
    for(int i = 0; i < total_pages; i++) {
        ptr = (uint8 *)HEAP_START + i;
        if(free_page(*ptr)){ 
            fp_desc = ptr;
            break;
        }
    }
    if(fp_desc == 0) return 0; //não há páginas livres
    set_free_page_flag(fp_desc, !FREEPG); //seta o bit 0 para 0
    //retornar o endereço da página alocada
    int desc_pos = (uint64)fp_desc - (uint64)HEAP_START;
    return (void *)(desc_pos * PAGE_SIZE + alloc_start);
}

// Aloca n páginas
// void* kalloc2(int pages);
// Libera a memória alocada
void Kfree(void *ptr);
// Copiar a string s para a memória alocada
void kstrcpy(char *s, void *ptr);


void *
kalloc(int pages) {
    // início da lista dos descritores de página
    uint8 * ptr = (uint8 *) HEAP_START;
    int i;
    int count = 0;
    uint8 * desc = 0; // O descritor da primeira página do bloco alocado
    
    if (pages == 0)
        return 0;
    for(i = 0; i < total_pages; i++) {
        ptr = (uint8 *) HEAP_START + i;
        if(free_page(*ptr)) {
            if (count == 0) 
                desc = ptr;
            count++;
        }
        else {
            count = 0;
            desc = 0;
        }
        if (count == pages) break;
    }
    if (count < pages)
        desc = 0;
    if (desc != 0) {
        for (i = 0; i < pages; i++) {
            set_free_page_flag(desc+i, !FREEPG);
            set_last_page_flag(desc+i, !LASTPG);
        }
        set_last_page_flag(desc + (i-1), LASTPG);
        printf(" Páginas alocadas:%d\n", i);
        return (uint8 *)(alloc_start + ((uint64)desc - (uint64)HEAP_START) * PAGE_SIZE); 
    }
    return 0;
}

void memory_init(){
    pages_init();

    // Copiar o endereço de trapframe para o reg. mscratch
    w_mscratch((uint64)&trapframe); 
    trapframe.trap_stack = kalloc(1);  // pilha de trap: 4096 bytes
    printf("Início da área de alocação: %p\n", alloc_start);
    char *p = kalloc(1);
    // *p = 'U';
    // *(p+1) = 'F';
    // *(p+2) = 'M';
    // *(p+3) = 'T';
    // *(p+4) = 0;
    p[0] = 'U';
    p[1] = 'F';
    p[2] = 'M';
    p[3] = 'T';
    p[4] = 0;
    printf("Endereço da memória alocada (página 1): %p\n", p);
    printf("String armazenada: %s\n", p);
    char *q = kalloc(1);
    printf("Endereço da memória alocada (q): %p\n", q);
}

//Estatísticas de uso da memória
void stats(){
    printf("Tamanho código: %d\n", (uint64)text_end - KERNEL_START);
    
}