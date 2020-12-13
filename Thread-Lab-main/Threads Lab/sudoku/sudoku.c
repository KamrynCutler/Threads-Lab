#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9

// Sudoku board. Modify this to test your checker!
// 0 == empty cell; 1-9 is the filled in digit.
int  board[SIZE][SIZE] = {
  {2, 8, 5, 4, 7, 3, 9, 1, 6},
  {4, 9, 6, 1, 8, 2, 5, 7, 3},
  {3, 7, 1, 9, 5, 6, 8, 4, 2},
  {7, 6, 2, 3, 9, 1, 4, 5, 8},
  {9, 5, 8, 2, 4, 7, 3, 6, 1},
  {1, 4, 3, 8, 6, 5, 7, 2, 9},
  {8, 3, 7, 6, 1, 4, 2, 9, 5},
  {5, 1, 9, 7, 2, 8, 6, 3, 4},
  {6, 2, 4, 5, 3, 9, 1, 8, 7}
};

// array of bools
bool row_check[SIZE], col_check[SIZE], box_check[SIZE];

typedef struct
{
  int row, col, box;
} check;


//Pring board fucntion
void printBoard(int board[SIZE][SIZE]) {
  for(int i = 0; i<SIZE; i++) {
    for(int j = 0; j<SIZE; j++) {
      printf("%5d", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Checks the given row for duplicate numbers, and updates the row_check
// value for that row appropriately. If no number is repeated in that row,
// row_check[row] will be set to true; otherwise, it will be false.
void* checkRow(void* args) {
  check * data = (check *) args;
  int row = data->row;
  int col = data->col;
  int sum = 0;
  int i = 0;
  int j = 0;
  for (i = row; i < SIZE; ++i) {
    sum = 0;
    for (j = col; j < SIZE; ++j) {
      int val = board[i][j];
      sum+= val;
    }
    if (sum != 45){
      row_check[i] = false;
    }else if(sum == 45){
      row_check[i] = true;
    }
  }
return row_check;
}


// Checks the given col for duplicate numbers, and updates the col_check
// value for that col appropriately. If no number is repeated in that col,
// col_check[col] will be set to true; otherwise, it will be false.
void* checkCol(void* args) {
  check * data = (check *) args;
  int row = data->row;
  int col = data->col;
  int sum = 0;
  for (int i = col; i < SIZE; ++i) {
    sum = 0;
    for (int j = row; j < SIZE; ++j) {
      int val = board[i][j];
      sum+= val;
    }
    if (sum != 45){
      col_check[i] = false;
    }else if(sum == 45){
      col_check[i] = true;
    }
  }
  return col_check;
}

// // Checks the given 3x3 box for duplicate numbers, and updates the box_check
// // value for that box appropriately. If no number is repeated in that box,
// // box_check[box] will be set to true; otherwise, it will be false.
void* checkBox(void* args) {
  check * data = (check *) args;
  int row = data->row;
  int col = data->col;
  int boxnum = data->box;
  int  sum = 0;
  for (int i = row; i < row + 3; ++i) {
    for (int j = col; j < col + 3; ++j) {
      int val = board[i][j];
      sum+= val;
    }
    if (sum != 45){
      box_check[boxnum] = false;
    }else if(sum == 45){
      box_check[boxnum] = true;
    }
  }
  return box_check;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {

  //args for column and row checks
  check * row_col_check = (check *) malloc(sizeof(check));
  row_col_check->row = 0;
  row_col_check->col = 0;

  check * boxes[SIZE];
  for (size_t i = 0; i < SIZE; i++) { // memory  allocation
    boxes[i] = (check *) malloc(sizeof(check));
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
  void * all_rows;
  void * all_cols;
  void * returnbox1;
  void * returnbox2;
  void * returnbox3;
  void * returnbox4;
  void * returnbox5;
  void * returnbox6;
  void * returnbox7;
  void * returnbox8;
  void * returnbox9;


  // 3. Create a thread for each cell of each matrix operation.
  pthread_create(&rows, NULL, checkRow, (void *) row_col_check);
  pthread_create(&cols, NULL, checkCol, (void *) row_col_check);
  for (size_t i = 0; i < SIZE; i++) {
    pthread_create(&box[i], NULL, checkBox, (void *) boxes[i]);
  }


  // 4. Wait for all threads to finish.
  //row_check
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
  bool all_rows_passed = true;
  printf("Rows:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!row_check[i]) {
      printf("Row %i did not pass\n", i+1);
      all_rows_passed = false;
    }
  }
  if (all_rows_passed) {
    printf("All rows passed!\n");
  }

  bool all_cols_passed = true;
  printf("Cols:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!(bool)col_check[i]) {
      printf("Col %i did not pass\n", i+1);
      all_cols_passed = false;
    }
  }
  if (all_cols_passed) {
    printf("All cols passed!\n");
  }

  bool all_boxes_passed = true;
  printf("Boxes:\n");
  for (int i = 0; i < SIZE; i++) {
    if (!(bool)box_check[i]) {
      printf("Box %i did not pass\n", i+1);
      all_boxes_passed = false;
    }
  }
  if (all_boxes_passed) {
    printf("All boxes passed!\n");
  }
  return 0;
}
