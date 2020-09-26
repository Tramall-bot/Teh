from PyQt5.QtWidgets import QApplication, QPushButton, QButtonGroup, QWidget, QMainWindow, QGridLayout, QLayout, \
    QLineEdit, QTableWidget, QSpinBox, QTableWidgetItem, QComboBox
import sys, random


class Journal(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()
        self.combobox.currentIndexChanged.connect(self.display)
        self.table.cellChanged.connect(self.redraw)

    def initUi(self):
        self.resize(self.parent().size())
        self.table = QTableWidget(self)
        self.table.setGeometry(10, 10, 320, 470)
        self.table.setColumnCount(6)
        self.table.setRowCount(6)
        self.combobox = QComboBox(self)
        self.settable()
        self.line = QLineEdit(" ", self)
        self.line.move(340, 70)
        self.combobox.move(340,40)
        self.line.setDisabled(True)

    def settable(self):
        for i in range(self.table.rowCount()-1):
            self.table.setItem(i, 0, QTableWidgetItem("Иванов"+str(i+1)))
            for j in range(self.table.columnCount()-1):
                self.table.setItem(i, j+1, QTableWidgetItem(str(int(random.uniform(2,6)))))
        self.setcombobox()


    def setcombobox(self):
        for i in range(self.table.rowCount()-1):
            self.combobox.addItem(self.table.item(i, 0).text())

    def display(self,):
        self.line.setText(self.calculate())

    def calculate(self):
        sum = 0
        count = 0
        for i in range(1, self.table.columnCount()):
            if self.table.item(self.combobox.currentIndex(), i) is None:
                continue
            if self.table.item(self.combobox.currentIndex(), i).text() =="":
                continue
            else:
                if int(self.table.item(self.combobox.currentIndex(), i).text()) >= 2:
                    sum += int(self.table.item(self.combobox.currentIndex(), i).text())
                    count += 1
        if count == 0:
            return "0"
        else:
            sum /= count
            return str(sum)

    def redraw(self):
        if self.table.item(self.combobox.count(), 0) is not None:
            self.combobox.addItem(self.table.item(self.combobox.count(), 0).text())
        else:
            for i in range(self.combobox.count()):
                if self.table.item(i, 0).text() != self.combobox.itemText(i):
                    self.combobox.setItemText(i, self.table.item(i, 0).text())
                    break

if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_windows = QMainWindow()
    j = Journal(main_windows)
    main_windows.resize(500, 500)
    main_windows.show()
    app.exec_()
