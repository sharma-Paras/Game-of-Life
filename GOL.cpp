#include < iostream >
#include < windows.h >
#include < stdlib.h >
#include < fstream >
#include < time.h >
 const int maxrows = 43;
const int maxcols = 150;
using namespace std;
void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void copy(char array1[maxrows][maxcols], char array2[maxrows][maxcols]) {
  for (int j = 0; j < maxrows; j++) {
    for (int i = 0; i < maxcols; i++)
      array2[j][i] = array1[j][i];
  }
}
class gol {
  private:
    char gen0[maxrows][maxcols], final[maxrows][maxcols], backup[maxrows][maxcols];
  char c2;
  public:
    void init() {

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
      int a;
      do {
        system("cls");
        cout << "\nWHICH PATTERN YOU WANT TO SEE?????";
        cout << "\n1.     Puffer Train";
        cout << "\n2.     Glider Gun ";

        cout << "\n3.     Symmetra";
        cout << "\n4.     Feeling Lucky";
        cout << "\n   Enter your choice\n";
        cin >> a;
        cout << "\n Do you want colour coding????(y/n)";
        cin >> c2;
        system("cls");
      } while (a > 4);

      if (a == 1) {

        char c;
        ifstream file("P2.txt");
        if (!file)
          cout << "error";
        else {
          file.seekg(0);
          for (int j = 0; j < maxrows; j++) {
            for (int i = 0; i < maxcols; i++) {
              file.get(c);
              gen0[j][i] = c;
              backup[j][i] = 0;
            }
          }

          file.close();
        }
      }
      if (a == 2) {
        char c;
        ifstream file("P5.txt");
        if (!file)
          cout << "error";
        else {
          file.seekg(0);
          for (int j = 0; j < maxrows; j++) {
            for (int i = 0; i < maxcols; i++) {
              file.get(c);
              gen0[j][i] = c;
              backup[j][i] = 0;
            }
          }

          file.close();
        }
      }

      if (a == 3)

      {

        char c;
        ifstream file("P1.txt");
        if (!file)
          cout << "error";
        else {
          file.seekg(0);
          for (int j = 0; j < maxrows; j++) {
            for (int i = 0; i < maxcols; i++) {
              file.get(c);
              gen0[j][i] = c;
              backup[j][i] = 0;
            }
          }

          file.close();
        }

      }
      if (a == 4) {
        srand(time(NULL));

        for (int j = 1; j < maxrows; j++) {
          for (int i = 1; i < maxcols; i++)
            gen0[j][i] = rand() % 2;
        }
      }
      for (int j = 0; j < maxrows; j++) {
        for (int i = 0; i < maxcols; i++) {

          backup[j][i] = 0;
        }
      }

      copy(gen0, final);

    }
  void generation(char choice);
  bool compare() {
    int count = 0;
    for (int j = 0; j < maxrows; j++) {
      for (int i = 0; i < maxcols; i++) {
        if (final[j][i] == backup[j][i])
          count++;
      }
    }

    if (count == maxrows * maxcols)
      return true;
    else
      return false;
  }
  void cpy() {
    copy(final, backup);
  }

  void display();
};

void gol::generation(char choice) {

  char temp[maxrows][maxcols];
  copy(final, temp);
  for (int j = 1; j < maxrows - 1; j++) {
    for (int i = 1; i < maxcols - 1; i++) {
      if (choice == 'm') {

        int count = 0;
        count = final[j - 1][i] +
          final[j - 1][i - 1] +
          final[j][i - 1] +
          final[j + 1][i - 1] +
          final[j + 1][i] +
          final[j + 1][i + 1] +
          final[j][i + 1] +
          final[j - 1][i + 1];

        if ((count < 2 || count > 3) && (final[j][i] == 1))
          temp[j][i] = 0;

        if (count == 2)
          temp[j][i] = final[j][i];

        if (count == 3)
          temp[j][i] = 1;
      } else if (choice == 'v') {
        //The Von Neumann neighborhood checks only the 4 surrounding cells in the array,
        //(N, S, E, and W).
        int count = 0;
        count = final[j - 1][i] +
          final[j][i - 1] +
          final[j + 1][i] +
          final[j][i + 1];

        if (count < 2 || count > 3)
          temp[j][i] = 0;

        if (count == 2)
          temp[j][i] = final[j][i];

        if (count == 3)
          temp[j][i] = 1;
      }
    }
  }

  copy(temp, final);
}
void gol::display() {

  if (c2 == 'y') {

    for (int j = 1; j < maxrows; j++) {
      for (int i = 1; i < maxcols; i++) {
        if (final[j][i] == 1) {
          if (backup[j][i] == 1) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

            cout << char(254);

          } else {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            cout << char(254);
          }
        } else
          cout << ' ';
      }
      cout << endl;
    }
  }

  if (c2 == 'n') {
    for (int j = 1; j < maxrows; j++) {
      for (int i = 1; i < maxcols; i++) {
        if (final[j][i] == 1) {
          cout << char(254);
        } else {
          cout << ' ';
        }
      }
      cout << "\n";
    }

  }
}

int main() {

  HANDLE hOut;
  CONSOLE_CURSOR_INFO ConCurInf;

  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  ConCurInf.dwSize = 10;
  ConCurInf.bVisible = FALSE;

  SetConsoleCursorInfo(hOut, & ConCurInf);

  Sleep(100);
  char neighborhood;
  char again;
  char cont;
  bool comparison;

  string decoration;
  for (int i = 10; i < 120; i++) {
    gotoxy(i, 15);
    Sleep(10);
    cout << char(254);
  }
  for (int i = 120; i >= 10; i--) {
    gotoxy(i, 22);
    Sleep(10);
    cout << char(254);
  }
  for (int j = 16; j <= 21; j++) {
    gotoxy(10, j);
    Sleep(10);
    cout << char(254);
  }
  for (int j = 21; j >= 16; j--) {
    gotoxy(120, j);
    Sleep(10);
    cout << char(254);
  }
  gotoxy(50, 17);
  cout << "GAME OF LIFE";
  gotoxy(12, 19);
  cout << "BY :-  PARAS\n";
  cout << "\n";
  cout << "\t\tPRESS A KEY TO BEGIN";
  getchar();
  system("cls");

  cout << endl << "This program is a C++ implementation of John Conway's Game of Life." <<
    endl << "With it, you can simulate how \"cells\" interact with each other." << endl <<
    endl << "There are two types of neighborhoods you can choose, the" <<
    endl << "Moore, and the Von Neumann.  The Moore neighborhood checks" <<
    endl << "all 8 surrounding cells, whereas the Von Neumann checks" <<
    endl << "only the 4 cardinal directions: (N, S, E, and W)." << endl << endl <<
    endl << "The rules of the \"Game of Life\" are as follows:" << endl <<
    endl << "1. Any live cell with fewer than two live neighbors dies, as if caused by under-population." <<
    endl << "2. Any live cell with two or three live neighbors lives on to the next generation." <<
    endl << "3. Any live cell with more than three live neighbors dies, as if by overcrowding." <<
    endl << "4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction." << endl <<
    endl << "The initial configuration (Generation 0) of the board is determined by the user" <<
    endl << "Every 125th Generations you will get the option to end or continue the simulation." <<
    endl << "If a system becomes \"stable\" (meaning the system does not change from one" <<
    endl << "generation to the next), the simulation will end automatically." << endl << "A Cell born is represented by red and  cell which remained alive is represented by green" << endl;
  gol g1;

  do {

    do {

      cout << "Which neighborhood would you like to use (m or v): ";
      cin >> neighborhood;
    } while (neighborhood != 'm' && neighborhood != 'v');

    system("cls");
    int i = 0;

    do {

      cout << "Generation " << i << endl;
      if (i == 0) {
        g1.init();
      }

      HANDLE hOut;
      CONSOLE_CURSOR_INFO ConCurInf;

      hOut = GetStdHandle(STD_OUTPUT_HANDLE);

      ConCurInf.dwSize = 10;
      ConCurInf.bVisible = FALSE;

      SetConsoleCursorInfo(hOut, & ConCurInf);

      g1.display();
      if (i == 0) {
        fflush(stdin);
        cout << "Press any key to Start Simulation";
        getchar();
      }

      g1.cpy();
      g1.generation(neighborhood);

      i++;
      if (i < 90) {
        Sleep(10);
      } else {
        Sleep(100);
      }

      if (i % 125 == 1 && i != 1) {
        cout << endl;

        do {
          cout << "Would you like to continue this simulation? (y/n): ";
          cin >> cont;
        } while (cont != 'y' && cont != 'n');
        if (cont == 'n')
          break;
      }
      comparison = g1.compare();
      if (comparison == false)
        system("cls");
      if (comparison == true)
        cout << endl;
    } while (comparison == false);

    do {
      cout << "Would you like to run another simulation? (y/n): ";
      cin >> again;
    } while (again != 'y' && again != 'n');
  } while (again == 'y');
  return 0;
}
