#include <iostream>
#include <iomanip>          //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>            //for time() in srand( time(NULL) );
#include <windows.h>        //for Sleep()
#include <fstream> //file i/o stream
using namespace std;

class Mars 
{
 private:
    vector < vector<char> > map;                
    int dimX, dimY; 
    int numOfGold;
    vector < vector<char> > mapSecret; //the map that will be displayed in the game
    int dimSecX,dimSecY;
    
 public:
    Mars(){ 
        init(); 
    }
    void init();
    void display();
    int getDimX()const;
    int getDimY()const;
    int getNumOfGold()const;
    char getObject(int,int); //allocating what character is inside the coordinate
    void setObject( int, int, char); //adding object into map
    bool isEmpty(int,int);//checking if the coordinate is empty
    bool isInsideMap(int,int);
    bool isWall(int,int);
    void addGold();
    bool victory(int);//checking if number of golds collected
    //for the secret map:
    void displaySecret();
    void initSec();
    void setObjectSec(int,int,char); 
};

bool Mars :: victory(int points)
{
    if(points == numOfGold)
        return true;
    else
        return false;
}

bool Mars :: isWall(int x, int y)
{
    if (map[dimY-y][x-1] == '#') 
        return true; 
    else
        return  false;
}

bool Mars :: isInsideMap(int x, int y) 
{
    if((x>0 && x <= dimX) && (y> 0 && y <= dimY))
        return true;
    else
        return false; 
}

bool Mars::isEmpty(int x,int y)
{
    if (map[dimY-y][x-1] == ' ')
        return true; 
    else
        return  false;
}

void Mars::setObject( int x, int y, char ch)
{
    map[dimY-y][x-1] = ch;
}

void Mars::setObjectSec( int x, int y, char ch)
{
    mapSecret[dimSecY-y][x-1] = ch;
}

char Mars::getObject(int x, int y) 
{
    return map[dimY-y][x-1];               
}

int Mars::getDimX()const
{
    return dimX;
}
int Mars::getDimY()const
{
    return dimY;
}

int Mars :: getNumOfGold()const
{
    return numOfGold;
}
void Mars :: addGold()
{
    int x,y;
    for (int j=0; j<numOfGold; ++j)
    {
        x = rand() % dimX+1;   
        y = rand() % dimY+1;
        
        if(getObject(x,y)!= '$') //making sure everything is $
            setObject(x,y,'$');
        else
            j=j-1;
        setObject(x,y,'$');//its always 1 less gold than numOfGold so we added another one 
    }
}

void Mars::init()
{
    system("pause");
    system("cls");
    
    char objects[] = {' ', ' ', '*',' ', 'O', '#', '*',' ',' ','#'};//character available in the game
    int noOfObjects = 10; 
    
    
    cout << "Let's explore Mars..." << endl;
    cout << "Mars dimension X => ";

    while (!(cin >> dimX)) //making sure user inputs only an integer value
            {
                cout << "Error! Please enter a number! => ";
                cin.clear();
                cin.ignore(100, '\n');
            }
    
    cout << "Mars dimension Y => ";
    while (!(cin >> dimY))
            {
                cout << "Error! Please enter a number! => ";
                cin.clear();
                cin.ignore(100, '\n');
            }
    
    cout << "No of Golds => ";
    while (!(cin >> numOfGold))
            {
                cout << "Error! Please enter a number! => ";
                cin.clear();
                cin.ignore(100, '\n');
            }

    dimSecX = dimX;
    dimSecY = dimY;

    map.resize(dimY); //create rows, redefine the structure as dimY dimX
    for (int i=0; i<dimY; ++i){
        map[i].resize(dimX); 
                            
    }
    //DESIGNING THE MAP
    //put random chars into the vector array
    for (int i=0; i<dimY; ++i)
    {
        for (int j=0; j<dimX; ++j)
        {
            int objNo = rand() % noOfObjects;
            map[i][j] = objects[ objNo ];//storing the random objects one by one into the matrix
        }                               
    }
    initSec();
}

void Mars::initSec()
{
    system("cls");
    char secret = '?';
    
    mapSecret.resize(dimSecY); 
    for (int i=0; i<dimSecY; ++i){
        mapSecret[i].resize(dimSecX);
                            
    }
    for (int i=0; i<dimSecY; ++i)
    {
        for (int j=0; j<dimSecX; ++j)
        {
            mapSecret[i][j] = secret;
        }                              
                                        
    }
}

void Mars::display()
{
    system("cls");
    cout << endl;
    for (int i=0; i<dimY; ++i)
    {
        cout << " ";
        for (int j=0; j<dimX; ++j){
            if (j==0)
                cout << " ";
            cout << "+-";
        }
        cout << "+" << endl;
        cout << setw(2) << (dimY-i);
        for (int j=0; j<dimX; ++j){
            cout << "|" << map[i][j];
        }
        cout << "|" << endl;
    }

    cout << " ";
    for (int j=0; j<dimX; ++j){
        if (j==0)
            cout << " ";
        cout << "+-";
    }
    cout << "+" << endl;

    cout << " ";
    for (int j=0; j<dimX; ++j) 
    {
        int digit = (j+1)/10;
        cout << " ";
        if (digit==0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;

    cout << " ";
    for (int j=0; j<dimX; ++j){
        cout << " " << (j+1)%10;
    }
    cout << endl << endl;
}

void Mars::displaySecret()
{
    system("cls");
    cout << "--__--__ Mars Rover Mapper__--__--" << endl;
    for (int i=0; i<dimSecY; ++i)
    {
        cout << " ";
        for (int j=0; j<dimSecX; ++j){
            if (j==0)
                cout << " ";
            cout << "+-";
        }
        cout << "+" << endl;
        cout << setw(2) << (dimSecY-i);
        for (int j=0; j<dimSecX; ++j)
        {
            cout << "|" << mapSecret[i][j];
        }
        cout << "|" << endl;
    }

    cout << " ";
    for (int j=0; j<dimSecX; ++j)
    {
        if (j==0)
            cout << " ";
        cout << "+-";
    }
    cout << "+" << endl;

    cout << " ";
    for (int j=0; j<dimSecX; ++j) 
    {
        int digit = (j+1)/10;
        cout << " ";
        if (digit==0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;

    cout << " ";
    for (int j=0; j<dimSecX; ++j){
        cout << " " << (j+1)%10;
    }
    cout << endl << endl;
}
///////////////////////////////////////////////////////////////////

class Rover 
{
    private:
        int x,y;
        char heading; 
        int points = 0;
        int bullets = 1;
        bool status = false, quitStatus = false;
        bool execute = true;

    public:
    Rover() //rover is using mars
    {
    }
    void land(Mars& mars); 
    int getroverX();
    int getroverY();
    void turnLeft(Mars& mars);
    void move(Mars& mars);
    void shoot(Mars& mars);
    void turnRight(Mars& mars);
    void instruction(Mars& mars);
    void appear(Mars& mars);
    bool failure(Mars &mars);
    bool quitFailure(Mars &mars);
    int getPoint(Mars& mars);
    char temporary(Mars& mars,int,int);
    void Quit(Mars&mars);
    int getBullet();
    bool executable(Mars &mars);
    
};

bool Rover :: executable(Mars &mars)
{
    return execute;
}

int Rover :: getBullet()
{
    return bullets;
}

int Rover :: getroverX()
{
    return x;
}

int Rover :: getroverY()
{
    return y;
}
int Rover:: getPoint(Mars &mars)
{
    return points;
}

bool Rover :: failure(Mars &mars)
{
    return status;
}

bool Rover :: quitFailure(Mars &mars)
{
    return quitStatus;
}

void Rover :: appear(Mars& mars) //DISPLAYING BACK OBJECTS FROM HIDDEN MAP
{
    char object;
    if (heading == '^')
    {
        
        if (mars.isInsideMap(x,y+1) == true) //top middle
        {
            object = mars.getObject(x,y+1);
            mars.setObjectSec(x,y+1,object);
           
        }
        if (mars.isInsideMap(x+1,y+1) == true) //top right
        {
            object = mars.getObject(x+1,y+1);
            mars.setObjectSec(x+1,y+1,object);
           
        }
        if (mars.isInsideMap(x-1,y+1) == true) //top left
        {
            object = mars.getObject(x-1,y+1);
            mars.setObjectSec(x-1,y+1,object);
           
        }
    }

    else if (heading == '>')
    {
        if (mars.isInsideMap(x+1,y) == true) //right middle
        {
            object = mars.getObject(x+1,y);
            mars.setObjectSec(x+1,y,object);
           
        }
        if (mars.isInsideMap(x+1,y+1) == true) //right top
        {
            object = mars.getObject(x+1,y+1);
            mars.setObjectSec(x+1,y+1,object);
           
        }
        if (mars.isInsideMap(x+1,y-1) == true) //right bottom
        {
            object = mars.getObject(x+1,y-1);
            mars.setObjectSec(x+1,y-1,object);
           
        }
    }
    else if (heading == 'v')
    {
        if (mars.isInsideMap(x,y-1) == true) //bottom middle
        {
            object = mars.getObject(x,y-1);
            mars.setObjectSec(x,y-1,object);
           
        }
        if (mars.isInsideMap(x+1,y-1) == true) //bottom right
        {
            object = mars.getObject(x+1,y-1);
            mars.setObjectSec(x+1,y-1,object);
           
        }
        if (mars.isInsideMap(x-1,y-1) == true) //bottom left
        {
            object = mars.getObject(x-1,y-1);
            mars.setObjectSec(x-1,y-1,object);
           
        }
    }

    else if (heading == '<')
    {
        if (mars.isInsideMap(x-1,y) == true) //left middle
        {
            object = mars.getObject(x-1,y);
            mars.setObjectSec(x-1,y,object);
           
        }
        if (mars.isInsideMap(x-1,y+1) == true) //left top
        {
            object = mars.getObject(x-1,y+1);
            mars.setObjectSec(x-1,y+1,object);
           
        }
        if (mars.isInsideMap(x-1,y-1) == true) //left bottom
        {
            object = mars.getObject(x-1,y-1);
            mars.setObjectSec(x-1,y-1,object);
           
        }
    }
}

char Rover :: temporary(Mars& mars,int j ,int k)
{
    char temporary = mars.getObject(j,k);
    return temporary;

}

void Rover :: instruction(Mars& mars) 
{
    cout << "Mission: Get all the golds!!, Do not get trapped!!"<< endl;
    cout << "L = Turn Left, R = Turn Right, M = Move, S = Shoot Wall, Q = Quit "<< endl;
    cout << "# = Hill, * = Trap , $= Gold, O = Bullets" << endl;
    cout << "Rover is at " << getroverX() << ", " << getroverY() << endl;
}

void Rover :: Quit(Mars&mars)
{
    quitStatus = true;
}

void Rover::turnLeft(Mars& mars)
{

    if (heading == '^')
        heading = '<';
    else if (heading == '>')
        heading = '^';
    else if (heading == 'v')
        heading = '>';
    else if (heading == '<')
        heading = 'v';

    mars.setObject(x,y,heading);
    mars.setObjectSec(x,y,heading);
    
}

void Rover:: move(Mars& mars)
{
    char store;
    if (heading == '^')
    {
        
        if (mars.isInsideMap(x,y+1) == true)
        {
            if (mars.isWall(x,y+1) == false)   
            {   
                store = temporary(mars,x,y+1);
                mars.setObject(x,y,' ');
                mars.setObject(x,y+1,heading);
                mars.setObjectSec(x,y,' ');
                mars.setObjectSec(x,y+1,heading);
                y=y+1;
                if(store == '*')
                {
                    status = true;
                }
                else if(store == '$')
                {
                    points = points+1;
                }
                else if(store == 'O')
                {
                    bullets = bullets+1;
                }
                
            }
            else
            {
                execute = false;
            }    
        }
        else
            execute = false;
    }
    else if (heading == '>')
    {
         
        if (mars.isInsideMap(x+1,y) == true)
        {
            if (mars.isWall(x+1,y) == false) 
            {
                store = temporary(mars,x+1,y);  
                mars.setObject(x,y,' ');
                mars.setObject(x+1,y,heading);
                mars.setObjectSec(x,y,' ');
                mars.setObjectSec(x+1,y,heading);
                x=x+1;   
                if(store == '*')
                {
                    status = true;
                }
                else if(store == '$')
                {
                    points = points+1;
                }
                else if(store == 'O')
                {
                    bullets = bullets+1;
                }
            }
            else
            {
                execute = false;
            }
        }
        else
            execute = false;
    
    }
    else if (heading == 'v')
    {
        
        if (mars.isInsideMap(x,y-1) == true)
        {
            if (mars.isWall(x,y-1) == false) 
            {   
                store = temporary(mars,x,y-1); 
                mars.setObject(x,y,' ');
                mars.setObject(x,y-1,heading);
                mars.setObjectSec(x,y,' ');
                mars.setObjectSec(x,y-1,heading);
                y=y-1;
                if(store == '*')
                {
                    status = true;
                }
                else if(store == '$')
                {
                    points = points+1;
                }
                else if(store == 'O')
                {
                    bullets = bullets+1;
                }
            }
            else
            {
                execute = false;
            }
        }
        else
            execute = false;
    }

    
    else if (heading == '<')
    {
        if (mars.isInsideMap(x-1,y) == true)
        {
            if (mars.isWall(x-1,y) == false) 
            {
                store = temporary(mars,x-1,y);
                mars.setObject(x,y,' ');
                mars.setObject(x-1,y,heading); 
                mars.setObjectSec(x,y,' ');
                mars.setObjectSec(x-1,y,heading);
                x=x-1;
                if(store == '*')
                {
                    status = true;
                }    
                else if(store == '$')
                {
                    points = points+1;
                }
                else if(store == 'O')
                {
                    bullets = bullets+1;
                }
            }
            else
            {
                execute = false;
            }
        }
        else
            execute = false;
    }
}

void Rover:: shoot(Mars& mars)
{
    if (bullets>0)
    {
        if (heading == '^')
        {
            
            if (mars.isInsideMap(x,y+1) == true)
            {
                if (mars.isWall(x,y+1) == true)   
                {   
                    mars.setObject(x,y+1,' ');
                    mars.setObjectSec(x,y+1,' ');
                    bullets = bullets-1;
                }
            }
        }
        else if (heading == '>')
        {
            
            if (mars.isInsideMap(x+1,y) == true)
            {
                if (mars.isWall(x+1,y) == true) 
                {
                    mars.setObject(x+1,y,' ');
                    mars.setObjectSec(x+1,y,' ');
                    bullets = bullets-1;
                }
            }
        }

        else if (heading == 'v')
        {
            
            if (mars.isInsideMap(x,y-1) == true)
            {
                if (mars.isWall(x,y-1) == true) 
                {   
                    mars.setObject(x,y-1,' ');
                    mars.setObjectSec(x,y-1,' ');
                    bullets = bullets-1;
                }
            }
        }
    
        else if (heading == '<')
        {
            if (mars.isInsideMap(x-1,y) == true)
            {
                if (mars.isWall(x-1,y) == true) 
                {
                    mars.setObject(x-1,y,' ');
                    mars.setObjectSec(x-1,y,' ');
                    bullets = bullets-1;
                }
            }
        }
    }
    else
        execute = false; 
}

void Rover::turnRight(Mars& mars)
{
    if (heading == '^')
        heading = '>';
    else if (heading == '>')
        heading = 'v';
    else if (heading == 'v')
        heading = '<';
    else if (heading == '<')
        heading = '^';
        
    mars.setObject(x,y,heading);
    mars.setObjectSec(x,y,heading);
}

void Rover::land(Mars& mars)//initialise where your rover should start at the middle of the map
{
    char possibleHeading[] = {'^', '>', '<', 'v'}; 
    int size = 4;

    heading = possibleHeading[rand()% size];

    if (mars.getDimX() % 2 == 0)
    {
        x = mars.getDimX() /2;
        y = mars.getDimY() /2;
    }
    else
    {
        x = (mars.getDimX() + 1)/2;
        y = (mars.getDimY() + 1)/2;
    }

    mars.setObject(x,y,heading);
    mars.setObjectSec(x,y,heading);
   
}
//////////////////////////////////////////////////////////////////////

int createFile()
{
    ofstream marsFile; //data type for output files
    marsFile.open("text.txt"); //1.creates file data.txt 

    if (!marsFile) //file not created
    {
        cout << "error opening file \n";
        return -1;
    }

    marsFile<< "0" << endl; //THIS WILL only be created if file hasnt
                            //been created yet           
    marsFile.close();

    return 0;
}

int readFile(int &highScore)
{
    ifstream ifile;
    ifile.open("text.txt");
    if(!ifile)
    {
        cout << "no file to read" << endl;
        createFile();
        return -1;
    }

    else
    {
        while(ifile >> highScore)
        {
            ifile>>highScore;
        }
    }
    return 0;
}


int appendFile(int &highScore)
{
    fstream file;
    file.open("text.txt");
    if(!file)
    {
        cout << "no file to read" << endl;
        return -1;
    }
    else
    {
        file << highScore << endl;
    }
    return 0;
}


void printMenu(int &finalscore,int &comSequence,int &command,int &point,int &totalGold,string &userCommand,int &bullets,int &highScore)
{
    finalscore = (point * 50) - (comSequence * 5) - (command * 1);
    cout << endl;
    cout << "Total Command Sequence = " << comSequence << " [S]" << endl; 
    cout << "Total Commands = " << command << " [C]" << endl;
    cout << "Total Bullets = " << bullets <<  endl;
    cout << "Total Golds = " << point << " [G] out of " << totalGold << endl;
    cout << "Total Score = [G] X 50 - [S] X 5 - [C] X 1 = " << finalscore << endl;
    cout << "High Score = " << highScore <<  endl;
    cout << endl;
    cout << "Example Sequence: MMLMMMRMMRMRMLLL" << endl;
    cout << "Enter command sequence => ";
    cin >> userCommand;
}


void execute()
{
    vector<char> input;
    string userCommand;
    char ch; // (Yes/No)
    int highScore;
    readFile(highScore);
    
    do
    {
        system("cls");
        Mars mars; 
        Rover curiosity;
        int command=0,comSequence = 0,point,finalscore; 
        int bullets;
        int totalGold = mars.getNumOfGold();
        curiosity.land(mars); 
        mars.addGold();
        
        do
        {
            system("cls");
            mars.display();
            curiosity.appear(mars);
            mars.displaySecret();
            curiosity.instruction(mars);

            point = curiosity.getPoint(mars);
            bullets = curiosity.getBullet();

            printMenu(finalscore,comSequence,command,point,totalGold,userCommand,bullets,highScore);
            
            for (int i=0; i<userCommand.size();i++)
            {
                input.push_back(userCommand[i]);
            }
            system("pause");

            comSequence = comSequence +1;
            command = input.size();
        
            for (auto i = input.begin(); i != input.end(); ++i)
            {
                system("cls");
                
                if (*i == 'L'|| *i == 'l') 
                {  
                    curiosity.turnLeft(mars); 
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    cout << "Command L = [executed] " << endl;
                    system("pause");
                }
                
                else if (*i == 'R'|| *i == 'r')
                {
                    curiosity.turnRight(mars); 
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    cout << "Command R = [executed] " << endl;
                    system("pause");
                }
                
                else if (*i == 'M'|| *i == 'm')
                {
                    curiosity.move(mars); 
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    if (curiosity.executable(mars)==false)
                        cout << "Command M = [failed to execute] " << endl;
                    else
                        cout << "Command M = [executed] " << endl;
                    system("pause");
                }

                else if (*i == 'S'|| *i == 's')
                {
                    curiosity.shoot(mars); 
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    if (curiosity.executable(mars)==false)
                        cout << "Command S = [out of bullet] " << endl;
                    else
                        cout << "Command S = [executed] " << endl;
                    system("pause");
                }
                else if (*i == 'Q'|| *i == 'q')
                {
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    curiosity.Quit(mars);
                }
                else
                {
                    curiosity.appear(mars);
                    mars.display();
                    mars.displaySecret();
                    curiosity.instruction(mars);
                    cout << "Command " << *i << " = [failed to executed] " << endl;
                    system("pause");
                }
            }

            point = curiosity.getPoint(mars);
            input.clear();
            system("cls");

        } while ((mars.victory(point) == false) && (curiosity.failure(mars) == false) && (curiosity.quitFailure(mars)== false));
        

        if(finalscore > highScore){
            highScore = finalscore;
            appendFile(highScore);
        }

        if(curiosity.failure(mars) == false && curiosity.quitFailure(mars) == false)
            cout << " Congratz, Mission ACCOMPLISHED!!" << endl;

        else if (curiosity.failure(mars) == true && curiosity.quitFailure(mars) == false)
            cout << "TRAPPED!! Mission FAILED!!" << endl;

        else if (curiosity.quitFailure(mars) == true)
            cout << "QUITTED!! Mission FAILED!!" << endl;  

        do{

            cout <<" Do you want to see the map of Mars? => ";
            cin >> ch;

        } while(ch != 'y'&& ch != 'Y' && ch!= 'n' && ch!= 'N');

        if(ch == 'y'||ch == 'Y')
            mars.display();

        do{
            cout << "Do you want to explore Mars again? => ";
            cin >> ch;

        } while(ch != 'y'&& ch != 'Y' && ch!= 'n' && ch!= 'N'); //to make sure user only input y/n

    }while((ch == 'y'||ch == 'Y')  && (ch!= 'n' || ch!= 'N'));

    cout << "Good Bye from Mars!" << endl;
} 


int main()
{    
    execute(); 
    return 0;
} 
