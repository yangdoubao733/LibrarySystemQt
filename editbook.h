#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QWidget>

namespace Ui {
class EditBook;
}

class EditBook : public QWidget
{
    Q_OBJECT

public:
    explicit EditBook(QWidget *parent = nullptr);
    ~EditBook();

private:
    Ui::EditBook *ui;
};

#endif // EDITBOOK_H
