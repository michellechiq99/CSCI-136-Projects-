/* Author:Michelle Chiquitero
Course CSCI-135
Instructor: Professor Gennady
Project 3
*/
#include <cstdlib>
#include <iostream>
#include "bot.h"
#include<cmath>
using namespace std;

int ydamg=0; //y variable of damaged robot
int xdamg=0; // x variable of damaged robot
int damagedr = -1; // keeps track of the the damaged robot
int fix=-1; // id of robot that will fix
bool check2=true;// makes sure the robot starts at col 0 and row 0
bool check3=true; // makes sure the robot starts at col 0 and row/2
bool rightpath=true; // 
bool rightpath1=true;//
bool rightpath2=true;//makes sure the robot starts at half way point of col and halfway point of row
bool rightpath3=true; // make sure the robot starts halfway point of col 
static int state = 0; // makes sure robot id of 1 is going through the right directions
static int state2 = 0;// makes sure robot id of 0 is going through the right directions
static int state5=0; // keeps track of id=1 state
static int state6=0;// keeps track of id=2 state
static int state7=0;//keeps track of id=3 state
static int state8=0;//keeps track of id=4 state
Action differentsides(int id, Loc loc, Area &area, ostream &log);



const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
	log << "Start!" << endl;
}
Action differentsides(int id, Loc loc, Area &area, ostream &log){
int row = loc.r;
int col= loc.c; // current row and column
		if(area.inspect(row,col)==DEBRIS){
			return COLLECT;
		}
		if(id==0 && col ==0 && row ==0)
			rightpath=false;
		if(id==1 && col==0 && row==ROWS/2)
			rightpath1=false;
		if(id==2 && col==COLS/2 && row==ROWS/2)
			rightpath2=false;
		if(id==3 && col==COLS/2 && row==0)
			rightpath3=false;
		if(rightpath==true){
			if (id==0 && row!=0){ //if it's not at row=0 
				return UP;
			}
			if (id==0 && col!=0){
				return LEFT;
			}
		}
		if(rightpath1==true){
			if(id==1 && col!=0){
				return LEFT;
			}
			if(id==1 && row<=ROWS/2){
				return DOWN;
			}
			if(id==1 && row>ROWS/2){
				return UP;
			}
		}
		if(rightpath2==true){
			if(id==2 && col>COLS/2){
				return LEFT;
			}

			if(id==2 && row<ROWS/2){
				return DOWN;
			}

			if(id==2 && col<COLS/2){
				return RIGHT;
			}
			if(id==2 && row>=ROWS/2){
				return UP;
			}

		}
		if(rightpath3==true){
			
			if(id==3 && col<COLS/2){
				return RIGHT;
			}
			if(id==3 && col>COLS/2){
				return LEFT;
			}
			else if(id==3 && row!=0){
				return UP;
			}
		}
		if(id==0 && col< COLS/2 && state5== 0 && row< ROWS/2)
			return RIGHT;
		else if (id ==0 && col== COLS/2 && state5==0 && row< ROWS/2){
			state5=1;
			return DOWN;
		}
		else if(id==0 && col>0 && state5== 1 && row< ROWS/2)
			return LEFT;
		else if (id ==0 && col== 0 && state5==1 && row< ROWS/2){
			state5=0;
			return DOWN;
		}
		if(id==1 && col< COLS/2 && state6== 0 && row>= ROWS/2)
			return RIGHT;
		else if (id ==1 && col== COLS/2 && state6==0 && row>= ROWS/2){
			state6=1;
			return DOWN;
		}
		else if(id==1 && col>0 && state6== 1 && row>= ROWS/2)
			return LEFT;
		else if (id ==1 && col== 0 && state6==1 && row>= ROWS/2){
			state6=0;
			return DOWN;
		}
		if(id==2 && col< COLS-1 && state7== 0 && row>= ROWS/2)
			return RIGHT;
		else if (id ==2 && col== COLS-1 && state7==0 && row> ROWS/2){
			state7=1;
			return DOWN;
		}
		else if (id ==2 && col== COLS/2 && state7==1 && row>= ROWS/2){
			return DOWN;
		}
		else if(id==2 && col>0 && state7== 1 && row> ROWS/2)
			state7=0;
			return LEFT;
		if(id==3 && col< COLS-1 && state8== 0 && row<= ROWS/2)
			return RIGHT;
		else if (id ==3 && col== COLS-1 && state8==0 && row< ROWS/2){
			state8=1;
			return DOWN;
		}
		else if (id ==3 && col== COLS/2 && state8==1 && row<= ROWS/2){
			return DOWN;
		}
		else if(id==3 && col>0 && state8==1 && row< ROWS/2)
			state8=0;
			return LEFT;

		if (area.inspect(row, col) == DEBRIS){
		 		return COLLECT;
		}
		else if (area.inspect(row+1, col) == DEBRIS){
		 		return DOWN;
		}
		else if (area.inspect(row-1, col) == DEBRIS){
		 		return UP;
		}
		else if (area.inspect(row, col+1) == DEBRIS){
				return RIGHT;
	    }
	    else if (area.inspect(row, col-1) == DEBRIS){
				return LEFT;
		}
		else{
		for (int j = 0; j < 500; j++) {
			for (int i = 0; i < 500; i++) {
			if (area.inspect(row, col) == DEBRIS) {
				return COLLECT;

			}
			else if (area.inspect(row - i, col + j) == DEBRIS) { //based on debris if the col is one higher move to the right
				return RIGHT;

			}
			else if (area.inspect(row + i, col + j) == DEBRIS) { //if the debris is located one col to the right and one row up move to the right 
				return RIGHT;

			}
			else if (area.inspect(row - i, col - j) == DEBRIS) {
				return LEFT;

			}
			else if (area.inspect(row + i, col - j) == DEBRIS) {
				return LEFT;

			}
		}
	}
		for (int i = 0; i < 500; i++) {
			if (area.inspect(row, col) == DEBRIS) {
				return COLLECT;

			}
			else if (area.inspect(row - i, col - i) == DEBRIS) {
				return LEFT;

			}
			else if (area.inspect(row + i, col - i) == DEBRIS) {
				return LEFT;

			}

			else if (area.inspect(row - i, col + i) == DEBRIS) {
				return RIGHT;

			}

			else if (area.inspect(row + i, col + i) == DEBRIS) {//Check diag upper right
				return RIGHT;

			}
		}
	}
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
	if (area.inspect(row, col) == DEBRIS){
		return COLLECT;
	}
	if(damagedr==-1){
			if(NUM==4){
				return differentsides(id, loc, area, log); //split int 4 sides
			}
	for (int i = 0; i < 500; i++) {
		if (area.inspect(row, col) == DEBRIS) {
			return COLLECT;

		}
		else if (area.inspect(row, col + i) == DEBRIS) {
			return RIGHT;

		}
		else if (area.inspect(row, col - i) == DEBRIS) {
			return LEFT;

		}
		else if (area.inspect(row - i, col) == DEBRIS) {
			return UP;

		}
		else if (area.inspect(row + i, col) == DEBRIS) {
			return DOWN;

		}
	}
	for (int j = 0; j < 500; j++) {
		for (int i = 0; i < 500; i++) {
			if (area.inspect(row, col) == DEBRIS) {
				return COLLECT;

			}
			else if (area.inspect(row - i, col - j) == DEBRIS) {
				return LEFT;

			}
			else if (area.inspect(row + i, col - j) == DEBRIS) {
				return LEFT;

			}
			else if (area.inspect(row - i, col + j) == DEBRIS) {
				return RIGHT;

			}
			else if (area.inspect(row + i, col + j) == DEBRIS) {
				return RIGHT;
			}
		}
	}
		for (int i = 0; i < 500; i++) {
			if (area.inspect(row, col) == DEBRIS) {
				return COLLECT;

			}
			else if (area.inspect(row - i, col - i) == DEBRIS) { //finds debri location if its less than row and col option 
				return LEFT;

			}
			else if (area.inspect(row + i, col - i) == DEBRIS) { // if the row is one higher but still to the left
				return LEFT;

			}

			else if (area.inspect(row - i, col + i) == DEBRIS) { // if col is to the right
				return RIGHT;

			}

			else if (area.inspect(row + i, col + i) == DEBRIS) {
				return RIGHT;

			}
		}
			if (area.inspect(row,col)==DEBRIS){
				return COLLECT;
			}
			if(id==0 && row==0 && col==0)
				check2=false;

			if(id==1 && row==ROWS/2 && col == 0)
				check3=false;
			if(check2==true){
				if(id==0 && row!=0){
					return UP;
				}
				if(id == 0 && col != 0){
					return LEFT;
				}
			}
			if (check3==true){
				if(id==1 && row <= ROWS/2 ){
					return DOWN;
				}
				if(id==1 && col != 0){
					return LEFT;
				}
				else if(id==1 && row>=ROWS/2){
					return UP;
				}
			}
			if(id==0 && col<COLS-1 && state2==0 && row>ROWS/2)
				return RIGHT;
			else if(id==0 && col==COLS-1 && state2==0 && row<ROWS/2){
				state2=1;
				return DOWN;
			}
			else if(id==0 && col>0 && state2==1 && row<ROWS/2)
				return LEFT;
			else if(id==0 && col==0 && state2==1 && row<ROWS/2){
				state2=0;
				return DOWN;
			}
			if(id==1 && col<COLS/2 && state==0 &&  row>=ROWS/2)
				return RIGHT;
			else if(id==1 && col==COLS/2 && state==0 && row>=ROWS/2){
				state=1;
				return DOWN;
			}
			else if(id==1 && col>0 && state==1 && row>=ROWS/2)
				return LEFT;
			else if(id==1 && col==0 && state==1 && row>=ROWS/2){
				state=0;
				return DOWN;
			}
		}
	else {
		if(damagedr==(NUM-1)) //if the id is the robot before the robot ahead
			fix=NUM-2; //
		else if(damagedr<(NUM-1)) //if the id of the robot is less than the robot before it
			fix=damagedr+1; 
		if(row+1==xdamg && col==ydamg){
			return REPAIR_DOWN;
		}
		else if(row-1==xdamg && col==ydamg){
			return REPAIR_UP;
		}
		else if(row==xdamg && col+1==ydamg){
			return REPAIR_RIGHT;
		}
 		else if(row==xdamg && col-1==ydamg){
 			return REPAIR_LEFT;
 		}
		else if(row>xdamg){ //if the row is greater than the row of the damaged rob move up to repair
			return UP;
 		}
 		else if(row<xdamg){ // if the row is less than the row of damaged rob move down 
			return DOWN;
		}
		else if(col>ydamg){
 			return LEFT;
		}
 		else if(col<ydamg){
 			return RIGHT;
		}
	}
	damagedr=-1; // resets damaged robot to not damaged 
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
		damagedr=id; //sets variable to id of robot
		xdamg=loc.r; //xvalue of damaged robot
		ydamg=loc.c; // y value of damaged robot
		log << "Robot " << id << " is damaged." << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
