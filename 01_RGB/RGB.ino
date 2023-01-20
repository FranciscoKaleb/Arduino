int r = 3;
int g = 5;
int b = 6;

void setup() {
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);

}

void loop() {
 pattern_1();
 pattern_2();
}

void pattern_1(){
  green_up();
  red_down();
  blue_up();
  green_down();
  red_up();
  blue_down();
}
void pattern_2(){
  green_up();
  blue_up();
  green_down();
  green_up();
  blue_down();
  blue_up();
  red_down();
  red_up();
  green_down();
  blue_down();
  red_down();
  red_up();
}
int x = 255;
int y = 0;
int z = 0;
void rgb(int x,int y,int z){
  analogWrite(r,x);
  analogWrite(g,y);
  analogWrite(b,z);  
}

void red_up(){
 for(x = 0;x < 255;x++ ){
   rgb(x,y,z);
   delay(10);
 }
}
void red_down(){
  for(x;x > 0;x-- ){
   rgb(x,y,z);
   delay(10);
 }
}
void green_up(){
  for(y;y < 255;y++ ){
   rgb(x,y,z);
   delay(10);
 }
}
void green_down(){
  for(y;y > 0;y-- ){
   rgb(x,y,z);
   delay(10);
 }
}
void blue_up(){
  for(z;z < 255;z++ ){
   rgb(x,y,z);
   delay(10);
 }
}
void blue_down(){
  for(z;z > 0;z-- ){
   rgb(x,y,z);
   delay(10);
 }
}

  
