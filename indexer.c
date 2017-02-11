#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Word{
  int file_name;
  char a[100];
  int count;
  struct Word *next;
};
struct Mword{
  char a[100];
  struct Mword *next1;
  struct Word *next2;
}*head=NULL;

void add_snode(struct Mword *n,char *a,int y){
  struct Word *ptr=n->next2;
  if(ptr==NULL){
    struct Word *nn=malloc(sizeof(struct Word));
    nn->next=NULL;
    nn->file_name=y;
    nn->count=1;
    n->next2=nn;
  }else{
    int flag=0;
    struct Word *ptr1=ptr;
    while (ptr1!=NULL) {
      ptr=ptr1;
      if(ptr1->file_name==y){
        flag=1;
        break;
      }
      ptr1=ptr1->next;
    }
    if(flag==1){
      ptr1->count++;

    }else{
      struct Word *nn=malloc(sizeof(struct Word));
      nn->next=NULL;
      ptr->file_name=y;
      ptr->count=1;
      ptr->next=nn;
    }
  }
}
void add_node(char *a,int y){//adding mwords
 struct Mword *n=malloc(sizeof(struct Mword));
  strcpy(n->a,a);
  n->next2=NULL;
  n->next1=NULL;
  if(head==NULL){
    head=n;
  }else{
    struct Mword *ptr=head;
    while(ptr->next1!=NULL){
      ptr=ptr->next1;
    }
    ptr->next1=n;
  }
add_snode(n,a,y);
}
void check_duplicate(char *a,int y){
struct Mword *ptr=head;
struct Mword *ptr1=ptr;
int flag=0;
  while(ptr!=NULL){
    ptr1=ptr;
    if(strcmp(ptr->a,a)==0){
      flag=1;
      break;
    }
    ptr=ptr->next1;
  }
  if (flag==0) {
    add_node(a,y);
  }else{
    add_snode(ptr1,a,y);
  }
}


void seprate_words(char *a,int y){
  char *b;
  char c[20]="-() ,/*|–";
  b=strtok(a,c);
  while (b!=NULL) {
    //add_node(b);
    if(strcmp(b,"-")!=0){
    check_duplicate(b,y);
  }
    b=strtok(NULL,c);

  }


}
void find_word(const char *aa,int y){
  char a[10]="<title>";
  char b[10]="</title>";
  int i;
  FILE *fl=fopen(aa,"r");
  	fseek(fl, 0, SEEK_END);
  	long long int file_size = ftell(fl);
  	fseek(fl, 0, SEEK_SET);
  char *f=(char*) malloc(sizeof(char)*file_size);
  memset(f,0,file_size);
  fprintf(fl,"%s",f);
  long long int code_s = sizeof(char) * file_size;
  f = malloc(code_s);
  long long int result = fread(f, 1, file_size, fl);
  for (i = 0;f[i]!='\0';i++) {
    if(strncmp(f+i,a,7)==0){
      break;
    }
  }
  int k,j;
  char *ch=malloc(sizeof(char)*1000);
  memset(ch,0,999);
  for(k=0,j=i+7;strncmp(f+j,b,8)!=0;k++,j++){
    ch[k]=f[j];
}
ch[k]='\0';
if(strcmp(ch,"-")!=0){
seprate_words(ch,y);
}
free(ch);
free(f);
fclose(fl);
}
void open_file(){
int i;
for (i=1;i<33;i++) {
  char *f_name=malloc(sizeof(char)*100);
  memset(f_name,0,99);
    sprintf(f_name,"nnn/%d.txt",i);
    find_word(f_name,i);
    free(f_name);
}
}
void print_all(){
struct Mword *ptr=head;
while(ptr!=NULL){
  struct Word *ptr1=ptr->next2;
  while (ptr1!=NULL){
    ptr1=ptr1->next;
  }
  ptr=ptr->next1;
}
}
void add_to_file(){
FILE *fptr=fopen("nnn/saved_data.txt","w");
if(fptr==NULL){
  printf("ERROR");
  exit(1);
}
struct Mword *ptr=head;
while(ptr!=NULL){
  struct Word *ptr1=ptr->next2;
  fprintf(fptr,"%s",ptr->a);
  int i=0;
  while(ptr1!=NULL){
    if (ptr1->next==NULL&&i>0) {
      break;
    }
    i++;
    fprintf(fptr,"-%d>%d",ptr1->count,ptr1->file_name);
    ptr1=ptr1->next;
  }
  fprintf(fptr,"\n");
  ptr=ptr->next1;
}
fclose(fptr);
}//*/
int main() {
  open_file();
  print_all();
  add_to_file();
  return 0;
}
