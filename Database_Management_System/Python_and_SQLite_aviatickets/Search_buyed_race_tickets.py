from PyQt5 import QtWidgets, QtCore, uic
import sqlite3
import datetime

from Buyed_race_tickets_after_input import Buyed_race_tickets_after_input


class Search_buyed_race_tickets(QtWidgets.QWidget):

    def __init__(self, widget):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("buyed_race_tickets.ui", self)
        self.setWindowTitle("Проданные билеты рейса")

        self.calendarWidget.setGeometry(QtCore.QRect(280, 180, 400, 260))
        self.calendarWidget.setVisible(False)

        self.label_6.setVisible(False)

        self.select_but_1.clicked.connect(self.show_calendar_1)
        self.pushButton.clicked.connect(self.buyed_race_tickets_after_input)
        self.calendarWidget.clicked.connect(self.showDate)

        with sqlite3.connect("db.db") as conn:
            cursor = conn.cursor()
            query = """SELECT DISTINCT races.race_number FROM races"""
            for i in cursor.execute(query).fetchall():
                self.comboBox.addItem(str(i[0]))

            cursor.close()

        self.show()

    def show_calendar_1(self):
        self.label_6.setVisible(False)
        self.calendarWidget.setVisible(True)

    def showDate(self):
        self.label_6.setVisible(False)
        self.datetime_1 = self.calendarWidget.selectedDate()
        self.date_1.setText(str(self.datetime_1.day()) + "." + str(self.datetime_1.month()) + "." + str(self.datetime_1.year()))
        self.calendarWidget.setVisible(False)

    def buyed_race_tickets_after_input(self):
        mas = {"race_number": self.comboBox.currentText(),
               "dateOut": self.date_1.text(),}
        if mas['dateOut'] == "":
            self.label_6.setVisible(True)
            self.label_6.setText("Неверная дата вылета!")
            return
        Buyed_race_tickets_after_input(self, mas)