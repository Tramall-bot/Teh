
import sqlite3
import sys
from PyQt5.QtCore import Qt, QAbstractTableModel, QModelIndex
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import QAbstractItemView
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QTableView


class CustomTableModel(QAbstractTableModel):
    def __init__(self, data=None):
        QAbstractTableModel.__init__(self)
        self.load_data(data)

    def load_data(self, data):
        self._data = data

    def rowCount(self, parent=QModelIndex()):
        return len(self._data[0])

    def columnCount(self, parent=QModelIndex()):
        return len(self._data)

    def headerData(self, section, orientation, role):
        if role != Qt.DisplayRole:
            return None
        if orientation == Qt.Horizontal:
            return ("Date", "Trans", "Symbol", "qty", "price")[section]
        else:
            return "{}".format(section)

    def data(self, index, role=Qt.DisplayRole):
        column = index.column()
        row = index.row()

        if role == Qt.DisplayRole or role == Qt.EditRole:
            if column == 0:
                raw_date = self._data[column][row]
                return raw_date
            elif column > 0:
                try:
                    s = self._data[column][row]
                    return s
                except ValueError:
                    return None

        elif role == Qt.BackgroundRole:
            return QColor(Qt.white)
        elif role == Qt.TextAlignmentRole:
            return Qt.AlignRight
        return None

    def flags(self, index):
        return Qt.ItemIsEnabled | Qt.ItemIsSelectable | Qt.ItemIsEditable

    def setData(self, index, value, role=Qt.EditRole):
        if index.isValid():
            row = index.row()
            col = index.column()
            if col == 1:
                try:
                    val = float(value)
                except ValueError:
                    val = self._data[col][row]
            self._data[col][row] = val
            self.dataChanged.emit(index, index, (Qt.DisplayRole,))
            return True
        return False

    def __repr__(self):
        return str(self._data)


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
        output = []
        for i in range(0, len(test[0])):
            output.append([])
            for j in range(0, len(test)):
                output[i].append(test[j][i])
        return output


if __name__ == '__main__':
    a = obertka()
    a.crateTable("stock", ('date text', 'trans text', 'symbol text', 'qty real', 'price real'))
    #a.InsertValues("stock", ('2006-07-25', 'BUY', 'IyhM', 2000.0, 895.00))
    print(a.getTable("stock"))
    data = [["09.10", "09.10"], [3, 4]]
    qapp = QApplication(sys.argv)
    model = CustomTableModel(a.getTable("stock"))
    main = QMainWindow()
    table_view = QTableView(main)
    table_view.setModel(model)
    table_view.setEditTriggers(QAbstractItemView.DoubleClicked)
    table_view.resize(500, 500)
    btn = QPushButton(main)
    btn.move(550, 10)
    btn.clicked.connect(lambda: print(model, data))
    main.show()
    qapp.exec()
