import collections, sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QTextEdit, QPushButton
from collections.abc import Iterable, Iterator

class Node:
    def __init__(self, text):
        self.node = dict()
        for i in text:
            if i == "(":
                text = text.lstrip(i)
                i = text[0]
                text = text.lstrip(text[0])
                text = text.lstrip(text[0])
                list = []
                if i in self.node.keys():
                    for k in self.node[i]:
                        list.append(k)
                list.append(text[0])
                self.node[i] = list
                text = text.lstrip(text[0])
            text = text.lstrip(i)


class MyWindow(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()
        self.button.clicked.connect(self.GetText)

    def initUi(self):
        self.resize(self.parent().size())
        self.InputEdit = QTextEdit(self)
        self.InputEdit.setGeometry(50, 50, 65, 100)
        self.OutputEdit = QTextEdit(self)
        self.OutputEdit.setGeometry(165, 50, 120, 20)
        self.button = QPushButton(self)
        #self.button.setGeometry(175, 100, 100, 30)
        self.button.setText("Вывести вершины")

    def GetText(self):
        a = Node(self.InputEdit.toPlainText())
        b = NodesCollection(a.node)
        self.OutputEdit.setText(" ".join(b))

class AlphabeticalOrderIterator(Iterator):
    def __init__(self, collection) -> None:
        self.collection = collection
        self.visited = set()
        self.nodecount = -1
        self.dictlen = self.collection.__len__()
        self.nodes = []
        for i in self.collection.keys():
            self.nodes.append(i)
        self.connection = 0

    def __next__(self):
        if self.nodecount < 0:
            self.nodecount += 1
            value = self.nodes[self.nodecount]
            return value
        if self.nodecount < self.dictlen:
            if self.collection[self.nodes[self.nodecount]].__len__() > self.connection + 1:
                value = self.collection[self.nodes[self.nodecount]][self.connection]
                self.connection += 1
            else:
                value = self.collection[self.nodes[self.nodecount]][self.connection]
                self.connection = 0
                self.nodecount += 1
        else:
            raise StopIteration()
        if value not in self.visited:
            self.visited.add(value)
            return value
        else:
            return ""


class NodesCollection(Iterable):

    def __init__(self, collection) -> None:
        self._collection = collection

    def __iter__(self) -> AlphabeticalOrderIterator:
        return AlphabeticalOrderIterator(self._collection)

    def get_reverse_iterator(self) -> AlphabeticalOrderIterator:
        return AlphabeticalOrderIterator(self._collection)

    def add_item(self, item):
        self._collection.append(item)




if __name__ == '__main__':
     qapp = QApplication(sys.argv)
     main = QMainWindow()
     window = MyWindow(main)
     main.show()
     qapp.exec()

