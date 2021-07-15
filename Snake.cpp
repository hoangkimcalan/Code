
#include <iostream>
#include "mylib.cpp"
#define MAX 500
using namespace std;

    int length_snake = 10;  // biến toàn cục cho con rắn

    // khai báo nguyên mẫu hàm
    void draw_wall_up();
    void draw_wall_down();
    void draw_wall_left();
    void draw_wall_right();
    void draw_wall();
    void initialization_snake(int pointx[], int pointy[]);
    void draw_snake(int pointx[], int pointy[]);
    void del_data_of_snake(int pointx[], int pointy[]);
    void handling_snake(int pointx[], int pointy[], int a, int b, int &x_fr, int &y_fr);
    void add_snake(int arr[], int a);
    void del_snake(int arr[], int b);
    bool check_snake_wall(int x, int y);
    bool check_snake_eat_itself(int pointx[], int pointy[]);
    bool check_total_snake(int pointx[], int pointy[]);
    void creadit_fruit (int &x_fr, int &y_fr, int pointx[], int pointy[]);
    bool snake_hide_fruit(int x_fr, int y_fr, int pointx[], int pointy[]);
    bool check_snake_eat_fruit(int x_fr, int y_fr, int x0,int y0);


int main(){
    srand(time(NULL));
    int x_fr = 0, y_fr = 0;
    int pointx[MAX], pointy[MAX];
    creadit_fruit (x_fr, y_fr, pointx, pointy);
    bool game_over_snake = false;
    
    draw_wall();
    initialization_snake( pointx, pointy);
    draw_snake(pointx, pointy);

    int x =30, y = 15;  // vị trí ban đầu của con rắn
    int check = 3;
    while(game_over_snake == false){
        
        // xóa dữ liệu cũ của con rắn
        del_data_of_snake(pointx, pointy);
        
        // điều khiển con rắn WASD
        if(kbhit()){
                char input = getch();           // Lấy dữ liệu trong bộ nhớ đệm
                if(input == 'w' && check != 0){                check = 1;
                }else{
                    if(input == 's'&& check != 1){             check = 0;
                    }else{
                        if(input == 'a' && check != 3){        check = 2;
                        }else{
                            if(input == 'd' && check != 2){    check = 3;
                        }
                    }
                }
            }    
        }

        // 0 chạm vào biên trên -> đi xuống
        // 1 chạm vào biên dưới -> đi lên
        // 2 chạm vào biên phải -> đi trái
        // 3 chạm vào biên trái -> đi phải
         if(check == 0)                  y++;
            else{
                if(check == 1)           y--;
                else{
                    if(check == 2)       x--;
                    else{
                        if(check == 3)   x++;
                    }
                }
            }
        
        handling_snake(pointx, pointy, x, y, x_fr, y_fr);
        //check sanke
        game_over_snake = check_total_snake(pointx, pointy);

        Sleep(150);
    }



    draw_snake(pointx, pointy);
    getch();
    return 0;
}


// vẽ tường trên
void draw_wall_up(){
        int x = 10, y = 1;
        while(x <=60 ){
            gotoxy(x, y);
            cout << "+";
            x++;
    }
}

// vẽ tường dưới
void draw_wall_down(){
        int x = 10, y = 30;
        while(x <= 60){ 
            gotoxy(x, y);
            cout << "+";
            x++;
    }
}

// vẽ tường phải
void draw_wall_right(){
        int x = 60, y = 1;
        while(y <= 30){
            gotoxy(x, y);
            cout << "+";
            y++;
    }
}

// vẽ tường trái
void draw_wall_left(){
        int x = 10, y = 1;
        while(y <= 30){
            gotoxy(x, y);
            cout << "+";
            y++;
    }
}

// kết hợp 
void draw_wall(){
    draw_wall_up();
    draw_wall_down();
    draw_wall_left();
    draw_wall_right();
}



// khởi tạo con rắn 
void initialization_snake(int pointx[], int pointy[]){
    int x = 30, y = 15;
    for(int i = 0; i < length_snake; i++){
        pointx[i] = x;
        pointy[i] = y;
        x--;
    }
}

// vẽ con rắn
void draw_snake(int pointx[], int pointy[]){
    for(int i = 0; i < length_snake; i++){
        gotoxy(pointx[i],pointy[i]);
            if(i == 0){
                cout << "0";
            }
            else{
                cout << "o";
            }
        }
    }

// xóa dữ liệu cũ của con rắn
void del_data_of_snake(int pointx[], int pointy[]){
    for(int i = 0; i < length_snake; i++){
        gotoxy(pointx[i], pointy[i]);
        cout << "     ";
    }
}




// xử lý con rắn
void handling_snake(int pointx[], int pointy[], int a, int b, int &x_fr, int &y_fr){

    // add first of snake
    add_snake(pointx, a);
    add_snake(pointy, b);

    // del end of snake

    if(check_snake_eat_fruit(x_fr, y_fr, pointx[0], pointy[0]) == false){
        del_snake(pointx, length_snake - 1);
        del_snake(pointy, length_snake - 1);
    }else{
        creadit_fruit(x_fr, y_fr, pointx, pointy);
    }

    // draw snake
    draw_snake(pointx, pointy);
}   

    // thêm tọa độ mới vào mảng
    void add_snake(int arr[], int a){
        for(int i = length_snake; i > 0; i--){
            arr[i] = arr[i-1];
        }
        arr[0] = a;   
        length_snake++;
    }

    // xóa đuôi của con rắn
    void del_snake(int arr[], int b){
        for(int i = b; i < length_snake; i++){
            arr[i] = arr[i+1];
        }
        length_snake--;
    }

bool check_snake_wall(int x0, int y0){

        // wall up
        if (y0 == 2 && (x0 > 10 && x0 < 60))
	{
		return true;
	}
        // wall down
	else if (y0 == 29 && (x0 > 10 && x0 < 60))
	{
		return true;//gameover
	}
	//ran cham tuong phai
	else if (x0 == 11 && (y0 > 1 && y0 < 30))
	{
		return true;//gameover
	}
	//ran cham tuong trai
	else if (x0 == 59 && (y0 > 1 && y0 < 30))
	{
		return true;//gameover
	}
	return false;
    }

    bool check_snake_eat_itself(int pointx[], int pointy[]){
        for (int i = 1;i < length_snake;i++)
	{
		if ((pointx[0] == pointx[i]) && (pointy[0] == pointy[i]))
		{
			return true;
		}
	}
	return false;
    }   


    bool check_total_snake(int pointx[], int pointy[]){
            bool check1 = check_snake_eat_itself(pointx, pointy);
            bool check2 = check_snake_wall(pointx[0], pointy[0]);
            if(check1 == true || check2 == true){
                    return true;
        }
        return false;
    }

void creadit_fruit (int &x_fr, int &y_fr, int pointx[], int pointy[]){
    do{
    // 11 <= x <= 59
    x_fr = rand() % (59 - 11 + 1) + 11;
    // 2 <= y <= 29
    y_fr = rand() % (29 - 2 + 1) + 2;
    }while(snake_hide_fruit(x_fr, y_fr,pointx, pointy) == true);
    int i = rand() % (15 - 1 + 1) + 1;
	SetColor(i);
    gotoxy(x_fr, y_fr);
        cout << "@";
}

bool snake_hide_fruit(int x_fr, int y_fr, int pointx[], int pointy[]){
    for (int i = 0;i < length_snake;i++)
	{
		if ((x_fr == pointx[i]) && (y_fr == pointy[i]))
		{
			return true;
		}
	}
	return false;
}

bool check_snake_eat_fruit(int x_fr, int y_fr, int x0,int y0)
{
	if ((x0 == x_fr) && (y0 == y_fr))
	{
		return true;
	}
	return false;
}

 
