int sensor0 = A4;
int sensor1 = A3;
int sensor2 = A2;
int sensor3 = A1;
int sensor4 = A0;
int mata0; 
int mata1; 
int mata2; 
int mata3; 
int mata4;

int motorR = 4; 
int onR = 5; 
int onL = 6; 
int motorL = 7; 

int data;
unsigned char s[5]; 

int pathlength; 
int readpath; 
char path[99]; 

int threshold = 990; 

int BLUEled = 13;
int GREENled = 12;
int YELLOWled = 11;

void strongright()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 105);
  digitalWrite(motorR, LOW);
}

void midright2()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 105);
  digitalWrite(motorR, HIGH);
}

void midright()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 125);
  digitalWrite(motorR, HIGH);
}

void softright()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 225);
  digitalWrite(motorR, HIGH);
}

void moveforward()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 255); 
  digitalWrite(motorR, HIGH);
}

void softleft()
{
  analogWrite(onL, 225);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 255);
  digitalWrite(motorR, HIGH);
}

void midleft()
{
  analogWrite(onL, 125);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 255);
  digitalWrite(motorR, HIGH);
}

void midleft2()
{
  analogWrite(onL, 105);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 255);
  digitalWrite(motorR, HIGH);
}

void strongleft()
{
  analogWrite(onL, 105);
  digitalWrite(motorL, LOW);
  analogWrite(onR, 255);
  digitalWrite(motorR, HIGH);
}

void turnright()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, HIGH);
  analogWrite(onR, 255);
  digitalWrite(motorR, LOW);
}

void turnleft()
{
  analogWrite(onL, 255);
  digitalWrite(motorL, LOW);
  analogWrite(onR, 255);
  digitalWrite(motorR, HIGH);
}

void righttillstraight()
{
  turnright();
  delay(500); 
  readsensor();
  while (s[2]==0)
  {
    turnright();readsensor();
  }
}

void lefttillstraight()
{
  turnleft();
  delay(500); 
  readsensor();
  while (s[2]==0)
  {
    turnleft();readsensor();
  }
}

void turnaround()
{
  lefttillstraight();
}

void stop()
{  
  analogWrite(onL, 0);
  digitalWrite(motorL, LOW);
  analogWrite(onR, 0);
  digitalWrite(motorR, LOW);
}

void lilmoveforward()
{
  moveforward();
  delay(150); 
  readsensor();
}

void ONforBLUEled()
{
  digitalWrite (BLUEled, HIGH); delay(25);
  digitalWrite (BLUEled, LOW);
}

void ONforGREENled()
{
  digitalWrite (GREENled, HIGH); delay(25);
  digitalWrite (GREENled, LOW);
}

void ONforYELLOWled()
{
  digitalWrite (YELLOWled, HIGH); delay(25);
  digitalWrite (YELLOWled, LOW);
}

void readsensor()
{
 
  mata0 = analogRead(sensor0);
  mata1 = analogRead(sensor1); 
  mata2 = analogRead(sensor2); 
  mata3 = analogRead(sensor3); 
  mata4 = analogRead(sensor4); 

if (mata0 < threshold)
  {s[0] = 1;}
else
  {s[0] = 0;}

if (mata1 < threshold)
  {s[1] = 1;}
else
  {s[1] = 0;}

if (mata2 < threshold)
  {s[2] = 1;}
else
  {s[2] = 0;}

if (mata3 < threshold)
  {s[3] = 1;}
else
  {s[3] = 0;}

if (mata4 < threshold)
  {s[4] = 1;}
else
  {s[4] = 0;}


data=(s[0]*16)+(s[1]*8)+(s[2]*4)+(s[3]*2)+(s[4]*1);


Serial.print(s[0]);
Serial.print("   ");
Serial.print(s[1]);
Serial.print("   ");
Serial.print(s[2]);
Serial.print("   ");
Serial.print(s[3]);
Serial.print("   ");
Serial.print(s[4]);
Serial.println(" ");
}

void condition()
{
 if (data==0b0000100)
   {moveforward();}
 else if (data==0b0000001)
   {
    strongright();
    readsensor();
    while (s[3]==0)
    {
      strongright();
      readsensor();
    }
   }	
 else if (data==0b0000011)
   {midright2();}  
 else if (data==0b0000010)
   {midright();}
 else if (data==0b0000110)
   {softright();}
 else if (data==0b0001100)
   {softleft();}
 else if (data==0b0001000)
   {midleft();}
 else if (data==0b0011000)
   {midleft2();}
 else if (data==0b0010000)
   {
    strongleft();
    readsensor();
    while (s[1]==0)
    {
     strongleft();
     readsensor();
    }
   }
 else 
   {
      if (data==0b0000000) 
        {
          turnaround();
          path[pathlength]='U';pathlength++;
          ONforYELLOWled();
        }
      else if (data==0b0011111) 
        {
          lilmoveforward();
          if (data==0b0000000)
            {
              lilmoveforward(); 
              righttillstraight();
              path[pathlength]='R';pathlength++;
              ONforGREENled();
            }
          else if (data==0b0011111)
            {
              stop(); 
              path[pathlength]='F';pathlength++;
              
              
              ONforBLUEled();delay(300);
              ONforBLUEled();delay(300);
              ONforYELLOWled();delay(300);
              ONforYELLOWled();delay(300);
              ONforGREENled();delay(300);
              ONforGREENled();delay(300);
              ONforBLUEled();ONforYELLOWled();ONforGREENled();
              
              shortpath(); 
              ONforBLUEled();ONforYELLOWled();ONforGREENled();
              
              
              ONforBLUEled();delay(300);
              ONforYELLOWled();delay(1000);
              ONforGREENled();delay(300);
              ONforGREENled();delay(300);
              ONforGREENled();delay(1000);
              
              shortestpath(); 
            }
          else 
            {
              lilmoveforward(); 
              righttillstraight();
              path[pathlength]='R';pathlength++;
              ONforGREENled();
            }
        }
	
      else if ((data==0b0000111)||(data==0b0001111))
        {
          lilmoveforward();lilmoveforward();
          if (data==0b0000000)
            {
              lilmoveforward();
              righttillstraight();
            }
    else if (s[0]==0)
          	      {
              lilmoveforward();
              righttillstraight();
              path[pathlength]='R';pathlength++;
              ONforGREENled();
            }
        }

      else if ((data==0b0011100)||(data==0b0011110))
        {
          lilmoveforward();lilmoveforward();
          if (data==0b0000000) 
            {
              lilmoveforward();
              lefttillstraight();
            }
        else if (s[4]==0) 
            {
              moveforward();
              path[pathlength]='S';pathlength++
              ONforBLUEled();
            }
         }
    }
}

void shortpath() 
{
  
  int x = (pathlength-2);

  while (x > 0)  
  {
    if (path[x]=='U')
      {
        if (path[x-1]=='L' && path[x+1]=='L')
          {path[x-1]='S';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='L' && path[x+1]=='S')
          {path[x-1]='R';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='R' && path[x+1]=='R')
          {path[x-1]='S';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='R' && path[x+1]=='S')
          {path[x-1]='L';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='S' && path[x+1]=='L')
          {path[x-1]='R';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='S' && path[x+1]=='R')
          {path[x-1]='L';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='L' && path[x+1]=='R')
          {path[x-1]='U';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='R' && path[x+1]=='L')
          {path[x-1]='U';path[x]='O';path[x+1]='O';}
        else if (path[x-1]=='S' && path[x+1]=='S')
          {path[x-1]='U';path[x]='O';path[x+1]='O';}
        
        x--;
      }
    else
    	{x--;}
  }
}

void shortestpath()
{
 readsensor();
 if (data==0b0000100)
   {moveforward();}
 else if (data==0b0000001)
   {
    strongright();
    readsensor();
    while (s[3]==0)
    {
      strongright();
      readsensor();
    }
   }
 else if (data==0b0000011)
   {midright2();}  
 else if (data==0b0000010)
   {midright();}
 else if (data==0b0000110)
   {softright();}
 else if (data==0b0001100)
   {softleft();}
 else if (data==0b0001000)
   {midleft();}
 else if (data==0b0011000)
   {midleft2();}
 else if (data==0b0010000)
   {
    strongleft();
    readsensor();
    while (s[1]==0)
    {
     strongleft();
     readsensor();
    }
   }
 else
     
     if ((data==0b0000111)||(data==0b0001111))
      {
        lilmoveforward();
        if (data==0b0000000)
          {
            lilmoveforward();
            righttillstraight();
          }
        else 
          {
            choosepath();
          }
      }
    
    else if ((data==0b0011100)||(data==0b0011110))
      {
        lilmoveforward();
        if (data==0b0000000) 
          {
            lilmoveforward();
            lefttillstraight();
          }
        else 
          {
            choosepath();
          }
      }
    
    else if  (data==0b0011111)
      {
        choosepath();
      }
  shortestpath();
}  

void choosepath()
{
  if (path[readpath]=='F')
    { 
      stop();finish();
    }
  else if (path[readpath]=='R')
    {
      ONforGREENled();
      righttillstraight();
    }
  else if (path[readpath]=='S')
    {
      ONforGREENled();ONforBLUEled();
      moveforward();delay(200);
    }
  else if (path[readpath]=='L')
    {
      ONforGREENled();ONforYELLOWled();
      lefttillstraight();
    }
  else if (path[readpath]=='O')
    {
      readpath++;choosepath();
    } 
  readpath++;
  shortestpath();
}

void finish()
{
  ONforBLUEled();delay(100);
  ONforYELLOWled();delay(100);
  ONforGREENled();delay(100);
  finish();
}

void setup()
{
  Serial.begin(9600);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(onR, OUTPUT);
  pinMode(onL, OUTPUT);
  pinMode(BLUEled, OUTPUT);
  pinMode(YELLOWled, OUTPUT);
  pinMode(GREENled, OUTPUT);
  analogReference(INTERNAL);
}

void loop()
{
 readsensor();
 condition();
}