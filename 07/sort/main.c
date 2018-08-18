#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM 20000

int rand_seq[NUM];

void init_rand_seq(void)
{
    int i;
    for (i = 0; i < NUM; i++)
        rand_seq[i] = (rand() % 100) - (rand() % 100);
}

void PrintSorted()
{
    int i;
    for (i = 0; i < 100; i++)
        printf("%d ", rand_seq[i]);

   printf("\n==========================\n");
}

void InsertionSort(int A[], int N)
{
    int j ,P;
    int tmp;
    for (P = 1; P < N; P++)
    {
        tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > tmp; j--)
            A[j] = A[j - 1];
        A[j] = tmp;
    }
}

void Shellsort(int A[], int N)
{
    int i, j, Increment;
    int tmp;
    for (Increment = N / 2; Increment > 0; Increment /= 2)
    {
        for (i = Increment; i < N; i++)
        {
            tmp = A[i];
            for (j = i; j >= Increment; j -= Increment)
            {
                if (A[j - Increment] > tmp)
                    A[j] = A[j - Increment];
                else
                    break;
            }
            A[j] = tmp;
        }
    }
}

#define LeftChild(i)    (2 * (i) + 1)
static void PercDown(int A[], int i, int N)
{
    int child;
    int tmp;
    for (tmp = A[i]; LeftChild(i) < N; i = child)
    {
        child = LeftChild(i);
        if (child != N - 1 && A[child] < A[child + 1])
            child++;
        if (tmp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = tmp;
}

inline static void Swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void Heapsort(int A[], int N)
{
    int i;
    for (i = N / 2; i >= 0; i--)
        PercDown(A, i, N);

    for (i = N - 1; i >= 0; i--)
    {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}

static void Merge(int A[], int TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, Num, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    Num = RightEnd - Lpos + 1;

    while (Lpos <= LeftEnd && Rpos <= RightEnd)
        if (A[Lpos] <= A[Rpos])
            TmpArray[TmpPos++] = A[Lpos++];
        else
            TmpArray[TmpPos++] = A[Rpos++];

    while (Lpos <= LeftEnd)
        TmpArray[TmpPos++] = A[Lpos++];
    while (Rpos <= RightEnd)
        TmpArray[TmpPos++] = A[Rpos++];

    for (i = 0; i < Num; i++, RightEnd--)
    {
        A[RightEnd] = TmpArray[RightEnd];
    }
}

static void Msort(int A[], int TmpArray[], int left, int right)
{
    int center;

    if (left < right)
    {
        center = (left + right) / 2;
        Msort(A, TmpArray, left, center);
        Msort(A, TmpArray, center + 1, right);
        Merge(A, TmpArray, left, center + 1, right);
    }
}

void Mergesort(int A[], int N)
{
    int *TmpArray;

    TmpArray = malloc(N * sizeof(int));
    if (TmpArray != NULL)
    {
        Msort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
    else
        printf("no space for TmpArray\n");
}

static int Median3(int A[], int left, int right)
{
    int center = (left + right) / 2;
    if (A[left] > A[center])
        Swap(&A[left], &A[center]);
    if (A[left] > A[right])
        Swap(&A[left], &A[right]);
    if (A[center] > A[right])
        Swap(&A[center], &A[right]);

    Swap(&A[center], &A[right - 1]);    //将枢纽元放置倒数第二的位置
    return A[right - 1];                //返回枢纽元
}

#define Cutoff  3   //小于3+1个元素就不用快速排序
static void Qsort(int A[], int left, int right)
{
    int i, j;
    int pivot;

    if (left + Cutoff <= right)
    {
        pivot = Median3(A, left, right);
        i = left;
        j = right - 1;
        for ( ; ; )
        {
            while (A[++i] < pivot);
            while (A[--j] > pivot);
            if (i < j)
                Swap(&A[i], &A[j]);
            else
                break;
        }
        Swap(&A[i], &A[right - 1]);

        Qsort(A, left, i - 1);
        Qsort(A, i + 1, right);
    }
    else
        InsertionSort(A + left, right - left + 1);
}

void Quicksort(int A[], int N)
{
    Qsort(A, 0, N - 1);
}

int main()
{
    long start_time, end_time;

    init_rand_seq();
    start_time = clock();
    InsertionSort(rand_seq, NUM);
    end_time = clock();
    printf("InsertionSort Time = %ldms\n", end_time - start_time);
    PrintSorted();

    init_rand_seq();
    start_time = clock();
    Shellsort(rand_seq, NUM);
    end_time = clock();
    printf("Shellsort Time = %ldms\n", end_time - start_time);
    PrintSorted();

    init_rand_seq();
    start_time = clock();
    Heapsort(rand_seq, NUM);
    end_time = clock();
    printf("Heapsort Time = %ldms\n", end_time - start_time);
    PrintSorted();

    init_rand_seq();
    start_time = clock();
    Mergesort(rand_seq, NUM);
    end_time = clock();
    printf("Mergesort Time = %ldms\n", end_time - start_time);
    PrintSorted();

    init_rand_seq();
    start_time = clock();
    Quicksort(rand_seq, NUM);
    end_time = clock();
    printf("Quicksort Time = %ldms\n", end_time - start_time);
    PrintSorted();

    return 0;
}
