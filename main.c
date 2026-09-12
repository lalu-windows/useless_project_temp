#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
int main(void){

	//screen size

	const int WIDTH = 800;
	const int HEIGHT = 600;


	//cordinate system
	const int cols = 200;
	const int rows = 110;
	const int cell_size = 8;

	int grid[cols][rows];
	for(int i =0 ; i<cols; i++){
		for(int j =0 ;j <rows; j++){
			grid[i][j]=0;
		}
	}


	InitWindow(WIDTH, HEIGHT, " \"sand\" simulator?");
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		//mouse click capture

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			//getting mouse cordinates
			int screenX = GetMouseX();
			int screenY = GetMouseY();

			int cellX = screenX / cell_size;
			int cellY = screenY / cell_size;
			/* old once cell at a time implementation
			//put sand at clicked mousecordinates
			if(cellX >= 0 && cellX<=cols && cellY>=0 && cellY<=rows){
			grid[cellX][cellY]=1;

			};
			*/

			//for brush implementation:
			int brush_size = 10;
			if(cellX >= 0 && cellX<=cols && cellY>=0 && cellY<=rows){
				for(int i = -(brush_size/2); i<=(brush_size/2);i++){
					for(int j =-(brush_size/2);j<=(brush_size/2);j++){
						if(rand() % 100 > 50){
							grid[cellX+i][cellY+j]=1;
						}
					}
				}
			}

		}
		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
			//getting mouse cordinates
			int screenX = GetMouseX();
			int screenY = GetMouseY();

			int cellX = screenX / cell_size;
			int cellY = screenY / cell_size;
			//old once cell at a time implementation
			//put sand at clicked mousecordinates
			int brush_size = 5;
			if(cellX >= 0 && cellX<=cols && cellY>=0 && cellY<=rows){
				for(int i = -(brush_size/2); i<=(brush_size/2);i++){
					for(int j =-(brush_size/2);j<=(brush_size/2);j++){
						grid[cellX+i][cellY+j]=2;
					}
				}

			}
		}
		if(IsKeyDown(KEY_LEFT_CONTROL)){

			//getting mouse cordinates
			int screenX = GetMouseX();
			int screenY = GetMouseY();

			int cellX = screenX / cell_size;
			int cellY = screenY / cell_size;
			//old once cell at a time implementation
			//put sand at clicked mousecordinates
			int brush_size = 5;
			if(cellX >= 0 && cellX<=cols && cellY>=0 && cellY<=rows){
				for(int i = -(brush_size/2); i<=(brush_size/2);i++){
					for(int j =-(brush_size/2);j<=(brush_size/2);j++){
						grid[cellX+i][cellY+j]=3;
					}
				}

			}
		};




		//physics engine:





		//three rules just three ! THREEEEEE!
		//if you encounter a sand block at (x,y), (which is (x,y) = 1 then:
		//1.if no sand below((x,y+1)=0), then (x,y)=0 and (x,y+1)=1.
		//2.if a sand below((x,y+1)=1), then we have to move diagonally either left((x-1,y+1)) or right((x+1,y+1)) to look realistic we will randomise this..the diagonal blocks will be subject to sand checks in the next iteration, always remember game is running at millions of checks per second.
		//3. there were only 2 rules




		for(int y = rows-2;y>=0;y--){
			for(int x = 0;x<=cols;x++){
				if(grid[x][y]==1){
					//ooh a dollah!
					if(grid[x][y+1]==0){
						grid[x][y]=0;
						grid[x][y+1]=1;
					}
					else if(grid[x][y+1]==1){
						//variable of randomness: r
						int r;
						if(rand()%2==0)
							r=1;
						else
							r=-1;

						if(grid[x+r][y+1]==0){
							grid[x][y]=0;grid[x+r][y+1]=1;}
						else if (grid[x-r][y+1]==0){
							grid[x][y]=0;grid[x-r][y+1]=1;
						}
					}
				}
			
				//water physics
				if(grid[x][y]==3){
					//ooh a dollah!
					if(grid[x][y+1]==0){
						grid[x][y]=0;
						grid[x][y+1]=3;
					}
					else{
						//variable of randomness: r
						int r;
						if(rand()%2==0)
							r=1;
						else
							r=-1;

						if(grid[x+r][y+1]==0){
							grid[x][y]=0;grid[x+r][y+1]=3;}
						else if (grid[x-r][y+1]==0){
							grid[x][y]=0;grid[x-r][y+1]=3;
						}
						else if(grid[x+r][y]==0){
							grid[x][y]=0;grid[x+r][y]=3;
						}
						else if(grid[x-r][y]==0){
							grid[x][y]=0;grid[x-r][y]=3;
						};
					
					}

				};
			}
		}



			BeginDrawing();
			ClearBackground(RAYWHITE);



			for(int i =0 ; i <cols; i++){
				for(int j =0; j<rows; j++){


					if(grid[i][j] == 1){
						DrawRectangle(i*cell_size,j*cell_size,cell_size,cell_size,(Color){192, 196, 65,255});
					}
					else if(grid[i][j] == 2){
						DrawRectangle(i*cell_size,j*cell_size,cell_size,cell_size,(Color){94, 102, 87,255});
					}
					else if(grid[i][j] == 3){
						DrawRectangle(i*cell_size,j*cell_size,cell_size,cell_size,(Color){3, 82, 252,255});
						
					}
					DrawRectangleLines(
							i*cell_size,
							j*cell_size,
							cell_size,
							cell_size,
							(Color){40,40,40,100});

				}
			}


			EndDrawing();


		}
		CloseWindow();
		return 0;
	}
