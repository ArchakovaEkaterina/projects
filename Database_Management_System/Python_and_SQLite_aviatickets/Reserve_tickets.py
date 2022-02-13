from PyQt5 import QtWidgets, QtCore, uic
import sqlite3
import datetime

from Tickets_reservation_after_search import Tickets_reservation_after_search

class Reserve_tickets(QtWidgets.QWidget):

    def __init__(self, widget):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("tickets_reservation.ui", self)
        self.setWindowTitle("Забронировать билеты")

        self.calendarWidget.setGeometry(QtCore.QRect(250, 120, 400, 260))
        self.calendarWidget.setVisible(False)

        self.calendarWidget_2.setGeometry(QtCore.QRect(170, 340, 400, 260))
        self.calendarWidget_2.setVisible(False)

        self.label_6.setVisible(False)

        self.select_but_1.clicked.connect(self.show_calendar_1)
        self.select_but_2.clicked.connect(self.show_calendar_2)
        self.pushButton.clicked.connect(self.tickets_reservation_after_search)
        self.calendarWidget.clicked.connect(self.showDate)
        self.calendarWidget_2.clicked.connect(self.showDate_2)
        self.checkBox.stateChanged.connect(self.select_back)

        with sqlite3.connect("db.db") as conn:
            cursor = conn.cursor()
            query = """SELECT DISTINCT races.point_out FROM races"""
            for i in cursor.execute(query).fetchall():
                self.comboBox.addItem(i[0])

            cursor = conn.cursor()
            query = """SELECT DISTINCT races.point_in FROM races"""
            for i in cursor.execute(query).fetchall():
                self.comboBox_2.addItem(i[0])

            cursor.close()

        self.show()

    def show_calendar_1(self):
        self.label_6.setVisible(False)
        self.date_2.setVisible(False)
        self.calendarWidget.setVisible(True)

    def show_calendar_2(self):
        self.label_6.setVisible(False)
        self.label_6.setVisible(False)
        self.calendarWidget_2.setVisible(True)

    def showDate_2(self):
        self.label_6.setVisible(False)
        self.datetime_2 = self.calendarWidget_2.selectedDate()
        self.date_2.setText(str(self.datetime_2.day()) + "." + str(self.datetime_2.month()) + "." + str(self.datetime_2.year()))
        self.calendarWidget_2.setVisible(False)
        self.date_2.setVisible(True)

    def showDate(self):
        self.label_6.setVisible(False)
        self.datetime_1 = self.calendarWidget.selectedDate()
        self.date_1.setText(str(self.datetime_1.day()) + "." + str(self.datetime_1.month()) + "." + str(self.datetime_1.year()))
        self.calendarWidget.setVisible(False)

    def select_back(self):
        self.label_6.setVisible(False)
        if self.checkBox.checkState():
            self.select_but_2.setEnabled(True)
        else:
            self.select_but_2.setEnabled(False)
            self.calendarWidget_2.setVisible(False)
            self.date_2.setText("")

    def tickets_reservation_after_search(self):
        mas = {"dateOut": self.date_1.text(),
               "pointOut": self.comboBox.currentText(),
               "toBack": self.checkBox.checkState(),
               "dateIn": self.date_2.text(),
               "pointIn": self.comboBox_2.currentText(),}
        if self.checkBox.checkState() and mas['dateOut'] != "" and mas['dateIn'] != "":
            if self.datetime_1 > self.datetime_2:
                self.label_6.setVisible(True)
                self.label_6.setText("Неверные даты вылета и прилета!")
                return
        if mas['dateOut'] == "" or (mas['dateIn'] == "" and mas['toBack']):
            self.label_6.setVisible(True)
            self.label_6.setText("Выберите даты прилета и вылета!")
            return
        Tickets_reservation_after_search(self, mas)
