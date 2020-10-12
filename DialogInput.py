from PyQt5.QtWidgets import QApplication, QPushButton, QButtonGroup, QWidget, QMainWindow,  \
    QLineEdit, QTableWidget, QTableWidgetItem, QDialog, QDialogButtonBox
import sys, random


class Table(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()
        self.button.clicked.connect(new_nubmer)
        self.table.cellDoubleClicked[int, int].connect(EditNumber)

    def initUi(self):
        self.resize(self.parent().size())
        self.table = QTableWidget(self)
        self.table.setGeometry(10, 10, 320, 470)
        self.table.setColumnCount(3)
        self.table.setRowCount(3)
        self.table.setHorizontalHeaderLabels(["Двоичный", "Шестнадцатеричный", "Десятичный"])
        self.button = QPushButton("Добавить число", self)
        self.button.move(370, 20)

    def new_line(self, number):
        try:
            if number == "":
                pass
            else:
                flag = True
                i = int(number)
                for i in range(0, self.table.rowCount() - 1):
                    if self.table.item(i, 2) is None:
                        self.table.setItem(i, 2, QTableWidgetItem(number))
                        flag = False
                        break
                if flag:
                    self.table.setRowCount(self.table.rowCount() + 1)
                    self.table.setItem(self.table.rowCount() - 1, 2, QTableWidgetItem(number))
                self.other_numbers(i, number)
        except ValueError:
            pass


    def other_numbers(self, i, number):
        self.table.setItem(i, 0, QTableWidgetItem(format(int(number), "b")))
        self.table.setItem(i, 1, QTableWidgetItem(format(int(number), "X")))

    def Edited(self, a, b, number):
        try:

            self.table.setItem(a, 0, QTableWidgetItem(format(int(number), "b")))
            self.table.setItem(a, 1, QTableWidgetItem(format(int(number), "X")))
            self.table.setItem(a, 2, QTableWidgetItem(format(int(number), "d")))
        except ValueError:
            pass


def EditNumber(a, b):
    new = QDialog()
    button = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel, new)
    line = QLineEdit(new)
    new.resize(200, 100)
    button.move(30, 50)
    line.move(50, 20)
    button.accepted.connect(lambda: j.Edited(a, b, line.text()))
    button.accepted.connect(lambda: new.close())
    button.rejected.connect(lambda: new.close())
    new.show()
    new.exec_()

def new_nubmer():
    new = QDialog()
    button = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel, new)
    line = QLineEdit(new)
    new.resize(200, 100)
    button.move(30, 50)
    line.move(50, 20)
    button.accepted.connect(lambda: j.new_line(line.text()))
    button.accepted.connect(lambda: new.close())
    button.rejected.connect(lambda: new.close())
    new.show()
    new.exec_()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_windows = QMainWindow()
    j = Table(main_windows)
    main_windows.resize(500, 500)
    main_windows.show()
    app.exec_()
