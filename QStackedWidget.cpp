from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QStackedWidget, QLabel, QPushButton
from PyQt5.QtGui import QFont
import sys

class Reg_Runner(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()


    def initUi(self):
        self.resize(500, 600)
        self.back = QPushButton(self)
        self.back.setStyleSheet("background-color: rgb(71, 71, 71)")
        self.back.setEnabled(False)
        self.back.setGeometry(-10, 0, 600, 50)
        self.head = QLabel(self)
        self.head.move(70, 10)
        self.head.setFont(QFont('Arial', 14))
        self.head.setText("MARATHON SKILLS 2016")
        self.head.setStyleSheet("color: rgb(240, 240, 240)")
        self.backbutton = QPushButton(self)
        self.backbutton.setGeometry(10, 10, 50, 30)
        self.backbutton.setText("Назад")
        self.backbutton.setFont(QFont('Arial', 10))
        self.line1 = QLabel("Регистрация бегуна", self)
        self.line1.setFont(QFont('Arial', 14))
        self.line1.move(140, 100)
        self.line1.setStyleSheet("color: rgb( 100, 100, 100)")
        self.line2 = QLabel("Пожалуйста заполните всю информацию, чтобы зарегистрироваться в качестве\n"
                            "                                                              бегуна", self)
        self.line2.setFont(QFont('Arial', 9))
        self.line2.move(20, 140)
        self.line2.setStyleSheet("color: rgb( 80, 80, 80)")

class Log_Runner(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()

    def initUi(self):
        self.resize(500, 600)
        self.back = QPushButton(self)
        self.back.setStyleSheet("background-color: rgb(71, 71, 71)")
        self.back.setEnabled(False)
        self.back.setGeometry(-10, 0, 600, 50)
        self.head = QLabel(self)
        self.head.move(70, 10)
        self.head.setFont(QFont('Arial', 14))
        self.head.setText("MARATHON SKILLS 2016")
        self.head.setStyleSheet("color: rgb(240, 240, 240)")
        self.backbutton = QPushButton(self)
        self.backbutton.setGeometry(10, 10, 50, 30)
        self.backbutton.setText("Назад")
        self.backbutton.setFont(QFont('Arial', 10))
        self.line1 = QLabel("Форма авторизации", self)
        self.line1.setStyleSheet("color: rgb( 100, 100, 100)")
        self.line1.setFont(QFont('Arial', 14))
        self.line1.move(140, 100)
        self.line2 = QLabel("Пожалуйста, авторизируйтесь в системе, используя ваш адрес электронной почты\n"
                            "                                                       и пароль", self)
        self.line2.setFont(QFont('Arial', 9))
        self.line2.setStyleSheet("color: rgb( 80, 80, 80)")
        self.line2.move(20, 140)

class Chose(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()

    def initUi(self):
        self.resize(500, 600)
        self.back = QPushButton(self)
        self.back.setStyleSheet("background-color: rgb(71, 71, 71)")
        self.back.setEnabled(False)
        self.back.setGeometry(-10, 0, 600, 50)
        self.head = QLabel(self)
        self.head.move(70, 10)
        self.head.setFont(QFont('Arial', 14))
        self.head.setText("MARATHON SKILLS 2016")
        self.head.setStyleSheet("color: rgb(240, 240, 240)")
        self.backbutton = QPushButton(self)
        self.backbutton.setGeometry(10, 10, 50, 30)
        self.backbutton.setText("Назад")
        self.backbutton.setFont(QFont('Arial', 10))
        self.logbutton = QPushButton("Я участвовал ранее", self)
        self.logbutton.setGeometry(150, 120, 200, 80)
        self.regisbutton = QPushButton("Я новый участник", self)
        self.regisbutton.setGeometry(150, 230, 200, 80)

class MainWindow(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()

    def initUi(self):
        self.resize(500, 600)
        self.back = QPushButton(self)
        self.back.setStyleSheet("background-color: rgb(71, 71, 71)")
        self.back.setEnabled(False)
        self.back.setGeometry(-10, 0, 600, 120)
        self.button = QPushButton("Я хочу стать бегуном", self)
        self.button.setGeometry(150, 150, 200, 80)
        self.head = QLabel(self)
        self.head.move(120, 30)
        self.head.setFont(QFont('Arial', 14))
        self.head.setText("MARATHON SKILLS 2016")
        self.head.setStyleSheet("color: rgb(240, 240, 240)")
        self.line1 = QLabel(self)
        self.line1.move(170, 60)
        self.line1.setStyleSheet("color: rgb(209, 209, 209)")
        self.line1.setFont(QFont('Arial', 10))
        self.line1.setText("     Москва, Росия\nсреда 21 октября 2016")


class MyWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUi()
        self.windows[1].backbutton.clicked.connect(lambda: self.set_state(0))
        self.windows[2].backbutton.clicked.connect(lambda: self.set_state(0))
        self.windows[3].backbutton.clicked.connect(lambda: self.set_state(0))
        self.windows[0].button.clicked.connect(lambda: self.set_state(1))
        self.windows[1].logbutton.clicked.connect(lambda: self.set_state(2))
        self.windows[1].regisbutton.clicked.connect(lambda: self.set_state(3))

    def initUi(self):
        self.stack = QStackedWidget(self)
        self.stack.resize(500, 600)
        self.windows = []
        self.windows.append(MainWindow())
        self.windows.append(Chose())
        self.windows.append(Log_Runner())
        self.windows.append(Reg_Runner())
        for i in range(len(self.windows)):
            self.stack.addWidget(self.windows[i])

    def set_state(self, state):
        self.stack.setCurrentIndex(state)

if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    w = MyWindow()
    w.resize(500, 600)
    w.show()
    qapp.setStyleSheet("QPushButton { background-color: rgb(220, 220, 220); border-radius: 9px; }")
    qapp.exec()


