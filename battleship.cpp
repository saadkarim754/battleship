#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>

using namespace std;

string name;
const int grid_max = 9;

void initiator();
void instructions();
void coordinates (int &a , int &b ,char ch1 , char ch2);
void copying_matrix(char mat1[][grid_max],char mat2[][grid_max],int grid_size);
void rand_array(int rand_arr[8],int min_limit);
void frigate_1(char mat[][grid_max], int grid_size,int a, int b);
void frigate_2(char mat[][grid_max], int grid_size,int a, int b);
void battle_ship(char mat[][grid_max], int grid_size,int a, int b);
void carrier(char mat[][grid_max], int grid_size,int a, int b);
void get_input (char mat[grid_max][grid_max], int grid_size);
void print (char mat[][grid_max], int grid_size);
void barrier ();


int main ()
{
    int shots;
    char start;
    int count_c=0 , count_b=0 , count_f1=0 , count_F2=0, count =0,t_count=0;
    int a,b;
    char decision;

    initiator();
    cout<<endl;

  int rand_a[8];
  //declarations
  int grid_size;
  char A,B;
  int difficulty;
  //the origiinal matrix in which all the changes are happening
  char mat_original[grid_max][grid_max];
  //the bogus matrix that we created to show to the user
  char mat_bogus[grid_max][grid_max];
  //to show the matrix to user in last
  char mat_dec[grid_max][grid_max];

  cout<<setw(30)<<" ******* TO START *******"<<endl;
  cout<<setw(25)<<"        press any key "<<endl<<endl;

  cout<<setw(30)<<" ******* FOR EXIT *******"<<endl;
  cout<<setw(25)<<"        press 'X' "<<endl<<endl;

  cout<<setw(20)<<" your choice == ";
  cin>>start;
  if(start=='x' || start=='X')
  {
      return 0;
  }
  cout<<endl<<endl;
  instructions();

  //prompt
  cout << endl << " Enter any grid size between 1 and 9 " << endl;
  cout << " Grid size = ";
  cin >> grid_size;

  //prompt
  cout << endl << " Enter the level of difficulty " << endl;
  cout << " esay = 1  ,hard = 2 , very hard = 3 "<<endl<<" Difficulty = ";
  cin >> difficulty;

switch (difficulty) {
    case 1:
        shots = 40;
        break;
    case 2:
        shots = 20;
        break;
    case 3:
        shots = 10;
        break;
    default:
        shots = 40;
        break;
}

  // places values in matrix
  get_input (mat_original, grid_size);

  //copies the original matrix into bogus matrix;
  copying_matrix(mat_original,mat_bogus,grid_size);

  //prepares random numbers for rows and columns of arrays
  rand_array(rand_a,grid_size);

  //code that places the ships in their desired places.
  carrier(mat_original,grid_size,rand_a[0],rand_a[1]);
  battle_ship(mat_original,grid_size,rand_a[2],rand_a[3]);
  frigate_1(mat_original,grid_size,rand_a[4],rand_a[5]);
  frigate_2(mat_original,grid_size,rand_a[6],rand_a[7]);

  //to make another matrixx that we can show to the user in the last
  copying_matrix(mat_original,mat_dec,grid_size);

  cout<<endl<<" The battle field is here ,, cap \n lets start "<<endl;
  print (mat_bogus, grid_size);

//mechanism to hit and detect the hits
   for(int i = 0 ; i < shots ; i++)
{
        cout<<" Take your shot = ";
        cin.ignore();
        cin>>A>>B;

        coordinates (a,b,A,B);

        if(mat_original[a][b] == 'c')
        {
            mat_original[a][b] = 'c';
            mat_bogus[a][b] = 'c';
            count_c++;
        }

        else if(mat_original[a][b] == 'b')
        {
            mat_original[a][b] = 'b';
            mat_bogus[a][b] = 'b';
            count_b++;
        }

        else if(mat_original[a][b] == 'f')
        {
            mat_original[a][b] = 'f';
            mat_bogus[a][b] = 'f';
            count_f1++;
        }

        else if(mat_original[a][b] == 'F')
        {
            mat_original[a][b] = 'F';
            mat_bogus[a][b] = 'F';
            count_F2++;
        }

        else
        {
            mat_original[a][b] = 'X';
            mat_bogus[a][b] = 'X';
            count++;
        }

      //a line that works as the clear screen command
    cout << "\033[2J\033[1;1H";

    cout<<endl<<" Your progress ,, captain !!"<<endl<<endl;
    cout<<" carrier destroyed = "<<count_c<<endl;
    cout<<" battle ship destroyed = "<<count_b<<endl;
    cout<<" Frigate 1 destroyed = "<<count_f1<<endl;
    cout<<" Frigate 2 destroyed = "<<count_F2<<endl;
    cout<<" !! Remaining shots !! = "<<(shots - t_count - 1)<<endl;
    cout<<" Missed shots = "<<count<<endl<<endl;

    if(count_c >= 4)
    {
        cout<<endl<<" THE carrier is destryed "<<endl;
    }

    else if(count_b >= 3)
    {
        cout<<endl<<" THE battle ship is destryed "<<endl;
    }

    else if(count_f1 == 2)
    {
        cout<<endl<<" one of the frigate is destryed "<<endl;
    }

    else if(count_F2 == 2)
    {
        cout<<endl<<" one of the frigate is destryed "<<endl;
    }

    print (mat_bogus, grid_size);

    //to count our shots
    t_count = count_c + count_b + count_f1 + count_F2 + count;

    if(count_c >=4 && count_b >= 3 && count_f1 ==2 && count_F2==2 )
    {
        cout<<" Congrats!! youve won the game";
        return 0;
    }

    else if(t_count == shots)
    {
        cout<<" ooppsss,,,\n  You ran out of shots !! sorryy"<<endl<<endl;
        cout<<" Still wanna see the locations ,,,\n"
            <<" IF yes, press 'y' = ";
        cin>>decision;

            if(decision == 'y' || decision == 'Y')
            {
                cout<<endl<<" The orginal locations were "<<endl;
                 print (mat_dec, grid_size);
            }
    }
 }


return 0;
}

void
get_input (char mat[grid_max][grid_max], int grid_size)
{
  char b = '-';
  for (int i = 0; i < grid_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
	{
	  mat[i][j] = b;
	}
    }
}

void
print (char mat[][grid_max], int grid_size)
{
  cout << "  ";

  for (int a = 65; a < (grid_size + 65); a++)
    {
      cout << "   " << (char) a << "";
    }

  cout << endl << endl;

  for (int i = 0; i < grid_size; i++)
    {
      cout << i << "    ";
      for (int j = 0; j < grid_size; j++)
	{
	  cout << mat[i][j] << "   ";
	}
      cout << endl <<endl;
    }
cout<<endl;
  barrier ();
}


void
barrier ()
{
  for (int a = 0; a < 4; a++)
    {
      cout << "******";
    }
}

void
instructions ()
{
  cout <<" ***  INSTRUCTIONS ***"<<endl;
  cout <<" --> Now ,, Read carefully ,,!! "<<name<<" !!!."<<endl<<endl;
  cout <<" --> 1) You can enter your desired grid size (9 * 9) is the most preffered\n ";
  cout <<" --> 2) Enter the co-ordinates you want to hit in any order \n ";
  cout <<" --> 3) Invalid shot will result in a miss \n ";
  cout <<" --> 4) Remember !! ,, You only have limited number of shots \n"<<endl<<endl;
}

void
carrier(char mat[][grid_max], int grid_size,int a, int b)
{

    for(int i = 0 ; i < 5;i++)
    {
            mat[a][b + i] = 'c';
    }
}

void
battle_ship(char mat[][grid_max], int grid_size,int a, int b)
{
    for(int i = 0 ; i < 4;i++)
    {
            mat[a][b + i] = 'b';
    }
}

void
frigate_1(char mat[][grid_max], int grid_size,int a, int b)
{
   for(int i = 0 ; i < 2;i++)
    {
            mat[a][b + i] = 'f';
    }
}

void
frigate_2(char mat[][grid_max], int grid_size,int a, int b)
{
    for(int i = 0 ; i < 2;i++)
    {
            mat[a][b + i] = 'F';
    }
}

void
rand_array(int rand_arr[8],int min_limit)
{
  srand(time(0));

  for(int i = 0 ;i<8 ;i++)
  {
   rand_arr[i] = rand() % min_limit;


   for(int j = 0 ; j < i ;j++)
   {
       while(rand_arr[i]==rand_arr[j])
       {
            rand_arr[i] = rand() % min_limit;
       }
   }

  }
}

void copying_matrix(char mat1[][grid_max],char mat2[][grid_max],int grid_size)
{
    for(int i = 0 ; i<grid_size ;i++)
    {
        for(int j = 0 ; j<grid_size;j++)
        {
            mat2[i][j] = mat1[i][j];
        }
    }
}

void coordinates (int &a , int &b ,char ch1 , char ch2)
{
    char temp;
    if(ch1>ch2)
    {
        temp = ch1;
        ch1 = ch2;
        ch2 = temp;
    }
    a = ch1 - 48;

    if(ch2>=65&&ch2<=90)
    {
        b=ch2-65;
    }
    else if(ch2>=97&&ch2<=122)
    {
        b=ch2-97;
    }
}

void initiator()
{
    barrier();
    cout<<"  BATTLE SHIP  ";
    barrier();
    cout<<endl<<endl;
    cout<<"  Enter your name for the record = ";
    getline(cin,name);
    cout<<endl<<setw(20)<<" ** Welcome "<<name<<" **"<<endl;
}
