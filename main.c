#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


typedef struct Line {
    int n; //колличество эллементов в строке матрицы
    int* parr; //массив элементов
} Line;

typedef struct Matrix {
    int lines; // колличество строк матрицы
    Line* pmatr;// массив строк матрицы
} Matrix;



int getIntbig(int *,int e);// ввод целого числа
int getIntsmall(int *,int e);
void output(const char *msg, Matrix a);//вывод матрицы
void erase(Matrix *a);//освобождение памяти
int vozr(int a);//по возрастанию или нет?

int inputM(Matrix *rm) {
    const char *pr = "";
    int m = 0, i, j, *p, e = 0;

    while ((m != 1) && (m != 2)) {
        printf("enter 1 for random or 2 for manual");
        getIntsmall(&m, 2);
        fflush(stdin);
        e = m;
    }

    do {
        printf("%s\n", pr);
        printf("Insert num of lines: -->");
        pr = "Error";
        if (getIntsmall(&m, e) == 0)
            return 0;
    } while (m < 1);
    rm->lines = m;
    rm->pmatr = (Line *) calloc(m, sizeof(Line));
    for (i = 0; i < rm->lines; i++) {
        //колличество столбцов для каждой строки матрицы
        pr = "";
        do {
            printf("%s\n", pr);
            printf("insert number of items in line %d: -->", i + 1);
            pr = "Error";
            if (getIntsmall(&m, e) == 0) {
                rm->lines = i;
                erase(rm);
                return 0;//обнаружен конец файла
            }
        } while (m < 1);
        rm->pmatr->n = m;
        // выделение необходимую память под элементы строки
        p = (int *) malloc(sizeof(int) * m);
        rm->pmatr->parr = p;
        rm->pmatr++;
        printf("Enter items for matrix line #%d:\n", i + 1);
        for (j = 0; j < m; ++j, ++p)
            if (getIntbig(p, e) == 0) {
                rm->lines = i + 1;
                erase(rm);

                return 0;
            }
    }
    rm->pmatr = rm->pmatr - rm->lines;
}

int vozrM(Matrix* rm,Matrix* nm){
    int mCount=0, i, j, e=0;
    int* pointer1, *pointer2;
    Line* pointeR1, *pointeR2;
    nm->pmatr = (Line *) calloc(rm->lines,sizeof(Line));
    nm->lines=rm->lines;
    pointeR1=rm->pmatr;
    pointeR2=nm->pmatr;
    pointeR2->parr=malloc(sizeof(int));
    for (i = 0; i < rm->lines; i++) {
        pointer2 = (int *) realloc(pointeR2->parr,20);
        pointeR2->parr=pointer2;
        pointer1 = pointeR1->parr;

        for (j = 0; j < pointeR1->n; j++,pointer1++){
        if(vozr(*pointer1))
        {   *(pointer2)=*(pointer1);
           // printf("%d ",*pointer2);
            pointer2++;
            e++;

            if (e>=20) pointeR2->parr = (int *) realloc(pointeR2->parr,e);
//            if(e%3==0&&e>1) {

//            }
           mCount++;
        }
        }
        pointeR2->n=e;
        e=0;
        //printf(" #%d\n",pointeR2->n);
        pointeR1++;
        pointeR2++;
            }
    if(mCount==0) { //то есть не было ни одного числа
        printf("warning your matrix is wrong");
        return 0;
    }
    }

void output(const char *msg, Matrix a)
{
    int i,j,*p;
    Line* pointer;
    printf("%s:\n",msg);
    pointer=a.pmatr;
    for (i=0;i<a.lines;i++){
        p=pointer->parr;
        for (j=0;j<pointer->n;++j,++p)
            printf("%d ",*p);
        printf(" #%d",pointer->n);
        pointer++;
        printf("\n");
    }

}
int vozr(int a)
{ int buf1=0,buf2=0;
  if (a/10==0)
      return 0;
  else
      {
        while(a>=10)
        {
            buf1=a%10;
            buf2=(a/10)%10;
            if(buf1<=buf2)
            {
                return 0;

            }
            a=(a/10);
        }
        return 1;
      }
}
int getIntbig(int *a,int e) {
    int n;

    if (e == 1) {
        srand(rand()*time(0));
        printf("%s\n", "random");
        *a = rand() % 1000 + 1;
        return 1;
    }

    if (e == 2)
    { do {
        n = scanf("%d", a);
            printf("%s\n", "manual");
        if (n < 0)
            return 0;
        if (n == 0) {
            printf("%s\n", "Error! Repeat input");
            scanf("%*[^\n]", 0);
        }
    } while (n == 0);
    return 1;
    }
}
int getIntsmall(int *a,int e) {
    int n;

    if (e == 1) {
        srand(rand()*time(0));
        printf("%s\n", "random");
        *a = rand() % 20 + 1;
        return 1;
    }

    if (e == 2)
    { do {
            n = scanf("%d", a);
            printf("%s\n", "manual");
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "Error! Repeat input");
                scanf("%*[^\n]", 0);
            }
        } while (n == 0);
        return 1;
    }
}
void erase(Matrix *a) {
    int i;
    for (i = 0; i < a->lines; ++i,a->pmatr++)
        free(a->pmatr->parr);
    a->pmatr=a->pmatr-i;
    free(a->pmatr);
    a->lines = 0;
    a->pmatr = NULL;
}
int main() {
//    int *a;
//   getIntbig(a,2);
//   printf("%d=+=>%d",*a,vozr(*a));
    Matrix matr ={0,NULL};
    Matrix matrnew={0,NULL};
    inputM(&matr);
    vozrM(&matr,&matrnew);
    output("Sourse matrix", matr);
    output("New Matrix", matrnew);

    return 0;
}