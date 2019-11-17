            // HOMEWORK 3 encryptION/DECRYPTION \\
      /*Computer Science  -  COSC 2347 - Special Topics*/
/* Jake Derkowski     ID: 000664315     jad084@shsu.edu*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>
using namespace std;

void program_header();                // display personal info
char UserOption(char& ans);           // pick ENCRYPT or DECRYPT
void encrypt(ifstream& in_stream, ofstream& out_stream);
void decrypt(ifstream& in_stream, ofstream& out_stream);


int main()
{
   program_header();       // begin running program
   char ans;               // answer to UserOption
   char input_file[26];    // users import file
   char output_file[26];   // users export file
   ifstream fin;    ofstream fout;   // file streaming objects

   UserOption(ans);

   if (ans == 'E' || ans == 'e'){ // Encryption

      cout << "Enter the name of your input file you want to encrypt: ";
      cin >> input_file;
      cout << "Enter the name of the output file to write the ciphertext to: ";
      cin >> output_file;

      fin.open(input_file);
		if (fin.fail()){/* INPUT CHECK*/
         cout << "ERROR! Unable to open file: " << input_file << endl;
         cout << "Terminating...\n";		exit(1);
      }

      fout.open(output_file);
      if (fout.fail()){/* OUTPUT CHECK */

         cout << "ERROR! Unable to open file: " << output_file << endl;
         cout << "Terminating...\n";		exit(1);
      }

      encrypt(fin, fout);  // perform encryption

   }

   if (ans == 'D' || ans == 'd'){ // Decryption

      cout << "Enter the name of your input file you want to decrypt: ";
      cin >> input_file;
      cout << "Enter the name of the output file to write the plaintext: ";
      cin >> output_file;

      fin.open(input_file);
      if (fin.fail()){/* INPUT CHECK*/
         cout << "ERROR! Unable to open file: " << input_file << endl;
         cout << "Terminating...\n";		exit(1);
      }

      fout.open(output_file);
      if (fout.fail()){/* OUTPUT CHECK */

         cout << "ERROR! Unable to open file: " << output_file << endl;
         cout << "Terminating...\n"; 	exit(1);
      }

      decrypt(fin, fout); // perform decryption
   }
   fin.close();
   fout.close();

} // end of main

void encrypt(ifstream& in_stream, ofstream& out_stream){

	char ch;			// character read from file
	char key[6];	// the acsii/int value of user defined key
	int knt = 0;	// allow to iterate array circlicly
	char res;		// enc/dec character result

	cout << "Enter a 5-letter key to encrypt file: ";	cin >> key;

	in_stream.get(ch);

	while(! in_stream.eof()){
		if(isupper(ch)){
			res = 'A' + (((ch - 'A') + (toupper(key[knt]) - 'A')) % 26);
			out_stream.put(res);
			if (knt == 4){
            knt = 0;}
			else {knt++;}
		}
		else if (islower(ch)){
			res = 'a' + (((ch - 'a') + (tolower(key[knt]) - 'a')) % 26);
			out_stream.put(res);
			if(knt == 4){
            knt = 0;}
			else {knt++;}
		}
      else {out_stream.put(ch);}

      in_stream.get(ch);
   }
}

void decrypt(ifstream& in_stream, ofstream& out_stream){

	char ch;			// character read from file
	char key[6];	// the acsii/int value of user defined key
	int knt = 0;	// allow to iterate array circlicly
	char res;			// enc/dec character result

	cout << "Enter a 5-letter key to decrypt file: ";		cin >> key;

	in_stream.get(ch);

   while(! in_stream.eof()){
      if(isupper(ch)){
         res = 'A' + ((26 + (ch - 'A') - (toupper(key[knt]) - 'A')) % 26);
         out_stream.put(res);
         if(knt == 4){
            knt = 0;}
         else {knt++;}
      }
      else if (islower(ch)){
         res = 'a' + ((26 + (ch - 'a') - (tolower(key[knt]) -'a')) % 26);
         out_stream.put(res);
         if(knt == 4){
            knt = 0;}
         else {knt++;}
      }
      else {out_stream.put(ch);}

      in_stream.get(ch);
   }
}

char UserOption(char &ans){
   cout << "Would you like to ENCRYPT OR DECRYPT a file (E or D)?\t  ";
   cin  >> ans;

   switch (ans) {
      //Encryption
      case 'E':
      case 'e':
               break;

      //Decryption
      case 'D':
      case 'd':
              break;

      // Checks if ansut is valid
      default:
              return UserOption(ans);
      }
}

void program_header(){
   cout << endl
   <<"  +----------------------------------------------------------+\n"
   <<"  |             Computer Science and Engineering             |\n"
   <<"  |               COSC 2347 - Special Topics                 |\n"
   <<"  |   Jake Derkowski     ID: 000664315     jad084@shsu.edu   |\n"
   <<"  +----------------------------------------------------------+\n"
   << endl;
   return;
}
