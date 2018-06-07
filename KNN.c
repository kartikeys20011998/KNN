#include<stdio.h>
#include<string.h>
#include<math.h>
float a[200][5];
char str[100];
int f=0,k=0,m=0,K=5;
int s,q,t,j=0,min,label[120],count[3]={0};
int t1,lbl[30],match=0;
float diff,accuracy,temp,sum,distance[120],train[120][5],test[30][5];

int max(int *p)
{
 if(p[0]>p[1])
 {
  if(p[0]>p[2])
   return 0;
  else
    return 2;
 }
 else
 {
  if(p[1]>p[2])
   return 1;
  else
   return 2;
 }
}


int main()
{
 int i=0;
 float sl,sw,pl,pw;
 FILE *fp=fopen("iris.txt","r");
 while(fscanf(fp,"%f%f%f%f%s",&sl,&sw,&pl,&pw,str)!=EOF)
 {
  a[i][0]=sl;
  a[i][1]=sw;
  a[i][2]=pl;
  a[i][3]=pw;
  if(strcmp(str,"Iris-setosa")==0)  //Iris-setosa --> 0
    a[i][4]=0;
  else if (strcmp(str,"Iris-virginica")==0) //Iris-virginica --> 1
    a[i][4]=1;
  else	 	//Iris-versicolor --> 2
    a[i][4]=2;
   i++;
 }

 //i=0;
/* while(i!=150)
 {
   printf("\n%f %f %f %f %f",a[i][0],a[i][1],a[i][2],a[i][3],a[i][4]);
   i++;
-- } */
// MAKING THE TRAIN AND TEST ARRAY
i=0;
while(i!=150)
{
  if(k<120 && f==0)
  {
   train[k][0]=a[i][0];
   train[k][1]=a[i][1];
   train[k][2]=a[i][2];
   train[k][3]=a[i][3];
   train[k][4]=a[i][4];
   k++;
   if(k==40 || k==80 || k==120)
    f=1;
  }
   else if( m<30 && f==1)
  {
   test[m][0]=a[i][0];
   test[m][1]=a[i][1];
   test[m][2]=a[i][2];
   test[m][3]=a[i][3];
   test[m][4]=a[i][4];
   m++;
   if(m==10 || m==20 || m==30)
   f=0;
  }
 i++;
}
/*PRINTING TRAIN ARRAY
for(k=0;k<120;k++)
  printf("\n %f %f %f %f %f",train[k][0],train[k][1],train[k][2],train[k][3],train[k][4]);
/PRINTING  TEST ARRAY
for(m=0;m<30;m++)
  printf("\n %f %f %f %f %f",test[m][0],test[m][1],test[m][2],test[m][3],test[m][4]); */



i=0;
j=0;
k=0;
m=0;

for(i=0;i<30;i++)
{
	//INITIALISING THE COUNT ARRAY WITH ZERO
	for(t=0;t<3;t++)
	  count[t]=0;
	
  //(I) FINDING DISTANCE AND LABEL ARRAY
  for(j=0;j<120;j++)
  {
   sum=0.0;
   for(k=0;k<4;k++)
   {
  //sum+=pow(train[j][k]-test[i][k],2);
        diff = train[j][k]-test[i][k];
        sum+=diff*diff;
   }
   distance[j]=sqrt(sum);
   label[j]=train[j][4];
  }

  //(II)SELECTION SORT
  for(t=0;t<120;t++)
  {
   min = t;
   for(j=t+1;j<120;j++)
   {
    if(distance[min]>distance[j])
     min=j;
   }
    //SWAPPING DISTANCE ELEMENTS
    temp=distance[min];
    distance[min]=distance[t];
    distance[t]=temp;
    //SWAPPING LABEL ELEMENTS
    t1=label[min];
    label[min]=label[t];
    label[t]=t1;
  }

   /* PRINTING THE SORTED  LABELS
   printf("\n");
  for(s=0;s<120;s++)
    printf("%d",label[s]); */

  // (III) FINDING THE LABEL
  for(q=0;q<K;q++)
  {
   count[label[q]]++;
  }
//  printf("\n%d %d %d",count[0],count[1],count[2]);
  lbl[i]=max(count);
//  printf("\n%d \t",lbl[i]);
}

match=0;
for(i=0;i<30;i++)
{
 if(lbl[i]==(int)test[i][4])
  match++;
  
}
accuracy=(match/30.0)*100;
printf("ACCURACY OF KNN IS %f",accuracy);
}
