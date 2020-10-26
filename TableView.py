import sqlite3
import sys
from PyQt5.QtCore import Qt, QAbstractTableModel, QModelIndex, QVariant
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import QAbstractItemView
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QTableView
from PyQt5.QtWidgets import QWidget,QCheckBox, QTableWidget, QTableWidgetItem
import os.path

class CustomTableModel(QAbstractTableModel):
    def __init__(self, TableName: str, parent, *args):
        QAbstractTableModel.__init__(self, parent, *args)
        self.db = Obertka()
        self.table_name = TableName
        self.head_name = self.db.getHeader(self.table_name)

    def rowCount(self, parent=QModelIndex()):
        return len(self.db.getTable(self.table_name))

    def columnCount(self, parent=QModelIndex()):
        return len(self.db.getTable(self.table_name)[0])

    def headerData(self, p_int, Qt_Orientation, int_role=None):
        if int_role == Qt.DisplayRole and Qt_Orientation == Qt.Horizontal:
            if p_int < len(self.head_name):
                return self.head_name[p_int]
        return QVariant()

    def data(self, index, role=Qt.DisplayRole):
        column = index.column()
        row = index.row()
        if role != Qt.DisplayRole:
            return None
        return self.db.getTable(self.table_name)[row][column]

    def flags(self, index):
        return Qt.ItemIsEnabled | Qt.ItemIsSelectable | Qt.ItemIsEditable

    def setData(self, index, value, role=Qt.EditRole):
        if role == Qt.EditRole:
            row=index.row()
            column=index.column()
            self.db.set(self.table_name, row+1, self.head_name[column], value)
            return True

class Obertka:
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.conn = sqlite3.connect("test.db")

    def crateTable(self, name: str, vocab):
        c = self.conn.cursor()
        s = []
        for i in vocab:
            s.append(f"{i} {vocab[i]}")
        value = ", ".join(s)
        c.execute(f"CREATE TABLE if not exists {name} (ID INT PRIMARY KEY, {value})")
        self.conn.commit()

    def InsertValues(self, name, vocab):
        c = self.conn.cursor()
        try:
            id = c.execute(f"Select * FROM {name}").fetchall()[-1][0] + 1
        except:
            id = 1
        s = []
        for i in vocab:
            s.append("?")
        value = ", ".join(s)
        c.execute(f"INSERT INTO {name} VALUES ({id} , {value})", vocab)
        self.conn.commit()

    def getTable(self, name):
        c = self.conn.cursor()
        c.execute(f'SELECT * FROM {name} ')
        test = c.fetchall()
        output = []
        for i in test:
            temp=[]
            for j in i:
                temp.append(j)
            output.append(temp)
        return output

    def set(self, name, id, column, value):
        c = self.conn.cursor()
        c.execute(f'UPDATE {name} SET {column} = "{value}" WHERE ID = {id}')
        self.conn.commit()

    def getHeader(self, name):
        c = self.conn.cursor()
        c.execute(f"SELECT * FROM {name}")
        headers = []
        for head in c.description:
            headers.append(head[0].upper())
        return headers

class FileDB:
    def __init__(self, name):
        self.filename = name
        self.f = open(self.filename, 'r+')

    def data(self, column, row):
        self.f.seek(100 * column + 400 * row, 0)
        return self.f.read(100)

    def rowCount(self):
        return os.path.getsize(self.filename)/400

    def columnCount(self):
        return 4

    def setdata(self, column, row, value):
        self.f.seek(100 * column + 400 * row, 0)
        self.f.write(str(value)[0:99] + '\0' * (100 - len(str(value))))

    def __repr__(self):
        max_size = 0
        for i in range(int(os.path.getsize(self.filename) / 100)):
            self.f.seek(i * 100, 0)
            temp = self.f.read(100)
            j = 0
            temp_size = 0
            while temp[j] != "\0":
                temp_size += 1
                j += 1
            if temp_size > max_size:
                max_size = temp_size
        string = "++"
        for i in range(4):
            for j in range(max_size):
                string += "-"

            string += "++"
        string += "\n"
        for i in range(int(self.rowCount())):
            string += "|"
            for j in range(int(self.columnCount())):
                string += "|"
                self.f.seek(i * 400 + j * 100, 0)
                temp = self.f.read(max_size)
                k = 0
                while k < max_size:
                    if temp[k] == "\0":
                        string += " "
                    string += temp[k]
                    k += 1
                string += "|"
            string += "|"
            string += "\n"
            string += "++"
            for j in range(4):
                for k in range(max_size):
                    string += "-"
                string += "++"
            string += "\n"
        return string

class FileTableModel(QAbstractTableModel):
    def __init__(self,name, filedb, parent, *args):
        QAbstractTableModel.__init__(self, parent, *args)
        self.filename = name
        self.db = filedb
        self.f = open(self.filename, "r+")

    def rowCount(self, parent=QModelIndex()):
        return self.db.rowCount()

    def columnCount(self, parent=QModelIndex()):
        return 4

    def data(self, index, role=Qt.DisplayRole):
        column = index.column()
        row = index.row()
        if role != Qt.DisplayRole:
            return None
        return self.db.data(column, row)

    def flags(self, index):
        return Qt.ItemIsEnabled | Qt.ItemIsSelectable | Qt.ItemIsEditable

    def setData(self, index, value, role=Qt.EditRole):
        if role == Qt.EditRole:
            row = index.row()
            column = index.column()
            self.db.setdata(column, row, value)
            return True

    def __repr__(self):
        return self.db.__repr__()


class MyWindow(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()
        self.checkbox.stateChanged.connect(self.change)
        self.button.clicked.connect(self.printfile)

    def initUi(self):
        self.resize(self.parent().size())
        self.tableview = CustomTableModel("abc", self)
        self.filedb = FileDB("test_db.txt")
        self.tablefile = FileTableModel("test_db.txt",self.filedb, self)
        self.showtable = QTableView(self)
        self.showtable.setModel(self.tableview)
        self.showtable.setGeometry(10, 30, 320, 200)
        self.checkbox = QCheckBox(self)
        self.checkbox.move(350, 50)
        self.check = True
        self.button = QPushButton(self)
        self.button.move(350, 80)

    def change(self):
        if self.check:
            self.showtable.setModel(self.tablefile)
        else:
            self.showtable.setModel(self.tableview)
        self.check = not self.check

    def printfile(self):
        print(self.tablefile)

if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    main = QMainWindow()
    w= MyWindow(main)
    main.show()
    qapp.exec()
