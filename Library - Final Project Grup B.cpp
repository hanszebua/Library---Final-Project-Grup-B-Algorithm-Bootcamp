#include <stdio.h>
#include <string.h>

// Requirements that are not met : Binary Search, File Processing, Merge Sort

//Structure
struct Book { //structure untuk memuat data buku
  char name[255];
  char writer[255];
  char isbn[255];
  char genre[255];
  double rating;
  long long yearPublished;
  bool available; // untuk mengecek apakah buku masih ada atau sudah dihapus
};

struct temp_book_info { //structure yang memuat informasi buku yang sementara (dipakai di function updateBook)
  char name[255];
  char writer[255];
  char isbn[255];
  char genre[255];
  double rating;
  long long yearPublished;
  bool available;
};



//Global Variables
temp_book_info temps[1000];
int tempCount = 0; // index dari structure temp_book_info
Book books[1000]; 
int total_book = 0; // index dari structure books
double sortedArray[1000];

//Prototype
void mainMenu(); // untuk akses main menu
void addBook(); // add a book
void burnBook(); // remove a book
void searchBook(); // search a book by its name
void sortBook(); //sort a book by its name
void viewAll(); // view all books  
void updateBook(); //update an information from a book
void showChoice(); // bagian dari mainMenu, berfungsi print choices
void updateMenuChoice (int i); //subMenu untuk memilih informasi apa yang ingin diupdate
void showUpdateChoices(); //bagian dari updateMenuChoice, berfungsi print pilihan yang diberikan dalam mengupdate informasi buku.
void createSortedArray();

int main() {
  
	mainMenu();


  
  return 0;
  }

void mainMenu () {
  bool usingLib = true; 

  while (usingLib){ // selama usingLib = true, maka kita akan terus print showChoice.
    showChoice();
    int choice;

    do{
	  puts("Please input your choice");
      printf(">> ");
      scanf("%d", &choice);
      getchar();
    }
    while (choice < 1 || choice > 7); // Kalau misalnya choicenya invalid, akan terus minta choice yang valid.

    if (choice == 1){
    	addBook();

    }
    else if (choice == 2){
		burnBook();
    }
    else if (choice == 3){
		searchBook();
    }
    else if (choice == 4){

    }
    else if (choice == 5){
		viewAll();
    }
    else if (choice == 6){
		updateBook();
    }
    else if (choice == 7){
      puts("See You Again");
      usingLib = false; // Jika user exit, maka showChoice tidak akan diprint dan programnya berhenti
    }
  }
}

void showChoice (){
  puts("Library");
  puts("1. Add Book");
  puts("2. Remove Book");
  puts("3. Search a Book");
  puts("4. Sort The Books by Alphabet");
  puts("5. View All Books");
  puts("6. Update Book Informations");
  puts("7. Exit the Library");
}

void addBook (){
    printf("Nama : ");
    scanf("%s", books[total_book].name); getchar(); 
    printf("Penulis : ");
    scanf("%s", books[total_book].writer); getchar();
    printf("ISBN : ");
    scanf("%s", books[total_book].isbn); getchar();
    printf("Genre : ");
    scanf("%s", books[total_book].genre); getchar();
    printf("Rating : ");
    scanf("%lf", &books[total_book].rating); getchar();
    printf("Year Published : ");
    scanf("%lld", &books[total_book].yearPublished); getchar();
    books[total_book].available = true; //Ketika kita menambah sebuah buku, maka secara defaultnya dia akan tersedia. Maka kita beri nilai true
    total_book++;
}

void viewAll () {
	for (int i = 0; i<total_book; i++){
		if (books[i].available == false){ //untuk buku yang diremove (ditandai bahwa sudah diremove), maka tidak akan diprint
			continue;
		}
		printf("Book Number : %d\n", i+1);
		printf("Nama : %s\n", books[i].name); 
	    printf("Penulis : %s\n", books[i].writer);
	    printf("ISBN : %s\n", books[i].isbn); 
	    printf("Genre : %s\n", books[i].genre); 
	    printf("Rating : %lf\n", books[i].rating); 
	    printf("Year Published : %lld\n", books[i].yearPublished); 
	    puts("");
	}
}

void burnBook() {
	char book_on_fire[255];
	printf("Input the name of the book you want to be burned : ");
	scanf("%[^\n]", book_on_fire); 
	getchar();
	for (int i = 0; i<total_book; i++){
		if (strcmp(books[i].name, book_on_fire) == 0){ // Kita melakukan linear search sampai ketemu struct dengan judul buku yang sama dengan yang akan dihapus
			books[i].available = false; // Tandai struct tersebut, agar dalam function viewAll, tidak ikut diprint
			break;
		}
	}
}

void searchBook() {
	char book_on_search[255];
	printf("Input the name of the book you want to search : ");
	scanf("%[^\n]", book_on_search); 
	getchar();
	for (int i = 0; i<total_book; i++){
		if (strcmp(books[i].name, book_on_search) == 0){ // Linear search juga, sistemnya cukup sama dengan di function burnBook
			printf("Book Number : %d\n", i+1);
			printf("Nama : %s\n", books[i].name); 
		    printf("Penulis : %s\n", books[i].writer);
		    printf("ISBN : %s\n", books[i].isbn); 
		    printf("Genre : %s\n", books[i].genre); 
		    printf("Rating : %lf\n", books[i].rating); 
		    printf("Year Published : %lld\n", books[i].yearPublished); 
		    puts("");
		}
	}
}

void updateBook() {
	char book_update[255];
	printf("Input the name of the book you want to update : ");
	scanf("%[^\n]", book_update); 
	getchar();
	for (int i = 0; i<total_book; i++){
		if (strcmp(books[i].name, book_update) == 0){
			printf("Book Number : %d\n", i+1);
			printf("Nama : %s\n", books[i].name); 
		    printf("Penulis : %s\n", books[i].writer);
		    printf("ISBN : %s\n", books[i].isbn); 
		    printf("Genre : %s\n", books[i].genre); 
		    printf("Rating : %lf\n", books[i].rating); 
		    printf("Year Published : %lld\n", books[i].yearPublished); 
		    puts("");
		    
		    updateMenuChoice(i);
		    
		}
	}
}

void showUpdateChoices() {
	puts("What information do you want to update?");
	puts("1. Book Name\n2.Writer\n3.ISBN\n4.Genre\n5.Rating\n6.Year Published\n7.Cancel");
	
}

void updateMenuChoice (int i) {
	  bool choosingUpdate = true; // Sistemnya sama dengan di mainMenu

  while (choosingUpdate){
    showUpdateChoices();
    int updateChoice;

    do{
      printf(">> ");
      scanf("%d", &updateChoice);
      getchar();
    }
    while (updateChoice < 1 || updateChoice > 6);
	
	puts("Input your changes");
	printf(">> ");

    if (updateChoice == 1){
    	scanf("%[^\n]", temps[tempCount].name); getchar();
    	strcpy(books[i].name, temps[tempCount].name);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 2){
		scanf("%[^\n]", temps[tempCount].writer); getchar();
    	strcpy(books[i].writer, temps[tempCount].writer);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 3){
		scanf("%[^\n]", temps[tempCount].isbn); getchar();
    	strcpy(books[i].isbn, temps[tempCount].isbn);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 4){
		scanf("%[^\n]", temps[tempCount].genre); getchar();
    	strcpy(books[i].genre, temps[tempCount].genre);
    	tempCount++;
    	return;
    }
    else if (updateChoice == 5){
		scanf("%lf", &temps[tempCount].rating); getchar();
    	books[i].rating = temps[tempCount].rating;
    	tempCount++;
    	return;
    }
    else if (updateChoice == 6){
    	scanf("%lld", &temps[tempCount].yearPublished); getchar();
    	books[i].yearPublished = temps[tempCount].yearPublished;
    	tempCount++;
    	return;
    }
    else if( updateChoice == 7){
    	return;
	}
    
  }

}

//void mS_part1(int L, int R, struct input){
//	int M = 0;
//	if (l < r){ //memastikan bahwa setidaknya ada 2 data
//		M = (L+R)/2;
//		
//	}
//}
//
//
//
//
//void mS_part2(int L, int R, int M, struct input){
//	double left[M-L+1];
//	double right[R-M];
//	
//	for (int i = 0; i<M-L+1; i++){
//		left[i] = books.rating[L+i];
//	}
//	for (int i = 0; i<R-M; i++){
//		right[j] = books.rating[M+i+1];
//	}
//	
//	int leftIdx = 0;
//	int rightIdx = 0;
//	int sortedArrIdx = 0;
//	
//	while (leftIdx < M-L+1 && rightIdx < R-M){
//		if (left[leftIdx] < right[rightIdx]){
//			
//		}
//		
//		
//	
//	}
//	
//	
	
//}

//void createSortedArray(double arr[]){
//	for (int i = 0; i<total_book; i++){
//		arr[i] = 
//	}
//}
