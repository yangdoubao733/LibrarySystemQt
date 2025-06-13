#ifndef BOOK
#define BOOK
#define MAXSIZE 1000

typedef struct Book
{
    int id; // 图书编号，调用时请初始化为-1
    char* name;
    char* author;
    char* publisher;
    int year;
    int ISBN;
    bool isBorrowed; // 是否被借阅
	int borrowedBy; // 借阅者的编号，-1表示未被借阅
    Book* next; // 指向下一本图书的指针
} book, *bookList;

// 查找图书函数，method为查找方式，foundBook为存放查找结果的数组，i为当前查找结果的数量
bool SearchBook(book Book, bookList L, char method, bookList foundBook, int &i);

// 添加图书函数
bool AddBook(book Book, bookList& L);

// 删除图书函数
bool DeleteBook(book Book, bookList L);

// 修改图书函数
bool ModifyBook(book bookPre, book bookMod, bookList L);

// 借阅图书函数
int BorrowBook(book Book, bookList L, int userId);

#endif // !BOOK

