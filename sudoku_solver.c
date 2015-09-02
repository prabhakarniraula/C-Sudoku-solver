#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


void board(int arr_2D[][9]);
void clr_buff(int );
void computer(int arr_2D[][9]);
void initialize(int arr_2D[][9],int arr_3D[][9][9]);
int  technique(int arr_2D[][9],int arr_3D[][9][9],int );
int  check(int arr_2D[][9]);
int  check_input(int arr_2D[][9],int ,int ,int);
int  single_candidate(int arr_2D[][9],int arr_3D[][9][9]);
int  single_position(int arr_2D[][9],int arr_3D[][9][9]);
int  candidate_lines(int arr_3D[][9][9]);
int  double_pairs(int arr_3D[][9][9]);
int  multiline(int arr_3D[][9][9]);
int  naked_pairs(int arr_3D[][9][9]);
int  xwing_swordfish(int arr_3D[][9][9]);
int  guessing(int arr_2D[][9],int arr_3D[][9][9]);
long int guess;
void good_bye();

int main()
{
   int arr_2D[9][9]={{0},{0},{0},{0},{0},{0},{0},{0},{0}},
 	choice,no=0,row,col,i,j,value;

   char ans;
   system("clear");

    printf("\n\n\t\t\t\tSUDOKU SOLVER");

        printf("\n\t\t\t\t");

        for(i=1;i<=13;i++)
        {
                printf("*");

                fflush(stdout);

                usleep(1500000);
        }



 //main loop until yes
  do
  {

                system("clear");
                board(arr_2D);



                for(i=0;i<=8;i++)
                {
                  for(j=0;j<=8;j++)
                  {
                       arr_2D[i][j]=0;
                  }
                }

                board(arr_2D);

  		printf("\n\n\t\t 1. Play The Game ");
  		printf("\n\n\t\t 2. Quit The Game ");

  		printf("\n\n\t\t\t Your Choice(1-2) : ");
  		no=scanf("%d",&choice);

  		clr_buff(no);
                if(no==0 || (choice!=1 && choice!=2))
                {
                  exit(0);
                  good_bye();
                }
		no=0;



		switch(choice)

               {
                  case 1 :

			printf("\nEnter Start Up Values (Press 999 To Terminate) : ");
                        while(1)
                         {

                               do
                               {

                                printf("\nEnter Row no : ");
                            	no=scanf("%d",&row);
                            	clr_buff(no);
                                if((row>9 && row!=999) || row<1)
                                  printf("\n Proper Input Required....!!!");



			       }while(no!=1 || (row>9 && row!=999) || row<1);
                               no=0;

                                if(row==999)
                                    {    break;

                                       }

				do
                               {

                                printf("\nEnter Col no : ");
                                no=scanf("%d",&col);
                                clr_buff(no);

                                if((col>9 && col!=999) || col<1)
                                  printf("\n Proper Input Required....!!!");

                               }while(no!=1 || (col>9 && col!=999) || col<1);
                               no=0;
                               if(col==999)
                                {
                                     break;
                                  }



                              do
                               {

                                printf("\nEnter value : ");
                                no=scanf("%d",&value);
                                clr_buff(no);
                                if((check_input(arr_2D,(row-1),(col-1),value)) && value!=0)
                                  value=10;

				if(value > 9 || value<0)
                                  printf("\n Proper Input Required.........!!");

                               }while(no!=1 || value>9 || value<0);
                               no=0;



                               arr_2D[row-1][col-1]=value;
                               board(arr_2D);





                         }



                             break;


                  case 2 :

                          good_bye();
                          exit(0);

               }

                computer(arr_2D);

                board(arr_2D);

               printf("\n\n\tNo Of Guesses : %lu",guess);

                printf("\n\n\tWish To Continue (y|n) : ");

	       while(getchar()!='\n')
		{
                  getchar();
		}

                scanf("%c",&ans);


   }while(ans=='y' || ans=='Y');

  good_bye();

 return 0;
}


void board(int arr_2D[][9])
{

  int i,j;

        system("clear");


         printf("\n\n\n\t\t\t\t\t SUDOKU SOLVER   ");
         printf("\n\t\t\t\t\t *************");


         printf("\n\n\n\t\t\t  1    2    3       4    5    6       7    8    9  ");


         printf("\n\n");


	 for(i=0;i<=8;i++)
 	{


		if(i==6 || i==3)
     			printf("\n\t\t\t__________________________________________________");

                printf("\n\n\t\t%d\t",i+1);

        	for(j=0;j<=8;j++)
        	 {
           		if((j%3)==0 && j!=0)
             		   printf(" | ");

           		if(arr_2D[i][j]!=0)
             		   printf("  %d  ",arr_2D[i][j]);

 			else
             		   printf("  %c  ",46);



        	}

 	}

	  printf("\n");

}


void clr_buff(int no)
{

  if(no==0)
  {
  	 printf("Proper Input Required.........!!!");

   	while(getchar()!='\n')
     	   getchar();

 }
}




void computer(int arr_2D[][9])
{
  int arr_3D[9][9][9],i,j;

  initialize(arr_2D,arr_3D);

   for(i=1;i<=8;i++)
   {
        j=0;

        j=technique(arr_2D,arr_3D,i);
 printf("\ntechnique %d applied",i);
        if(j!=0)
        {
		if(i==1 || i==2)
		      initialize(arr_2D,arr_3D);

   		if(check(arr_2D))
		       break;

	        i=0;
        }
   }

}





void initialize(int arr_2D[][9],int arr_3D [][9][9] )
{
   int i,j,k,l,m,count=0;

   for(i=0;i<9;i++)
   {
     for(j=0;j<9;j++)
      {
           for(k=0;k<9;k++)
           {
               if(arr_2D[i][j]!=0)
               {
                   if(arr_2D[i][j]!=(k+1))
                    arr_3D[i][j][k]=0;

                   else
                     arr_3D[i][j][k]=arr_2D[i][j];
               }

              else

               {  count=0;
                 for(l=0;l<9;l++)
                 {
                    if(arr_2D[i][l]==(k+1) )
		    {
                        count++;
			break;
		    }
                 }

                 if(count==0)
		{
		for(l=0;l<9;l++)
                 {

                       if(arr_2D[l][j]==(k+1))
			{
                          count++;
			  break;
			}

                 }
 		}

                 if(count==0)
		{
                 for(l=((i/3)*3);l<=(((i/3)*3)+2);l++)
                 {

                   for(m=((j/3)*3);m<=(((j/3)*3)+2);m++)
                   {
                        if(arr_2D[l][m]==(k+1))
			{
                           count++;
			   break;
			}


                   }

                 }
		}

                 if(count==0)

                      arr_3D[i][j][k]=(k+1);

                 else

                      arr_3D[i][j][k]=0;


               }
           }
      }

   }


}



int check(int arr_2D[][9])
{
 	int i,j,k=0;

 	for(i=0;i<9;i++)
  	{
     	    for(j=0;j<9;j++)
      	    {
           	if(arr_2D[i][j]!=0)
           	{
                	k++;
           	}
       	    }

  	}

 	if(k==81)
   	  return 1;
 	else
   	  return 0;

}



int check_input(int arr_2D[][9],int i,int j,int n)
{
 int l,k,p=0;

 for(l=0;l<9;l++)          //checking rows
 {
   if(arr_2D[i][l]==n)
      p++;

 }

 for(l=0;l<9;l++)         //checking columns
 {
   if(arr_2D[l][j]==n)
      p++;


 }

 for(l=((i/3)*3);l<((i/3)*3)+3;l++)   //checking 3x3 grids
 {
    for(k=((j/3)*3);k<((j/3)*3)+3;k++)
    {
       if(arr_2D[l][k]==n)
         p++;


    }

 }

  return p;



}


int technique(int arr_2D[][9],int arr_3D[][9][9],int n)
{

   int p=0;


 switch(n)

 {
    case 1 :
                                                        //single candidate
            p=single_candidate(arr_2D,arr_3D);

              return p;


   case 2 :					        //single position


           p=single_position(arr_2D,arr_3D);

             return p;

   case 3 :                                             //candidate lines


            p=candidate_lines(arr_3D);
              return p;

   case 4 :                                             //double pairs


            p=double_pairs(arr_3D);
              return p;

  case 5 :
                                                       //multiple lines


              p=multiline(arr_3D);
              return p;


  case 6 :
             		                               // naked pairs,triples,quads

              p=naked_pairs(arr_3D);
              return p;


  case 7 :                                             // X-wing and Swordfish
               p=xwing_swordfish(arr_3D);
               return p;


  case 8 :

                                                      //Guessing
             p=guessing(arr_2D,arr_3D);
   	      return p;

 }
  return 0;

}





int  single_candidate(int arr_2D[][9],int arr_3D[][9][9])
{
   int i,j,k,count,l,p=0;

          for(i=0;i<9;i++)
              {
 		for(j=0;j<9;j++)
                 {
                   count=0;

                    for(k=0;k<9;k++)
                    {
                       if(arr_3D[i][j][k]!=0)
                       {
                              count++;
                              l=k;
                       }
                    }

                    if(count==1 && arr_2D[i][j]==0)
                    {
                         arr_2D[i][j]=arr_3D[i][j][l];
                         p++;
                    }
                 }


              }

               return p;

}



int  single_position(int arr_2D[][9],int arr_3D[][9][9])
{
  int i,j,k,l,count,m,o,q,p=0;


	    for(l=1;l<=9;l++)                                           //checking rows
            {

               for(i=0;i<9;i++)
               {
                  count=0;

                  for(j=0;j<9;j++)
                  {
                     if(arr_3D[i][j][l-1]==l && arr_2D[i][j]==0)
                     {
                       count++;
                       m=j;

                     }

                  }

                  if(count==1)
                  {
                      arr_2D[i][m]=l;
                      p++;
                  }

               }

            }

        if(p==0)
        {
           for(l=1;l<=9;l++)                                           //checking columns
           {
              for(i=0;i<9;i++)
              {
                count=0;
                for(j=0;j<9;j++)
                {
                  if(arr_3D[j][i][l-1]==l && arr_2D[j][i]==0)
                  {
                     count++;
                     m=j;

                  }

                }

              if(count==1)
              {
                 arr_2D[m][i]=l;
                 p++;
              }

              }


           }

         }

       if(p==0)
       {
          for(l=1;l<=9;l++)                                       //checking 3x3 grids
          {
             for(i=0;i<9;i++)
             {
               if(i%3==0)
               {
                 for(j=0;j<9;j++)
                 {
                   count=0;
                   if(j%3==0)
                   {
                      for(k=i;k<(i+3);k++)
                      {
                         for(o=j;o<(j+3);o++)
                         {
                            if(arr_3D[k][o][l-1]==l && arr_2D[k][o]==0)
                            {
                               count++;
                               m=k;
                               q=o;
                            }
                         }
                      }

                      if(count==1)
                      {
                        arr_2D[m][q]=l;
                        p++;

                      }


                   }
                 }

               }
             }

          }

         }

         return p;

}



int  candidate_lines(int arr_3D[][9][9])
{
   int i,j,k,m=0,l,o,p=0,r,q,count;

         for(l=1;l<=9;l++)
         {
           for(i=0;i<9;i++)
           {
             if(i%3==0)
             {
                for(j=0;j<9;j++)
                {
                   count=0,r=0,q=10;

		   if(j%3==0)
                   {
                     for(k=i;k<(i+3);k++)
                     {
                        for(o=j;o<(j+3);o++)
                        {
                           if(arr_3D[k][o][l-1]==l)
                           {
                             count++;
                             if(o==q)
                              r++;
                             m=k;
                             q=o;

                           }

                        }
                     }

                    if((count==2 && r==1) || (count==3 && r==2))
                    {
                       for(o=0;o<9;o++)
                       {
                         if ((arr_3D[o][q][l-1]==l) &&  ((o<(k-3)) || (o>=k)))
                         {
                            arr_3D[o][q][l-1]=0;

                            p++;


                         }

                       }


                    }

                   }


                }

             }

           }

         }

         return p;

}



int  double_pairs(int arr_3D[][9][9])
{
   int i,j,k,l,o,flag,count,m,q,r,s,p=0;
   int save[2][3]={ {0,0,0},{0,0,0}};


        for(l=1;l<=9;l++)
              {
                 for(j=0;j<9;j++)
                 {
                     flag=0;
                     for(k=0;k<2;k++)
                     {
                       for(o=0;o<3;o++)
                       {
                          save[k][o]=0;
                       }
                     }

                     if((j%3)==0)
                     {
                        for(i=0;i<9;i++)
                        {
                          count=0,r=0,m=10;

                           if((i%3)==0)
                           {
                             for(k=i;k<(i+3);k++)
                             {
                                for(o=j;o<(j+3);o++)
                                {
                                   if(arr_3D[k][o][l-1]==l)
                                   {
                                     count++;
                                     s=q;
                                     if(m==k)
                                      r++ ;                                  // checking if they are in same row
                                     m=k;
                                     q=o;
                                   }
                                }
                             }

                             if((count==2) && (r==1))
                             {
                                  if(flag==0)
                                  {
                                     save[flag][0]=m;
                                     save[flag][1]=s;
                                     save[flag][2]=q;
				     flag++;
                                  }

                                  else if((flag==1) && (s==(save[0][1])) && (q==(save[0][2])) )
                                  {
                                     save[flag][0]=m;
                                     save[flag][1]=s;
                                     save[flag][2]=q;
				     flag++;
                                     break;
                                  }

                                  else
                                  {
                                     continue;
                                  }
                             }

                           }
                        }

			if(flag==2)
                        {
                           for(k=0;k<9;k++)
                           {
                             if((k!=(save[0][0])) && ((k!=(save[1][0]))))
                             {
                               m=save[0][1];
                               s=save[0][2];

                               if(arr_3D[k][m][l-1]==l)
                               {
				arr_3D[k][m][l-1]=0;
				p++;
                               }

                               if(arr_3D[k][s][l-1]==l)
                               {
  			       	arr_3D[k][s][l-1]=0;
				p++;
                               }

                             }
                           }

                        }

                     }
                 }
              }

              return p;

}



int  multiline(int arr_3D[][9][9])
{
   int i,j,k,l,o,m,s,q,t,u,count,flag,p=0,mark,mask;
   int save[3][3]={ {10,10,10},{10,10,10},{10,10,10}};


             for(l=1;l<=9;l++)
              {
                 for(j=0;j<9;j++)
                 {
                    flag=0,mark=0,mask=0;
                    for(k=0;k<3;k++)
                     {
                       for(o=0;o<3;o++)
                       {
                          save[k][o]=100;
                       }
                     }

                     if((j%3)==0)
                     {
                       for(i=0;i<9;i++)
                       {
                         count=0,q=11,s=11;
                         if((i%3)==0)
                         {

                           for(k=i;k<(i+3);k++)
                           {
                             for(o=j;o<(j+3);o++)
                             {
                                if(arr_3D[k][o][l-1]==l)
                                {
                                  if((q!=o && s!=o) && count<3)
                                  {

                                    s=q;
                                    q=o;
                                    count++;

                                  }



                                }
                             }
                           }

                           if((count==2))
                           {

                               if(flag==0)
                               {
                                 save[0][0]=i;
                                 save[0][1]=s;
                                 save[0][2]=q;
                                 flag++;
                               }
                               else if((((flag==1) && mask==0 ) || ((flag==2) && (mask==1))) && (((s==save[0][1]) && (q==save[0][2])) || ((q==save[0][1]) && (s==save[0][2]))) )
                               {

				  save[1][0]=i;
                                  save[1][1]=s;
                                  save[1][2]=q;

                                 if(flag==1)
                                  flag++;
                                  break;
                               }
                               else if(((flag==2) && (mask==1) ) && (((s==save[2][1]) && (q==save[2][2])) || ((q==save[2][1]) && (s==save[2][2]))) )
                               {
                                  save[1][0]=i;
                                  save[1][1]=s;
                                  save[1][2]=q;

                                  mark++;
                                  break;
                               }
                               else
                               {
                                 save[2][0]=i;
                                 save[2][1]=s;
                                 save[2][2]=q;
                                 flag++;
                                 mask++;

                               }
                           }
                         }

                       }

                       if(flag==2)
                       {


                        if(mark==0)
                              u=((save[0][0])/3);
                        if(mark==1)
                             u=((save[2][0])/3);

                         m=save[1][1];
                         t=save[1][2];


                        for(k=0;k<9;k++)
                         {

                            if((((k/3)!=u) && ((k/3)!=((save[1][0])/3))))
                            {


                               if(arr_3D[k][m][l-1]==l)
                               {
				arr_3D[k][m][l-1]=0;

                                p++;
                               }

                               if(arr_3D[k][t][l-1]==l)
                               {
				arr_3D[k][t][l-1]=0;

                                p++;
                               }

                            }
                         }

                       }

                     }


                 }
              }

              return p;

}



int  naked_pairs(int arr_3D[][9][9])
{
  int i,j,l,k,r,m,q,s,o,t,u,count,flag,p=0;


               for(i=0;i<9;i++)                                           // checking rows
           {
              for(j=0;j<9;j++)
              {
                 r=0,flag=0;
                 for(k=0;k<9;k++)
                 {
                    if(arr_3D[i][j][k]==(k+1))
                      r++;

                 }

                 if(r<=4 && r>1)
                 {

                    for(l=0;l<9;l++)
                    {
                        u=0;
                       for(k=0;k<9;k++)
                       {
                          if(arr_3D[i][l][k]==(k+1))
                           {

		         if  (arr_3D[i][l][k]!=arr_3D[i][j][k])
                          {
                 	      u++;
                              break;


                          }

			  }
			}


			if(u==0)
			{
	          		if(r>3)
	                         o=m;

                             if(r>2)
                              m=q;

                              q=s;
                              s=l;
                             flag++;

			}

                    }

                    if(flag==r)
                    {
                      for(l=0;l<9;l++)
                      {

                         if(r==2)
                         {
                            if((l!=q) && (l!=s))
                            {
                               for(k=0;k<9;k++)
                               {

                               		if((arr_3D[i][l][k]==arr_3D[i][j][k]) && (arr_3D[i][l][k]==(k+1)) )
                               		{

                                  	     	arr_3D[i][l][k]=0;
                                                p++;

                               		}
                              }

                            }

                         }

                         else if(r==3)
                         {
                            if((l!=q) && (l!=s) && (l!=m))
                            {

                                for(k=0;k<9;k++)
                               	{
					if((arr_3D[i][l][k]==arr_3D[i][j][k]) && (arr_3D[i][l][k]==(k+1)) )
                               		{
                                  		arr_3D[i][l][k]=0;
					        p++;

                               		}
                               }
                            }

                         }

                         else
                         {
                           if((l!=q) && (l!=s) && (l!=m) && (l!=o))
                           {
                              for(k=0;k<9;k++)
                              {

                               		if((arr_3D[i][l][k]==arr_3D[i][j][k]) && (arr_3D[i][l][k]==(k+1)) )
                           		{
                               			arr_3D[i][l][k]=0;
					        p++;

                           		}
                              }
                           }

                         }

                      }

                    }

                 }
                        if(p!=0)
                           return p;

              }

           }


          for(i=0;i<9;i++)                                           // checking columns
           {
              for(j=0;j<9;j++)
              {
                 r=0,flag=0;
                 for(k=0;k<9;k++)
                 {
                    if(arr_3D[j][i][k]==(k+1))
                      r++;

                 }

                 if(r<=4 && r>1)
                 {
                    for(l=0;l<9;l++)
                    {
                       u=0;
                       for(k=0;k<9;k++)
                       {
                          if (arr_3D[l][i][k]==(k+1))
                          {
				if (arr_3D[l][i][k]!=arr_3D[j][i][k])
                          {
			     u++;
                             break;
                          }
			}

                       }
                 	if(u==0)
			{

                            if(r>3)
                              o=m;

                             if(r>2)
                              m=q;

                              q=s;
                              s=l;
                              flag++;

			}

                    }


                if(flag==r)
                    {
                      for(l=0;l<9;l++)
                      {

                         if(r==2)
                         {
                            if((l!=q) && (l!=s))
                            {
                              for(k=0;k<9;k++)
                              {

                               		if((arr_3D[l][i][k]==arr_3D[j][i][k]) && (arr_3D[l][i][k]==(k+1)))
                               		{
                                  		arr_3D[l][i][k]=0;

                                                p++;

                               		}
                              }
                            }

                         }

                         else if(r==3)
                         {
                            if((l!=q) && (l!=s) && (l!=m))
                            {
				for(k=0;k<9;k++)
                                {

                               		if((arr_3D[l][i][k]==arr_3D[j][i][k]) && (arr_3D[l][i][k]==(k+1)) )
                               		{
                                  		arr_3D[l][i][k]=0;

                                                p++;
                                        }
                               }

                            }

                         }


                         else
                         {
                           if((l!=q) && (l!=s) && (l!=m) && (l!=o))
                           {
				for(k=0;k<9;k++)
                                {

                               		if((arr_3D[l][i][k]==arr_3D[j][i][k]) && (arr_3D[l][i][k]==(k+1)) )
                           		{
                               			arr_3D[l][i][k]=0;

                                                p++;
                                        }
                           	}

                           }

                         }

                      }

                    }

                 }
                    if(p!=0)
			return p;

              }

           }


           for(i=0;i<9;i++)                              // checking 3x3 grids
           {
             for(j=0;j<9;j++)
             {
                r=0,flag=0;
                for(k=0;k<9;k++)
                {
                   if(arr_3D[i][j][k]==(k+1))
                     r++;

                }

                if(r<=4 && r>1)
                {
                   count=0;
                   for(t=((i/3)*3);t<(((i/3)*3)+3);t++)
                   {
                      for(l=((j/3)*3);l<(((j/3)*3)+3);l++)
                      {  u=0;
                         count++;
                         for(k=0;k<9;k++)
                         {
                            if(arr_3D[t][l][k]==(k+1))
                              {

				if (arr_3D[t][l][k]!=arr_3D[i][j][k])
                            {
                               u++;
			       break;
                            }

			    }
                         }
			if(u==0)
			{
				 if(r>3)
                                o=m;

                               if(r>2)
                                m=q;

                               q=s;
                               s=count;
                               flag++;
			}

                      }

                   }

                   if(flag==r)
                   {
                        count=0;
                        for(t=((i/3)*3);t<(((i/3)*3)+3);t++)
                        {
                           for(l=((j/3)*3);l<(((j/3)*3)+3);l++)
                           {
                              count++;

                              if(r==2)
                              {
                                if((count!=q) && (count!=s))
                                {
                                  for(k=0;k<9;k++)
                                  {
                                    if((arr_3D[t][l][k]==arr_3D[i][j][k]) && (arr_3D[t][l][k]==(k+1)) )
                                    {
                                       arr_3D[t][l][k]=0;

                                       p++;

                                    }

                                  }

                                }

                              }

                              else if(r==3)
                              {
                                if((count!=q) && (count!=s) && (count!=m))
                                {
                                  for(k=0;k<9;k++)
                                  {
                                    if((arr_3D[t][l][k]==arr_3D[i][j][k]) && (arr_3D[t][l][k]==(k+1)) )
                                    {
                                       arr_3D[t][l][k]=0;

                                       p++;

                                    }

                                  }

                                }

                              }

                              else
                              {
                                if((count!=q) && (count!=s) && (count!=m) && (count!=o))
                                {
                                  for(k=0;k<9;k++)
                                  {
                                    if((arr_3D[t][l][k]==arr_3D[i][j][k]) && (arr_3D[t][l][k]==(k+1)) )
                                    {
                                       arr_3D[t][l][k]=0;

                                       p++;

                                    }

                                  }

                                }

                              }

                           }

                        }

                   }


                }

		   if(p!=0)
			return p;
             }

           }


           return p;

}




int  xwing_swordfish(int arr_3D[][9][9])
{
   int i,j,l,k,r,m,q,s,o,t,count,flag,p=0;
   int save[2][3]={ {0,0,0},{0,0,0}};


          for(l=1;l<=9;l++)
           {
             for(i=0;i<9;i++)
             {
               flag=0;

               for(j=0;j<9;j++)
               {
                  if(arr_3D[i][j][l-1]==l)
                  {
                    r=i;
                    s=q;
                    q=j;
                    flag++;
                  }
               }

               if(flag==2)
               {


                 for(count=(r+1);count<9;count++)
                 {
                   if(arr_3D[count][q][l-1]==l)
                   {
                    flag=0;

                    for(j=0;j<9;j++)
                    {
                      if(arr_3D[count][j][l-1]==l)
                      {
                        m=count;
                        o=t;
                        t=j;
                        flag++;

                      }

                    }

                    if(flag==2)
                    {


                       if(o==s)                                           //code for x-wing
                       {
                         for(j=0;j<9;j++)
                         {
                              if((j!=r) && (j!=m))
                              {
                                if((arr_3D[j][s][l-1]==l) || (arr_3D[j][q][l-1]==l))
                                {
					arr_3D[j][s][l-1]=0;
                                	arr_3D[j][q][l-1]=0;

                                	p++;
                                }

                              }

                         }


                       }
                       else
                       {
                         for(k=(m+1);k<9;k++)
                         {
                            if(arr_3D[k][t][l-1]==l)
                            {
                               flag=0;

                              for(j=0;j<9;j++)
                              {
                                if(arr_3D[k][j][l-1]==l)
                                {
                                  save[0][0]=k;
                                  save[0][1]=save[0][2];
                                  save[0][2]=j;
                                  flag++;

                                }

                              }
                              if(flag==2)
                              {

                                if(save[0][1]==s)                //code for swordfish
                                {
                                  for(j=0;j<9;j++)
                                  {
                                     if((j!=r) && (j!=m) && (j!=(save[0][0])))
                                     {
                                        if((arr_3D[j][t][l-1]==l) || (arr_3D[j][q][l-1]==l) || (arr_3D[j][s][l-1]==l))
                                        {
                                         arr_3D[j][t][l-1]=0;
                                         arr_3D[j][q][l-1]=0;
                                         arr_3D[j][s][l-1]=0;

                                         p++;
                                        }

                                     }

                                  }


                                }

                              }


                            }

                         }

                       }

                    }

                   }

                 }

               }

             }

           }

           return p;


}





int  guessing(int arr_2D[][9],int arr_3D[][9][9])
{
   int i,j,k;

          if(check(arr_2D))
             {
              return (1);
             }

             else
             {
               for(i=0;i<9;i++)
               {
                 for(j=0;j<9;j++)
                 {
                   if(arr_2D[i][j]==0)
                   {
                     for(k=0;k<9;k++)
                     {

			if(arr_3D[i][j][k]!=0)
                         {
                                   arr_2D[i][j]=(k+1);
                                   initialize(arr_2D,arr_3D);


                                if(technique(arr_2D,arr_3D,8))
                                {
                                 guess++;
                                return (1);

                                }

				  arr_2D[i][j]=0;
                                  initialize(arr_2D,arr_3D);

                 	 }
              	     }
                        return 0;
             	   }


		}
           }
         }
  return 0;
}

void good_bye()

{

	int i;
	char msg1[100] = "THANK YOU FOR PLAYING THE GAME.......";
	char msg2[100] = "CREATED BY : Prabhakar Niraula";
	char msg3[100] = "INSPIRED BY : PROF.JIGAR M PANDYA";

	system("clear");

	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t");


	for(i=0;msg1[i]!='\0';i++)

	{

		printf("%c",msg1[i]);

		fflush(stdout);

		usleep(150000);

	}

	  usleep(1000000);

	  printf("\n\n\n\n\t\t\t\t\t\t");


	for(i=0;msg2[i]!='\0';i++)

	{

		printf("%c",msg2[i]);

		fflush(stdout);

		usleep(150000);

	}




	  usleep(1000000);
	  printf("\n\n\n\t\t\t\t\t\t");


	for(i=0;msg3[i]!='\0';i++)

	{

	printf("%c",msg3[i]);

	fflush(stdout);

	usleep(150000);

	}

	usleep(2000000);
	system("clear");

}
