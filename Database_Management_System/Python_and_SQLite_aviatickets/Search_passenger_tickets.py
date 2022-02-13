from PyQt5 import QtWidgets, QtCore, uic
import sqlite3
import datetime

from Show_passenger_tickets import Show_passenger_tickets


class Search_passenger_tickets(QtWidgets.QWidget):

    def __init__(self, widget):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("search_passenger_reservation.ui", self)
        self.setWindowTitle("Билеты пассажира")

        self.label_6.setVisible(False)
        self.pushButton.clicked.connect(self.show_passenger_tickets)
        self.show()


    def show_passenger_tickets(self):
        mas = {
               "surname": self.lineEdit_surname.text(),
               "name": self.lineEdit_name.text(),
               "lastName": self.lineEdit_last_name.text(),
               "passport": self.lineEdit_passport.text(),}
        if mas['surname'] == "" or mas['name'] == "" or mas['lastName'] == "" or mas['passport'] == "":
            self.label_6.setVisible(True)
            self.label_6.setText("Заполните все поля")
            return
        Show_passenger_tickets(self, mas)
