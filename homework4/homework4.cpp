      // HOMEWORK 4 - Counting objects in a image \\
   /*Computer Science  -  COSC 2347 - Special Topics*/
/* Jake Derkowski     ID: 000664315     jad084@shsu.edu*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

void program_header();
void print_vector(vector<int>, int);
vector<vector<int>> create_matrix(vector<int>, int);
void print_matrix(vector<vector<int> >, int);
// void scan_image(vector<vector<int>>, vector<int>, vector<int>, int);
void scan_image(vector<vector<int>>, int);
void output2file(vector<vector<int>>, int);

int main()
{
   program_header();

   ifstream fin;           // file stream variables
   char input_file[25];       // filename storage

   char ch; // variables for reading in bit
   int bit, lines;

   vector<int> imgVec;    // input vector
   // vector<int> look;      // comparing vectors
   // vector<int> replace;

   // get the name of the image file
   cout << "Image file: ";
   cin >> input_file;

   fin.open(input_file); // open file
   if (fin.fail()){ // check file
      cout << endl << "This file does not exist." << endl << "Program terminated." << endl;
      exit (EXIT_FAILURE); // abort program
   }

   else { // read/store image bit
      cout << "\nReading bit from image...\n";

      while (!fin.eof()) { // only store pixels
         fin.get(ch);
         if (isdigit(ch)){          // character is  digit -> push to vector
            bit = int(ch) - 48;     // convert from ASCII
            imgVec.push_back(bit);  // add element to the end of the current vector
         }
      }
      fin.close(); // close the image file
   }

   lines = sqrt(imgVec.size()); // because all input squares

   vector< vector<int> > imgMatrix(lines, vector<int>(lines, 0));
   imgMatrix = create_matrix(imgVec, lines); // 2d vector

   scan_image(imgMatrix, lines);
   // scan_image(imgMatrix, look, replace, lines); // function includes both passes
   // counting of objects, number of pixels each of them has, and prints results

   cout << "\nEnd of image processing.\n";

} // end of main

/*============================================================================*/
void program_header(){ // print title of assignmnet and my information
   cout << endl
   <<"  +----------------------------------------------------------+\n"
   <<"  |             Computer Science and Engineering             |\n"
   <<"  |               COSC 2347 - Special Topics                 |\n"
   <<"  |   Jake Derkowski     ID: 000664315     jad084@shsu.edu   |\n"
   <<"  +----------------------------------------------------------+\n"
   << endl;
   return;
}
/*============================================================================*/
void print_vector(vector<int> vec, int rows){ // prints in image format
   for (int i = 0; i < vec.size(); i++) { // iteratation
      if (i % rows == 0){ // display image in line
         cout << endl;
      }
      cout << vec.at(i) << ' ';
   }
   // cout << "\n\nNumber of pixels: " << vec.size() << endl;
   // cout << "\nDimensions: " << rows << " x " << rows << endl;
}
/*============================================================================*/
vector<vector<int>> create_matrix(vector<int> input, int rows){
   vector<vector<int>> matrix(rows, vector<int>(rows, 0));
   int knt = 0;
   for(int y = 0 ; y < rows; y++){  // store file into matrix
      for(int x = 0 ; x < rows; x++){
       matrix[x][y] = input[knt];
       knt++;
      }
   }
   return matrix;
}
/*============================================================================*/
void print_matrix(vector<vector<int> > matrix, int rows){
   for(int y = 0 ; y < rows ; y++){
      for(int x = 0 ; x < rows ; x++){
         cout << matrix[x][y] << " ";
      }
      cout << "\n";
   }
}
/*============================================================================*/
void output2file(vector<vector<int>> matrix, int rows){
   ofstream file;
   char filename[20] = "output.txt";

   file.open(filename);

   for(int y = 0 ; y < rows ; y++){
      for(int x = 0 ; x < rows ; x++){
         file << matrix[x][y] << " ";
      }
      file << "\n";
   }
   cout << "\nOutput saved in 'output.txt'\n";
}
/*============================================================================*/
// void scan_image(vector<vector<int>> matrix, vector<int> look, vector<int> replace, int row){
void scan_image(vector<vector<int>> matrix, int row){
   vector<int> look;      // comparing vectors
   vector<int> replace;
   bool check = true;
   int large = 0;
   int label = 0;

   for(int y = 0 ; y < row ; y++){ // first pass
      for(int x = 0 ; x < row ; x++){
         if(matrix[x][y] != 0){ // value = 1
            if( ((x-1) >= 0) && ((y-1) >= 0)){ // index check
               if((matrix[x-1][y] > 0) && (matrix[x][y-1] > 0)){//
                  if(matrix[x-1][y] != matrix[x][y-1]){ // values not same
                     if(matrix[x-1][y] > matrix[x][y-1]){ // label is lower
                        for(int i = 0 ; i < look.size() ; i++){
                           if( matrix[x-1][y] == look[i] ){
                              check = false;
                              break;
                           }
                        }
                        if(check){
                           look.push_back(matrix[x-1][y]);
                           replace.push_back(matrix[x][y-1]);
                        }
                        check = true;
                        matrix[x][y] = matrix[x][y-1];
                     }
                     else{
                        for(int i = 0 ; i < look.size() ; i++){
                           if(matrix[x][y-1]==look[i]){
                              check = false;
                              break;
                           }
                        }
                        if(check){
                           look.push_back(matrix[x][y-1]);
                           replace.push_back(matrix[x-1][y]);
                        }
                        check = true;
                        matrix[x][y] = matrix[x-1][y];
                     }
                  }
                  else{ // else they are
                     matrix[x][y] = matrix[x-1][y];
                  }
               }

               if((matrix[x-1][y] > 0) && (matrix[x][y-1] == 0)){ //x label, y none
                  matrix[x][y] = matrix[x-1][y];
               }

               if((matrix[x-1][y] == 0) && (matrix[x][y-1] > 0)){ //y label, x none
                  matrix[x][y] = matrix[x][y-1];
               }

               if((matrix[x-1][y] == 0) && (matrix[x][y-1] == 0)){ //no label
                  label++;
                  matrix[x][y] = label;
               }
            }
            else if(((x-1) >= 0) && ((y-1) < 0)){ // x is real, y DNE
               if(matrix[x-1][y] > 0){
                  matrix[x][y] = matrix[x-1][y];
               }
               else{
                  label++;
                  matrix[x][y] = label;
               }
            }
            else if(((x-1) < 0) && ((y-1) >= 0)){ // if y real, x DNE
               if(matrix[x][y-1] > 0){
                  matrix[x][y] = matrix[x][y-1];
               }
               else{
                  label++;
                  matrix[x][y] = label;
               }
            }
            else{ // else neither valid on the grid
               label++;
               matrix[x][y] = label;
            }
         }
      }
   }

   // cout << "\nImage after first pass:\n";
   // print_matrix(matrix, row);
   // cout << endl;

   for(int y = 0 ; y < row ; y++){ // second pass
      for(int x = 0 ; x < row ; x++){
         for(int i = 0 ; i < look.size() ; i++){
            if(matrix[x][y] == look[i])
               matrix[x][y] = replace[i];
         }
      }
   }

   label = label - look.size();

   look.clear();
   replace.clear();

   for(int i = 1 ; i < label ; i++){
      look.push_back(i);
      replace.push_back(0);
   }

   cout << "\nResult:\n" << endl;
   print_matrix(matrix, row);
   output2file(matrix, row);
   cout << endl;

   for(int y = 0 ; y < row ; y++){ // count pixels in object
      for(int x = 0 ; x < row ; x++){
         for(int i = 0 ; i < look.size() ; i++){
            if(matrix[x][y] == look[i]){
               replace[i] = replace[i] + 1;
            }
         }
      }
   }

   for(int i = 0 ; i < replace.size() ; i++){ // size of largest object
      if(replace[i] > large){
         large = replace[i];
      }
   }

   cout << "\nNumber of objects: " << (label) << endl;
   cout << "BONUS: " << "The largest object has a length of " << large << endl;
}
/*============================================================================*/
