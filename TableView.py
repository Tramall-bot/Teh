#Сделать через TableView
from PyQt5.QtWidgets import QApplication, QPushButton, QButtonGroup, QWidget, QMainWindow, QGridLayout, QLayout, \
    QLineEdit, QTableWidget, QSpinBox, QTableWidgetItem, QComboBox, QTableView
import sqlite3, sys

class Journal(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()

    def initUi(self):
        self.resize(self.parent().size())
        self.table = QTableView(self)

        self.table.setGeometry(0, 0, 500, 500)
        self.table.setHorizontalHeader(['date', 'trans', 'symbol', 'qty', 'price'])
        self.table.show()

    def fill(self, values):
        for i in range(values.__len__()):
             for j in range(5):
                self.table.setItem(i, j, QTableWidgetItem(str(values[i][j])))

class obertka:
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.conn = sqlite3.connect("test.db")

    def crateTable(self, name, vocab):
        c = self.conn.cursor()
        c.execute(f'CREATE TABLE if not exists {name} {str(vocab)}')
        self.conn.commit()



    def InsertValues(self, name, values):
        c = self.conn.cursor()
        c.execute(f"INSERT INTO {name} VALUES {str(values)}")
        self.conn.commit()

    def getTable(self, name):
        c = self.conn.cursor()
        c.execute(f'SELECT * FROM {name} ')
        test = c.fetchall()
        return test



if __name__ == '__main__':
    a = obertka()
    a.crateTable("stock", ('date text', 'trans text', 'symbol text', 'qty real', 'price real'))
    a.InsertValues("stock", ('2006-07-25', 'BUY', 'IyhM', 2000.0, 895.00))
    a.getTable("stock")
    app = QApplication(sys.argv)
    main_windows = QMainWindow()
    j = Journal(main_windows)
    main_windows.resize(500, 500)
    main_windows.show()
    j.fill(a.getTable("stock"))
    app.exec_()
