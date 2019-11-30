#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS         // fopen 보안 경고로 인한 컴파일 에러 방지.
/*

학번 : 2014150010
이름 : 김홍준

*/

typedef struct movie
{
   char id[20];
   char title[300];
   char genres[300];
   char year[10];
   int year2;
}Movie;


typedef struct Year
{
   int count;
   int uni;
}year;

/*
퀵 정렬 (제목)
*/
year* quick(Movie* m, int count);
void powerQuick(Movie* m, year* arr);
void quicksort_title2(Movie* a, int low, int high);
int split_title(Movie* a, int low, int high);
void QuickResult_title(Movie* m, int count);

/*
퀵 정렬(년도)
*/
void QuickResult(Movie* m, int count);
int split(Movie* a, int low, int high);
void AccistQuick(year* y, int count, Movie* m);

/*
합병 정렬 (년도)
*/
void MergeResult(Movie* m, int count);
void MergeTwoArea(Movie* m, int left, int mid, int right, Movie* sortArr);
void MergeSort(Movie* m, int left, int count, Movie* temp);  //left 왼쪽의 인덱스, rigth 오른쪽의 인덱스
                                              /*
                                              합병 정렬 (제목)
                                              */
void MergeResult_title(Movie* m, int count);
void MergeSort_title(Movie* m, int left, int count, Movie* temp);  //left 왼쪽의 인덱스, rigth 오른쪽의 인덱스;
void MergeTwoArea_title(Movie* m, int left, int mid, int right, Movie* sortArr);
/*
삽입 정렬 (제목), (년도)
*/
void InserSort(Movie* arr, int n);
void InserSort_title(Movie* arr, int n, int* a);
/*
힙 정렬 (년도), (제목)
*/
void Heap_Sort_title(Movie* m, int count);
void Heap_Sort(Movie* m, int count);
void timeHeap(Movie* m, int count);

/*
기수 정렬 (년도), (제목)
*/

void Radix_sort(Movie* m, int size, int base);
void Radix_sort_result(Movie* m, int count);

/*
인프라 구축 함수
*/

void countYear(Movie* m, int count, int* arr);
void MainMenu(Movie* m, int k);
void crossFunction(Movie* m, int count);
int startMovie(Movie* m);
void showshowshow(Movie* m, int count);
void changeNumber(Movie* m, int count);
int MakeNode2(Movie* m, int a, int b, char* content);
void goDatas2(Movie* prev);
char* splitYear(char* content);
char* makeYear(char* content);
void goDatas(Movie* head);
char* LinkNode(Movie* head);
int cut1(char* content); // 앞자리 인덱스 짜르는 함수
int cut2(char* content); // 앞자리 인덱스 짜르는 함수
char* copy(char* content); // 문자열 복사.
int menu();
int menu2();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////      메인 함수 부
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main(int argc, const char * argv[])
{
   char content[500];
   Movie* mm = NULL;
   int i = 0;
   int k = 0;
   int j = 0;
   FILE* P = NULL;
   P = fopen("C:\\movies.txt", "r");

   while (!feof(P)) // 데이터의 갯수 새기
   {
      fgets(content, 500, P);  // 한줄 다 읽어옴.
      if (i == 0)
      {
         i = 1;
         continue;
      }
      j++;
   }
   fclose(P);
   i = 0;
   mm = (Movie*)malloc(sizeof(Movie)*j);
   k = startMovie(mm);
   crossFunction(mm, k);
   MainMenu(mm, k);

   return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  함수 구현 부
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
startMovie 함수
Param : main 함수의 영화 구조체 주소
return : 영화 구조체의 갯수
기능 : 파일 내용을 읽어 들여서, 영화 구조체에 변수에 대입
*/

int startMovie(Movie* m)
{
   int i = 0;
   FILE* P = NULL;
   char content[500];
   int l = 0; // 뒤에서 ,까지의 문자열 길이.
   int r = 0; // 전체 문자열 길이
   int length = 0;
   int com = 0;
   int  k = 0;
   P = fopen("C:\\movies.txt", "r");
   while (!feof(P))
   {

      fgets(content, 500, P);  // 한줄 다 읽어옴.
      if (i == 0)
      {
         i = 1;
         continue;
      }

      l = cut1(content); //앞자리
      r = cut2(content);
      length = strlen(content) - r; // 뒷자리
      com = MakeNode2(&m[k], l, length, content);

      if (com == 1) //년도가 없어서 인덱스 값을 그대로 받아오는 경우
      {
         fgets(content, 500, P);
         l = cut1(content); //앞자리
         r = cut2(content);
         length = strlen(content) - r; // 뒷자리
         com = MakeNode2(&m[k], l, length, content);
         k++;
      }
      else
      {
         k++;
      }
   }

   fclose(P);
   return k;

}

/*
Param 1 : main 함수의 영화 구조체 변수 주소값
param 2 : 구조체 변수의 갯수
기능 : startMoive 함수와 ChangNumber 함수를 하나의 함수로 합치는 것.
*/

void crossFunction(Movie* m, int count)
{
   int k = 0;
   k = startMovie(m);
   changeNumber(m, k + 1);
}
/*
param 1 : 영화 구조체 배열
param 2 : 영화 구조체 배열의 수
기능 : 영화 구조체의 속성 값들을 출력.
*/
void showshowshow(Movie* m, int count)
{
   int i = 0;
   for (i = 0; i<count; i++)
   {
      printf(" ID : %s \n", m[i].id);
      printf(" title : %s \n", m[i].title);
      printf(" year : %d \n", m[i].year2);
      printf(" genres : %s \n\n", m[i].genres);
   }
}
void showshowshow2(Movie* m, int count)
{
   int i = count - 1;
   while (1)
   {
      printf(" ID : %s \n", m[i].id);
      printf(" title : %s \n", m[i].title);
      printf(" year : %d \n", m[i].year2);
      printf(" genres : %s \n\n", m[i].genres);
      i--;
      if (i<0)
      {
         break;
      }
   }
}
/*
MakeNode2의 매개변수
리스트 주소값, 리스트에 이어줄 영화 구조체, 제목속성 값의 첫번째 인덱스 값, 제목속성 값의 두번째 인덱스 값, 파일에서 한줄 읽어온 문자열

*/

int MakeNode2(Movie* m, int a, int b, char* content)
{
   char title[1000];
   char back[1000];
   char back2[1000];
   char back3[1000];
   char* contain = NULL;
   char compare[10] = "없음";

   int i = 0;
   int j = 0;
   int count = 0;
   for (i = 0; i<1000; i++)
   {
      title[i] = 0;
   }
   for (i = a; i<b; i++)
   {
      title[j] = content[i];
      j++;
   }
   strcpy(back, title);
   strcpy(back2, back);
   strcpy(back3, title);
   if (!strcmp(compare, makeYear(copy(back2)))) //년도가 없는 경우
   {
      count = 1;
      return count;
   }
   if (count == 0)
   {
      strcpy(m->title, splitYear(title));
      strcpy(m->year, makeYear(copy(back)));
      contain = strtok(copy(content), ",");
      strcpy(m->id, contain);
      contain = strrchr(copy(content), ',');
      contain = strtok(contain, ",");
      strcpy(m->genres, contain);
   }
   return count;
}


/*
splitYear의 매개변수
제목과 년도 까지 담긴 문자열 ex)  content = "begin agine (2015)"
설명 : begin again (2015) 문자열에서 begin again 만 추출
*/
char* splitYear(char* content)
{
   char* contain = NULL;
   int l = 0;
   int r = 0;
   int i = 0;
   int length = 0;
   contain = strrchr(content, '(');
   if (contain == NULL) // 년도가 없는 영화.
   {
      return content;
   }



   else // 년도가 있는 영화.
   {
      l = strlen(contain);
      r = strlen(content);
      length = r - l;
      for (i = length; i<r; i++)
      {
         content[i] = 0;
      }
      return content;
   }
}


/*
makeYear의 매개변수
제목과 년도가 포함된 문자열 즉 ex) content = begin again(2015)
설명 : 매개변수 문자열에서 년도만 추출하는 것.
*/
char* makeYear(char* content)
{
   char* contain = NULL;
   char* year2 = "없음";
   int count = 0;
   int i = 0;
   contain = strrchr(content, '(');
   if (contain == NULL)
   {
      return year2;
   }

   if (contain[1]>47 && contain[1]<58) //년도가 있는 경우
   {
      for (i = 0; i<4; i++)
      {
         contain[i] = contain[i + 1];
      }
      count = 1;
      if (count == 1)
      {
         contain[4] = 0;
         contain[5] = 0;
      }
      return contain;
   }
   else
   {
      return year2;
   }

}

/*
copy의 매개변수
매개변수에 해당되는 문자열을 복사해서 복사한 문자열 변수를 리턴값으로 지정.
*/

char* copy(char* content)
{
   char cp[1000];
   strcpy(cp, content);
   return cp;
}


/*
cut1의 매개변수
앞자리의 인덱스를 자르는 것 ex)  1,begin again(2015),music|romance 이러한 문자열에서 'b'의 인덱스 번호를 리턴해줌
설명 : 영화 정보 중 제목을 초기화 하기위해 필요한 함수.
*/
int cut1(char* content) // 앞자리 인덱스 짜르는 함수
{
   int count = 0;
   char c[2000];
   char* contain = NULL;
   strcpy(c, content);
   contain = strtok(c, ",");
   count = strlen(contain) + 1;
   return count;
}


/*
cut2의 매개변수
뒷자리의 인덱스를 자르는 것 ex)  1,begin again(2015),music|romance 이러한 문자열에서 ')'의 인덱스 번호를 리턴해줌
설명 : 영화 정보 중 제목을 초기화 하기위해 필요한 함수.
*/
int cut2(char* content) // 뒷자리 인덱스 짜르는 함수.
{
   int count = 0;
   char* contain = NULL;
   char c[2000];
   strcpy(c, content);
   contain = strrchr(c, ',');
   count = strlen(contain);
   return count;
}
/*

Param1 : 영화 구조체 주소
Param2 : 영화 구조체 갯수

기능 : 메뉴 함수.

*/

void MainMenu(Movie* m, int k)
{
   int number = 0;
   int temp = 0;
   int arr[200] = { 0, };
   while (1)
   {
      switch (menu()) // 년도 정렬
      {
      case 1:
         InserSort(m, k);
         number = 0;
         break;
      case 2:
         MergeResult(m, k - 1);
         number = 0;
         break;
      case 3:
         QuickResult(m, k - 1);
         number = 0;
         break;
      case 4:
         Heap_Sort(m, k - 1);
         number = 0;
         break;
      case 5:
         Radix_sort_result(m, k);
         number = 0;
         break;
      case 6:
         showshowshow(m, k);
         number = 1;
         break;
      case 0:
         number = 1;
         break;
      default:
         number = 0;
         break;
      }
      if (number == 0)
      {
         break;
      }
   }
   if (number == 0)
   {
      while (1)
      {
         switch (menu2()) // 제목 정렬
         {
         case 1:
            showshowshow(m, k);
            number = 1;
            break;
         case 2:
            countYear(m, k, arr);
            InserSort_title(m, k, arr);
            number = 0;
            break;
         case 3:
            MergeResult_title(m, k - 1);
            number = 9;
            break;
         case 4:
            QuickResult_title(m, k - 1);
            number = 0;
            break;
         case 5:
            timeHeap(m, k - 1);
            number = 0;
            break;
         case 6:
            number = 0;
            break;
         case 0:
            number = 2;
            break;
         default:
            break;
         }
         if (number == 0)
         {
            printf("------------------------------------------------\n\n");
            printf(" 년도와 제목을 정렬한 결과를 확인 input -> 아무 숫자  \n\n");
            scanf("%d", &temp);
            printf("-------------------------------------------------\n");
            showshowshow(m, k);
            printf("------------------------------------------------\n");
            printf(" 년도 정렬 이후 제목 정렬을 Stable 하게 성공 하였습니다. \n");
            printf("------------------------------------------------\n");
            break;
         }
         if (number == 9)
         {
            printf("------------------------------------------------\n\n");
            printf(" 년도와 제목을 정렬한 결과를 확인 input -> 아무 숫자  \n\n");
            scanf("%d", &temp);
            printf("-------------------------------------------------\n");
            showshowshow2(m, k);
            printf("------------------------------------------------\n");
            printf(" 년도 정렬 이후 제목 정렬을 Stable 하게 성공 하였습니다. \n");
            printf("------------------------------------------------\n");
            break;
         }

         if (number == 2)
         {
            break;
         }
      }
   }
}

int menu()
{
   int number = 0;
   printf("------------------------<년도 정렬>--------------------------\n");
   printf("1. 삽입 정렬 \n");
   printf("2. 합병 정렬 \n");
   printf("3. 퀵 정렬 \n");
   printf("4. 힙 정렬 \n");
   printf("5. 기수 정렬 \n");
   printf("6. 영화 목록 출력 \n");
   printf("0. 나가기 \n");
   printf("-----------------------------------------------------------\n");
   printf(" choice --> ");
   scanf("%d", &number);
   return number;
}

int menu2()
{
   int number = 0;
   printf("----------------------------------------------------------\n\n");
   printf(" 년도 정렬이 완료 되었습니다. 제목을 정렬하기 위해 정렬 종류를 골라주세요 \n\n");
   printf("------------------------<제목 정렬>--------------------------\n");
   printf("1. 년도 정렬한 결과 보기 \n");
   printf("2. 삽입 정렬 \n");
   printf("3. 합병 정렬 \n");
   printf("4. 퀵 정렬 \n");
   printf("5. 힙 정렬 \n");
   printf("6. 기수 정렬 \n");
   printf("0. 종료 \n");
   printf("-----------------------------------------------------------\n");
   printf(" choice --> ");
   scanf("%d", &number);
   return number;
}

/*
changeNumber의 매개변수
m은, 영화 구조체 배열의 첫번째 주소값, count는 구조체의 갯수
기능 : 문자열로 받아온 년도 year를 정수형으로 year2로 변환해줌. 즉, 년도 정렬을 위해 필요한 작업.
*/

void changeNumber(Movie* m, int count)
{
   int i = 0;
   for (i = 0; i<count - 1; i++)
   {
      m[i].year2 = atoi(m[i].year);
   }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////      정렬 함수 구현 부
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
합병 정렬 (제목)
*/

void MergeTwoArea_title(Movie* m, int left, int mid, int right, Movie* sortArr)
{
   int fIdx = left;
   int rIdx = mid + 1;
   int i;

   int sIdx = left;

   while (fIdx <= mid && rIdx <= right)
   {
      if ((strcmp(m[rIdx].title, m[fIdx].title)) < 0 && (m[rIdx].year2 == m[fIdx].year2))
         sortArr[sIdx] = m[fIdx++];
      else
         sortArr[sIdx] = m[rIdx++];

      sIdx++;
   }

   if (fIdx > mid)
   {
      for (i = rIdx; i <= right; i++, sIdx++)
         sortArr[sIdx] = m[i];
   }
   else
   {
      for (i = fIdx; i <= mid; i++, sIdx++)
         sortArr[sIdx] = m[i];
   }

   for (i = left; i <= right; i++)
   {
      m[i] = sortArr[i];
   }
}

void MergeSort_title(Movie* m, int left, int count, Movie* temp)  //left 왼쪽의 인덱스, rigth 오른쪽의 인덱스
{
   int mid;

   if (left < count)
   {
      // 중간 지점을 계산한다.
      mid = (left + count) / 2;

      // 둘로 나눠서 각각을 정렬한다.
      MergeSort_title(m, left, mid, temp);
      MergeSort_title(m, mid + 1, count, temp);

      // 정렬된 두 배열을 병합한다.
      MergeTwoArea_title(m, left, mid, count, temp);
   }
}

void MergeResult_title(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   Movie* temp = (Movie*)malloc(sizeof(Movie)*count);
   start = clock();
   MergeSort_title(m, 0, count, temp);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("합병 정렬하는데 걸리는 시간 :%.6f \n", res);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
합병 정렬 (년도)
*/

void MergeTwoArea(Movie* m, int left, int mid, int right, Movie* sortArr)
{
   int fIdx = left;
   int rIdx = mid + 1;
   int i;

   int sIdx = left;

   while (fIdx <= mid && rIdx <= right)
   {
      if (m[fIdx].year2 <= m[rIdx].year2)
         sortArr[sIdx] = m[fIdx++];
      else
         sortArr[sIdx] = m[rIdx++];

      sIdx++;
   }

   if (fIdx > mid)
   {
      for (i = rIdx; i <= right; i++, sIdx++)
         sortArr[sIdx] = m[i];
   }
   else
   {
      for (i = fIdx; i <= mid; i++, sIdx++)
         sortArr[sIdx] = m[i];
   }

   for (i = left; i <= right; i++)
   {
      m[i] = sortArr[i];
   }
}

void MergeSort(Movie* m, int left, int count, Movie* temp)  //left 왼쪽의 인덱스, rigth 오른쪽의 인덱스
{
   int mid;

   if (left < count)
   {
      // 중간 지점을 계산한다.
      mid = (left + count) / 2;

      // 둘로 나눠서 각각을 정렬한다.
      MergeSort(m, left, mid, temp);
      MergeSort(m, mid + 1, count, temp);

      // 정렬된 두 배열을 병합한다.
      MergeTwoArea(m, left, mid, count, temp);
   }
}

void MergeResult(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   Movie* temp = (Movie*)malloc(sizeof(Movie)*count);
   start = clock();
   MergeSort(m, 0, count, temp);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("합병 정렬하는데 걸리는 시간 :%.6f \n", res);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
퀵 정렬 (년도)
*/

void quicksort(Movie* a, int low, int high)
{
   int middle = 0;

   if (low >= high) return;
   middle = split(a, low, high);
   quicksort(a, low, middle - 1);
   quicksort(a, middle + 1, high);
}

int split(Movie* a, int low, int high)
{
   Movie part_element = a[low];

   for (;;) {
      while (low < high && part_element.year2 <= a[high].year2)
         high--;
      if (low >= high) break;
      a[low++] = a[high];

      while (low < high && a[low].year2 <= part_element.year2)
         low++;
      if (low >= high) break;
      a[high--] = a[low];
   }

   a[high] = part_element;
   return high;
}
void QuickResult(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   start = clock();
   quicksort(m, 0, count);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("퀵 정렬하는데 걸리는 시간 :%.6f \n", res);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
퀵 정렬 (제목)
*/
void quicksort_title2(Movie* a, int low, int high)
{
   int middle = 0;

   if (low >= high)
      return;
   middle = split_title(a, low, high);
   quicksort_title2(a, low, middle - 1);
   quicksort_title2(a, middle + 1, high);
}

int split_title(Movie* a, int low, int high)
{
   Movie part_element = a[low];

   for (;;) {
      while (low < high && strcmp(part_element.title, a[high].title) < 0)
         high--;
      if (low >= high)
         break;
      a[low++] = a[high];

      while (low < high && strcmp(a[low].title, part_element.title) < 0)
         low++;
      if (low >= high)
         break;
      a[high--] = a[low];
   }
   a[high] = part_element;
   return high;
}
/*
기능 : 년도가 겹치는 영화의 인덱스의 시작과 끝을 뽑아서 그 해당 되는 인덱스만 퀵정렬 시작.
*/
void powerQuick(Movie* m, year* arr) // 같은 년도 끼리 퀵정렬 시작하는 함수.
{
   int i = 0;
   int temp = 0;
   for (i = 0; i<arr->uni + 1; i++)
   {
      if (arr[i].count == 1)
      {
         temp += 1;
      }
      else
      {
         quicksort_title2(m, temp, temp + arr[i].count - 1); // 같은 년도 끼리 퀵 정렬 시작.
         temp += arr[i].count;
      }
   }
}

void QuickResult_title(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   year* arr = NULL;
   arr = quick(m, count);
   start = clock();
   powerQuick(m, arr);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("퀵 정렬하는데 걸리는 시간 :%.6f \n", res);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
힙 정렬 (년도)
*/

void Heap_Sort(Movie* m, int count)
{
   int root = 0;
   int i = 0;
   Movie temp;
   int c = 0;


   clock_t start, end;
   float res = 0;
   start = clock();

   for (i = 1; i<count; i++)
   {
      c = i;
      do {
         root = (c - 1) / 2;
         if (m[root].year2 < m[c].year2)
         {
            temp = m[root];
            m[root] = m[c];
            m[c] = temp;
         }
         c = root;
      } while (c != 0);
   }

   for (i = count; i >= 0; i--)
   {
      temp = m[0];
      m[0] = m[i];
      m[i] = temp;

      root = 0;
      c = 1;

      do
      {
         c = 2 * root + 1;
         if (c < i - 1 && m[c].year2 < m[c + 1].year2)
         {
            c++;
         }

         if (c < i && m[root].year2 < m[c].year2)
         {
            temp = m[root];
            m[root] = m[c];
            m[c] = temp;
         }
         root = c;
      } while (c<i);
   }

   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("힙 정렬하는데 걸리는 시간 :%.6f \n", res);
}

/*
힙 정렬 (제목)
*/


void Heap_Sort_title(Movie* m, int count)
{
   int root = 0;
   int i = 0;
   Movie temp;
   int c = 0;

   for (i = 1; i<count; i++)
   {
      c = i;
      do {
         root = (c - 1) / 2;
         if (strcmp(m[root].title, m[c].title) > 0)
         {
            temp = m[root];
            m[root] = m[c];
            m[c] = temp;
         }
         c = root;
      } while (c != 0);
   }

   for (i = count; i >= 0; i--)
   {
      temp = m[0];
      m[0] = m[i];
      m[i] = temp;

      root = 0;
      c = 1;

      do
      {
         c = 2 * root + 1;
         if (c < i - 1 && strcmp(m[c].title, m[c + 1].title) > 0)
         {
            c++;
         }
         if (c < i &&  strcmp(m[root].title, m[c].title) > 0)
         {
            temp = m[root];
            m[root] = m[c];
            m[c] = temp;
         }
         root = c;
      } while (c<i);
   }
}

void timeHeap(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   year* arr = NULL;
   arr = quick(m, count);
   start = clock();
   Heap_Sort_title(m, count);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("힙 정렬하는데 걸리는 시간 :%.6f \n", res);
}


/*
기수 정렬 (년도)
*/

void Radix_sort(Movie* m, int size, int base)
{
   int ex, i, j, max = m[0].year2;
   Movie* temp = (Movie*)malloc(sizeof(Movie)*size);
   int* count;
   count = (int*)malloc(sizeof(int)*base);

   for (i = 1; i<size; i++)
   {
      if (m[i].year2>max)
         max = m[i].year2;
   }

   for (ex = 1; ex <= max; ex *= base)
   {
      for (i = 0; i<base; i++)
      {
         count[i] = 0;
      }
      for (i = 0; i<size; i++)
      {
         count[(m[i].year2 / ex) % base]++;
      }
      for (i = 1; i<base; i++)
      {
         count[i] += count[i - 1];
      }
      for (i = size - 1; i>-1; i--)
      {
         j = (m[i].year2 / ex) % base;
         temp[count[j] - 1] = m[i];
         count[j]--;
      }
      for (i = 0; i<size; i++)
      {
         m[i] = temp[i];
      }
   }
}

void Radix_sort_result(Movie* m, int count)
{
   clock_t start, end;
   float res = 0;
   start = clock();
   Radix_sort(m, count, 10);
   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("기수 정렬하는데 걸리는 시간 :%.6f \n", res);
}

/*
삽입 정렬
*/

void InserSort(Movie* arr, int n)
{
   int i, j;
   Movie insData;

   clock_t start, end;
   float res = 0;
   start = clock();

   for (i = 1; i<n; i++)
   {
      insData = arr[i];   // 정렬 대상을 insData에 저장

      for (j = i - 1; j >= 0; j--)
      {
         if (arr[j].year2 > insData.year2)
            arr[j + 1] = arr[j];    // 비교 대상 한 칸 뒤로 밀기
         else
            break;   // 삽입 위치 찾았으니 탈출!
      }

      arr[j + 1] = insData;  // 찾은 위치에 정렬 대상 삽입!
   }

   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("삽입 정렬하는데 걸리는 시간 :%.6f \n", res);
}

void InserSort_title(Movie* arr, int n, int* a)
{
   int i, j;
   Movie insData;
   int k = 0;
   clock_t start, end;

   for (i = 0; i<200; i++)
   {
      if (a[i] == 0)
      {
         k++;
      }
   }
   k = 200 - k;
   float res = 0;
   start = clock();

   for (i = 1; i<n; i++)
   {
      insData = arr[i];   // 정렬 대상을 insData에 저장
      for (j = i - 1; j >= 0; j--)
      {
         if ((strcmp(arr[j].title, insData.title) > 0) && (arr[i].year2 == arr[j].year2)) // 같은 년도 인 경우에서, 제목 문자열 비교
            arr[j + 1] = arr[j];    // 비교 대상 한 칸 뒤로 밀기
         else
            break;   // 삽입 위치 찾았으니 탈출!
      }

      arr[j + 1] = insData;  // 찾은 위치에 정렬 대상 삽입!
   }

   end = clock();
   res = (float)(end - start) / CLOCKS_PER_SEC;
   printf("삽입 정렬하는데 걸리는 시간 :%.6f \n", res);
}

/*
param 1 : 영화 구조체 배열
param 2 : 영화 구조체 배열의 수
param 3 : 각 년도의 갯수를 담을 정수형 배열
*/
void countYear(Movie* m, int count, int* arr)
{
   int i = 0;
   int k = 0;

   for (i = 0; i<count; i++)
   {
      if (i == 0)
      {
         arr[i] = m[i].year2;
         k = i;
         continue;
      }
      if (arr[k] != m[i].year2)
      {
         k++;
         arr[k] = m[i].year2;
         continue;
      }
   }
}
/*
param 1 : 영화 구조체 배열
param 2 : 영화 구조체 배열의 수
기능 : 각 고유 년도 마다 갯수를 구하고, 그 년도의 수를 통해서 퀵 정렬(제목)을 하기 위해 year 구조체 변수에 초기화 하는 과정
*/
year* quick(Movie* m, int count)
{
   year* ye = NULL;
   int i = 0;
   int k = 0;
   int c = 0;
   int arr[150] = { 0, };

   for (i = 0; i<count; i++)  // arr 변수에 영화 리스트에 존재하는 년도를 년도 순으로 담는다 (이미 년도가 정렬되어 있으니 인덱스 순서대로 담길 것.)
   {
      if (i == 0)
      {
         arr[i] = m[i].year2;
         k = i;
         continue;
      }
      if (arr[k] != m[i].year2)
      {
         k++;
         arr[k] = m[i].year2;
         continue;
      }
   }
   ye = (year*)malloc(sizeof(year)*k); // 해당 년도의 수 만큼 year 구조체 배열을 선언한다.
   ye->uni = k;

   i = 0;
   k = 0;
   while (1) // 해당 년도의 겹치는 년도 수를 구조체 변수에 초기화 한다.
   {
      if (arr[k] == 0) // 년도의 끝인 경우 나오기
      {
         break;
      }
      if (m[i].year2 == arr[k]) // 같은 년도의 갯수를 구해준다
      {
         c++;
      }
      else // 같은 년도가 아닌 경우 해당 년도의 갯수를 해당 년도의 구조체 변수에 초기화 시켜준다.
      {
         ye[k].count = c;
         c = 0;
         k++;
         continue;
      }
      i++;
   }

   return ye;
}
