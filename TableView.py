
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

class CustomTableModel(QAbstractTableModel):
    def __init__(self, TableName: str, parent, *args):
        QAbstractTableModel.__init__(self, parent, *args)
        self.db = obertka()
        self.table_name = TableName
        self.head_name = self.db.getHeader(self.table_name)

    def rowCount(self, parent=QModelIndex()):
        return len(self.db.getTable(self.table_name)[0])

    def columnCount(self, parent=QModelIndex()):
        return len(self.db.getTable(self.table_name))

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

class obertka:
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


class MyWindow(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()


    def initUi(self):
        self.resize(self.parent().size())
        self.tableview = QTableView(self)
        self.tableview.setModel(CustomTableModel("base", self))
        self.tableview.setGeometry(10, 30, 320, 200)
        self.table.setGeometry(10,30, 320, 200)
        self.checkbox = QCheckBox(self)
        self.checkbox.move(350, 50)



if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    main = QMainWindow()
    w= MyWindow(main)
    main.show()
    qapp.exec()
