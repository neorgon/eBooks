#include <iostream>
#include <windows.h>

using namespace std;

void gotoXY(int x, int y)
{
	 //Initialize the coordinates
	 COORD coord = {x, y};
	 //Set the position
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	 return;
}

void ClearConsole()
{
	 //Get the handle to the current output buffer...
	 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	 //This is used to reset the carat/cursor to the top left.
	 COORD coord = {0, 0};
	 //A return value... indicating how many chars were written
	 //   not used but we need to capture this since it will be
	 //   written anyway (passing NULL causes an access violation).
	 DWORD count;
	 //This is a structure containing all of the console info
	 // it is used here to find the size of the console.
	 CONSOLE_SCREEN_BUFFER_INFO csbi;
	 //Here we will set the current color
	 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	 {
		  //This fills the buffer with a given character (in this case 32=space).
		  FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		  FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
		  //This will set our cursor position for the next print statement.
		  SetConsoleCursorPosition(hStdOut, coord);
	 }
	 return;
}

int main() {
	ClearConsole();
	cout << "The number is: ";
	cout.flush();
	for (int i = 0; i < 1000; i++) {
		gotoXY(15,0);
		cout << i;
		cout.flush();
		Sleep(25); //Needed to add because the computer was too fast...
	}
	return 0;
}

/*

#include <iostream>
#include <windows.h>

//This will set the position of the cursor
	void gotoXY(int x, int y) {
	//Initialize the coordinates
	COORD coord = {x, y};
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void getCursorXY(int &x, int&y) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;

	}
}

using namespace std;

int main() {
	int x = 0, y = 0;
	cout << "Find the cursor test 1";
	gotoXY(30, 10);
	getCursorXY(x, y);
	cout << endl;
	cout << "cursor was at: (" << x <<", " << y << ")" << endl;


	return 0;
}
*/

/*
    Author: http://HelloACM.com
            http://CodingForSpeed.com
*/
/*
#include <stdio.h>
#include <unistd.h> // for usleep function

const char rocket[] =
"           _\n\
          /^\\\n\
          |-|\n\
          | |\n\
          |N|\n\
          |A|\n\
          |S|\n\
          |A|\n\
         /| |\\\n\
        / | | \\\n\
       |  | |  |\n\
        `-\"\"\"-`\n\
";

int main()
{
    for (int i = 0; i < 50; i ++) printf("\n"); // jump to bottom of console
    printf("%s", rocket);
    int j = 300000;
    for (int i = 0; i < 50; i ++) {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        printf("\n"); // move rocket a line upward
    }
    printf("Visit http://HelloACM.com !\n");
    return 0;
}
*/
/*

#include <iostream>

using namespace std;

int main()
{
    cout << char(218) << char(196) << 55 << char(196) << char(191) << endl;
    cout << char(179) << char(32) << char(32) << char(32) << char(32) << char(179) << endl;
    cout << char(192) << char(196) << 22 << char(196) << char(217) << endl;
    return 0;
}
*/


/*
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<ctime>

void draw_grid();		//declare function
void copy1d();
void copy2d();
void bubblesort();

//Name:
//Author:
//Date:
using namespace std;

int arr[5][5];
int arr1d[25];
//---------------------------------------------------------
main()
{
 int x,y,rtot=0;
 srand(time(0));

 for(x=0;x<5;x++)    //load data into 2d array
 {
  for(y=0;y<5;y++)
   {
        arr[x][y]=rand() % 20 + 1;
   }
  }
cout<<"2D Array unsorted"<<endl;
 draw_grid();
 copy1d();
 bubblesort();
 copy2d();
 cout<<endl<<endl;
 getch();
 cout<<"2D array sorted"<<endl;
 draw_grid();
cout<<endl;

 getch();
}
void draw_grid() //--------------------------------------------
 {
  int x,y;
  char topl[25]={char(201),char(205),char(205),char(205),char(203),char(205),char(205),char(205),char(203),char(205),char(205),char(205),char(203),char(205),char(205),char(205),char(203),char(205),char(205),char(205),char(187)};
  char midl[25]={char(204),char(205),char(205),char(205),char(206),char(205),char(205),char(205),char(206),char(205),char(205),char(205),char(206),char(205),char(205),char(205),char(206),char(205),char(205),char(205),char(185)};
  char bottoml[25]={char(200),char(205),char(205),char(205),char(202),char(205),char(205),char(205),char(202),char(205),char(205),char(205),char(202),char(205),char(205),char(205),char(202),char(205),char(205),char(205),char(188)};
  //clrscr();
  cout<<endl;
  cout<<topl<<endl;
  for(x=0;x<5;x++)
   {
   	for(y=0;y<5;y++)
   	 {
   	    if(y==0)
   	     cout<<char(186);
		cout<<char(32)<<arr[x][y];
		if (arr[x][y] <10)
		cout<<char(32)<<char(186);
	    else
	    cout<<char(186);
     }
     cout<<endl;
    if (x<4)
     cout<<midl<<endl;
   }
   cout<<bottoml<<endl;
  }
//------------------------------------------------------
void copy1d()
{
 int x,y,w=0;
 for(x=0;x<5;x++)    //load data into 2d array
 {
  for(y=0;y<5;y++)
   {
        arr1d[w] = arr[x][y];
        w++;
   }
  }
}
//--------------------------------------------------------
void bubblesort()
{
int i,x, j, temp,flag = 1;    // set flag to 1 to start first pass

    while(flag == 1)
     {
          flag = 0;
          for (j=0; j < 24; j++)
           {
               if (arr1d[j+1] < arr1d[j])      // ascending order simply changes to <
              {
                    temp = arr1d[j];             // swap elements
                    arr1d[j] = arr1d[j+1];
                    arr1d[j+1] = temp;
                    flag = 1;               // indicates that a swap occurred.
               }
           }
     }
}
//--------------------------------------------------------
void copy2d()
{
 int x,y,w=0;
 for(x=0;x<5;x++)    //load data into 2d array
 {
  for(y=0;y<5;y++)
   {
     arr[x][y]=arr1d[w];
     w++;
   }
  }
}
//--------------------------------------------------------
*/



/*
#include <iostream>

int Modulus(int iN, int iMod) {
	int iQ = (iN/iMod);
	return iN - (iQ*iMod);
}

char GetChar(int iGenerator, char cBase, int iRange) {
	return (cBase + Modulus(iGenerator, iRange));
}

int main() {
	char caRow[80];
	int j = 7;
	int k = 2;
	int l = 5;
	int m = 1;
	while (true) {
		int i = 0;
		// Output a random row of characters
		while (i < 80) {
			if (caRow[i] != ' ') {
				caRow[i] = GetChar(j + i*i, 33, 30);
			}
			std::cout << caRow[i];
			++i;
		}
		j = (j + 31);
		k = (k + 17);
		l = (l + 47);
		m = (m + 67);
		caRow[Modulus(j, 80)] = '-';
		caRow[Modulus(k, 80)] = ' ';
		caRow[Modulus(l, 80)] = '-';
		caRow[Modulus(m, 80)] = ' ';
		// Delay
		i = 0;
		while (i < 300000) {
			GetChar(1, 1, 1);
			 ++i;
		}
	}
    return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    int id = 0;
    int N = 4;

    vector<int> adyacent;

    map<int, vector<int> > mapa;

    vector<string> S_adyacent;
    S_adyacent = {"0","0"};

    map<string, vector<string>> mapa_semaforos;

    for (int i = 1; i <= N; ++i)
    {
        for (int j= 1; j <= N; ++j)
        {
            id++;

            adyacent={0,0};

             if (i%2!=0 && j%2 != 0)         //---->>>> y ^ arriba
            {
                if (id-(N*i)!=0)
                {
                    S_adyacent[0] = to_string(id+1)+"V";
                    adyacent[0]=id+1;
                }
                if (id-N>=1)
                {
                    S_adyacent[1] = to_string(id-N)+"H";
                    adyacent[1]=id-N;
                }

                if(id-(N*(i-1)+1)==0   ||  id+N > N*N  )
                {
                        mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id) ,S_adyacent));
                }
                else
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"V" ,S_adyacent));
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"H" ,S_adyacent));

                }
            }
            if (i%2!=0 && j%2 == 0)         //---->>> y v abajo
            {
                if (id-(N*i)!=0)
                {
                    S_adyacent[0] = to_string(id+1)+"V";
                    adyacent[0]=id+1;
                }
                if (id+N <= N*N)
                {
                    S_adyacent[1] = to_string(id+N)+"H";
                    adyacent[1]=id+N;
                }

                if(id-(N*(i-1)+1)==0   ||  id-N<1 )
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id) ,S_adyacent));
                }
                else
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"V" ,S_adyacent));
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"H" ,S_adyacent));
                }

            }

            if (i%2==0 && j%2 != 0)         //<<<---- y ^ arriba
            {
                if (id-(N*(i-1)+1)!=0)
                {
                    S_adyacent[0] = to_string(id-1)+"V";
                    adyacent[0]=id-1;
                }
                if (id-N>=1)
                {
                    S_adyacent[1] = to_string(id-N)+"H";
                    adyacent[1]=id-N;
                }
                if(id-(N*i)==0  ||  id+N > N*N  )
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id) ,S_adyacent));
                }
                else
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"V" ,S_adyacent));
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"H" ,S_adyacent));
                }
            }

            if (i%2==0 && j%2 == 0)         //<<<---- y v abajo
            {
                if (id-(N*(i-1)+1)!=0)
                {
                    S_adyacent[0] = to_string(id-1)+"V";
                    adyacent[0]=id-1;
                }
                if (id+N <= N*N)
                {
                    S_adyacent[1] = to_string(id+N)+"H";
                    adyacent[1]=id+N;
                }

                if(id-(N*i)==0  ||  id-N<1 )
                {
                        mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id) ,S_adyacent));
                }
                else
                {
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"V" ,S_adyacent));
                    mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"H" ,S_adyacent));
                }
            }


            mapa.insert(pair<int,vector<int>> (id,adyacent));

            //mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"V" ,S_adyacent));
            //mapa_semaforos.insert(pair<string,vector<string>> ( to_string(id)+"H" ,S_adyacent));
        }
    }


    map<int,vector<int>>::iterator it = mapa.begin();

    for (it=mapa.begin(); it!=mapa.end(); ++it)
        cout << it->first << " => " << it->second[0] << " => "<< it->second[1] << '\n';

    cout<<"*********************************************************\n";

    map<string,vector<string>>::iterator it2 = mapa_semaforos.begin();

    for (it2=mapa_semaforos.begin(); it2!=mapa_semaforos.end(); ++it2)
        cout << it2->first << " => " << it2->second[0] << " => "<< it2->second[1] << '\n';

    return 0;
}
*/
