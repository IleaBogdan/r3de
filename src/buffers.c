#include"buffers.h"

void init_buffer(buffer*bf,const Mesh*m){
    glGenVertexArrays(1,&bf->VAO);
    glGenBuffers(1,&bf->VBO);
    glGenBuffers(1,&bf->EBO);

    glBindVertexArray(bf->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,bf->VBO);
    glBufferData(GL_ARRAY_BUFFER,m->vertex_count*sizeof(float),m->vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bf->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m->index_count*sizeof(unsigned int),m->indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    bf->mesh_index_count=m->index_count;
}

void draw_shape(const buffer*bf){
    glBindVertexArray(bf->VAO);
    glDrawElements(GL_TRIANGLES,bf->mesh_index_count,GL_UNSIGNED_INT,0);
}

void push(stack_buf**head,buffer val){
    stack_buf*n=malloc(sizeof(stack_buf));
    if(!n)return;
    n->bf=val;
    n->next=*head;
    *head=n;
}
int stack_size(stack_buf*head){
    int cnt=0;
    while(head!=NULL){
        ++cnt;
        head=head->next;
    }
    return cnt;
}
void clear_stack(stack_buf*head){
    while(head!=NULL){
        stack_buf*nxt=head->next;
        free(head);
        head=nxt;
    }
}

void draw_stack(stack_buf*head,void(*draw_function)(const buffer*)){
    while(head!=NULL){
        draw_function(&head->bf);
        head=head->next;
    }
}

void pop(stack_buf**head){
    if(!head||!*head)return;
    stack_buf*nxt=(*head)->next;
    free(*head);
    *head=nxt;
}

void delete_by_index(stack_buf**head,int index){
    if(!head||!*head)return;
    if(index==0){
        pop(head);
        return;
    }
    stack_buf*cur=*head;
    for(int i=0;cur!=NULL&&i<index-1;++i)cur=cur->next;
    if(cur==NULL||cur->next==NULL)return;
    stack_buf*to_del=cur->next;
    cur->next=to_del->next;
    free(to_del);
}