#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9

// Sudoku board. Modify this to test your checker!
// 0 == empty cell; 1-9 is the filled in digit.
int board[SIZE][SIZE] = {
  {2, 2, 4, 5, 3, 9, 6, 8, 7},
  {5, 1, 9, 7, 2, 8, 6, 3, 4},
  {8, 3, 9, 6, 1, 4, 2, 9, 5},
  {1, 4, 3, 9, 6, 5, 7, 2, 9},
  {5, 5, 8, 2, 4, 7, 3, 6, 1},
  {7, 6, 2, 3, 9, 7, 4, 5, 8},
  {3, 7, 1, 9, 5, 6, 8, 5, 2},
  {4, 2, 6, 1, 8, 2, 5, 7, 4},
  {2, 8, 2, 4, 7, 3, 9, 1, 6}
};
//correct
// int board[SIZE][SIZE] = {
//   {6, 2, 4, 5, 3, 9, 1, 8, 7},
//   {5, 1, 9, 7, 2, 8, 6, 3, 4},
//   {8, 3, 7, 6, 1, 4, 2, 9, 5},
//   {1, 4, 3, 8, 6, 5, 7, 2, 9},
//   {9, 5, 8, 2, 4, 7, 3, 6, 1},
//   {7, 6, 2, 3, 9, 1, 4, 5, 8},
//   {3, 7, 1, 9, 5, 6, 8, 4, 2},
//   {4, 9, 6, 1, 8, 2, 5, 7, 3},
//   {2, 8, 5, 4, 7, 3, 9, 1, 6}
// };

// array of bools
bool check_row[SIZE], check_col[SIZE], check_box[SIZE]; // one for each box

typedef struct {
  int row, col, box;
} check_data;
int i,j;

//Pring board fucntion
void printBoard(int board[SIZE][SIZE]) {
  for(i = 0; i < SIZE; i++) {
    for(j = 0; j < SIZE; j++) {
      printf("%5d", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Checks the given row for duplicate numbers, and updates the check_row
// value for that row appropriately. If no number is repeated in that row,
// check_row[row] will be set to true; otherwise, it will be false.
void* checkRow(void* args) {
  check_data * data = (check_data *) args;
  int row = data->row;
  int col = data->col;
  int  sum = 0;
  for (int i = row; i < SIZE; ++i) {
    sum = 0;
    for (int j = col; j < SIZE; ++j) {
      int val = board[i][j];
      sum+= val;
    }
    if (sum != 45){
      check_row[i] = false;
    }else if(sum == 45){
      check_row[i] = true;
    }
  }
return  check_row;
}


// Checks the given col for duplicate numbers, and updates the check_col
// value for that col appropriately. If no number is repeated in that col,
// check_col[col] will be set to true; otherwise, it will be false.
void* checkCol(void* args) {
  check_data * data = (check_data *) args;
  int row = data->row;
  int col = data->col;
  int sum = 0;
  int val;

  for (int i = col; i < SIZE; ++i) {
    sum = 0;
    for (int j = row; j < SIZE; ++j) {
      val = board[i][j];
      sum += val;
    }
    if (sum != 45){
      check_col[i] = false;
    } else if(sum == 45){
      check_col[i] = true;
    }
  }
  return check_col;
}

// // Checks the given 3x3 box for duplicate numbers, and updates the check_box
// // value for that box appropriately. If no number is repeated in that box,
// // check_box[box] will be set to true; otherwise, it will be false.
void* checkBox(void* args) {
  check_data * data = (check_data *) args;
  int row = data->row;
  int col = data->col;
  int box_num = data->box;
  int sum = 0;
  int val;

  for (int i = row; i < row + 3; ++i) {
    for (int j = col; j < col + 3; ++j) {
      val = board[i][j];
      sum+= val;
    }
    if (sum != 45){
      check_box[box_num] = false;
    }else if(sum == 45){
      check_box[box_num] = true;
    }
  }
  return check_box;
}


// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {

  //args for column and row checks
  check_data * check_row_col = (check_data *) malloc(sizeof(check_data));
  check_row_col->row = 0;
  check_row_col->col = 0;

  check_data * boxes[SIZE];
  for (size_t i = 0; i < SIZE; i++) { 
    // memory  allocation
    boxes[i] = (check_data *) malloc(sizeof(check_data));
  }
  //box 1 0,0
  boxes[0]->row = 0;
  boxes[0]->col = 0;
  boxes[0]->box = 0;

  // box 2 0,3
  boxes[1]->row = 0;
  boxes[1]->col = 3;
  boxes[1]->box = 1;

  // box 3 0,6
  boxes[2]->row = 0;
  boxes[2]->col = 6;
  boxes[2]->box = 2;

  // box 4 3,0
  boxes[3]->row = 3;
  boxes[3]->col = 0;
  boxes[3]->box = 3;

  // box 5 3,3
  boxes[4]->row = 3;
  boxes[4]->col = 3;
  boxes[4]->box = 4;

  // box 6 3,6
  boxes[5]->row = 3;
  boxes[5]->col = 6;
  boxes[5]->box = 5;

  // box 7 6,0
  boxes[6]->row = 6;
  boxes[6]->col = 0;
  boxes[6]->box = 6;

  // box 8 6,3
  boxes[7]->row = 6;
  boxes[7]->col = 3;
  boxes[7]->box = 7;

  // box 9 6,6
  boxes[8]->row = 6;
  boxes[8]->col = 6;
  boxes[8]->box = 8;


  // 1. Print the board.
  printf("Board:\n");
  printBoard(board);


  // 2. Create pthread_t objects for our threads.
  pthread_t rows,cols, box[SIZE];

  //return vales for threads
  void *all_rows;
  void *all_cols;
  void *returnbox1;
  void *returnbox2;
  void *returnbox3;
  void *returnbox4;
  void *returnbox5;
  void *returnbox6;
  void *returnbox7;
  void *returnbox8;
  void *returnbox9;

  // 3. Create a thread for each cell of each matrix operation.
  pthread_create(&rows, NULL, checkRow, (void *) check_row_col);
  pthread_create(&cols, NULL, checkCol, (void *) check_row_col);
  for (size_t i = 0; i < SIZE; i++) {
    pthread_create(&box[i], NULL, checkBox, (void *) boxes[i]);
  }

  // 4. Wait for all threads to finish.
  pthread_join(rows, &all_rows);
  pthread_join(cols, &all_cols);

  pthread_join(box[0], &returnbox1);
  pthread_join(box[1], &returnbox2);
  pthread_join(box[2], &returnbox3);
  pthread_join(box[3], &returnbox4);
  pthread_join(box[4], &returnbox5);
  pthread_join(box[5], &returnbox6);
  pthread_join(box[6], &returnbox7);
  pthread_join(box[7], &returnbox8);
  pthread_join(box[8], &returnbox9);

  // 5. Print the results.
  printf("Results:\n");
  bool pass_all_rows = true;
  printf("Rows:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!check_row[i]) {
      printf("Row %i failed\n", i+1);
      pass_all_rows = false;
    }
  }
  if (pass_all_rows) {
    printf("All rows passed!\n");
  }

  bool pass_all_cols = true;
  printf("Cols:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!(bool)check_col[i]) {
      printf("Col %i failed\n", i+1);
      pass_all_cols = false;
    }
  }
  if (pass_all_cols) {
    printf("All cols passed!\n");
  }

  bool pass_all_boxes = true;
  printf("Boxes:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!(bool)check_box[i]) {
      printf("Box %i failed\n", i+1);
      pass_all_boxes = false;
    }
  }
  if (pass_all_boxes) {
    printf("All boxes passed!\n");
  }
  return 0;
}