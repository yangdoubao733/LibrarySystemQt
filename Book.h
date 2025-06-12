#ifndef BOOK
#define BOOK
#define MAXSIZE 1000

typedef struct Book
{
    int id; // ͼ���ţ�����ʱ���ʼ��Ϊ-1
    char* name;
    char* author;
    char* publisher;
    int year;
    int ISBN;
    bool isBorrowed; // �Ƿ񱻽���
    Book* next; // ָ����һ��ͼ���ָ��
} book, *bookList;

// ����ͼ�麯����methodΪ���ҷ�ʽ��foundBookΪ��Ų��ҽ�������飬iΪ��ǰ���ҽ��������
bool SearchBook(book Book, bookList L, char method, bookList foundBook, int &i);

// ���ͼ�麯��
bool AddBook(book Book, bookList& L);

// ɾ��ͼ�麯��
bool DeleteBook(book Book, bookList L);

// �޸�ͼ�麯��
bool ModifyBook(book bookPre, book bookMod, bookList L);

// ����ͼ�麯��
int BorrowBook(book Book, bookList L, int borrowTime);

#endif // !BOOK

